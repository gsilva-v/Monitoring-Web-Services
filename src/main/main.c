#include "monitoring.h"

t_conf	conf;

int	main(int argc, char **argv){
	if (argc < 2){
		printf(MISSARG);
		exit(1);
	}
	check_flags(argv);
	char *conf_file = find_conf(argv);
	if (conf_file)
		run(conf_file);
	else
		printf(MISSARG);
	return 0;
}
