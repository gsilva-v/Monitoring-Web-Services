#include "monitoring.h"

int main(int argc, char **argv)
{
	if (argc != 2){
		printf("Need one config file: conf/monitoring.db");
		exit(1);
	}
	run(argv[1]);

	

	return 0;
}
