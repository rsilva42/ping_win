#include "print.h"

void	print_reply(ping_packet_t reply, time_t rtt)
{
	(void)reply;
	(void)rtt;
	printf("printing reply info and rtt\n");
}

void	print_info(ping_info_t info)
{
	(void)info;
	printf("printing final info\n");
}
