#include "monitoring.h"

static bool	http_flag(char *flag){
	if (!strcmp(flag, FHTTPOFF))
		conf.http = false;
	else if (!strcmp(flag, FHTTPON))
		conf.http = true;
	else
		return false;
	return true;
}

static bool	ping_flag(char *flag){
	if (!strcmp(flag, FPINGOFF))
		conf.ping = false;
	else if (!strcmp(flag, FPINGON))
		conf.ping = true;
	else
		return false;
	return true;
}

static bool	dns_flag(char *flag){
	if (!strcmp(flag, FDNSOFF))
		conf.dns = false;
	else if (!strcmp(flag, FDNSON))
		conf.dns = true;
	else
		return false;
	return true;
}

static bool	beautify_checker(char *flag){
	if (!strcmp(flag, FSIMP) || !strcmp(flag, FS)){
		conf.simplified = true;
		return true;
	} else if (strstr(flag, PRETTY)){
		conf.pretty = true;
		return true;
	}
	return false;
}

static bool help_checker(char *flag){
	if (!strcmp(flag, FHELP))
		error_exit(HELP, 1);
	else if (strstr(flag, TIMES)){
		char **times = split(flag, '=');
		if (matrix_len(times) != 2)
			error_exit(INVOPT, 1);
		conf.times = atoi(times[1]);
		free_matrix(times);
		return true;
	}
	return false;
}

static void	protocol_checker(char *flag){
	if (strstr(flag, FHTTP)){
		if (!http_flag(flag))
			error_exit(INVOPT, 1);
	} else if (strstr(flag, FPING)){
		if (!ping_flag(flag))
			error_exit(INVOPT, 1);
	} else if (strstr(flag, FDNS)){
		if(!dns_flag(flag))
			error_exit(INVOPT, 1);
	} else if (flag[0] == '-')
			error_exit(INVOPT, 1);
}

static void initialize_conf(void){
	conf.simplified = false;
	conf.times = 0;
	conf.pretty = false;
	conf.http = true;
	conf.ping = true;
	conf.dns = true;
	conf.log_fd = open("./logs/success.log", O_CREAT| O_RDWR | O_APPEND, 0777);
	conf.error_log_fd = open("./logs/errors.log", O_CREAT | O_APPEND | O_RDWR, 0777);
	if (conf.log_fd < 0 || conf.error_log_fd < 0)
			error_exit(LOGFAIL, 1);
}

void	check_flags(char **args){
	initialize_conf();
	for(int i = 0; args[i]; i++){
		if (beautify_checker(args[i]) || help_checker(args[i]))
			continue ;
		protocol_checker(args[i]);
	}
	if (conf.ping == false && conf.http == false && conf.dns == false)
		error_exit(WITHOUTPROTOCOL, 6);
}

char	*find_conf(char **args){
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], DBEXT))
			return args[i];
	}
	return NULL;
}
