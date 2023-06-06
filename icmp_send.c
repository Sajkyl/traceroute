//Daniel Sarniak 322701
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

u_int16_t compute_icmp_checksum(const void *buff, int length) {
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}


void init_icmp_packet(struct icmp* icmp_header, int seq) {
    assert(icmp_header != NULL);
    icmp_header->icmp_type = ICMP_ECHO;
    icmp_header->icmp_code = 0;
    icmp_header->icmp_hun.ih_idseq.icd_id = getpid() & 0xFF;
    icmp_header->icmp_hun.ih_idseq.icd_seq = seq;
    icmp_header->icmp_cksum = 0;
    icmp_header->icmp_cksum = compute_icmp_checksum((u_int16_t*) icmp_header, sizeof(*icmp_header));
}

int send_packet(int sockfd, int seq, struct sockaddr_in *recipient) {

    struct icmp icmp_header;
    init_icmp_packet(&icmp_header, seq);

    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &seq, sizeof(int)) < 0)
        return -1;

    return sendto( sockfd, &icmp_header, sizeof(icmp_header),0,(struct sockaddr *) recipient, sizeof(*recipient) );
}