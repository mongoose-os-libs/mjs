/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include "common/platform.h"

#include "mgos_app.h"
#include "mgos_dlsym.h"
#include "mgos_hal.h"
#include "mgos_hooks.h"
#include "mgos_mongoose.h"
#include "mgos_net.h"
#include "mgos_sys_config.h"
#ifdef MGOS_HAVE_WIFI
#include "mgos_wifi.h"
#endif

#include "mos_mjs.h"

struct mjs *mjs = NULL;

/*
 * Runs when all initialization (all libs + app) is done
 */
static void s_init_done_hook(enum mgos_hook_type type,
                             const struct mgos_hook_arg *arg, void *userdata) {
  int mem1, mem2;

  mem1 = mgos_get_free_heap_size();
  mjs_err_t err = mjs_exec_file(mjs, "init.js", NULL);
  if (err != MJS_OK) {
    mjs_print_error(mjs, stdout, NULL, 1 /* print_stack_trace */);
  }
  mem2 = mgos_get_free_heap_size();
  LOG(LL_DEBUG,
      ("mJS memory stat: before init.js: %d after init.js: %d", mem1, mem2));

  (void) type;
  (void) arg;
  (void) userdata;
}

struct cb_info {
  void (*cb)(enum mgos_net_event ev, void *arg);
  void *arg;
};

static void mgos_net_add_event_handler_js_cb(
    enum mgos_net_event ev, const struct mgos_net_event_data *ev_data,
    void *arg) {
  struct cb_info *cbi = (struct cb_info *) arg;
  cbi->cb(ev, cbi->arg);
  (void) ev_data;
}

void mgos_net_add_event_handler_js(void (*cb)(enum mgos_net_event ev,
                                              void *arg),
                                   void *arg) {
  struct cb_info *cbi = (struct cb_info *) calloc(1, sizeof(*cbi));
  cbi->cb = cb;
  cbi->arg = arg;
  mgos_net_add_event_handler(mgos_net_add_event_handler_js_cb, cbi);
}

bool mgos_mjs_init(void) {
  /* Initialize JavaScript engine */
  int mem1, mem2;
  mem1 = mgos_get_free_heap_size();
  mjs = mjs_create();
  mem2 = mgos_get_free_heap_size();
  mjs_set_ffi_resolver(mjs, mgos_dlsym);
  mjs_set_generate_jsc(mjs, mgos_sys_config_get_mjs_generate_jsc());

#ifdef MGOS_HAVE_WIFI
  {
    mjs_val_t global_obj = mjs_get_global(mjs);
    mjs_val_t wifi_obj = mjs_mk_object(mjs);
    mjs_set(mjs, global_obj, "Wifi", ~0, wifi_obj);
    mjs_set(mjs, wifi_obj, "scan", ~0, mjs_mk_foreign(mjs, mgos_wifi_scan_js));
  }
#endif

  /*
   * We also need to run init.js, but we can't do that here because init.js
   * might depend on some other libs which weren't initialized yet. Thus we use
   * the INIT_DONE hook.
   */
  mgos_hook_register(MGOS_HOOK_INIT_DONE, s_init_done_hook, NULL);

  LOG(LL_DEBUG,
      ("mJS memory stat: before init: %d after init: %d", mem1, mem2));
  return true;
}

struct mgos_config *mgos_mjs_get_config(void) {
  return &mgos_sys_config;
}

struct mjs *mgos_mjs_get_global(void) {
  return mjs;
}
