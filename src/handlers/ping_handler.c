#include "monitoring.h"

static void	ping_handler(PING_Monitoring *monitor);

static bool has_awake(PING_Monitoring **monitor){
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 )
			return true;
	}
	return false;
}

void	ping_manager(PING_Monitoring **monitor){
	int	i = 0;
	static int first = 1;

	if (has_awake(monitor) || first == 1)
		printf("Ping routine started: checking necessary requests ...\n");
	else
		return ;
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			ping_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
			// if (monitor[i + 1] == NULL)
		}
	}
				printf(FROUTINE);
	first = 0;
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    return size * nmemb;
}

static void	show_log(PING_Monitoring *monitor){
	char *stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(PING, monitor->latency);
	if (!log_file.simplified){
		dprintf(log_file.log_fd, PLOG, stamp, monitor->name, monitor->url, monitor->latency);
	} else{
		dprintf(log_file.log_fd, PLOGS, stamp, monitor->name, monitor->latency);
	}
}

static void	ping_handler(PING_Monitoring *monitor){
	CURL	*curl = curl_easy_init();
	long	finish_time, http_status = 0, init_time = current_time();

	if (curl){
		curl_easy_setopt(curl, CURLOPT_URL, monitor->url);
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
		if(curl_easy_perform(curl) != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(CURLE_COULDNT_CONNECT));
		}
		finish_time = current_time();
		curl_easy_cleanup(curl);
	}
	monitor->latency = (finish_time - init_time) / 10.0f; 
	show_log(monitor);
}
