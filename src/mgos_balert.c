#include "mgos.h"
#include "mgos_bthing.h"
#include "mg_balert_sdk.h"
#include "mgos_balert.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

mgos_bthing_t MGOS_BALERT_THINGCAST(mgos_balert_t alert) {
  return MG_BTHING_SENS_CAST4(MG_BALERT_CAST1(alert));
}

mgos_bsensor_t MGOS_BALERT_DOWNCAST(mgos_balert_t alert) {
  return (mgos_bsensor_t)alert;
}

mgos_balert_t mgos_balert_create(const char *id, const char *domain) {
  mgos_balert_t MG_BALERT_NEW(alert);
  if (mg_bthing_init(MG_BTHING_SENS_CAST3(alert), id, MGOS_BALERT_TYPE, domain)) {
    struct mg_balert_cfg *cfg = calloc(1, sizeof(struct mg_balert_cfg));
    if (cfg) {
      mgos_bthing_t thing = MGOS_BALERT_THINGCAST(alert);
      if (mg_balert_init(alert, cfg) && mg_bthing_register(thing)) {
        LOG(LL_INFO, ("bAlert '%s' successfully created.", mgos_bthing_get_uid(thing)));
        return alert;
      }
      mg_bthing_reset(MG_BTHING_SENS_CAST3(alert));
    } else {
      LOG(LL_ERROR, ("Unable to allocate memory for 'mg_balert_cfg'"));
    }
    free(cfg);
  }
  free(alert);
  LOG(LL_ERROR, ("Error creating bAlert '%s'. See above error message for more details.'", (id ? id : "")));
  return NULL; 
}

bool mgos_balert_set(mgos_balert_t alert, enum mgos_balert_level level,
                           int code, const char *msg) {
  if (alert) {
    mgos_bvar_t state = mg_bthing_get_state_4update(MGOS_BALERT_THINGCAST(alert));
    if (state) {
      mgos_bvar_set_key_integer(state, "level", level);
      mgos_bvar_set_key_integer(state, "code", code);
      mgos_bvar_set_key_str(state, "message", msg ? msg : "");
      return true;
    }
  }
  return false;
}

bool mgos_balert_info(mgos_balert_t alert, int code, const char *msg) {
  return mgos_balert_set(alert, MGOS_BALERT_LEVEL_INFO, code, msg);
}

bool mgos_balert_warning(mgos_balert_t alert, int code, const char *msg) {
  return mgos_balert_set(alert, MGOS_BALERT_LEVEL_WARNING, code, msg);
}

bool mgos_balert_error(mgos_balert_t alert, int code, const char *msg) {
  return mgos_balert_set(alert, MGOS_BALERT_LEVEL_ERROR, code, msg);
}

void mgos_balert_clear(mgos_balert_t alert) {
  if (alert) {
    mgos_bvar_t state = mg_bthing_get_state_4update(MGOS_BALERT_THINGCAST(alert));
    if (state) {
      mgos_bvar_set_key_integer(state, "level", MGOS_BALERT_LEVEL_NONE);
      mgos_bvar_set_key_integer(state, "code", 0);
      mgos_bvar_set_key_str(state, "message", "");
    }
  }
}


bool mgos_balert_init() {
  return true;
}