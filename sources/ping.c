#include "ping.h"

int			no_sigint = 1;

void		handle_sigint(int signal)
{
	if (signal == SIGINT)
		no_sigint = 0;
}

// sets a connection and pings in a loop
ping_info_t	ping(ping_token_t token)
{
	ping_info_t		info;
	ping_connect_t	connection;
	time_t			send_time, reply_time; //data type may change
	reply_t			reply;

	connection = connect(host);
	//signal_handler set up
	while (no_sigint)
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
