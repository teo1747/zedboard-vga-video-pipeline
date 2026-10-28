// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvideo_invert.h"

extern XVideo_invert_Config XVideo_invert_ConfigTable[];

XVideo_invert_Config *XVideo_invert_LookupConfig(u16 DeviceId) {
	XVideo_invert_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVIDEO_INVERT_NUM_INSTANCES; Index++) {
		if (XVideo_invert_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVideo_invert_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVideo_invert_Initialize(XVideo_invert *InstancePtr, u16 DeviceId) {
	XVideo_invert_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVideo_invert_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVideo_invert_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

