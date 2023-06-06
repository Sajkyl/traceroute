//Daniel Sarniak 322701
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

void translate_address(const char buffer[20], struct sockaddr_in* addr) {
    if (inet_pton(AF_INET, buffer, &addr->sin_addr) != 1) {
        fprintf(stderr, "IP address error\n");
        exit(EXIT_FAILURE);
    }
}


void print_time(struct timeval* time, int n) {
	double avg = 0;
	for (int i = 0; i < n; i++)
		avg += time[i].tv_usec + 1000000 * time[i].tv_sec;
	avg /= n * 1000;
	printf("%.2fms\n", avg);
}

void print_route(int packets, char ip_str[][20], struct timeval *time) {
    if (packets == 0) {
        printf("*\n");
        return;
    }

    if (packets >= 1) printf("%s ", ip_str[0]);

    if (packets >= 2 && strcmp(ip_str[0], ip_str[1]) != 0)
        printf("%s ", ip_str[1]);

    if (
		packets >= 3 &&
		strcmp(ip_str[0], ip_str[1]) != 0 &&
		strcmp(ip_str[0], ip_str[2]) != 0
	) printf("%s ", ip_str[2]);

    if (packets == 3) print_time(time, packets);
    else printf("???\n");
}