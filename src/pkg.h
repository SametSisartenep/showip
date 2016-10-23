#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "arg.h"

#undef strlcpy
size_t strlcpy(char *, const char *, size_t);
size_t estrlcpy(char *, const char *, size_t);
