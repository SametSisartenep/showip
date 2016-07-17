CPPFLAGS:=-D_FORTIFY_SOURCE=2
CFLAGS:=-Wall -Wextra -Werror -fno-exceptions -fstack-protector-strong -Wl,-z,relro -Wl,-z,now -Wformat-security -Wpointer-arith -Wformat-nonliteral -Winit-self -Wl,-O1a -Wl,--no-undefined -Wl,--build-id=sha1 -Wpedantic -pedantic --param=ssp-buffer-size=4
LDFLAGS:=-Wall -Werror
CC:=$(CC)

showip: showip.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -s -o $@ $<

all: showip

.PHONY: all
