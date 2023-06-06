//Daniel Sarniak 322701
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include "icmp_send.h"
#include "icmp_receive.h"
#include "utils.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "As argument provide only IP address\n");
        return EXIT_FAILURE;
    }

    struct sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;

    translate_address(argv[1], &recipient);


	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "Socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    int pid = getpid() & 0xFF;

    for (int ttl = 1; ttl <= MAX_TTL; ttl++) {
        struct timeval send_time;
        gettimeofday(&send_time, NULL);

        for (int j = 0; j < PACKETS_NUMBER; j++)
            if (send_packet(sockfd, ttl, &recipient) < 0) {
                fprintf(stderr, "Send error: %s\n", strerror(errno));
                return EXIT_FAILURE;
            }

        int result = receive(pid, sockfd, WAIT_TIME , ttl, PACKETS_NUMBER, &send_time);

        if (result < 0) {
            fprintf(stderr, "Recive error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        else if (result == 1) 
            break;
    }

    close(sockfd);
    return EXIT_SUCCESS;
}