#include "monitoring.h"

static void	ping_handler(PING_Monitoring *monitor);
static bool	has_awake(PING_Monitoring **monitor);

void	ping_manager(PING_Monitoring **monitor){
	static int	first = 1;

	if (!(has_awake(monitor) || first == 1))
		return ;
	printf(PINGR);
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			ping_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
		}
	}
	printf(FROUTINE);
	first = 0;
}

static bool has_awake(PING_Monitoring **monitor){
	for (int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000)
			return true;
	}
	return false;
}

static size_t silent_curl(char *ptr, size_t size, size_t nmemb, void *userdata){
    (void)ptr;
    (void)userdata;
	return size * nmemb;
}

static void	ping_handler(PING_Monitoring *monitor){
	CURL	*curl = curl_easy_init();
	long	finish_time, init_time = current_time();

	if (curl){
		curl_easy_setopt(curl, CURLOPT_URL, monitor->url);
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, silent_curl);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
		if(curl_easy_perform(curl) != CURLE_OK){
			printf("Ping: Name or service not know\n");
			monitor->latency = 0;
			monitor->last_request_status = false;
			goto showlog;
		}
		monitor->last_request_status = true;
		finish_time = current_time();
		curl_easy_cleanup(curl);
	}
	monitor->latency = (finish_time - init_time) / 10.0f;
	showlog : show_log_ping(monitor);
}
