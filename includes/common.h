#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>	/*size_t, exit*/
#include <unistd.h>	/*write, gethostname, sleep*/
#include <netdb.h>	/*NI_MAXHOST*/

#include <stdio.h>	/*printf*/

/*bit flags, used with '|' to set and '&' to check true or flase*/
#define PING_FLAG_ERR	1
#define PING_FLAG_C 	2
#define PING_FLAG_T 	4

#define PING_PACKET_SIZE	64

typedef struct	ping_token_s
{
	size_t			flags;
	size_t			count;
	size_t			ttl;
	char			src_ip[NI_MAXHOST];
	char			dest_ip[NI_MAXHOST];
}					ping_token_t;

typedef struct	ping_packet_s
{
	char		buffer[PING_PACKET_SIZE];
	struct ip	*ip_header;
	struct icmp	*icmp_header;
}				ping_packet_t;

typedef struct		ping_info_s
{
	size_t			sent_count;
	size_t			recv_count;
	// a lot of other info yet to implement
}					ping_info_t;

#endif
