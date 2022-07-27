#include "monitoring.h"

int main(int argc, char const *argv[])
{
	if (argc != 2){
		printf("Need one config file: conf/monitoring.db");
		exit(1);
	}

	HTTP_Monitoring monitoring;

	monitoring.method;

	return 0;
}
