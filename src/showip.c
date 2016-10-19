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

#define VERSION "1.0"
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
	ARGBEGIN {
	case 'v':
		die("showip-%s, Copyright (C) 2016 %s"
		    ", see LICENSE for details.\n", VERSION, AUTHOR);
	default:
		usage();
	} ARGEND;

	char hn[HNSIZE];

	if (argc > 0) {
		strncpy(hn, argv[0], HNSIZE);
	}

	struct addrinfo hints, *res, *np;
	int s;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((s = getaddrinfo(hn, NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return 2;
	}

	printf("IP addresses for %s\n\n", hn);

	for (np = res; np; np = np->ai_next) {
		char *ipver;
		char ipstr[INET6_ADDRSTRLEN];

		switch (np->ai_family) {
			case AF_INET:
				ipver = "IPv4";
				break;
			case AF_INET6:
				ipver = "IPv6";
				break;
		}

		getnameinfo(np->ai_addr, np->ai_addrlen,
			ipstr, sizeof ipstr,
			NULL, 0, NI_NUMERICHOST);

		printf("\t%s:\t%s\n", ipver, ipstr);
	}

	freeaddrinfo(res);

	return EXIT_SUCCESS;
}
