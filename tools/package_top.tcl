# tools/package_top.tcl
# Vivado 2020.2+ / 2024.x IP packager — top-level GPU system
#
# Packages the top-level design under src/ (plus optional deps like modules/)
# into a single IP in ip_repo/, suitable for dropping into a block design.
#
# - Expects this directory layout (relative to this script):
#     ../src       : top-level GPU system HDL
#     ../modules   : optional submodule RTL (if not only used as IP)
#     ../ip_repo   : output IP repository
#     ../ip.json   : optional metadata for the top IP
#
# - ip.json fields (all optional):
#     {
#       "vendor":  "local.org",
#       "library": "user",
#       "name":    "gpu_top",
#       "version": "1.0",
#       "top":     "gpu_top",
#       "deps":    ["modules", "some/other/dir"]
#     }
#
# - Uses -import_files so the IP is self-contained
# - Tries to infer AXI/AXIS, exposes HDL params, sets clk FREQ_HZ, etc.
# - Robust to current working directory

# ----------------------------------
# Small helpers
# ----------------------------------

proc dict_getdef {d key default} {
  if {[dict exists $d $key]} {
    return [dict get $d $key]
  } else {
    return $default
  }
}

proc read_json {path} {
  if {![file exists $path]} { return {} }
  set fh [open $path r]
  set raw [read $fh]
  close $fh

  # Prefer Tcl json package if present
  if {![catch {package require json}]} {
    return [::json::json2dict $raw]
  }

  # Fallback: very rough-and-ready JSON for simple flat objects + "deps" array
  set d {}
  foreach {all k v} [regexp -all -inline {"([^"]+)"\s*:\s*"([^"]*)"} $raw] {
    dict set d $k $v
  }
  if {[regexp {"deps"\s*:\s*\[([^\]]*)\]} $raw -> inside]} {
    set deps {}
    foreach {m val} [regexp -all -inline {"([^"]+)"} $inside] {
      lappend deps $val
    }
    dict set d deps $deps
  }
  return $d
}

proc infer_top_from_fileset {fileset} {
  set fs [get_filesets $fileset]
  set flist [get_files -of_objects $fs]
  if {[llength $flist] == 0} { return "" }

  # Heuristic: last-added file's rootname
  return [file rootname [file tail [lindex $flist end]]]
}

# ----------------------------------
# Packaging logic
# ----------------------------------

proc package_top_level {proj_root ip_repo partname} {
  # Read metadata from ip.json at project root or src/ip.json
  set meta {}
  set ipjson_candidates [list \
    [file join $proj_root ip.json] \
    [file join $proj_root src ip.json] \
  ]

  foreach p $ipjson_candidates {
    if {[file exists $p]} {
      puts "Using metadata from $p"
      set meta [read_json $p]
      break
    }
  }

  set vendor   [dict_getdef $meta vendor  "local.org"]
  set library  [dict_getdef $meta library "user"]
  set ipname   [dict_getdef $meta name    "gpu_top"]
  set version  [dict_getdef $meta version "1.0"]
  set top_hint [dict_getdef $meta top     ""]
  set deps     [dict_getdef $meta deps    {"modules" "lib"}]

  puts "Top-level IP metadata:"
  puts "  • vendor = $vendor"
  puts "  • library= $library"
  puts "  • name   = $ipname"
  puts "  • version= $version"
  if {$top_hint eq ""} {
    set top_print "<infer>"
  } else {
    set top_print $top_hint
  }
  puts "  • top    = $top_print"
  puts "  • deps   = $deps"

  # Check src/ exists
  set srcdir [file normalize [file join $proj_root src]]
  if {![file exists $srcdir]} {
    puts "ERROR: src/ directory not found at $srcdir"
    return
  }

  # Create a temporary project for packaging
  set workdir [file normalize [file join $proj_root "_pkg_${ipname}_top"]]
  file mkdir $workdir
  puts "Working directory: $workdir"

  create_project ${ipname}_top_pkg $workdir -part $partname -force

  # Add top-level src/ HDL
  puts "Adding top-level sources from $srcdir"
  add_files -fileset sources_1 -norecurse -scan_for_includes $srcdir

  # Add dependency directories (e.g. modules/)
  # Add dependency directories (e.g. modules/, lib/)
  foreach d $deps {
    set absd [file normalize [file join $proj_root $d]]
    if {![file exists $absd]} {
      puts "  ! dep dir not found: $absd"
      continue
    }

    set added_any 0

    # Case 1: dep itself has a src/ directory (e.g. ../some_dep/src)
    set root_src [file join $absd src]
    if {[file isdirectory $root_src]} {
      set dep_src [file normalize $root_src]
      puts "Adding dep sources from $dep_src"
      add_files -fileset sources_1 -norecurse -scan_for_includes $dep_src
      set added_any 1
    }

    # Case 2: dep is a container of submodules with their own src/ (e.g. lib/fifo/src)
    foreach sub [glob -type d -nocomplain [file join $absd *]] {
      set sub_src [file join $sub src]
      if {[file isdirectory $sub_src]} {
        set sub_src_norm [file normalize $sub_src]
        puts "Adding dep submodule sources from $sub_src_norm"
        add_files -fileset sources_1 -norecurse -scan_for_includes $sub_src_norm
        set added_any 1
      }
    }

    # Fallback: if no src/ or submodule src/ found, just add the directory itself
    if {!$added_any} {
      puts "Adding dep sources from $absd"
      add_files -fileset sources_1 -norecurse -scan_for_includes $absd
    }
  }

  # Select top module/entity
  if {$top_hint ne ""} {
    puts "Setting explicit top: $top_hint"
    set_property top $top_hint [get_filesets sources_1]
  } else {
    set maybe_top [infer_top_from_fileset sources_1]
    if {$maybe_top ne ""} {
      puts "Inferred top: $maybe_top"
      set_property top $maybe_top [get_filesets sources_1]
    } else {
      puts "WARNING: Could not infer a top module/entity automatically."
    }
  }

  # Avoid propagating include_dirs as 'Dependency' into IP
  catch {
    set_property include_dirs {} [get_filesets sources_1]
  }

  # Prepare output dir for the IP
  set outdir [file normalize [file join $ip_repo "${ipname}_${version}"]]
  file mkdir $outdir

  puts "Packaging top-level IP to: $outdir"

  # Package and import files so everything lives under the IP dir
  ipx::package_project -root_dir $outdir \
    -vendor $vendor -library $library -name $ipname -version $version \
    -taxonomy {/UserIP} -import_files

  set core [ipx::current_core]

  # Friendly metadata
  set_property display_name $ipname $core

  if {![llength [get_property description $core]] || \
      [string trim [get_property description $core]] eq ""} {
    set_property description "Top-level GPU system IP packaged from $proj_root" $core
  }

  # Import HDL, infer bus interfaces (AXI, AXIS, etc)
  catch { ipx::import_top_level_hdl -quiet $core }
  catch { ipx::infer_bus_interfaces $core }

  # Expose HDL generics/params as user parameters in the IP GUI
  foreach hp [ipx::get_hdl_parameters -of_objects $core] {
    set pname [get_property NAME $hp]
    if {![llength [ipx::get_user_parameters $pname -of_objects $core]]} {
      ipx::add_user_parameter $pname $core
    }
  }

  # Set a default FREQ_HZ on 'clk' interface if present (helps BD automation)
  set clk_if [ipx::get_bus_interfaces clk -of_objects $core]
  if {[llength $clk_if]} {
    if {![llength [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]]} {
      ipx::add_bus_parameter FREQ_HZ $clk_if
    }
    # Default 100 MHz; tweak as needed or make this configurable via env var
    set_property value 100000000 [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]
  }

  # Generate XGUI, check, save
  ipx::create_xgui_files $core
  ipx::check_integrity $core
  ipx::save_core $core

  puts "✓ Top-level IP packaged at $outdir"

  close_project
  file delete -force $workdir
}

# ----------------------------------
# Entry point
# ----------------------------------

set script_dir [file dirname [file normalize [info script]]]
set proj_root  [file normalize [file join $script_dir ..]]
set ip_repo    [file normalize [file join $proj_root ip_repo]]

if {[info exists ::env(VIVADO_PART)]} {
  set PARTNAME $::env(VIVADO_PART)
} else {
  # Fallback; change to match your real target
  set PARTNAME xc7a200tsbg484-1
}

puts "Project root: $proj_root"
puts "IP repo:      $ip_repo"
puts "Temp part:    $PARTNAME"

file mkdir $ip_repo

package_top_level $proj_root $ip_repo $PARTNAME

puts "Done."
