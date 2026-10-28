// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvideo_incrusion.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVideo_incrusion_CfgInitialize(XVideo_incrusion *InstancePtr, XVideo_incrusion_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVideo_incrusion_Start(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL) & 0x80;
    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVideo_incrusion_IsDone(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVideo_incrusion_IsIdle(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVideo_incrusion_IsReady(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVideo_incrusion_EnableAutoRestart(XVideo_incrusion *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL, 0x80);
}

void XVideo_incrusion_DisableAutoRestart(XVideo_incrusion *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_AP_CTRL, 0);
}

void XVideo_incrusion_Set_binome(XVideo_incrusion *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_BINOME_DATA, Data);
}

u32 XVideo_incrusion_Get_binome(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_BINOME_DATA);
    return Data;
}

void XVideo_incrusion_Set_enable(XVideo_incrusion *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_ENABLE_DATA, Data);
}

u32 XVideo_incrusion_Get_enable(XVideo_incrusion *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_ENABLE_DATA);
    return Data;
}

void XVideo_incrusion_InterruptGlobalEnable(XVideo_incrusion *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_GIE, 1);
}

void XVideo_incrusion_InterruptGlobalDisable(XVideo_incrusion *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_GIE, 0);
}

void XVideo_incrusion_InterruptEnable(XVideo_incrusion *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_IER);
    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_IER, Register | Mask);
}

void XVideo_incrusion_InterruptDisable(XVideo_incrusion *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_IER);
    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_IER, Register & (~Mask));
}

void XVideo_incrusion_InterruptClear(XVideo_incrusion *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVideo_incrusion_WriteReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_ISR, Mask);
}

u32 XVideo_incrusion_InterruptGetEnabled(XVideo_incrusion *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_IER);
}

u32 XVideo_incrusion_InterruptGetStatus(XVideo_incrusion *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVideo_incrusion_ReadReg(InstancePtr->Ctrl_BaseAddress, XVIDEO_INCRUSION_CTRL_ADDR_ISR);
}

