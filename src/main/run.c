#include "monitoring.h"

int run(char *file_conf){
	HTTP_Monitoring **http = parse_http(file_conf);
	PING_Monitoring **ping = parse_ping(file_conf);
	DNS_Monitoring **dns = parse_dns(file_conf);

	log_file.log_fd = open("./logs/file.log", O_CREAT| O_RDWR | O_APPEND, 0777);
	if (log_file.log_fd < 0){
		printf("Error: Can't open log file!\n");
		exit(1);
	}
	while (true){
		if (http)
			http_manager(http);
		if (ping)
			ping_manager(ping);
		if (dns)
			dns_manager(dns);
	}
}
