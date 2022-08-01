#include "monitoring.h"

static void	http_handler(HTTP_Monitoring *monitor);
static bool has_awake(HTTP_Monitoring **monitor);

void	http_manager(HTTP_Monitoring **monitor){
	static int	first = 1;

	if (!(has_awake(monitor) || first == 1))
		return ;
	printf(HTTPR);
	for(int i = 0; monitor[i]; i++){
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			http_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
		}
	}
	printf(FROUTINE);
	first = 0;
}

static bool has_awake(HTTP_Monitoring **monitor){
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

static CURL *set_options_curl(CURL *curl , HTTP_Monitoring *monitor){
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, silent_curl);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
	if (!strcmp(monitor->method, "GET"))
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	else if (!strcmp(monitor->method, "POST"))
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
	return curl;
}

static void	show_log(HTTP_Monitoring *monitor){
	char	*stamp = get_time_stamp();

	printf(MONITORED, stamp, monitor->name);
	printf(STATUS, (monitor->last_request_status == true ? OK : KOE), monitor->status);
	if (!conf.simplified)
		dprintf(conf.log_fd, HLOG, stamp,  monitor->name, monitor->url, monitor->protocol, monitor->status, \
			(monitor->last_request_status == true ? SUCCESS : FAILED), monitor->latency);
	else 
		dprintf(conf.log_fd, HLOGS, stamp, monitor->name, monitor->protocol, \
			(monitor->last_request_status == true ? SUCCESS : KO));
}

static void	http_handler(HTTP_Monitoring *monitor){
	CURL	*curl = curl_easy_init();
	long	http_status = 0, finish_time, init_time = current_time();

	if (curl){ 
		char	*url = !strstr(monitor->url, "http://") ? \
		strjoin(strdup("http://"), monitor->url) : strdup(monitor->url); 
	
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl = set_options_curl(curl, monitor);		
		if(curl_easy_perform(curl) != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(CURLE_COULDNT_CONNECT));
		}
		finish_time = current_time();
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
		monitor->last_request_status = (http_status == monitor->status) ? true : false;
		monitor->latency = (finish_time - init_time) / 10.0f; 
		show_log(monitor);
		curl_easy_cleanup(curl);
	}
}
