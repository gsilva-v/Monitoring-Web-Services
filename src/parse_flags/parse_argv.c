#include "monitoring.h"

static	void initialize_conf(void);

void	check_flags(char **args){
	initialize_conf();
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], FSIMP) || strstr(args[i], FS))
			conf.simplified = true;
		else if (strstr(args[i], FHELP))
			error_exit(HELP,1);
		else if (strstr(args[i], FHTTP)){
			if (strstr(args[i], FHTTPOFF))
				conf.http = false;
			else if (strstr(args[i], FHTTPON))
				conf.http = true;
			else 
				goto stop;
		} else if (strstr(args[i], FPING)){
			if (strstr(args[i], FPINGOFF))
				conf.ping = false;
			else if (strstr(args[i], FPINGON))
				conf.ping = true;
			else 
				goto stop;
		} else if (strstr(args[i], FDNS)){
			if (strstr(args[i], FDNSOFF))
				conf.dns = false;
			else if (strstr(args[i], FDNSON))
				conf.dns = true;
			else 
				goto stop;
		} else if (strstr(args[i], PRETTY))
			conf.pretty = true;
		else if (strstr(args[i], "-"))
			goto stop;
	}
	return ;
	stop : error_exit(INVOPT, 1);
}

char	*find_conf(char **args){
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], DBEXT))
			return args[i];
	}
	return NULL;
}

static	void initialize_conf(void){
	conf.simplified = false;
	conf.pretty = false;
	conf.http = true;
	conf.ping = true;
	conf.dns = true;
}