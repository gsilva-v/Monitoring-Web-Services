#include "monitoring.h"

void	run(char *file_conf){
	HTTP_Monitoring	**http = parse_http(file_conf);
	PING_Monitoring	**ping = parse_ping(file_conf);
	DNS_Monitoring	**dns = parse_dns(file_conf);

	conf.log_fd = open("./logs/file.log", O_CREAT| O_RDWR | O_APPEND, 0777);
	if (conf.log_fd < 0)
			error_exit(LOGFAIL, 1);
	while (true){
		if (http && conf.http)
			http_manager(http);
		if (ping && conf.ping)
			ping_manager(ping);
		if (dns && conf.dns)
			dns_manager(dns);
	}
}
