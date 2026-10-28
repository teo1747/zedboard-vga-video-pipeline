// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvideo_incrusion.h"

extern XVideo_incrusion_Config XVideo_incrusion_ConfigTable[];

XVideo_incrusion_Config *XVideo_incrusion_LookupConfig(u16 DeviceId) {
	XVideo_incrusion_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVIDEO_INCRUSION_NUM_INSTANCES; Index++) {
		if (XVideo_incrusion_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVideo_incrusion_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVideo_incrusion_Initialize(XVideo_incrusion *InstancePtr, u16 DeviceId) {
	XVideo_incrusion_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVideo_incrusion_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVideo_incrusion_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

