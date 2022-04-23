#include "mgos.h"
#include "mgos_bthing.h"
#include "mg_balert_sdk.h"
#include "mgos_balert.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

static char s_tmpbuf[256];

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

bool mgos_balert_set(mgos_balert_t alert, enum mgos_balert_level level, int code, const char *msg) {
  if (alert) {
    struct mgos_bthing_updatable_state state;
    if (mgos_bthing_start_update_state(MGOS_BALERT_THINGCAST(alert), &state)) {
      sprintf(s_tmpbuf, "%c%d %s",
        (level == MGOS_BALERT_LEVEL_ERROR ? 'E' : (level == MGOS_BALERT_LEVEL_WARNING ? 'W' : 'I')),
        code, (msg ? msg: ""));

      mgos_bvar_set_str(state.value, s_tmpbuf);

      mgos_bthing_end_update_state(state);
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
  mgos_balert_set(alert, MGOS_BALERT_LEVEL_NONE, 0, NULL);
}


bool mgos_balert_init() {
  return true;
}