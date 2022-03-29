#include "mgos.h"
#include "mg_balert_sdk.h"

/*****************************************
 * Cast Functions
 */

// Convert (mgos_balert_t) into (struct mg_bthing_sens *)
struct mg_bthing_sens *MG_BALERT_CAST1(mgos_balert_t thing) {
  return (struct mg_bthing_sens *)thing;
}
/*****************************************/


enum mg_bthing_state_result mg_balert_getting_state_cb(struct mg_bthing_sens *alert,
                                                           mgos_bvar_t state,
                                                           void *userdata) {
  if (alert && state) {
    if (mgos_bvar_is_null(state) || (mgos_bvar_get_type(state) == MGOS_BVAR_TYPE_DIC)) {
      return MG_BTHING_STATE_RESULT_UNHANDLED;
    }
  }
  return MG_BTHING_STATE_RESULT_ERROR;
}

bool mg_balert_init(mgos_balert_t alert, struct mg_balert_cfg *cfg) {
  if (cfg) {
    if (mg_bsensor_init(alert, &cfg->base)) {
      /* initalize overrides cfg */
      cfg->overrides.getting_state_cb = mg_bthing_on_getting_state(alert, mg_balert_getting_state_cb);
      mgos_balert_clear(alert);

      return true; // initialization successfully completed
    }
    mg_balert_reset(alert);
  } else {
    LOG(LL_ERROR, ("Invalid NULL 'cfg' parameter."));
  }

  LOG(LL_ERROR, ("Error initializing bAlert '%s'. See above error message for more details.",
    mgos_bthing_get_uid(MGOS_BALERT_THINGCAST(alert))));
  return false; 
}

void mg_balert_reset(mgos_balert_t alert) {
  struct mg_balert_cfg *cfg = MG_BALERT_CFG(alert);

  /* clear overrides cfg */
  if (cfg->overrides.getting_state_cb) {
    mg_bthing_on_getting_state(alert, cfg->overrides.getting_state_cb);
    cfg->overrides.getting_state_cb = NULL;
  }

  mgos_balert_clear(alert);

  // reset alert-base obj
  mg_bsensor_reset(alert);
}
