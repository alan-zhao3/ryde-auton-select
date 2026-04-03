#include "auton_selector.h"
#include "main.h"
#include <vector>

using namespace pros;

int selected_auton_id = -1;
static std::vector<lv_obj_t*> btn_list;
static lv_obj_t* scroll_container = nullptr;

lv_obj_t* lbl_battery = nullptr;
lv_obj_t* lbl_status  = nullptr;
lv_obj_t* lbl_xyh     = nullptr;
lv_obj_t* lbl_temps   = nullptr;

static lv_style_t style_btn;
static lv_style_t style_btn_selected;
static lv_style_t style_telebar;

const char* AUTON_NAMES[7] = {
    "Auto Left 1", "Auto Left 2", "Auto Right 1", "Auto Right 2",
    "Center Score", "Defense", "DEBUG TEST"
};

static void init_styles() {
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 8);
    lv_style_set_bg_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_text_color(&style_btn, lv_color_black());

    lv_style_init(&style_btn_selected);
    lv_style_set_radius(&style_btn_selected, 8);
    lv_style_set_bg_color(&style_btn_selected, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_color(&style_btn_selected, lv_color_white());
    lv_style_set_border_width(&style_btn_selected, 3);
    lv_style_set_border_color(&style_btn_selected, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_init(&style_telebar);
    lv_style_set_bg_color(&style_telebar, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_border_width(&style_telebar, 0);
}

static void refresh_button_styles() {
    for (int i = 0; i < (int)btn_list.size(); i++) {
        lv_obj_t* b = btn_list[i];
        lv_obj_remove_style(b, &style_btn, 0);
        lv_obj_remove_style(b, &style_btn_selected, 0);
        lv_obj_add_style(b, (i == selected_auton_id) ? &style_btn_selected : &style_btn, 0);
    }
}

static void btn_event_cb(lv_event_t* e) {
    lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);
    for (int i = 0; i < (int)btn_list.size(); i++) {
        if (btn_list[i] == btn) {
            selected_auton_id = i;
            refresh_button_styles();
            break;
        }
    }
}

static void scroll_up_cb(lv_event_t* e) {
    if (scroll_container) lv_obj_scroll_by(scroll_container, 0, -160, LV_ANIM_ON);
}

static void scroll_down_cb(lv_event_t* e) {
    if (scroll_container) lv_obj_scroll_by(scroll_container, 0, 160, LV_ANIM_ON);
}

void create_selector_ui() {
    init_styles();
    lv_obj_t* scr = lv_screen_active();

    // Simple Tabview (compatible with your LVGL version)
    lv_obj_t* tabview = lv_tabview_create(scr);
    lv_obj_t* tab_tele = lv_tabview_add_tab(tabview, "Telemetry");
    lv_obj_t* tab_auton = lv_tabview_add_tab(tabview, "Autons");

    // Telemetry Tab
    lv_obj_set_flex_flow(tab_tele, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(tab_tele, 12, 0);

    lbl_battery = lv_label_create(tab_tele);
    lv_label_set_text(lbl_battery, "Bat: 100%");
    lv_obj_set_style_text_font(lbl_battery, &lv_font_montserrat_16, 0);

    lbl_status = lv_label_create(tab_tele);
    lv_label_set_text(lbl_status, "Sel: None (Waiting)");
    lv_obj_set_style_text_font(lbl_status, &lv_font_montserrat_16, 0);

    lbl_xyh = lv_label_create(tab_tele);
    lv_label_set_text(lbl_xyh, "X: 0.0  Y: 0.0  H: 0.0");
    lv_obj_set_style_text_color(lbl_xyh, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(lbl_xyh, &lv_font_montserrat_16, 0);

    lbl_temps = lv_label_create(tab_tele);
    lv_label_set_text(lbl_temps, "Drive: --C | Mech: --C");
    lv_obj_set_style_text_font(lbl_temps, &lv_font_montserrat_16, 0);

    // Auton Tab
    lv_obj_set_flex_flow(tab_auton, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(tab_auton, 8, 0);

    scroll_container = lv_obj_create(tab_auton);
    lv_obj_set_size(scroll_container, 370, 200);
    lv_obj_set_flex_flow(scroll_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scrollbar_mode(scroll_container, LV_SCROLLBAR_MODE_AUTO);

    btn_list.clear();
    for (int i = 0; i < 7; i++) {
        lv_obj_t* btn = lv_button_create(scroll_container);
        lv_obj_set_size(btn, 340, 48);
        lv_obj_add_style(btn, &style_btn, 0);
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, nullptr);

        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, AUTON_NAMES[i]);
        lv_obj_center(label);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_18, 0);

        btn_list.push_back(btn);
    }

    lv_obj_t* arrows = lv_obj_create(tab_auton);
    lv_obj_set_size(arrows, 70, 200);
    lv_obj_set_style_border_width(arrows, 0, 0);
    lv_obj_set_style_bg_opa(arrows, LV_OPA_TRANSP, 0);
    lv_obj_set_flex_flow(arrows, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(arrows, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t* up = lv_button_create(arrows);
    lv_obj_set_size(up, 55, 80);
    lv_obj_add_style(up, &style_btn, 0);
    lv_obj_add_event_cb(up, scroll_up_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* lu = lv_label_create(up); lv_label_set_text(lu, "↑"); lv_obj_center(lu);

    lv_obj_t* down = lv_button_create(arrows);
    lv_obj_set_size(down, 55, 80);
    lv_obj_add_style(down, &style_btn, 0);
    lv_obj_add_event_cb(down, scroll_down_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* ld = lv_label_create(down); lv_label_set_text(ld, "↓"); lv_obj_center(ld);
}

lv_obj_t* get_scroll_container() {
    return scroll_container;
}