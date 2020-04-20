#ifndef PING_H
#define PING_H

#include <sys/socket.h>			/*socket*/
#include <arpa/inet.h>			/*inet_aton*/
#include <signal.h>				/*signal, SIGINT*/
#include <time.h>				/*clock_gettime, CLOCK_MONOTONIC*/

#include "common.h"				/*ping_token_t, ping_info_t*/

#define PING_TIMEOUT	1

void	print_reply(ping_packet_t *reply, uint64_t rtt);

#endif
