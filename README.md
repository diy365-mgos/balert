# bAlerts Library
## Overview
A bAlert allows you to easily set alert messages: info, warning and errors.
## Inherited APIs
A bAlert inherits inherits APIs from:
- [bThing](https://github.com/diy365-mgos/bthing)
- [bSensor](https://github.com/diy365-mgos/bsensor)
### Remarks on: mgos_bthing_on_get_state()
The bAlert doesn't need a [get-state handler](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state_handler_t). So, even if you set an handler, it is ignored.
### Remarks on: mgos_bthing_get_state()
The [mgos_bthing_get_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state) returns a `NULL` value or a formatted string value: `"<level:E,W,I>|<code>|<message>"`.
```c
mgos_balert_t alert = mgos_balert_create(...);
mgos_bvarc_t state = mgos_bthing_get_state(MGOS_BALERT_THINGCAST(alert));
if (!mgos_bvar_is_null(state))
  const char *msg = mgos_bvar_get_str(state);
```
## C/C++ APIs Reference
### MGOS_BALERT_TYPE
```c
#define MGOS_BALERT_TYPE
```
The bAlert type ID. It can be used with [mgos_bthing_is_typeof()](https://github.com/diy365-mgos/bthing#mgos_bthing_is_typeof).

Example:
```c
mgos_balert_t alert = mgos_balert_create(...);
if (mgos_bthing_is_typeof(MGOS_BALERT_THINGCAST(alert), MGOS_BALERT_TYPE))
  LOG(LL_INFO, ("I'm a bAlert."));
if (mgos_bthing_is_typeof(MGOS_BALERT_THINGCAST(alert), MGOS_BSENSOR_TYPE))
  LOG(LL_INFO, ("I'm a bSensor."));
if (mgos_bthing_is_typeof(MGOS_BALERT_THINGCAST(alert), MGOS_BTHING_TYPE_SENSOR))
  LOG(LL_INFO, ("I'm a bThing alert."));
```
Output console:
```bash
I'm a bAlert.
I'm a bSensor.
I'm a bThing alert.
```
### MGOS_BALERT_THINGCAST
```c
mgos_bthing_t MGOS_BALERT_THINGCAST(mgos_balert_t alert);
```
Casts a bAlert to a generic bThing to be used with [inherited bThing APIs](https://github.com/diy365-mgos/bthing).

|Parameter||
|--|--|
|alert|A bAlert.|

Example:
```c
mgos_balert_t alert = mgos_balert_create(...);
LOG(LL_INFO, ("%s successfully created.", mgos_bthing_get_uid(MGOS_BALERT_THINGCAST(alert))));
```
### MGOS_BALERT_DOWNCAST
```c
mgos_bsensor_t MGOS_BALERT_DOWNCAST(mgos_balert_t alert);
```
Casts a bAlert to a bSensor to be used with [inherited bSensor APIs](https://github.com/diy365-mgos/bsensor).

|Parameter||
|--|--|
|alert|A bAlert.|
### mgos_balert_level
```c
enum mgos_balert_level {
    MGOS_BALERT_LEVEL_INFO = 0,
    MGOS_BALERT_LEVEL_WARNING = 1,
    MGOS_BALERT_LEVEL_ERROR = 2,
};
```
The alert's level.
### mgos_balert_create
```c
mgos_balert_t mgos_balert_create(const char *id, const char *domain);
```
Creates a bAlert. Returns `NULL` on error.

|Parameter||
|--|--|
|id|The bAlert ID.|
|domain|The domain name or `NULL`.|
### mgos_balert_set
```c
bool mgos_balert_set(mgos_balert_t alert, enum mgos_balert_level level, int code);
```
Sets an alert message. Returns `true` if success, `true` otherwise.

|Parameter||
|--|--|
|alert|A bAlert.|
|level|The alert's level.|
|code|The alert's code.|
### mgos_balert_info
```c
bool mgos_balert_info(mgos_balert_t alert, int code);
```
Sets an alert info message. Returns `true` if success, `true` otherwise.

|Parameter||
|--|--|
|alert|A bAlert.|
|code|The info code.|
### mgos_balert_warning
```c
bool mgos_balert_warning(mgos_balert_t alert, int code);
```
Sets an alert warning message. Returns `true` if success, `true` otherwise.

|Parameter||
|--|--|
|alert|A bAlert.|
|code|The warning code.|
### mgos_balert_error
```c
bool mgos_balert_error(mgos_balert_t alert, int code);
```
Sets an alert error message. Returns `true` if success, `true` otherwise.

|Parameter||
|--|--|
|alert|A bAlert.|
|code|The error code.|
### mgos_balert_clear
```c
void mgos_balert_clear(mgos_balert_t alert);
```
Clears an alert message. 

|Parameter||
|--|--|
|alert|A bAlert.|

**Remarks**

The state of a cleared bAlert is: `level=MGOS_BALERT_LEVEL_NONE` and `code=0`.
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).
