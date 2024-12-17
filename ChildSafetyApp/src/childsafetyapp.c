#include <tizen.h>
#include <Elementary.h>
#include <efl_extension.h>
#include <app.h>

static Evas_Object *naviframe = NULL;

// Forward declarations
static void create_dashboard_page(Evas_Object *naviframe);
static void create_parental_settings_page(Evas_Object *naviframe);
static void create_safezone_settings_page(Evas_Object *naviframe);

// App create callback
static bool app_create(void *data) {
    // Window
    Evas_Object *win = elm_win_util_standard_add("ChildSafetyApp", "ChildSafetyApp");
    elm_win_autodel_set(win, EINA_TRUE);

    // Naviframe for navigation
    naviframe = elm_naviframe_add(win);
    evas_object_size_hint_weight_set(naviframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(win, naviframe);
    evas_object_show(naviframe);

    // Start with Dashboard Page
    create_dashboard_page(naviframe);

    evas_object_show(win);
    return true;
}

// Function to create a scroller for pages
static Evas_Object *create_scroller(Evas_Object *parent) {
    Evas_Object *scroller = elm_scroller_add(parent);
    elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
    evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
    return scroller;
}

// Function to create Dashboard Page
static void create_dashboard_page(Evas_Object *naviframe) {
    Evas_Object *scroller = create_scroller(naviframe);
    Evas_Object *box = elm_box_add(scroller);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(box);

    // Title
    Evas_Object *title = elm_label_add(box);
    elm_object_text_set(title, "Dashboard");
    evas_object_show(title);
    elm_box_pack_end(box, title);

    // Table
    Evas_Object *table = elm_table_add(box);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_homogeneous_set(table, EINA_TRUE);

    const char *headers[] = {"Time", "Audio", "Loc", "HR", "Alert"};
    for (int col = 0; col < 5; col++) {
        Evas_Object *label = elm_label_add(table);
        elm_object_text_set(label, headers[col]);
        elm_table_pack(table, label, col, 0, 1, 1);
        evas_object_show(label);
    }

    for (int row = 1; row <= 3; row++) {
        for (int col = 0; col < 5; col++) {
            Evas_Object *label = elm_label_add(table);
            elm_object_text_set(label, "Data");
            elm_table_pack(table, label, col, row, 1, 1);
            evas_object_show(label);
        }
    }

    elm_box_pack_end(box, table);

    // Settings Button
    Evas_Object *settings_btn = elm_button_add(box);
    elm_object_text_set(settings_btn, "Settings");
    evas_object_size_hint_min_set(settings_btn, 200, 50);
    evas_object_smart_callback_add(settings_btn, "clicked", create_parental_settings_page, naviframe);
    evas_object_show(settings_btn);
    elm_box_pack_end(box, settings_btn);

    // Attach box to scroller
    elm_object_content_set(scroller, box);

    elm_naviframe_item_push(naviframe, "Dashboard", NULL, NULL, scroller, NULL);
}

// Function to create Parental Settings Page
static void create_parental_settings_page(Evas_Object *naviframe) {
    Evas_Object *scroller = create_scroller(naviframe);
    Evas_Object *box = elm_box_add(scroller);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(box);

    const char *labels[] = {"Parental Password", "Parent-1 Phone", "Parent-2 Phone"};
    for (int i = 0; i < 3; i++) {
        Evas_Object *label = elm_label_add(box);

        elm_object_text_set(label,labels[i]);
        evas_object_show(label);
        elm_box_pack_end(box, label);

        Evas_Object *entry = elm_entry_add(box);
        elm_entry_single_line_set(entry, EINA_TRUE);
        evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0);
        evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0.5);
        evas_object_show(entry);
        elm_box_pack_end(box, entry);
    }

    // Save Button
    Evas_Object *save_btn = elm_button_add(box);
    elm_object_text_set(save_btn, "Save");
    evas_object_size_hint_min_set(save_btn, 200, 50);
    evas_object_show(save_btn);
    elm_box_pack_end(box, save_btn);

    elm_object_content_set(scroller, box);
    elm_naviframe_item_push(naviframe, "Parental Settings", NULL, NULL, scroller, NULL);
}

// Function to create Safezone Settings Page
static void create_safezone_settings_page(Evas_Object *naviframe) {
    Evas_Object *scroller = create_scroller(naviframe);
    Evas_Object *box = elm_box_add(scroller);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(box);

    Evas_Object *label = elm_label_add(box);
    elm_object_text_set(label, "<font_size=15>Latitude, Longitude:</font_size>");
    evas_object_show(label);
    elm_box_pack_end(box, label);

    Evas_Object *entry = elm_entry_add(box);
    elm_entry_single_line_set(entry, EINA_TRUE);
    evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0);
    evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0.5);
    evas_object_show(entry);
    elm_box_pack_end(box, entry);

    Evas_Object *add_del_btn = elm_button_add(box);
    elm_object_text_set(add_del_btn, "Add/Delete");
    evas_object_size_hint_min_set(add_del_btn, 200, 50);
    evas_object_show(add_del_btn);
    elm_box_pack_end(box, add_del_btn);

    elm_object_content_set(scroller, box);
    elm_naviframe_item_push(naviframe, "Safezone Settings", NULL, NULL, scroller, NULL);
}

// App lifecycle callbacks
static void app_terminate(void *data) {}

int main(int argc, char *argv[]) {
    ui_app_lifecycle_callback_s event_callback = {0};
    event_callback.create = app_create;
    event_callback.terminate = app_terminate;

    return ui_app_main(argc, argv, &event_callback, NULL);
}
