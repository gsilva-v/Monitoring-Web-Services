#include "monitoring.h"

void check_flags(char **args){
	log_file.simplified = false;
	for(int i = 0; args[i]; i++){
		if (strstr(args[i], "--simplify")){
			log_file.simplified = true;
		} else if (strstr(args[i], "--help")){
			printf("Web Monitor: use ./monitoring [file config] [flags]\nAccepted flags: \n--simplify : will simplify the generated log\n");
			exit(1);
		} else if (strstr(args[i], "-")){
			printf("Sintax error: Invalid flags or option; %s\nUse \"--help\" to see how to use command\n", args[i]);
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
