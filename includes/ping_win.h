#ifndef PING_WIN_H
# define PING_WIN_H

# include <stdlib.h>	/*exit*/
# include "common.h"	/*ping_token_t, ping_info_t*/

ping_token_t	parse(int ac, char **av);
ping_info_t		ping(ping_token_t tokens);
void			print_info(ping_info_t info);
void			print_usage(void);

#endif
