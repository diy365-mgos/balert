/*
 * Copyright (c) 2021 DIY356
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MG_BALERT_SDK_H_
#define MG_BALERT_SDK_H_

#include <stdbool.h>
#include "mg_bthing_sdk.h"
#include "mg_bsensor_sdk.h"
#include "mgos_balert.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MG_BALERT_NEW(s) MG_BTHING_SENS_NEW(s);

/*****************************************
 * Cast Functions
 */

// Convert (mgos_balert_t) into (struct mg_bthing_sens *)
struct mg_bthing_sens *MG_BALERT_CAST1(mgos_balert_t thing);
/*****************************************/

#define MG_BALERT_CFG(s) ((struct mg_balert_cfg *)MG_BALERT_CAST1(s)->cfg)

struct mg_balert_overrides {
  mg_bthing_getting_state_handler_t getting_state_cb;
};

struct mg_balert_cfg {
  struct mg_bsensor_cfg base;
  struct mg_balert_overrides overrides;
  // add here extra fields
};

bool mg_balert_init(mgos_balert_t alert, struct mg_balert_cfg *cfg);

void mg_balert_reset(mgos_balert_t alert);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MG_BALERT_SDK_H_ */