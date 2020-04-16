#ifndef PING_WIN_H
# define PING_WIN_H

# include "parser.h"
# include "ping.h"

ping_token_t	parse(int ac, char **av);
ping_info_t		ping(ping_token_t tokens);
void			print_info(ping_info_t);
void			print_usage(void);

#endif
