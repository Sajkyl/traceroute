//Daniel Sarniak 322701
void translate_address(const char buffer[20], struct sockaddr_in* addr);
double avg_time(struct timeval* times, int n);
void print_route(int packets, char ip_str[][20], struct timeval *times);