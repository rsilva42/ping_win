#include "parser.h"

int				pull_flag_val(char **flag_str)
{
	int		val = 0;

	if (flag_str[0][2])
		val = atoi(&flag_str[0][2]);
	else if (flag_str[1])
		val = atoi(flag_str[1]);
	return (val);
}

void			get_flag(ping_token_t *token, char **flag_str)
{
	if (flag_str[0][1] == 'c')
	{
		token->flags |= PING_FLAG_C;
		if ((token->count = pull_flag_val(flag_str)) == 0)
			token->flags |= PING_FLAG_ERR;
	}
	else if (flag_str[0][1] == 't')
	{
		token->flags |= PING_FLAG_T;
		if ((token->ttl = pull_flag_val(flag_str)) == 0)
			token->flags |= PING_FLAG_ERR;
	}
	else
		token->flags |= PING_FLAG_ERR;
}

int				parse_flags(ping_token_t *token, int ac, char **av)
{
	int		i;
	printf("parsing flags\n");
	for (i = 1; i < ac && av[i][0] == '-'; i++)
	{
		get_flag(token, &av[i]);
		if (token->flags & PING_FLAG_ERR)
			flag_parse_error(token);
	}
	return (i);
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
	ping_token_t	token = { 0 };

	offset = parse_flags(&token, ac, av);
	token.host = parse_host(token.flags, av + offset);
	return (token);
}
