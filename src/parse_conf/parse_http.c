#include "monitoring.h"

static int	count_http(char *file_conf);
static HTTP_Monitoring *set_config(char **conf);
static bool	check_line(char **line);

HTTP_Monitoring	**parse_http(char *file_conf){
	char			*buffer = NULL;
	char			**conf = NULL; 
	int				i = 0, count = count_http(file_conf);
	size_t			buffer_size = 0;
	HTTP_Monitoring	**ret = calloc(count, sizeof(HTTP_Monitoring));
	FILE			*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	if (count == 0)
		return NULL;
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "HTTP")){
			conf = split(buffer, '\t');	
			if (check_line(conf) == false){
				free_matrix(conf);
				error_exit(INVTABS, 1);
			}
			ret[i] = set_config(conf);
			free_matrix(conf);
			i++;
		}
	}
	fclose(fd);
	return ret;
}

static int	count_http(char *file_conf){
	char	*buffer = NULL;
	int		http_counter = 0;
	size_t	buffer_size = 0;
	FILE	*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "HTTP"))
			http_counter++;
	}
	fclose(fd);
	return (http_counter);
}

static HTTP_Monitoring	*set_config(char **conf){
	HTTP_Monitoring	*ret = calloc(1, sizeof(HTTP_Monitoring));

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
	if (matrix_len(line) != 6)
		return false;
	return true;
}
