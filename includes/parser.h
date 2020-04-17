#ifndef PARSER_H
# define PARSER_H

// # include <sys/types.h>
# include <netdb.h>			/*addrinfo, getaddrinfo, gai_strerror*/

# include "common.h"		/*ping_token_t*/

void	flag_parse_error(ping_token_t *token);
void	too_many_args_error(void);
void	get_host_error(const char *error_msg);


#endif
