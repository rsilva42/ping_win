#include "parser.h"

ping_tokens_t	parse(int ac, char **av)
{
	ping_flags_t	flags;
	ping_host_t	host; // may just be a string
	size_t		offset;
	ping_token_t	token;

	token.flags = parse_flags(*offset, ac, av);
	token.host = parse_host(flags, av + offset);
	return (token);
}
