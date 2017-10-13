/*
 * Copyright 2015-2017 Cesanta
 * All rights reserved
 */

/*
 * mJS wrapper API.
 */

#ifndef MOS_MJS_H_
#define MOS_MJS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mjs.h"

bool mgos_mjs_init(void);

/* Return global mJS instance. */
struct mjs *mgos_mjs_get_global(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
