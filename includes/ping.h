#ifndef PING_H
#define PING_H

#include <sys/socket.h>			/*socket*/
#include <netinet/ip.h>			/*ip*/
#include <netinet/ip_icmp.h>	/*icmp*/
#include <arpa/inet.h>			/*inet_aton*/
#include <string.h>				/*memset*/
#include <signal.h>				/*signal, SIGINT*/

#include "common.h"		/*ping_token_t, ping_info_t*/

#define PING_PACKET_SIZE 64

typedef struct	ping_packet_s
{
	char		buffer[PING_PACKET_SIZE];
	struct ip	*ip_header;
	struct icmp	*icmp_header;
}				ping_packet_t;

void	print_error(char *error_msg);
void	print_reply(ping_reply_t reply, time_t rtt);

#endif
