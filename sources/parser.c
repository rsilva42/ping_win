#include "parser.h"

/*pulls the associated value form a flag*/
int				pull_flag_val(int *offset, char **flag_str)
{
	int		val = 0;

	/*if value is in the same string*/
	if (flag_str[0][2])
		val = atoi(&flag_str[0][2]);
	/*if value is in the next string*/
	else if (flag_str[1])
	{
		val = atoi(flag_str[1]);
		*offset = 1;
	}
	return (val);
}

/*set flag in token and return an offset*/
int			get_flag(ping_token_t *token, char **flag_str)
{
	int		offset = 0;
	if (flag_str[0][1] == 'c')
	{
		token->flags |= PING_FLAG_C;
		if ((token->count = pull_flag_val(&offset, flag_str)) == 0)
			token->flags |= PING_FLAG_ERR;
	}
	else if (flag_str[0][1] == 't')
	{
		token->flags |= PING_FLAG_T;
		if ((token->ttl = pull_flag_val(&offset, flag_str)) == 0)
			token->flags |= PING_FLAG_ERR;
	}
	else
		token->flags |= PING_FLAG_ERR;
	return (offset);
}

int				parse_flags(ping_token_t *token, int argc, char **argv)
{
	int		i;

	for (i = 1; i < argc && argv[i][0] == '-'; i++)
	{
		i += get_flag(token, &argv[i]);
		if (token->flags & PING_FLAG_ERR)
			flag_parse_error(token);
	}
	return (i);
}

struct addrinfo *dns_lookup(char *domain)
{
	struct addrinfo	*host;
	struct addrinfo	hints = { 0 };
	int				gai_error;

	hints.ai_family = AF_INET;
	if ((gai_error = getaddrinfo(domain, NULL, &hints, &host)))
	{
		print_error(gai_strerror(gai_error));
		exit(EXIT_FAILURE);
	}

	return (host);
}

void	reverse_dns_lookup(char ip_buf[], size_t ip_buflen, struct addrinfo *host)
{
	int				gai_error;

	if ((gai_error = getnameinfo(host->ai_addr, host->ai_addrlen,
		ip_buf, ip_buflen, NULL, 0, NI_NUMERICHOST)))
	{
		print_error(gai_strerror(gai_error));
		exit(EXIT_FAILURE);
	}
}

void			parse_host(char host_ip[], size_t ip_buflen, char *hostname)
{
	struct addrinfo	*host;

	host = dns_lookup(hostname);

	reverse_dns_lookup(host_ip, ip_buflen, host);
	freeaddrinfo(host);
}

/*tokenizes user input*/
ping_token_t	*parse(int argc, char **argv)
{
	size_t			offset;
	ping_token_t	*token = malloc(sizeof(ping_token_t));

	offset = parse_flags(token, argc, argv);

	if (argv[offset] && argv[offset + 1])
		too_many_args_error();

	/*resolve destination ip*/
	parse_host(token->dest_ip, sizeof(token->dest_ip), argv[offset]);

	printf("connecting to %s ip: %s\n", argv[offset], token->dest_ip);
	return (token);
}
