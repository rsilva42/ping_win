#include "parser.h"

int				pull_flag_val(char **flag_str)
{
	int				val = 0;

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
	int				i;

	for (i = 1; i < ac && av[i][0] == '-'; i++)
	{
		get_flag(token, &av[i]);
		if (token->flags & PING_FLAG_ERR)
			flag_parse_error(token);
	}
	return (i);
}

struct addrinfo *dns_lookup(char *domain)
{
	struct addrinfo	*host; //Remember to free
	struct addrinfo	hints = { 0 };
	int				gai_error;

	hints.ai_family = AF_INET;
	if ((gai_error = getaddrinfo(domain, NULL, &hints, &host)))
		print_error(gai_strerror(gai_error));

	return (host);
}

void	reverse_dns_lookup(char ip_buf[], size_t ip_buflen, struct addrinfo *host)
{
	int				gai_error;

	if ((gai_error = getnameinfo(host->ai_addr, host->ai_addrlen,
		ip_buf, ip_buflen, NULL, 0, NI_NUMERICHOST)))
		print_error(gai_strerror(gai_error));
}

void			parse_host(char host_ip[], size_t ip_buflen, char **av)
{
	struct addrinfo	*host;

	printf("parsing host\n");

	if (av[0] && av[1])
		too_many_args_error();

	host = dns_lookup(av[0]);

	reverse_dns_lookup(host_ip, ip_buflen, host);
	freeaddrinfo(host);
}

/*tokenizes user input*/
ping_token_t	parse(int ac, char **av)
{
	size_t			offset;
	ping_token_t	token = { 0 };
	char			src_ip[NI_MAXHOST];



	offset = parse_flags(&token, ac, av);
	if (gethostname(src_name, sizeof(src_name)) < 0)
		print_error("error getting host name");
	parse_host(token.src_ip, sizeof(dest_ip), src_name)
	parse_host(token.dest_ip, sizeof(token.host_ip), av + offset);
	printf("host ip: %s\n", token.host_ip);
	return (token);
}
