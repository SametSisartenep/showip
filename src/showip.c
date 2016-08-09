#include <stdio.h>
#include <string.h>
#include <argp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const char *argp_program_version = "ShowIP v0.1.0";
const char *argp_program_bug_address = "Rodrigo González López <rodrigosloop@gmail.com>";

static char doc[] = "ShowIP -- A simple domain name resolution tool.";
static char args_doc[] = "hostname";

static struct argp argp = { 0, 0, args_doc, doc, 0, 0, 0 };

int main (int argc, char **argv)
{
	if (argc != 2) {
		argp_help(&argp, stderr, ARGP_HELP_USAGE, 0);
		return 1;
	}

	int argsno = 1;

	argp_parse(&argp, argc, argv, 0, &argsno, 0);

	struct addrinfo hints = {0}, *result, *node_ptr;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &result)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	printf("IP addresses for %s\n\n", argv[1]);

	for (node_ptr = result; node_ptr; node_ptr = node_ptr->ai_next) {
		char *ipver;

		switch (node_ptr->ai_family) {
			case AF_INET:
				ipver = "IPv4";
				break;
			case AF_INET6:
				ipver = "IPv6";
				break;
		}

		getnameinfo(node_ptr->ai_addr, node_ptr->ai_addrlen, ipstr, sizeof ipstr, NULL, 0, NI_NUMERICHOST);
		printf("\t%s:\t%s\n", ipver, ipstr);
	}

	freeaddrinfo(result);

	return 0;
}
