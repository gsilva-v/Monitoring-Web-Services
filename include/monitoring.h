#if !defined(MONITORING_H)
# define MONITORING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <curl/curl.h>
# include "defines.h"

typedef struct monitoring_http {
	char	*name;
	char	*protocol;
	char	*url;
	char	*method;
	int		status;
	int		pause;
	long	last_monitoring;
	bool	last_request_status;
	float	latency;
} HTTP_Monitoring;

typedef struct monitoring_ping {
	char	*name;
	char	*protocol;
	char	*url;
	int		pause;
	long	last_monitoring;
	bool	last_request_status;
	float	latency;
} PING_Monitoring;

typedef struct monitoring_dns {
	char	*name;
	char	*protocol;
	char	*url;
	int		pause;
	char	*dns_server;
	char	*query;
	long	last_monitoring;
	bool	last_request_status;
	float	latency;
} DNS_Monitoring;

typedef struct conf {
	int		log_fd;
	int		error_log_fd;
	bool	simplified;
	bool	pretty;
	bool	dns;
	bool	http;
	bool	ping;
} t_conf ;

extern t_conf conf;

/* CONF */
void			check_flags(char **args);
char			*find_conf(char **args);

/* TIME */
void			miliseconds_sleep(int time_in_ms);
long			current_time(void);
long			passed_time(long time_started);
char			*get_time_stamp(void);

/* EXEC */
void			run(char *file_conf);

/* HTTP */
HTTP_Monitoring	**parse_http(char *file_conf);
void			http_manager(HTTP_Monitoring **monitor);
void			show_log_http(HTTP_Monitoring *monitor, int status);

/* PING */
PING_Monitoring	**parse_ping(char *file_conf);
void			ping_manager(PING_Monitoring **monitor);
void			show_log_ping(PING_Monitoring *monitor);

/* DNS */
DNS_Monitoring	**parse_dns(char *file_conf);
void			dns_manager(DNS_Monitoring **monitor);
void			show_log_dns(DNS_Monitoring *monitor);

/* UTIL */
char			**split(char *s, char c);
char			*strjoin(char *s1, const char *s2);
int				check_ber(char *what_map, char *extension);
int				matrix_len(char **m);
void			free_matrix(char **m);
char			*strtrim(char *s1, char const *set);
void			error_exit(char *s, int status);

#endif // MONITORING_H
