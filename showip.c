#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "arg.h"
#include "strlcpy.h"

#define AUTHOR "Rodrigo González López <rodrigosloop AT gmail DOT com>"

#define HNSIZE 512

static void die(const char*, ...);
static void usage(void);

char *argv0;

void
die(const char *errstr, ...)
{
	va_list ap;

	va_start(ap, errstr);
	vfprintf(stderr, errstr, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

void
usage(void)
{
	die("usage: %s <hostname>\n", basename(argv0));
}

int main (int argc, char *argv[])
{
	char host[HNSIZE];
	struct addrinfo hints, *res, *np;
	int s;

	char ipstr[INET6_ADDRSTRLEN];

	ARGBEGIN {
	case 'v':
		die("showip-%s, Copyright (C) 2016 %s"
		    ", see LICENSE for details.\n", VERSION, AUTHOR);
	default:
		usage();
	} ARGEND;

	if (isatty(STDIN_FILENO)) {
		if (argc > 0) {
			strlcpy(host, argv[0], HNSIZE);
		} else {
			usage();
		}
	} else {
		if (fgets(host, HNSIZE, stdin) == NULL) {
			die("fgets: Couldn't read input\n");
		} else {
			host[strlen(host)-1] = '\0';
		}
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((s = getaddrinfo(host, NULL, &hints, &res)) != 0) {
		die("getaddrinfo: %s\n", gai_strerror(s));
	}

	for (np = res; np; np = np->ai_next) {
		getnameinfo(np->ai_addr, np->ai_addrlen,
			ipstr, sizeof ipstr,
			NULL, 0, NI_NUMERICHOST);

		printf("%s\n", ipstr);
	}

	freeaddrinfo(res);

	return EXIT_SUCCESS;
}
