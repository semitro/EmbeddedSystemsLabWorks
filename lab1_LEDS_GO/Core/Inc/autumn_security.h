#ifndef SEC_SEC_H
#define SEC_SEC_H

#include <stdint.h>
#include "simple_io.h"

int8_t security(uint8_t pass[], int8_t level, int8_t max_lvl, uint8_t character);

#endif // SEC_SEC_H
