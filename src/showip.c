#include "pkg.h"

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
		strlcpy(hn, argv[0], HNSIZE + 1);
	} else {
		usage();
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
		char ipver[5];
		char ipstr[INET6_ADDRSTRLEN];

		switch (np->ai_family) {
			case AF_INET:
				strlcpy(ipver, "IPv4", 5);
				break;
			case AF_INET6:
				strlcpy(ipver, "IPv6", 5);
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
