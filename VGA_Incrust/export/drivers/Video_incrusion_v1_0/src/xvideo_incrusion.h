// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVIDEO_INCRUSION_H
#define XVIDEO_INCRUSION_H

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
#include "xvideo_incrusion_hw.h"

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
} XVideo_incrusion_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XVideo_incrusion;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVideo_incrusion_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVideo_incrusion_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVideo_incrusion_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVideo_incrusion_ReadReg(BaseAddress, RegOffset) \
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
int XVideo_incrusion_Initialize(XVideo_incrusion *InstancePtr, u16 DeviceId);
XVideo_incrusion_Config* XVideo_incrusion_LookupConfig(u16 DeviceId);
int XVideo_incrusion_CfgInitialize(XVideo_incrusion *InstancePtr, XVideo_incrusion_Config *ConfigPtr);
#else
int XVideo_incrusion_Initialize(XVideo_incrusion *InstancePtr, const char* InstanceName);
int XVideo_incrusion_Release(XVideo_incrusion *InstancePtr);
#endif

void XVideo_incrusion_Start(XVideo_incrusion *InstancePtr);
u32 XVideo_incrusion_IsDone(XVideo_incrusion *InstancePtr);
u32 XVideo_incrusion_IsIdle(XVideo_incrusion *InstancePtr);
u32 XVideo_incrusion_IsReady(XVideo_incrusion *InstancePtr);
void XVideo_incrusion_EnableAutoRestart(XVideo_incrusion *InstancePtr);
void XVideo_incrusion_DisableAutoRestart(XVideo_incrusion *InstancePtr);

void XVideo_incrusion_Set_binome(XVideo_incrusion *InstancePtr, u32 Data);
u32 XVideo_incrusion_Get_binome(XVideo_incrusion *InstancePtr);
void XVideo_incrusion_Set_enable(XVideo_incrusion *InstancePtr, u32 Data);
u32 XVideo_incrusion_Get_enable(XVideo_incrusion *InstancePtr);

void XVideo_incrusion_InterruptGlobalEnable(XVideo_incrusion *InstancePtr);
void XVideo_incrusion_InterruptGlobalDisable(XVideo_incrusion *InstancePtr);
void XVideo_incrusion_InterruptEnable(XVideo_incrusion *InstancePtr, u32 Mask);
void XVideo_incrusion_InterruptDisable(XVideo_incrusion *InstancePtr, u32 Mask);
void XVideo_incrusion_InterruptClear(XVideo_incrusion *InstancePtr, u32 Mask);
u32 XVideo_incrusion_InterruptGetEnabled(XVideo_incrusion *InstancePtr);
u32 XVideo_incrusion_InterruptGetStatus(XVideo_incrusion *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
