#include "errors.h"

/*print usage info*/
void	print_usage(void)
{
	char	*usage_str = "usage: ./ping_win [-c count] [-t ttl] destination\n";
	write(STDERR_FILENO, usage_str, strlen(usage_str));
	exit(EXIT_FAILURE);
}

void	flag_parse_error(ping_token_t *token)
{
	char	*error_prefix = "ping_win: ";

	write(STDERR_FILENO, error_prefix, strlen(error_prefix));
	if ((token->flags & PING_FLAG_C) && !token->count)
	{
		char	*error_msg = "invalid packet count.\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
	}
	else if ((token->flags & PING_FLAG_T) && !token->ttl)
	{
		char	*error_msg = "invalid time to live value.\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
		printf("token:\n flags: %ld\n ttl: %ld\n", token->flags, token->ttl);
	}
	else
	{
		char	*error_msg = "invalid flag.\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
		print_usage();
	}
	exit(EXIT_FAILURE);
}
