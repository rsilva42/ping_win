#ifndef PING_H
#define PING_H

#include <sys/socket.h>			/*socket*/
#include <netinet/ip.h>			/*ip*/
#include <netinet/ip_icmp.h>	/*icmp*/
#include <arpa/inet.h>			/*inet_aton*/
#include <string.h>				/*memset*/
#include <signal.h>				/*signal, SIGINT*/

#include "common.h"				/*ping_token_t, ping_info_t*/

#define PING_TIMEOUT	4

void	print_error(char *error_msg);
void	print_reply(ping_packet_t reply, time_t rtt); //this may change

#endif
