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

#ifndef MGOS_BALERT_H_
#define MGOS_BALERT_H_

#include <stdbool.h>
#include "mgos_bthing.h"
#include "mgos_bsensor.h"
#include "mgos_bvar_dic.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mg_bthing_sens;
typedef struct mg_bthing_sens *mgos_balert_t;

#define MGOS_BALERT_LEVEL_NONE 0;

enum mgos_balert_level {
    MGOS_BALERT_LEVEL_INFO = 1,
    MGOS_BALERT_LEVEL_WARNING = 2,
    MGOS_BALERT_LEVEL_ERROR = 3,
};

mgos_bthing_t MGOS_BALERT_THINGCAST(mgos_balert_t alert);

mgos_bsensor_t MGOS_BALERT_DOWNCAST(mgos_balert_t alert);

mgos_balert_t mgos_balert_create(const char *id, const char *domain);

bool mgos_balert_set(mgos_balert_t alert, enum mgos_balert_level level,
                     int code, const char *msg);

bool mgos_balert_info(mgos_balert_t alert, int code, const char *msg);
bool mgos_balert_warning(mgos_balert_t alert, int code, const char *msg);
bool mgos_balert_error(mgos_balert_t alert, int code, const char *msg);

void mgos_balert_clear(mgos_balert_t alert);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_BALERT_H_ */