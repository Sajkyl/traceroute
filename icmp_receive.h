//Daniel Sarniak 322701
#define MAX_TTL 30
#define WAIT_TIME 1
#define PACKETS_NUMBER 3

int receive(int pid, int sockfd, int max_time, int TTL, int max_packets, struct timeval* send_time);