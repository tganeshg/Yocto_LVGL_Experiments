/**
 * @file menu.h
 *
 */

#ifndef MENU_H
#define MENU_H

/*********************
 *      INCLUDES
 *********************/
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define MDCU_MAJOR_VER  1
#define MDCU_MINOR_VER  0
#define MDCU_BUILD_VER  0

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;

typedef enum
{
    paint_static,
    paint_dynamic
}PAINT_STATE;

typedef enum
{
    mm_overview_id,
    mm_protocols_id,
    mm_com_id,
    mm_settings_id,
    mm_about_id,
    mm_count
}MAIN_MENU_ID;

typedef struct
{
    uint32_t mmId;
    char    *mmName;
}MAIN_MENU;

typedef struct
{
    lv_obj_t        *tv;
    uint32_t        current_mmId;
    PAINT_STATE     pntState;
}MAIN_MENU_INST;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void menu_loop(void);
void menu_create(void);

/**********************
 *      MACROS
 **********************/

#endif /*MENU_H*/
