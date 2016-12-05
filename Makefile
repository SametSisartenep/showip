
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

VERSION = 1.2
SRC = showip.c strlcpy.c
BIN = showip
MAN = showip.1

TARBALL = $(BIN)-$(VERSION)

CPPFLAGS = -D_FORTIFY_SOURCE=2 -D_DEFAULT_SOURCE -D_BSD_SOURCE \
	-D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS = -Wall -Wextra -Werror -Wformat-security -Wpointer-arith \
	-Winit-self -fno-exceptions -fstack-protector-strong \
	--param=ssp-buffer-size=4 -std=c99 -Wpedantic -pedantic \
	-pipe -O2 -fpie -pie -Wl,--no-undefined -Wl,--build-id=sha1 \
	-Wl,-z,relro -Wl,-z,now -Wl,-O1a -s

CC ?= cc

all: $(BIN)

$(BIN): $(SRC)

install: all
	@echo Installing...
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	@cp -f $(MAN) $(DESTDIR)$(MANPREFIX)/man1
	@mkdir -p $(DESTDIR)$(PREFIX)/share/licenses/showip
	@cp -f LICENSE $(DESTDIR)$(PREFIX)/share/licenses/showip

distclean:
	@echo Cleaning distribution tarball...
	@rm -fv ${TARBALL}.tar.gz

dist: distclean
	@echo Creating distribution tarball...
	@mkdir -p ${TARBALL}
	@cp LICENSE Makefile README.md arg.h strlcpy.h showip.1 \
	${SRC} ${TARBALL}
	@tar -cf ${TARBALL}.tar ${TARBALL}
	@gzip ${TARBALL}.tar
	@rm -rfv ${TARBALL}

uninstall:
	@echo Removing...
	@rm -fv $(DESTDIR)$(PREFIX)/bin/$(BIN)
	@rm -fv $(DESTDIR)$(MANPREFIX)/man1/$(MAN)
	@rm -fv $(DESTDIR)$(PREFIX)/share/licenses/showip/LICENSE

clean:
	@echo Cleaning...
	@rm -fv $(BIN)

.PHONY:
	all install uninstall clean dist distclean
