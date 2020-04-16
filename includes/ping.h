#ifndef PING_H
# define PING_H

# include <stdlib.h>	/*size_t*/
# include <signal.h>	/*signal, SIGINT*/

# include "common.h"	/*ping_token_t, ping_info_t*/

typedef struct	ping_connect_s
{
	int		ip; //change type
	int		imp; //change type
}				ping_connect_t;

typedef struct	ping_reply_s
{
	int		packet //change type
}				ping_reply_t;
#endif
