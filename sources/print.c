#include "common.h"

void	print_reply(ping_packet_t *reply, uint64_t rtt)
{
	/*set packet pinters*/
	reply->ip_header = (struct ip *)reply->buffer;
	reply->icmp_header = (struct icmp *)(reply->ip_header + 1);

	printf("icmp_seq=%d ttl=%d time=%2.02fms\n",
			reply->icmp_header->icmp_seq, reply->ip_header->ip_ttl,
			rtt / 1000000.0);	
}

void	print_info(ping_info_t info)
{
	float		sent_float = (float)info.sent_count;
	float		recv_float = (float)info.recv_count;

	/*print information at the end of program*/
	/*if info sent is zero, divide by one instead*/
	printf("packets sent: %ld, packets received: %ld, %.2f%% packet loss\n",
			info.sent_count, info.recv_count,
			((sent_float - recv_float) / (sent_float > 1.0 ? sent_float : 1.0)) * 10);
}
