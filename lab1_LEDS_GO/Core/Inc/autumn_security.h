#ifndef SEC_SEC_H
#define SEC_SEC_H

#include "simple_io.h"

typedef struct Password {
	size_t len;
	Press pass[20];
} Password;

void security(Password* pass);

#endif // SEC_SEC_H
