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

	for (i = 1; i < ac && av[i][0] == '-'; i++)
	{
		get_flag(token, &av[i]);
		if (token->flags & PING_FLAG_ERR)
			flag_parse_error(token);
	}
	return (i);
}

struct addrinfo	*parse_host(char **av)
{
	struct addrinfo	*host_list; //Remember to free
	struct addrinfo	hints = { 0 };
	int				gai_error;

	printf("parsing host\n");

	if (av[0] && av[1])
		too_many_args_error();

	hints.ai_family = AF_INET;
	if ((gai_error = getaddrinfo(av[0], NULL, &hints, &host_list)))
		get_host_error(gai_strerror(gai_error));

	return (host_list);
}

ping_token_t	parse(int ac, char **av)
{
	size_t			offset;
	ping_token_t	token = { 0 };

	offset = parse_flags(&token, ac, av);
	token.host_list = parse_host(av + offset); //do i need the whole list?
	return (token);
}
