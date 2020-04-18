#include "ping.h"

int			ping_no_sigint = 1;

void			handle_sigint(int signal)
{
	if (signal == SIGINT)
		ping_no_sigint = 0;
}

int				create_socket(ping_token_t token)
{
	int			socket_fd;
	int			set = 1;

	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		print_error("error creating socket");
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &set, sizeof(set)) < 0)
		print_error("error setting socket options");
	return (socket_fd);
}

void			set_ip_header(struct ip *header)
{
	header->ip_v = 4;
	header->ip_hl = 5;
	header->ip_tos = 0;
	header->ip_len = htons(sizeof(packet->buffer));
	header->ip_id = htons(1111);
	header->ip_off = htons(0);
	header->ip_ttl = 255;
	header->ip_p = IPPROTO_IP;
	header->ipsum = 0;
}

void			set_icmp_header(struct icmp *header)
{
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_id = 1001;
	header->icmp_seq = 0;
}

void			create_packet(ping_packet_t *packet)
{
	memset(packet, 0, sizeof(packet));
	packet->ip_header = buffer;
	packet->icmp_header = ip_header + 1;

	set_ip_header(ip_header);
	set_icmp_header(icmp_header);
}

time_t			get_time()
{
	printf("getting the time\n");
	return (0);
}

void			ping_send(ping_token_t connection)
{
	(void)connection;
	printf("sending\n");
}

ping_reply_t	ping_listen(ping_token_t connection)
{
	ping_reply_t	reply;

	(void)connection;
	reply.error = 0;
	reply.packet = 0;
	printf("listening\n");
	sleep(1);
	return(reply);
}

/*sets finds destination's ip and pings it in a loop*/
ping_info_t		ping(ping_token_t token)
{
	int				ping_socketfd;
	ping_packet_t	send_packet;
	time_t			send_time, reply_time; //data type may change
	ping_reply_t	reply;
	ping_info_t		info;

	ping_socketfd = create_socket(token);
	create_packet(&send_packet); //<-working here, need ip_src and ip_dst from inet_aton()
//left of here, past this is pseudocode
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
		{
			token.count--;
			if (!token.count)
				break;
		}
	}
	return (info);
}
