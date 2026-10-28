############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project VGA_Incrust
set_top Video_incrusion
add_files VGA_Incrust/Video_Incrust.cpp
add_files -tb VGA_Incrust/tb_video_incrust.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output ./VGA_Incrust -rtl verilog
source "./VGA_Incrust/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog -output ./VGA_Incrust
