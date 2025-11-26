# tools/package_all.tcl
# Vivado 2020.2+ / 2024.x IP packager
# - Walks modules/* and packages src/ (+ deps from ip.json) into ip_repo/
# - Uses -import_files so the IP is self-contained
# - Infers AXI/AXIS, exposes HDL params, sets clock FREQ_HZ
# - Robust to current working directory

# -------------------------------
# Small helpers
# -------------------------------

proc dict_getdef {d key default} {
  if {[dict exists $d $key]} { return [dict get $d $key] } else { return $default }
}

proc read_json {path} {
  if {![file exists $path]} { return {} }
  set fh [open $path r]; set raw [read $fh]; close $fh
  if {![catch {package require json}]} { return [::json::json2dict $raw] }
  set d {}
  foreach {all k v} [regexp -all -inline {"([^"]+)"\s*:\s*"([^"]*)"} $raw] { dict set d $k $v }
  if {[regexp {"deps"\s*:\s*\[([^\]]*)\]} $raw -> inside]} {
    set deps {}
    foreach {m val} [regexp -all -inline {"([^"]+)"} $inside] { lappend deps $val }
    dict set d deps $deps
  }
  return $d
}

proc infer_top_from_fileset {fileset} {
  set fs [get_filesets $fileset]
  set flist [get_files -of_objects $fs]
  if {[llength $flist] == 0} { return "" }
  return [file rootname [file tail [lindex $flist end]]]
}

# -------------------------------
# Packaging logic
# -------------------------------

proc package_module {mod_dir ip_repo partname} {
  set name    [file tail $mod_dir]
  set ipjson  [file join $mod_dir ip.json]
  set meta    [expr {[file exists $ipjson] ? [read_json $ipjson] : {}}]

  set vendor   [dict_getdef $meta vendor  "local.org"]
  set library  [dict_getdef $meta library "user"]
  set ipname   [dict_getdef $meta name    $name]
  set version  [dict_getdef $meta version "1.0"]
  set deps     [dict_getdef $meta deps    {}]
  set top_hint [dict_getdef $meta top     ""]

  puts "  • vendor=$vendor library=$library name=$ipname version=$version"

  set workdir [file normalize [file join [pwd] "_pkg_$ipname"]]
  file mkdir $workdir
  create_project ${ipname}_pkg $workdir -part $partname -force

  # Sources
  set srcdir [file join $mod_dir src]
  if {![file exists $srcdir]} {
    puts "    ! No src/ in $mod_dir — skipping."
    close_project; file delete -force $workdir; return
  }

  # Add src and deps (scan for includes so headers get pulled in)
  add_files -fileset sources_1 -norecurse -scan_for_includes $srcdir
  foreach d $deps {
    set absd [file normalize [file join $mod_dir $d]]
    if {[file exists $absd]} {
      add_files -fileset sources_1 -norecurse -scan_for_includes $absd
      puts "    + dep dir: $absd"
    } else {
      puts "    ! dep dir not found: $absd"
    }
  }

  # Select top (hint overrides heuristic)
  if {$top_hint ne ""} {
    set_property top $top_hint [get_filesets sources_1]
  } else {
    set maybe_top [infer_top_from_fileset sources_1]
    if {$maybe_top ne ""} { set_property top $maybe_top [get_filesets sources_1] }
  }

  # Important: avoid carrying include_dirs as a 'Dependency' into the IP
  # (Scan already pulled headers into the project.)
  catch { set_property include_dirs {} [get_filesets sources_1] }

  # Output dir for the IP
  set outdir [file normalize [file join $ip_repo "${ipname}_${version}"]]
  file mkdir $outdir

  # Package and import files so everything lives under the IP dir
  ipx::package_project -root_dir $outdir \
    -vendor $vendor -library $library -name $ipname -version $version \
    -taxonomy {/UserIP} -import_files

  set core [ipx::current_core]
  set_property display_name "Matrix Inverse" $core
  set_property description  "Streaming matrix inversion core (AXI4-Lite control, AXIS data)" $core


  # Friendly metadata (optional)
  set_property display_name $ipname $core
  if {![llength [get_property description $core]] || [string trim [get_property description $core]] eq ""} {
    set_property description "Custom IP '$ipname' packaged from $mod_dir" $core
  }

  # Discover params/ports and infer standard interfaces
  catch { ipx::import_top_level_hdl -quiet $core }
  catch { ipx::infer_bus_interfaces $core }

  # Expose HDL params to GUI
  foreach hp [ipx::get_hdl_parameters -of_objects $core] {
    set pname [get_property NAME $hp]
    if {![llength [ipx::get_user_parameters $pname -of_objects $core]]} {
      ipx::add_user_parameter $pname $core
    }
  }

  # Set a frequency on 'clk' if present (helps BD automation)
  set clk_if [ipx::get_bus_interfaces clk -of_objects $core]
  if {[llength $clk_if]} {
    if {![llength [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]]} {
      ipx::add_bus_parameter FREQ_HZ $clk_if
    }
    set_property value 100000000 [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]
  }

  # Create XGUI, check, save
  ipx::create_xgui_files $core
  ipx::check_integrity $core
  ipx::save_core $core

  puts "    ✓ Packaged -> $outdir"

  close_project
  file delete -force $workdir
}

# -------------------------------
# Entry point
# -------------------------------

set script_dir [file dirname [file normalize [info script]]]
set top_dir    [file normalize [file join $script_dir ..]]
set modules    [file normalize [file join $top_dir modules]]
set ip_repo    [file normalize [file join $top_dir ip_repo]]

if {[info exists ::env(VIVADO_PART)]} {
  set PARTNAME $::env(VIVADO_PART)
} else {
  set PARTNAME xc7a200tsbg484-1
}

puts "Top dir:     $top_dir"
puts "Modules dir: $modules"
puts "IP repo:     $ip_repo"
puts "Temp part:   $PARTNAME"

file mkdir $ip_repo

set moddirs [lsort [glob -type d -nocomplain [file join $modules *]]]
if {![llength $moddirs]} {
  puts "WARNING: No module directories under $modules"
}

foreach mod $moddirs {
  if {[file exists [file join $mod src]]} {
    puts "Packaging [file tail $mod]..."
    package_module $mod $ip_repo $PARTNAME
  } else {
    puts "Skipping [file tail $mod] (no src/)"
  }
}

puts "IP packaged to: $ip_repo"
