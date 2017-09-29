// Copyright (c) Cesanta Software Limited
// All rights reserved

#ifndef MOS_MJS_H_
#define MOS_MJS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mjs.h"

bool mgos_mjs_init(void);

struct mjs *mgos_mjs_get_global(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
