#ifndef COMMON_H
# define COMMON_H

# include <stdlib.h>	/*size_t*/
# include <stdio.h>		/*printf*/

typedef struct	ping_token_s
{
	size_t			flags;
	size_t			count;
	struct hostent	*host;
}					ping_token_t;

typedef struct	ping_info_s
{
	size_t		sent_count;
	size_t		recv_count;
	// a lot of other info yet to implement
}				ping_info_t;

typedef struct	ping_reply_s
{
	int		error;
	int		packet; //change type
}				ping_reply_t;

#endif
