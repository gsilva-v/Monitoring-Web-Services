#include "monitoring.h"

static int	count_http(char *file_conf){
	char *buffer = NULL;
	int http_counter = 0;
	size_t buffer_size = 0;
	FILE *fd = fopen(file_conf, "r");

	if (fd < 0){
		printf(INVCONF);
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

static HTTP_Monitoring *set_config(char **conf){
	HTTP_Monitoring *ret = calloc(1, sizeof(HTTP_Monitoring));

	ret->name = strdup(conf[0]);
	ret->protocol = strdup(conf[1]);
	ret->url = strdup(conf[2]);
	ret->method = strdup(conf[3]);
	ret->status = atoi(conf[4]);
	ret->pause = atoi(conf[5]);
	ret->last_monitoring = current_time();
	return ret;
}

static bool	check_line(char **line){
	if (matrix_len(line) != 6){
		printf(INVTABS);
		return false;
	}	
	return true;
}

HTTP_Monitoring **parse_http(char *file_conf){
	char *buffer = NULL;
	char **conf = NULL; 
	int http_counter = 0, i = 0;
	size_t buffer_size = 0;
	HTTP_Monitoring **ret = calloc(count_http(file_conf), \
		sizeof(HTTP_Monitoring));
	FILE *fd = fopen(file_conf, "r");

	if (fd < 0){
		printf(INVCONF);
		exit (1);
	}
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "HTTP")){
			conf = split(buffer, '\t');	
			if (check_line(conf) == false)
				exit(1);
			ret[i] = set_config(conf);
			i++;
		}
	}
	fclose(fd);
	return ret;
}
