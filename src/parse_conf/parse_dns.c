#include "monitoring.h"

static int	count_dns(char *file_conf);
static bool	check_line(char **line);
static DNS_Monitoring *set_config(char **conf);
static char	*make_dns_query(DNS_Monitoring* parse);

DNS_Monitoring **parse_dns(char *file_conf){
	char			*buffer = NULL;
	char			**conf = NULL; 
	int				i = 0;
	size_t			buffer_size = 0;
	DNS_Monitoring	**ret = calloc(count_dns(file_conf), \
		sizeof(DNS_Monitoring));
	FILE			*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "DNS")){
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

static int	count_dns(char *file_conf){
	char	*buffer = NULL;
	int		dns_counter = 0;
	size_t	buffer_size = 0;
	FILE	*fd = fopen(file_conf, "r");

	if (fd == NULL)
		error_exit(INVCONF, 1);
	while (getline(&buffer, &buffer_size, fd) >= 0){
		if (strstr(buffer, "DNS"))
			dns_counter++;
	}
	fclose(fd);
	return (dns_counter);
}

static char *make_dns_query(DNS_Monitoring* parse){
	char	*query = strjoin(strdup("dig @"), parse->dns_server);

	query = strtrim(query, "\n");
	query = strjoin(query, " ");
	query = strjoin(query, parse->url);
	query = strjoin(query, DNSFLAGS);	
	return query;
}

static DNS_Monitoring *set_config(char **conf){
	DNS_Monitoring	*ret = calloc(1, sizeof(DNS_Monitoring));

	ret->name = strdup(conf[0]);
	ret->protocol = strdup(conf[1]);
	ret->url = strdup(conf[2]);
	ret->pause = atoi(conf[3]);
	ret->dns_server = strdup(conf[4]);
	ret->query = make_dns_query(ret);
	ret->last_monitoring = current_time();
	return ret;
}

static bool	check_line(char **line){
	if (matrix_len(line) != 5)
		return false;
	return true;
}
