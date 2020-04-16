#include "parser.h"

int				parse_flags(ping_token_t *token, int ac, char **av)
{
	(void)token;
	(void)ac;
	(void)av;
	printf("parsing flags\n");
	return (0);
}

struct hostent	*parse_host(int flags, char **av)
{
	(void)flags;
	(void)av;
	printf("parsing host\n");
	return (NULL);
}

ping_token_t	parse(int ac, char **av)
{
	size_t			offset;
	ping_token_t	token;

	offset = parse_flags(&token, ac, av);
	token.host = parse_host(token.flags, av + offset);
	return (token);
}
