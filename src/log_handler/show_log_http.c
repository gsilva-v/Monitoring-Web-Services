#include "monitoring.h"

static void	pretty_log_ok(HTTP_Monitoring *monitor, int status, char *stamp);
static void	pretty_log_ko(HTTP_Monitoring *monitor, int status, char *stamp);
static void	handle_log_error(HTTP_Monitoring *monitor, int status, char *stamp);
static void handle_log_success(HTTP_Monitoring *monitor, int status, char *stamp);

void	show_log_http(HTTP_Monitoring *monitor, int status){
	char	*stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(STATUS, (monitor->last_request_status == true ? OK : KOE), monitor->status);
	if (monitor->last_request_status == false)
		handle_log_error(monitor, status, stamp);
	else 
		handle_log_success(monitor, status, stamp);
}

static void	pretty_log_ok(HTTP_Monitoring *monitor, int status, char *stamp){
	if (!conf.simplified)
		dprintf(conf.log_fd, PHLOGOK, stamp,  monitor->name, monitor->url, \
			monitor->protocol, monitor->status, status, SUCCESS, monitor->latency);
	else 
		dprintf(conf.log_fd,  PHLOGS, stamp, monitor->name, monitor->protocol, SUCCESS);
}

static void	pretty_log_ko(HTTP_Monitoring *monitor, int status, char *stamp){
	if (!conf.simplified)
		dprintf(conf.error_log_fd, PHLOGKO, stamp,  monitor->name, monitor->url, \
			monitor->protocol, monitor->status, status, KO, monitor->latency);
	else 
		dprintf(conf.error_log_fd, PHLOGS, stamp, monitor->name, monitor->protocol, KO);
}

static void	handle_log_error(HTTP_Monitoring *monitor, int status, char *stamp){
	printf("Some error happened, see \'errors.log\' for more information\n");
	if (conf.pretty){
		dprintf(conf.error_log_fd, DIVL);
		pretty_log_ko(monitor, status, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.error_log_fd, HLOG, stamp,  monitor->name, monitor->url, \
			monitor->protocol, monitor->status, status, KO, monitor->latency);
		else 
			dprintf(conf.error_log_fd,  HLOGS, stamp, monitor->name, monitor->protocol, KO);
	}
}

static void handle_log_success(HTTP_Monitoring *monitor, int status, char *stamp){
	if (conf.pretty){
		dprintf(conf.log_fd, DIVL);
		pretty_log_ok(monitor, status, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.log_fd, HLOG, stamp,  monitor->name, monitor->url, \
			monitor->protocol, monitor->status, status, OK, monitor->latency);
		else 
			dprintf(conf.log_fd,  HLOGS, stamp, monitor->name, monitor->protocol, OK);
	}
}
