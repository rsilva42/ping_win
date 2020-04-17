#include "ping_win.h"

int		main(int argc, char **argv)
{
	ping_token_t	tokens;
	ping_info_t		info;

	if (argc > 1)
	{
		tokens = parse(argc, argv);
		info = ping(tokens);
		print_info(info);
	}
	else
		print_usage();
	return (EXIT_SUCCESS);
}
