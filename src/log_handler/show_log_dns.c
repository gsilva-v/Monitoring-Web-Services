#include "monitoring.h"

static void	pretty_log_ok(DNS_Monitoring *monitor, char *stamp);
static void	pretty_log_ko(DNS_Monitoring *monitor, char *stamp);
static void	handle_log_error(DNS_Monitoring *monitor, char *stamp);
static void handle_log_success(DNS_Monitoring *monitor, char *stamp);

void	show_log_dns(DNS_Monitoring *monitor){
	char	*stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(STATUSWD, (monitor->last_request_status == true ? OK : KOE));
	if (monitor->last_request_status == false)
		handle_log_error(monitor,  stamp);
	else 
		handle_log_success(monitor, stamp);
}

static void	pretty_log_ok(DNS_Monitoring *monitor, char *stamp){
	if (!conf.simplified)
		dprintf(conf.log_fd, PDLOGOK, stamp, monitor->name, monitor->url, monitor->protocol, monitor->latency);
	else 
		dprintf(conf.log_fd, PDLOGSOK, stamp, monitor->name, monitor->protocol);
}

static void	pretty_log_ko(DNS_Monitoring *monitor, char *stamp){
	if (!conf.simplified)
		dprintf(conf.error_log_fd, PDLOGKO, stamp, monitor->name, monitor->url, monitor->protocol, monitor->dns_server);
	else 
		dprintf(conf.error_log_fd, PDLOGSKO, stamp, monitor->name, monitor->protocol);
}

static void	handle_log_error(DNS_Monitoring *monitor, char *stamp){
	printf(FAIL);
	if (conf.pretty){
		dprintf(conf.error_log_fd, DIVL);
		pretty_log_ko(monitor, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.error_log_fd, DLOGKO, stamp, monitor->name, monitor->url, monitor->protocol, monitor->dns_server);
		else 
			dprintf(conf.error_log_fd, DLOGSKO, stamp, monitor->name, monitor->protocol);
	}
}

static void handle_log_success(DNS_Monitoring *monitor, char *stamp){
	if (conf.pretty){
		dprintf(conf.log_fd, DIVL);
		pretty_log_ok(monitor, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.log_fd, DLOGOK , stamp,  monitor->name, monitor->url, monitor->protocol, monitor->latency);
		else 
			dprintf(conf.log_fd, DLOGSOK, stamp, monitor->name, monitor->protocol);
	}
}
