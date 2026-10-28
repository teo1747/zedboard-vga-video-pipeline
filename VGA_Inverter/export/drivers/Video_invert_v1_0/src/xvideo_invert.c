// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvideo_invert.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVideo_invert_CfgInitialize(XVideo_invert *InstancePtr, XVideo_invert_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVideo_invert_Start(XVideo_invert *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL) & 0x80;
    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVideo_invert_IsDone(XVideo_invert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVideo_invert_IsIdle(XVideo_invert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVideo_invert_IsReady(XVideo_invert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVideo_invert_EnableAutoRestart(XVideo_invert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL, 0x80);
}

void XVideo_invert_DisableAutoRestart(XVideo_invert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_AP_CTRL, 0);
}

void XVideo_invert_Set_enable(XVideo_invert *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_ENABLE_DATA, Data);
}

u32 XVideo_invert_Get_enable(XVideo_invert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_ENABLE_DATA);
    return Data;
}

void XVideo_invert_InterruptGlobalEnable(XVideo_invert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_GIE, 1);
}

void XVideo_invert_InterruptGlobalDisable(XVideo_invert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_GIE, 0);
}

void XVideo_invert_InterruptEnable(XVideo_invert *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_IER);
    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_IER, Register | Mask);
}

void XVideo_invert_InterruptDisable(XVideo_invert *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_IER);
    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_IER, Register & (~Mask));
}

void XVideo_invert_InterruptClear(XVideo_invert *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_invert_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_ISR, Mask);
}

u32 XVideo_invert_InterruptGetEnabled(XVideo_invert *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_IER);
}

u32 XVideo_invert_InterruptGetStatus(XVideo_invert *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVideo_invert_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INVERT_CTRL_ADDR_ISR);
}

