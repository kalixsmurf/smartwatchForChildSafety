#ifndef __childsafetyapp_H__
#define __childsafetyapp_H__

#include <app.h>
#include <Elementary.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "childsafetyapp"

// Application lifecycle functions
bool app_create(void *data);
void app_control(app_control_h app_control, void *data);
void app_pause(void *data);
void app_resume(void *data);
void app_terminate(void *data);

#if !defined(PACKAGE)
#define PACKAGE "org.example.childsafetyapp"
#endif

#endif /* __childsafetyapp_H__ */
