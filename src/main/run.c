#include "monitoring.h"

int run(char *file_conf){
	HTTP_Monitoring **http = parse_http(file_conf);

	log_file.log_fd = open("./logs/file.log", O_RDWR | O_APPEND, 0777);
	if (log_file.log_fd < 0){
		printf("Error: Can't open log file!\n");
		exit(1);
	}
	while (true){
		http_manager(http);
		
	}
	

}
