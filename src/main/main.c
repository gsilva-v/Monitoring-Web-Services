#include "monitoring.h"

t_log	log_file;

int main(int argc, char **argv)
{
	if (argc < 2){
		exit(1);
	}
	check_flags(argv);
	char *conf_file = find_conf(argv);
	if (conf_file)
		run(conf_file);
	else
		printf("Need one config file: conf/monitoring.db");
	return 0;
}
