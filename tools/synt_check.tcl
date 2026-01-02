# Usage: vivado -mode batch -source synth_check.tcl -tclargs <source_file> <top_module>

if {$argc < 2} {
    puts "Usage: vivado -mode batch -source synth_check.tcl -tclargs <source_file> <top_module>"
    exit 1
}

set src_file [lindex $argv 0]
set top_module [lindex $argv 1]

read_verilog -sv $src_file
synth_design -top $top_module -part xck26-sfvc784-2lv-c -mode out_of_context
report_utilization -file ${top_module}_util.txt
report_timing_summary -file ${top_module}_timing.txt

puts "Done. Check ${top_module}_util.txt and ${top_module}_timing.txt"
