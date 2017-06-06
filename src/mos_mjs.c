#include "common/platform.h"
#include "fw/src/mgos_app.h"
#include "fw/src/mgos_hal.h"
#include "fw/src/mgos_mongoose.h"
#include "fw/src/mgos_sys_config.h"
#include "fw/src/mgos_dlsym.h"
#include "mos_mjs.h"

bool mgos_mjs_init(void) {
  /* Initialize JavaScript engine */
  struct sys_config *cfg = get_cfg();
  int mem1, mem2, mem3;
  mem1 = mgos_get_free_heap_size();
  struct mjs *mjs = mjs_create();
  mem2 = mgos_get_free_heap_size();
  mjs_set_ffi_resolver(mjs, mgos_dlsym);
  mjs_set_generate_jsc(mjs, cfg->mjs.generate_jsc);
  mjs_err_t err = mjs_exec_file(mjs, "init.js", NULL);
  if (err != MJS_OK) {
    mjs_print_error(mjs, stdout, NULL, 1 /* print_stack_trace */);
  }
  mem3 = mgos_get_free_heap_size();
  LOG(LL_DEBUG, ("mJS memory stat: before init: %d "
                 "after init: %d after init.js: %d",
                 mem1, mem2, mem3));
  return true;
}
