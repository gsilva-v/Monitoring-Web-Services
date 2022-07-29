#if !defined(MONITORING_H)
# define MONITORING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
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
	float	latency;
} PING_Monitoring;

typedef struct monitoring_dns {
	char	*name;
	char	*protocol;
	char	*url;
	char	*server;
	int		pause;
	long	last_monitoring;
} DNS_Monitoring;

typedef struct log {
	int		log_fd;
	bool	simplified;

} t_log ;

extern t_log log_file;

void check_flags(char **args);
char *find_conf(char **args);

/* TIME */
void	miliseconds_sleep(int time_in_ms);
long	current_time(void);
long	passed_time(long time_started);
char *get_time_stamp(void);

int	run(char *file_conf);

/* HTTP */
HTTP_Monitoring	**parse_http(char *file_conf);
void	http_manager(HTTP_Monitoring **monitor);

PING_Monitoring **parse_ping(char *file_conf);
void	ping_manager(PING_Monitoring **monitor);

/* UTIL */
char	**split(char *s, char c);
char	*strjoin(const char *s1, const char *s2);
int		check_ber(char *what_map, char *extension);
int		matrix_len(char **m);
void	free_matrix(char **m);

#endif // MONITORING_H
