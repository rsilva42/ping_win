#ifndef PARSER_H
# define PARSER_H

# include <sys/socket.h>

typedef struct	ping_token_s
{
	size_t			flags;
	size_t			count;
	struct hostent	*host;
}					ping_token_t;

#endif
