/*
Copyright (C) EEMBC(R). All Rights Reserved

All EEMBC Benchmark Software are products of EEMBC and are provided under the
terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
are proprietary intellectual properties of EEMBC and its Members and is
protected under all applicable laws, including all applicable copyright laws.

If you received this EEMBC Benchmark Software without having a currently
effective EEMBC Benchmark License Agreement, you must discontinue use.

Copyright 2020 The MLPerf Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This file reflects a modified version of th_lib from EEMBC. All wrapped libc
methods from th_libc.h and all testharness methods from th_lib.h are here.
==============================================================================*/
/// \file
/// \brief Submitter-implemented methods required to perform inference.
/// \detail All methods with names starting with th_ are to be implemented by
/// the submitter. All basic I/O, inference and timer APIs must be implemented
/// in order for the benchmark to output useful results, but some auxiliary
/// methods default to an empty implementation. These methods are provided to
/// enable submitter optimizations, and are not required for submission.

#ifndef MLPERF_TINY_V0_1_API_SUBMITTER_IMPLEMENTED_H_
#define MLPERF_TINY_V0_1_API_SUBMITTER_IMPLEMENTED_H_

/// \brief These defines set logging prefixes for test harness integration.
/// \detail This API is designed for performance evaluation only. In order to
/// gather energy measurments we recommend using the EEMBC test suite.
#define EE_MSG_TIMESTAMP "m-lap-us-%.0lf\r\n"
#define TH_VENDOR_NAME_STRING "Xilinx_ArtyA7_100T"

//TODO Check/optimizez, set = INPUT_N_FEATURES potentially?
#define MAX_DB_INPUT_SIZE (490*2) // Change this for other models? this assumes IC, but probably wont hurt anything past mem usage

//#ifndef TH_MODEL_VERSION
// See "internally_implemented.h" for a list
// #error "PLease set TH_MODEL_VERSION to one of the EE_MODEL_VERSION_* defines"
// e.g.: to inform the user of model `ic01` use this:
#define TH_MODEL_VERSION EE_MODEL_VERSION_KWS01
//#endif

// Use this to switch between DUT-direct (perf) & DUT-inderrect (energy) modes
#ifndef EE_CFG_ENERGY_MODE
#define EE_CFG_ENERGY_MODE 0
#endif

#if EE_CFG_ENERGY_MODE == 1
//GPIO Config for Timestamp
#include "xgpio.h"

#define PIN 0x01
#define GPIO_PMOD_PIN_DEVICE_ID  XPAR_GPIO_0_DEVICE_ID

#define set_pin_high(InstancePtr, Mask) \
        XGpio_DiscreteWrite(InstancePtr, 1, Mask)

#define set_pin_low(InstancePtr, Mask) \
        XGpio_DiscreteClear(InstancePtr, 1, Mask)
#endif

// This is a visual cue to the user when reviewing logs or plugging an
// unknown device into the system.
#if EE_CFG_ENERGY_MODE == 1
#define EE_MSG_TIMESTAMP_MODE "m-timestamp-mode-energy\r\n"
#else
#define EE_MSG_TIMESTAMP_MODE "m-timestamp-mode-performance\r\n"
#endif

//Accelerator Input/Output Sizes
#define INPUT_N_FEATURES (490)
#define OUTPUT_N_FEATURES (1)


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \brief required core API
void th_load_tensor();
void th_results();
void th_infer();
void th_timestamp(void);
void th_printf(const char *fmt, ...);
char th_getchar();

/// \brief optional API
void th_serialport_initialize(void);
void th_timestamp_initialize(void);
void th_final_initialize(void);
void th_pre();
void th_post();
void th_command_ready(char volatile *msg);

//Accelerator
//XResnet_axi do_resnet;
//XResnet_axi_Config *do_resnet_cfg;
//uint8_t slices;
//uint8_t bins;

/// \brief libc hooks
int th_strncmp(const char *str1, const char *str2, size_t n);
char *th_strncpy(char *dest, const char *src, size_t n);
size_t th_strnlen(const char *str, size_t maxlen);
char *th_strcat(char *dest, const char *src);
char *th_strtok(/*@null@*/ char *str1, const char *sep);
int th_atoi(const char *str);
void *th_memset(void *b, int c, size_t len);
void *th_memcpy(void *dst, const void *src, size_t n);
int th_vprintf(const char *format, va_list ap);

#endif  // MLPERF_TINY_V0_1_API_SUBMITTER_IMPLEMENTED_H_
