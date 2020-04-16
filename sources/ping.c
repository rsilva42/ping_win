#include "ping.h"

// todo: make global for the loop that gets set to zero when crtl c i pressed

// sets a connection and pings in a loop
void	ping(t_ping_info *info, t_ping_token token)
{
	t_ping_connect	connection;
	t_time		send_time, reply_time; //data type may change
	t_reply		reply;

	connection = connect(host);
	//signal_handler set up
	if (tokens.flags & PING_FLAG_N) //may change to work like sys ping
		while (token.count)
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
			num--;
		}
	else
		while (1)
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
		}
}
