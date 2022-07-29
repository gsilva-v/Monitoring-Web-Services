#include "monitoring.h"

void check_flags(char **args){
	log_file.simplified = false;
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], "--simplify")){
			log_file.simplified = true;
		} else if (strstr(args[i], "--help")){
			printf(HELP);
			exit(1);
		} else if (strstr(args[i], "-")){
			printf(INVUSE, args[i]);
			exit(1);	
		}
	}
}

char *find_conf(char **args){
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], ".db")){
			return args[i];
		}
	}
	return NULL;
}
