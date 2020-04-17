#include "ping.h"

int			ping_no_sigint = 1;

void		handle_sigint(int signal)
{
	if (signal == SIGINT)
		ping_no_sigint = 0;
}

ping_connect_t	ping_connect(ping_token_t token)
{
	ping_connect_t	connection;

	(void)token;
	connection.ip = 0;
	connection.icmp = 0;
	printf("connecting\n");
	return (connection);
}

time_t			get_time()
{
	printf("getting the time\n");
	return (0);
}

void			ping_send(ping_connect_t connection)
{
	(void)connection;
	printf("sending\n");
}

ping_reply_t	ping_listen(ping_connect_t connection)
{
	ping_reply_t	reply;

	(void)connection;
	reply.error = 0;
	reply.packet = 0;
	printf("listening\n");
	sleep(1);
	return(reply);
}

/*sets a connection and pings in a loop*/
ping_info_t		ping(ping_token_t token)
{
	ping_info_t		info;
	ping_connect_t	connection;
	time_t			send_time, reply_time; //data type may change
	ping_reply_t	reply;

	connection = ping_connect(token);
	signal(SIGINT, handle_sigint);
	while (ping_no_sigint)
	{
		ping_send(connection);
		info.sent_count++;
		send_time = get_time();
		reply = ping_listen(connection);
		if (!reply.error)
		{
			reply_time = get_time();
			info.recv_count++;
		}
		print_reply(reply, reply_time - send_time);
		//move relevant reply data into info
		if (token.flags & PING_FLAG_C)
			token.count--;
		if (!token.count)
			break;
	}
	return (info);
}
