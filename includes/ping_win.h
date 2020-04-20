#ifndef PING_WIN_H
#define PING_WIN_H

#include "common.h"	/*ping_token_t, ping_info_t*/

ping_token_t	*parse(int argc, char **argv);
ping_info_t		ping(ping_token_t *token);
void			print_info(ping_info_t info);
void			print_usage(void);

#endif
