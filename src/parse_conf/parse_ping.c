#include "monitoring.h"

static int	count_ping(char *file_conf);
static PING_Monitoring *set_config(char **conf);
static bool	check_line(char **line);

PING_Monitoring **parse_ping(char *file_conf){
	char			*buffer = NULL;
	char			**conf = NULL; 
	int				i = 0;
	size_t			buffer_size = 0;
	PING_Monitoring	**ret = calloc(count_ping(file_conf), \
		sizeof(PING_Monitoring));
	FILE			*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "PING")){
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

static int	count_ping(char *file_conf){
	char	*buffer = NULL;
	int		ping_counter = 0;
	size_t	buffer_size = 0;
	FILE	*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "PING"))
			ping_counter++;
	}
	fclose(fd);
	return (ping_counter);
}

static PING_Monitoring *set_config(char **conf){
	PING_Monitoring	*ret = calloc(1, sizeof(PING_Monitoring));

	ret->name = strdup(conf[0]);
	ret->protocol = strdup(conf[1]);
	ret->url = strdup(conf[2]);
	ret->pause = atoi(conf[3]);
	ret->last_monitoring = current_time();
	return ret;
}

static bool	check_line(char **line){
	if (matrix_len(line) != 4)
		return false;
	return true;
}
