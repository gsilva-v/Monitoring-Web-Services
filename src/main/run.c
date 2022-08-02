#include "monitoring.h"

void	run(char *file_conf){
	HTTP_Monitoring	**http = parse_http(file_conf);
	PING_Monitoring	**ping = parse_ping(file_conf);
	DNS_Monitoring	**dns = parse_dns(file_conf);
	int	times = 0;

	while (true){
		if (http && conf.http)
			times += http_manager(http);
		if (ping && conf.ping)
			times += ping_manager(ping);
		if (dns && conf.dns)
			times += dns_manager(dns);
		if (conf.times != 0 && times == conf.times)
			break;

	}
}
