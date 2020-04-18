#ifndef PING_H
#define PING_H

#include <sys/socket.h>	/*socket*/
#include <signal.h>		/*signal, SIGINT*/
#include <unistd.h>		/*sleep*/

#include "common.h"		/*ping_token_t, ping_info_t*/

#define PING_PACKET_SIZE 64

typedef struct	ping_packet_s
{
	char		buffer[PING_PACKET_SIZE]
	struct ip	*ip_header;
	struct icmp	*icmp_header;
};

void	print_error(char *error_msg);
void	print_reply(ping_reply_t reply, time_t rtt);

#endif
