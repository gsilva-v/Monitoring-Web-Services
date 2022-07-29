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
# include <oping.h>
long double	current_time(void){
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	miliseconds_sleep(float time_in_ms){
	double	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
		usleep(100);
}

long	passed_time(long time_started){
	return (current_time() - time_started);
}

#include <time.h>
#include <errno.h>    

/* msleep(): Sleep for the requested number of milliseconds. */
void fracSleep(float sec) {
    struct timespec ts;
    ts.tv_sec = (int) sec;
    ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
    nanosleep(&ts,NULL);
}

int msleep(float msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = ((int)msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int main(int argc, char const *argv[])
{
	float ping = 0;

	long init_time = current_time();






	long finish_time = current_time();
	ping = finish_time - init_time; 

	printf ("%.1f ms\n", ping);




	return 0;
}
