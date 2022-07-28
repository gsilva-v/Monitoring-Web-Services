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

typedef struct monitoring_http {
	char	*name;
	char	*protocol;
	char	*url;
	int		status;
	char	*method;
	int		pause;
	int		last_monitoring;
	

} HTTP_Monitoring;

typedef struct monitoring_ping {
	char	*name;
	char	*protocol;
	char	*url;
	int		pause;
	int		last_monitoring;
} PING_Monitoring;

typedef struct monitoring_dns {
	char	*name;
	char	*protocol;
	char	*url;
	char	*server;
	int		pause;
	int		last_monitoring;
} DNS_Monitoring;




/* TIME */

void	miliseconds_sleep(int time_in_ms);
long	current_time(void);
long	passed_time(long time_started);



int run(char *file_conf);

HTTP_Monitoring **parse_http(char *file_conf);
void	http_manager(HTTP_Monitoring **monitor);
void	http_handler(HTTP_Monitoring *monitor);


char	**split(char *s, char c);
char	*strjoin(const char *s1, const char *s2);
#endif // MONITORING_H
