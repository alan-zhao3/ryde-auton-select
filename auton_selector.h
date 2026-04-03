#pragma once
#include "pros/apix.h"

extern int selected_auton_id;
extern const char* AUTON_NAMES[];

extern lv_obj_t* lbl_battery;
extern lv_obj_t* lbl_status;
extern lv_obj_t* lbl_xyh;
extern lv_obj_t* lbl_temps;

void create_selector_ui();

lv_obj_t* get_scroll_container();