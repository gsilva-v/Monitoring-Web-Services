#if !defined(MONITORING_H)
# define MONITORING_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct monitoring_http {
	char	*name;
	char	*protocol;
	char	*url;
	int		status;
	char	*method;
	int		pause;
} HTTP_Monitoring;

typedef struct monitoring_ping {
	char	*name;
	char	*protocol;
	char	*url;
	int		pause;
} PING_Monitoring;

typedef struct monitoring_dns {
	char	*name;
	char	*protocol;
	char	*url;
	int		pause;
	char	*server;
} DNS_Monitoring;




/* TIME */

void	miliseconds_sleep(int time_in_ms);
long	current_time(void);
long	passed_time(long time_started);



#endif // MONITORING_H
