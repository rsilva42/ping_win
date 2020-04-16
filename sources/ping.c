#include "ping.h"

int			ping_no_sigint = 1;

void		handle_sigint(int signal)
{
	if (signal == SIGINT)
		ping_no_sigint = 0;
}

ping_connect_t	connect(ping_token_t token)
{
	ping_connect_t	connection;

	(void)token;
	printf("connecting\n");
	return (connection);
}

void			send(ping_connect_t connection)
{
	(void)connection;
	printf("sending\n");
}

// sets a connection and pings in a loop
ping_info_t		ping(ping_token_t token)
{
	ping_info_t		info;
	ping_connect_t	connection;
	time_t			send_time, reply_time; //data type may change
	ping_reply_t	reply;

	connection = connect(token);
	signal(SIGINT, handle_sigint);
	while (ping_no_sigint)
	{
		send(connection);
		info->sent_count++;
		send_time = get_time();
		if ((reply = listen(connection)) != NULL)
		{
			reply_time = get_time();
			info->recv_count++;
		}
		print_ping(info, reply, reply_time - send_time);
		if (flags & PING_FLAG_N)
			token.count--;
		if (!token.count)
			break;
	}
}
