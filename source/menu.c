/**
 * @file menu.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "menu.h"
#include <lvgl/lvgl_private.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN && LV_MEM_SIZE < (38ul * 1024ul)
    #error Insufficient memory for lv_demo_widgets. Please set LV_MEM_SIZE to at least 38KB (38ul * 1024ul).  48KB is recommended.
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size = DISP_LARGE;

static lv_style_t style_text_muted;
static lv_style_t style_title;
static lv_style_t style_icon;
static lv_style_t style_bullet;

static const lv_font_t * font_large;
static const lv_font_t * font_normal;

static MAIN_MENU mMenu[mm_count] ={  {mm_overview_id,"Overview"},
                                     {mm_protocols_id,"Protocols"},
                                     {mm_com_id,"IOT"},
                                     {mm_settings_id,"Settings"},
                                     {mm_about_id,"About"} };
static MAIN_MENU_INST mmInst;
static lv_obj_t *rtc_date = NULL;

/* To get RTC time */
time_t rawtime;
struct tm *timeinfo=NULL;

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void mm_event_cb(lv_event_t * e)
{
    lv_obj_t * dropdown = lv_event_get_target(e);
    mmInst.current_mmId = lv_dropdown_get_selected(dropdown);
    LV_LOG_USER("'%d' is selected", mmInst.current_mmId);
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void menu_loop(void)
{
    uint32_t idle_time = 0;
    uint32_t mm_id = mm_overview_id;

    /*Handle LVGL tasks*/
    while(true)
    {
        if(mm_id != mmInst.current_mmId)
        {
            mm_id = mmInst.current_mmId;
            mmInst.pntState = paint_static;
        }

        switch(mmInst.current_mmId)
        {
            case mm_overview_id:
            {
                if(mmInst.pntState == paint_static)
                {
                    lv_obj_t *tab1 = lv_win_get_content(mmInst.tv);
                    lv_obj_clean(tab1);
                    //analytics_create(tab1);
                    mmInst.pntState = paint_dynamic;
                }
               // else //paint_dynamic
                //  LV_LOG_USER("DYN>> %s Need to show\n",mMenu[mmInst.current_mmId].mmName);
            }
            break;
            case mm_protocols_id:
            {
                if(mmInst.pntState == paint_static)
                {
                    lv_obj_t *tab1 = lv_win_get_content(mmInst.tv);
                    lv_obj_clean(tab1);
                    //profile_create(tab1);
                    mmInst.pntState = paint_dynamic;
                }
               // else //paint_dynamic
                //  LV_LOG_USER("DYN>> %s Need to show\n",mMenu[mmInst.current_mmId].mmName);
            }
            break;
            case mm_com_id:
            {
                if(mmInst.pntState == paint_static)
                {
                    lv_obj_t *tab1 = lv_win_get_content(mmInst.tv);
                    lv_obj_clean(tab1);
                    //shop_create(tab1);
                    mmInst.pntState = paint_dynamic;
                }
               // else //paint_dynamic
                //  LV_LOG_USER("DYN>> %s Need to show\n",mMenu[mmInst.current_mmId].mmName);
            }
            break;
            case mm_settings_id:
            {
                if(mmInst.pntState == paint_static)
                {
                    lv_obj_t *tab1 = lv_win_get_content(mmInst.tv);
                    lv_obj_clean(tab1);
                    //color_changer_create(tab1);
                    mmInst.pntState = paint_dynamic;
                }
               // else //paint_dynamic
                //  LV_LOG_USER("DYN>> %s Need to show\n",mMenu[mmInst.current_mmId].mmName);
            }
            break;
            case mm_about_id:
            {
               // LV_LOG_USER("%s Need to show\n",mMenu[mmInst.current_mmId].mmName);
            }
            break;
            default:
            {
               // LV_LOG_USER("%d - Wrong menu\n",mmInst.current_mmId);
            }
            break;
        }
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        lv_label_set_text_fmt(rtc_date,"%02d/%02d/%04d %02d:%02d:%02d", timeinfo->tm_mday,(timeinfo->tm_mon+1),(timeinfo->tm_year+1900),
                                                                        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        idle_time = lv_timer_handler(); /*Returns the time to the next timer execution*/
        usleep(idle_time * 100);
    }
}

void menu_create(void)
{
    int32_t tab_h = 90;
    uint8_t mm_idx = 0;

#if LV_FONT_MONTSERRAT_24
    font_large = &lv_font_montserrat_24;
#endif
#if LV_FONT_MONTSERRAT_16
    font_normal = &lv_font_montserrat_16;
#endif

#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,font_normal);
#endif

    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_large);

    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_large);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);

    lv_obj_set_style_text_font(lv_screen_active(), font_normal, 0);
    mmInst.tv = lv_win_create(lv_screen_active());

    if(disp_size == DISP_LARGE) {
        lv_obj_t *tab_bar = lv_win_get_header(mmInst.tv);
        lv_obj_set_size(tab_bar, LV_HOR_RES, tab_h);
        lv_obj_set_style_pad_left(tab_bar, LV_HOR_RES / 2, 0);
        lv_obj_t *logo = lv_image_create(tab_bar);
        lv_obj_add_flag(logo, LV_OBJ_FLAG_IGNORE_LAYOUT);
        LV_IMAGE_DECLARE(img_lvgl_logo);
        lv_image_set_src(logo, &img_lvgl_logo);
        lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

        lv_obj_t *label = lv_label_create(tab_bar);
        lv_obj_add_style(label, &style_title, 0);
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_label_set_text_fmt(label, "MDCU v%d.%d.%d", MDCU_MAJOR_VER, MDCU_MINOR_VER, MDCU_BUILD_VER);
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

        label = lv_label_create(tab_bar);
        lv_label_set_text_static(label, "Mini DCU");
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_add_style(label, &style_text_muted, 0);
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);

        rtc_date = lv_label_create(tab_bar);
        lv_label_set_text(rtc_date, "00/00/0000 00:00:00");
        lv_obj_add_flag(rtc_date, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_add_style(rtc_date, &style_text_muted, 0);
        lv_obj_align(rtc_date, LV_ALIGN_TOP_RIGHT, -10, 6);
    }

#if LV_USE_DROPDOWN
    /*Create a drop down list*/
    lv_obj_t *dropdown = lv_dropdown_create(lv_scr_act());
    lv_obj_align(dropdown, LV_ALIGN_TOP_RIGHT, -35, 40);
    lv_dropdown_set_options_static(dropdown,mMenu[mm_idx].mmName);
    for(mm_idx=1;mm_idx<mm_count;mm_idx++)
        lv_dropdown_add_option(dropdown,mMenu[mm_idx].mmName,mMenu[mm_idx].mmId);

    /*Set a fixed text to display on the button of the drop-down list*/
    lv_dropdown_set_text(dropdown, "Menu");
    lv_obj_set_size(dropdown,90,40);

    /*Use a custom image as down icon and flip it when the list is opened*/
    LV_IMG_DECLARE(img_caret_down)
    lv_dropdown_set_symbol(dropdown, &img_caret_down);
    lv_obj_set_style_transform_angle(dropdown, 1800, LV_PART_INDICATOR | LV_STATE_CHECKED);

    /*In a menu we don't need to show the last clicked item*/
    lv_dropdown_set_selected_highlight(dropdown, true);

    lv_obj_add_event_cb(dropdown, mm_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
#endif
}
/* EOF */
