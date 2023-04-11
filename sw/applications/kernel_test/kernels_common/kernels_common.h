/*
                              *******************
******************************* H HEADER FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : CGRA-X-HEEP                                                  **
** filename : kernels_common.h                                             **
** version  : 1                                                            **
** date     : 05/04/23                                                     **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (c) EPFL                                                      **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************
*/

/***************************************************************************/
/***************************************************************************/

/**
* @file   kernel_common.h
* @date   05/04/23
* @brief  The declarations for the common kernel module.
*
*/

#ifndef _KERNEL_COMMON_H
#define _KERNEL_COMMON_H

/****************************************************************************/
/**                                                                        **/
/**                            MODULES USED                                **/
/**                                                                        **/
/****************************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "cgra.h"
#include "cgra_x_heep.h"


// For the timer
#include "rv_timer.h"
#include "soc_ctrl.h"
#include "core_v_mini_mcu.h"

/****************************************************************************/
/**                                                                        **/
/**                       DEFINITIONS AND MACROS                           **/
/**                                                                        **/
/****************************************************************************/

/* Configuration Definitions */

#define DEBUG



/* Macros */

#ifdef DEBUG
  #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
  #define PRINTF(...)
#endif
#define PRINTF_ALWAYS(fmt, ...) printf(fmt, ## __VA_ARGS__)

#define PRINT64(x) "%8x%08x",(uint32_t)( x >> 32 ), (uint32_t)( x & 0xffffffff)


/* Definitions */


#define CGRA_STAT_PERCENT_MULTIPLIER    100

#define CGRA_MAX_COLS                   4

#define HART_ID                         0

#define KCOM_FUNC_RET_OK                0

#define TICK_FREQ_HZ                    20 * 1000 * 1000 // 20 MHz

#define KERNEL_NAME_LENGTH_MAX          20

/****************************************************************************/
/**                                                                        **/
/**                       TYPEDEFS AND STRUCTURES                          **/
/**                                                                        **/
/****************************************************************************/

typedef uint32_t    kcom_func_ret_t;

typedef uint32_t    kcom_time_t;

typedef uint32_t*   kcom_mem_t;

typedef int32_t*    kcom_io_t;

typedef kcom_time_t kcom_param_t;

typedef struct 
{
    kcom_mem_t  kmem;
    kcom_mem_t  imem;
    kcom_io_t   input;
    kcom_io_t   output;
    uint8_t     col_n;
    void        ( *config ) (void);
    void        ( *func )   (void);
    uint32_t    ( *check )  (void);
    int8_t      name[ KERNEL_NAME_LENGTH_MAX ];
} kcom_kernel_t;


typedef struct
{
    uint32_t cyc_act;
    uint32_t cyc_stl;
} kcom_col_perf_t;

typedef struct
{
    kcom_time_t start_cy;
    kcom_time_t end_cy;
    kcom_time_t spent_cy;
} kcom_time_diff_t;

typedef struct 
{
    kcom_time_diff_t    sw;
    kcom_time_diff_t    cgra;
    kcom_time_diff_t    config;
    kcom_time_diff_t    dead;
    rv_timer_t          timer;
} kcom_timing_t;

typedef struct
{
    kcom_col_perf_t    cols[CGRA_MAX_COLS];
    kcom_col_perf_t    cols_total;
    uint32_t           cyc_ratio; // Stored *CGRA_STAT_PERCENT_MULTIPLIER 
    kcom_timing_t      time;
} kcom_perf_t;

typedef struct 
{
    kcom_param_t sw;
    kcom_param_t config;
    kcom_param_t cgra;
    kcom_param_t cyc_ratio;
} kcom_run_t;

typedef struct
{
   kcom_run_t  avg;
   kcom_run_t  var;
   uint32_t     n;
} kcom_stats_t;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/



/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED FUNCTIONS                            **/
/**                                                                        **/
/****************************************************************************/
uint32_t kcom_getRand();

void kcom_timerInit( rv_timer_t *timer);
uint64_t kcom_getTime( rv_timer_t *timer );
void kcom_timeStart( kcom_time_diff_t *perf, rv_timer_t *timer );
void kcom_timeStop( kcom_time_diff_t *perf,  rv_timer_t *timer );
void kcom_subtractDead( kcom_time_t *time, kcom_time_t *dead );

void kcom_getPerf( cgra_t *cgra, kcom_perf_t *perf );
void kcom_populateRun( kcom_run_t *run, kcom_perf_t *perf, uint32_t it_idx );
void kcom_getKernelStats( kcom_run_t *run, kcom_stats_t *stats );

void kcom_printPerf( cgra_t *cgra, kcom_perf_t *perf );
void kcom_printKernelStats( kcom_stats_t *stats  );
void kcom_printSummary( cgra_t *cgra);

/****************************************************************************/
/**                                                                        **/
/**                          INLINE FUNCTIONS                              **/
/**                                                                        **/
/****************************************************************************/



#endif /* _KERNEL_COMMON_H*/
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/























