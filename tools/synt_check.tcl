# Usage: vivado -mode batch -source synth_check.tcl -tclargs <top_module> <source_files...>
if {$argc < 2} {
    puts "Usage: vivado -mode batch -source synth_check.tcl -tclargs <top_module> <source_files...>"
    exit 1
}

set top_module [lindex $argv 0]
set source_files [lrange $argv 1 end]

# Read all source files
foreach src_file $source_files {
    puts "Reading: $src_file"
    read_verilog -sv $src_file
}

synth_design -top $top_module -part xck26-sfvc784-2lv-c -mode out_of_context
report_utilization -file ${top_module}_util.txt
report_timing_summary -file ${top_module}_timing.txt
puts "Done. Check ${top_module}_util.txt and ${top_module}_timing.txt"
