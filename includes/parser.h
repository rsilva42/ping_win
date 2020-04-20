#ifndef PARSER_H
#define PARSER_H

#include "common.h"		/*ping_token_t, addrinfo,
						getaddrinfo, gai_strerror*/

void	flag_parse_error(ping_token_t *token);
void	too_many_args_error(void);

#endif
