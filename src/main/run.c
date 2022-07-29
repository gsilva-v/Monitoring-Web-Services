#include "monitoring.h"
HTTP_Monitoring **http;
PING_Monitoring **ping;

void free_matrix(char **m){
	if (m == NULL)
		return ;
	for (int i = 0; m[i]; i++)
		free(m[i]);
	free(m);
}

int run(char *file_conf){
	http = parse_http(file_conf);
	ping = parse_ping(file_conf);
	log_file.log_fd = open("./logs/file.log", O_RDWR | O_APPEND, 0777);
	if (log_file.log_fd < 0){
		printf("Error: Can't open log file!\n");
		exit(1);
	}
	while (true){
		if (http)
			http_manager(http);
		if (ping)
			ping_manager(ping);
		
	}
}
