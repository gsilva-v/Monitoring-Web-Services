#include "monitoring.h"

static void	dns_handler(DNS_Monitoring *monitor);
static bool has_awake(DNS_Monitoring **monitor);

void	dns_manager(DNS_Monitoring **monitor){
	static int	first = 1;

	if (!(has_awake(monitor) || first == 1))
		return ;
	printf(DNSR);
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			dns_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
		}
	}
	printf(FROUTINE);
	first = 0;
}

static bool has_awake(DNS_Monitoring **monitor){
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000)
			return true;
	}
	return false;
}

static void	show_log(DNS_Monitoring *monitor){
	char	*stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(STATUSWD, (monitor->last_request_status == true ? OK : KOE));
	if (!conf.simplified)
		dprintf(conf.log_fd, DLOG, stamp, monitor->name, monitor->url, monitor->protocol, \
			(monitor->last_request_status == true ? SUCCESS : FAILED), monitor->latency);
	else 
		dprintf(conf.log_fd, DLOGS, stamp, monitor->name, monitor->protocol, \
			(monitor->last_request_status == true ? SUCCESS : KO));
}

static void	dns_handler(DNS_Monitoring *monitor){
	int		fd = open("./logs/dns.log", O_CREAT | O_TRUNC | O_RDWR , 0777);
	int		_stdout = dup(STDOUT_FILENO);
	long	finish_time, init_time = current_time();
	
	if (fd < 0)
		error_exit(FDNSH, 1);
	dup2(fd, STDOUT_FILENO);
	int		ret = system(monitor->query);
	finish_time = current_time();
	dup2(_stdout, STDOUT_FILENO);
	monitor->last_request_status = true;
	if (ret != 0)
		monitor->last_request_status = false;
	monitor->latency = (finish_time - init_time) / 10.0f; 
	show_log(monitor);
	close(fd);
	unlink("./logs/dns.log");
}
