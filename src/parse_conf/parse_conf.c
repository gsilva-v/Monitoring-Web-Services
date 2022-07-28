#include "monitoring.h"

// 3 fazer 3 funções de parseamento, 1 pra cada monitor 


int	count_http(char *file_conf){
	char *buffer = NULL;
	int http_counter = 0;
	size_t buffer_size = 0;
	FILE *fd = fopen(file_conf, "r");
	
	if (fd < 0){
		printf("Invalid config file, Try Another!\n");
		exit (1);
	}
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "HTTP")){
			http_counter++;
		}
	}
	fclose(fd);
	return (http_counter);
}

HTTP_Monitoring **parse_http(char *file_conf){

	char *buffer = NULL;
	char **conf = NULL; 
	int http_counter = 0;
	size_t buffer_size = 0;
	HTTP_Monitoring **ret = calloc(count_http(file_conf), sizeof(HTTP_Monitoring));
	FILE *fd = fopen(file_conf, "r");

	if (fd < 0){
		printf("Invalid config file, Try Another!\n");
		exit (1);
	}
	int i = 0;
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "HTTP")){
			ret[i] = calloc(1, sizeof(HTTP_Monitoring));
			conf = split(buffer, '\t');	
			// intra	HTTP	intra.42.fr	GET	200	120
			ret[i]->name = strdup(conf[0]);
			ret[i]->protocol = strdup(conf[1]);
			ret[i]->url = strdup(conf[2]);
			ret[i]->method = strdup(conf[3]);
			ret[i]->status = atoi(conf[4]);
			ret[i]->pause = atoi(conf[5]);
			ret[i]->last_monitoring = current_time();
			i++;
		}
	}
	fclose(fd);

	
	return ret;
}