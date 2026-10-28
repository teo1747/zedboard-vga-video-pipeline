############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Video_Inverter
set_top AXI_inverter
add_files Video_Inverter/inverter.cpp
add_files -tb Video_Inverter/tb_inverter_video.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
#source "./Video_Inverter/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -flow impl -rtl vhdl -format ip_catalog -output C:/Users/jm134934/Desktop/video_stream-processing/AXI_inverter.zip
