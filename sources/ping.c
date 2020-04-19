#include "ping.h"

int			ping_no_sigint = 1;

void			handle_sigint(int signal)
{
	if (signal == SIGINT)
		ping_no_sigint = 0;
}

time_t			get_time()
{
	printf("getting the time\n");
	return (0);
}

int				ping_create_socket(void)
{
	int			socket_fd;
	int			set = 1;

	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		print_error("error creating socket");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(socket_fd, IPPROTO_IP, IP_HDRINCL, &set, sizeof(set)) < 0)
	{
		print_error("error setting socket options");
		exit(EXIT_FAILURE);
	}
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
	//to do: make sure that the headers are right,
	//print output, error check (ex check if root),
	//peer review, check formatting
}

void			set_dest_addr(struct sockaddr_in *dest_addr, struct in_addr dest_ip)
{
	dest_addr->sin_family = AF_INET;
	dest_addr->sin_port = htons(0);
	dest_addr->sin_addr = dest_ip;
}

u_short	packet_checksum(u_short *ptr, size_t len)
{
	int			sum = 0;
	u_short		result = 0;

	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
		sum += *(u_char *)ptr;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	result = ~sum;

	return (result);
}

int				ping_send(int socket_fd, ping_packet_t *packet, struct sockaddr_in *destaddr)
{
	u_short		*ip_sum = &packet->ip_header->ip_sum;
	u_short		*icmp_sum = &packet->icmp_header->icmp_cksum;

	printf("sending\n");

	*icmp_sum = 0;
	*ip_sum = packet_checksum((u_short *)(packet->buffer), packet->ip_header->ip_hl);
	*icmp_sum = packet_checksum((u_short *)(packet->icmp_header),
								sizeof(packet->buffer) - sizeof(struct icmp));

	if (sendto(socket_fd, packet->buffer, sizeof(packet->buffer), 0,
				(struct sockaddr *)destaddr, sizeof(*destaddr)) < 0)
	{
		print_error("error sending packet\n");
		return (1);
	}
	return (0);
}


int				ping_listen(int socket_fd, fd_set *select_fd,
							ping_packet_t *packet, struct sockaddr_in *destaddr)
{
	struct timeval	time;
	int				select_ret, recv_len;
	socklen_t		dest_len = sizeof(*destaddr);

	printf("listening\n");

	time.tv_sec = PING_TIMEOUT;
	time.tv_usec = 0;

	select_ret = select(socket_fd + 1, select_fd, NULL, NULL, &time);

	/*for debug, will probably remove the printfs*/
	if (select_ret < 0)
	{
		printf("select error\n");
		return (1);
	}
	else if (select_ret > 0)
	{
		recv_len = recvfrom(socket_fd, packet->buffer, sizeof(packet->buffer),
								0, (struct sockaddr *)destaddr, &dest_len);
		if (recv_len < 0)
		{
			printf("recvfrom error\n");
			return (1);
		}
		else
			printf("received %d bytes\n", recv_len);
	}
	else
	{
		printf("timed out\n");
		return (1);
	}

	/*return zero on success*/
	return(0);
}

/*sets finds destination's ip and pings it in a loop*/
ping_info_t		ping(ping_token_t *token)
{
	int					socket_fd;
	ping_packet_t		send_packet;
	struct sockaddr_in	dest_sockaddr;
	fd_set				select_fd;
	ping_packet_t		reply_packet;
	//below initializations are from the pseudocode
	time_t			send_time, reply_time; //data type may change
	ping_info_t		info;

	socket_fd = ping_create_socket();
	ping_create_packet(token, &send_packet);
	set_dest_addr(&dest_sockaddr, send_packet.ip_header->ip_dst);

	signal(SIGINT, handle_sigint);
	while (ping_no_sigint)
	{
		FD_ZERO(&select_fd);
		FD_SET(socket_fd, &select_fd);

		if (ping_send(socket_fd, &send_packet, &dest_sockaddr))
		{
			sleep(PING_TIMEOUT);
			continue;
		}
		info.sent_count++;
		send_time = get_time();

		if (!ping_listen(socket_fd, &select_fd,
						&reply_packet, &dest_sockaddr))
		{
			reply_time = get_time();
			info.recv_count++;
			print_reply(reply_packet, reply_time - send_time);
		}
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
