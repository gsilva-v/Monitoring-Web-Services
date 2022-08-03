#include "monitoring.h"

static void	pretty_log_ok(PING_Monitoring *monitor, char *stamp);
static void	pretty_log_ko(PING_Monitoring *monitor, char *stamp);
static void	handle_log_error(PING_Monitoring *monitor, char *stamp);
static void	handle_log_success(PING_Monitoring *monitor, char *stamp);

void	show_log_ping(PING_Monitoring *monitor){
	char	*stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(STATUSWD, (monitor->last_request_status == true ? OK : KOE));
	if (monitor->last_request_status == false)
		handle_log_error(monitor, stamp);
	else
		handle_log_success(monitor, stamp);
}

static void	pretty_log_ok(PING_Monitoring *monitor, char *stamp){
	if (!conf.simplified)
		dprintf(conf.log_fd, PPLOGOK, stamp, monitor->name, monitor->url, \
			monitor->protocol, monitor->latency);
	else
		dprintf(conf.log_fd, PPLOGSOK, stamp, monitor->name, monitor->latency);
}

static void	pretty_log_ko(PING_Monitoring *monitor, char *stamp){
	if (!conf.simplified)
		dprintf(conf.error_log_fd, PPLOGKO, stamp, monitor->name, monitor->url, \
			monitor->protocol, monitor->latency);
	else
		dprintf(conf.error_log_fd, PPLOGSKO, stamp, monitor->name, monitor->protocol);
}

static void	handle_log_error(PING_Monitoring *monitor, char *stamp){
	printf(FAIL);
	if (conf.pretty){
		dprintf(conf.error_log_fd, DIVL);
		pretty_log_ko(monitor, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.error_log_fd, PLOGKO, stamp, monitor->name, monitor->protocol);
		else 
			dprintf(conf.error_log_fd, PLOGSKO, stamp, monitor->name, monitor->protocol);
	}
}

static void	handle_log_success(PING_Monitoring *monitor, char *stamp){
	if (conf.pretty){
		dprintf(conf.log_fd, DIVL);
		pretty_log_ok(monitor, stamp);
	} else {
		if (!conf.simplified)
			dprintf(conf.log_fd, PLOGOK , stamp, monitor->name, monitor->url, \
			monitor->protocol, monitor->latency);
		else
			dprintf(conf.log_fd, PLOGSOK , stamp, monitor->name, monitor->latency);
	}
}
