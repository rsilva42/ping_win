#include "ping.h"

int			ping_no_sigint = 1;

void			handle_sigint(int signal)
{
	if (signal == SIGINT)
		ping_no_sigint = 0;
}

int				ping_create_socket(void)
{
	int			socket_fd;
	int			set = 1;

	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		print_error("error creating socket");
	if (setsockopt(socket_fd, IPPROTO_IP, IP_HDRINCL, &set, sizeof(set)) < 0)
		print_error("error setting socket options");
	return (socket_fd);
}

void			set_ip_header(ping_token_t *token, ping_packet_t *packet)
{
	struct ip	*header = packet->ip_header;

	header->ip_v = 4;
	header->ip_hl = 5;
	header->ip_tos = 0;
	header->ip_len = htons(sizeof(packet->buffer));
	header->ip_id = htons(1111);
	header->ip_off = htons(0);
	header->ip_ttl = 255;
	header->ip_p = IPPROTO_IP;
	header->ip_sum = 0;
	inet_aton(token->src_ip, &header->ip_src);
	inet_aton(token->dest_ip, &header->ip_dst);
}

void			set_icmp_header(struct icmp *header)
{
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_id = 1001;
	header->icmp_seq = 0;
}

void			ping_create_packet(ping_token_t *token, ping_packet_t *packet)
{
	memset(packet, 0, sizeof(ping_packet_t));
	packet->ip_header = (struct ip *)packet->buffer;
	packet->icmp_header = (struct icmp *)(packet->ip_header + 1);

	set_ip_header(token, packet);
	set_icmp_header(packet->icmp_header);
	//to do: make sure that the headers are right, implment checksum,
	//implement sendto and recvfrom, print output, error check (ex check if root),
	//peer review, check formatting
}

time_t			get_time()
{
	printf("getting the time\n");
	return (0);
}

void			ping_send(int socket_fd)
{
	(void)socket_fd;
	printf("sending\n");
}

ping_reply_t	ping_listen(int socket_fd)
{
	ping_reply_t	reply;

	(void)socket_fd;
	reply.error = 0;
	reply.packet = 0;
	printf("listening\n");
	sleep(1);
	return(reply);
}

/*sets finds destination's ip and pings it in a loop*/
ping_info_t		ping(ping_token_t *token)
{
	int				socket_fd;
	ping_packet_t	send_packet;
	time_t			send_time, reply_time; //data type may change
	ping_reply_t	reply;
	ping_info_t		info;

	socket_fd = ping_create_socket();
	ping_create_packet(token, &send_packet);

	signal(SIGINT, handle_sigint);
	while (ping_no_sigint)
	{
		ping_send(socket_fd);
		info.sent_count++;
		send_time = get_time();
		reply = ping_listen(socket_fd);
		if (!reply.error)
		{
			reply_time = get_time();
			info.recv_count++;
		}
		print_reply(reply, reply_time - send_time);
		//move relevant reply data into info
		if (token->flags & PING_FLAG_C)
		{
			token->count--;
			if (!token->count)
				break;
		}
	}
	return (info);
}
