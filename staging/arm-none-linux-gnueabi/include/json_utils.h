
#include <stdbool.h>

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "json.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool json_get_string(json_t *object, const char *label, const char **ret_string);
bool json_get_int(json_t *object, const char *label, int *ret_int);
bool json_get_bool(json_t *object, const char *label, bool *ret_bool);

#ifdef __cplusplus
}
#endif
#endif

