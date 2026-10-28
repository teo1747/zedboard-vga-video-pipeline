// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVIDEO_INVERT_H
#define XVIDEO_INVERT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xvideo_invert_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Ctrl_BaseAddress;
} XVideo_invert_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XVideo_invert;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVideo_invert_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVideo_invert_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVideo_invert_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVideo_invert_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XVideo_invert_Initialize(XVideo_invert *InstancePtr, u16 DeviceId);
XVideo_invert_Config* XVideo_invert_LookupConfig(u16 DeviceId);
int XVideo_invert_CfgInitialize(XVideo_invert *InstancePtr, XVideo_invert_Config *ConfigPtr);
#else
int XVideo_invert_Initialize(XVideo_invert *InstancePtr, const char* InstanceName);
int XVideo_invert_Release(XVideo_invert *InstancePtr);
#endif

void XVideo_invert_Start(XVideo_invert *InstancePtr);
u32 XVideo_invert_IsDone(XVideo_invert *InstancePtr);
u32 XVideo_invert_IsIdle(XVideo_invert *InstancePtr);
u32 XVideo_invert_IsReady(XVideo_invert *InstancePtr);
void XVideo_invert_EnableAutoRestart(XVideo_invert *InstancePtr);
void XVideo_invert_DisableAutoRestart(XVideo_invert *InstancePtr);

void XVideo_invert_Set_enable(XVideo_invert *InstancePtr, u32 Data);
u32 XVideo_invert_Get_enable(XVideo_invert *InstancePtr);

void XVideo_invert_InterruptGlobalEnable(XVideo_invert *InstancePtr);
void XVideo_invert_InterruptGlobalDisable(XVideo_invert *InstancePtr);
void XVideo_invert_InterruptEnable(XVideo_invert *InstancePtr, u32 Mask);
void XVideo_invert_InterruptDisable(XVideo_invert *InstancePtr, u32 Mask);
void XVideo_invert_InterruptClear(XVideo_invert *InstancePtr, u32 Mask);
u32 XVideo_invert_InterruptGetEnabled(XVideo_invert *InstancePtr);
u32 XVideo_invert_InterruptGetStatus(XVideo_invert *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
