#include "monitoring.h"

static void	dns_handler(DNS_Monitoring *monitor);

static bool has_awake(DNS_Monitoring **monitor){
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 ){
			return true;
		}
	}
	return false;
}

static void	show_log(DNS_Monitoring *monitor){
	char *stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf("\033[0mStatus: %s\033[0m\n\n", (monitor->last_request_status == true ? OK : KOE));
	if (!log_file.simplified){
		dprintf(log_file.log_fd, DLOG, stamp, monitor->name, monitor->url, monitor->protocol,\
			(monitor->last_request_status == true ? SUCCESS : FAILED), monitor->latency);
	} else {
		dprintf(log_file.log_fd, DLOGS, stamp, monitor->name, monitor->protocol,\
			(monitor->last_request_status == true ? SUCCESS : KO));
	}
}

void	dns_manager(DNS_Monitoring **monitor){
	int	i = 0;
	static int first = 1;

	if (has_awake(monitor) || first == 1)
		printf("DNS routine started: checking necessary requests ...\n");
	else
		return ;
	while (monitor[i]){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			dns_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
			// if (monitor[i + 1] == NULL)
		}
		i++;
	}
				printf(FROUTINE);
	first = 0;
}

static void	dns_handler(DNS_Monitoring *monitor){
	int fd = open("./logs/dns.log", O_CREAT | O_TRUNC | O_RDWR , 0777);
	int _stdout = dup(STDOUT_FILENO);
	long	finish_time, init_time = current_time();
	
	if (fd < 0){
		printf("nao criou o arquivo\n");
		exit (1);
	}

	dup2(fd, STDOUT_FILENO);
	int ret = system(monitor->query);
	dup2(_stdout, STDOUT_FILENO);
	finish_time = current_time();
	if (ret != 0){
		monitor->last_request_status = false;
	} else 
		monitor->last_request_status = true;
	monitor->latency = (finish_time - init_time) / 10.0f; 
	show_log(monitor);
	close(fd);
	unlink("./logs/dns.log");
}
