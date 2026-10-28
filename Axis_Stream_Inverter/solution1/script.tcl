############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Axis_Stream_Inverter
set_top Axis_Stream_invert
add_files Axis_Inverter.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
config_export -output D:/Xilinx/projet_VGA_vrai/video_stream-processing/Video_Inverter
#source "./Axis_Stream_Inverter/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog -output D:/Xilinx/projet_VGA_vrai/video_stream-processing/Video_Inverter
