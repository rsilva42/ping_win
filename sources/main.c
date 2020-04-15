#include "ping_win.h"

int		main(int argc, char **argv)
{
	t_ping_token	tokens;
	t_ping_info	ping_info;

	if (argc > 1)
	{
		tokens = parse(argc, argv);
		ping_info = ping(tokens);
		print_info(ping_info);
	}
	else
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
