#include "common/platform.h"
#include "fw/src/mgos_app.h"
#include "fw/src/mgos_hal.h"
#include "fw/src/mgos_hooks.h"
#include "fw/src/mgos_mongoose.h"
#include "fw/src/mgos_sys_config.h"
#include "fw/src/mgos_dlsym.h"
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

bool mgos_mjs_init(void) {
  /* Initialize JavaScript engine */
  struct sys_config *cfg = get_cfg();
  int mem1, mem2;
  mem1 = mgos_get_free_heap_size();
  mjs = mjs_create();
  mem2 = mgos_get_free_heap_size();
  mjs_set_ffi_resolver(mjs, mgos_dlsym);
  mjs_set_generate_jsc(mjs, cfg->mjs.generate_jsc);

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
