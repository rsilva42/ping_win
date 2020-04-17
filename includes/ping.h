#ifndef PING_H
# define PING_H

# include <signal.h>	/*signal, SIGINT*/
# include <unistd.h>	/*sleep*/

# include "common.h"	/*ping_token_t, ping_info_t*/

typedef struct	ping_connect_s
{
	int		ip; //change type
	int		icmp; //change type
}				ping_connect_t;

void	print_reply(ping_reply_t reply, time_t rtt);

#endif
