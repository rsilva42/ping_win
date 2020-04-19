#include "ping_win.h"

int		main(int argc, char **argv)
{
	ping_token_t	*token;
	ping_info_t		info;

	if (argc > 1)
	{
		token = parse(argc, argv);
		info = ping(token);
		print_info(info);
		free(token);
	}
	else
		print_usage();
	return (EXIT_SUCCESS);
}
