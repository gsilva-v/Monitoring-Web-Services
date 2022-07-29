#include "monitoring.h"
#include <curl/curl.h>

static void	http_handler(HTTP_Monitoring *monitor);

void	http_manager(HTTP_Monitoring **monitor){
	int	i = 0;
	static int first = 1;

	while (monitor[i]){
		
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000 || first == 1){
			http_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
			if (monitor[i + 1] == NULL)
				printf("--------------------------------\n");

		}
		i++;
	}
	first = 0;
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    return size * nmemb;
}

static CURL *set_options_curl(CURL *curl , HTTP_Monitoring *monitor){
	// Configuram o curl pro modo silencioso
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

	// Define qual o método será usado na request
	if (!strcmp(monitor->method,"GET"))
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	else if (!strcmp(monitor->method,"POST"))
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
	return curl;
}

static void	show_log(HTTP_Monitoring *monitor){
	printf("Monitored: \033[33m%s\n", monitor->name);
	printf("\033[0mStatus: %s %d\033[0m\n\n", \
		(monitor->last_request_status == true ? "\033[32mOK": "\033[31mKO expected "), monitor->status);
	if (!log_file.simplified){
		dprintf(log_file.log_fd, "Monitored: %s -> Url: %s; Expected Status: %d; Working : %s\n", monitor->name, monitor->url, monitor->status, \
			(monitor->last_request_status == true ? "OK Success": "KO The service didn't respond as expected, something might be broken"));
	} else{
		dprintf(log_file.log_fd, "Monitored: %s -> Working : %s\n", monitor->name, \
			(monitor->last_request_status == true ? "OK Success": "KO"));
	}

}

static void	http_handler(HTTP_Monitoring *monitor){
	CURL *curl = curl_easy_init();
	long http_status = 0;

	if (curl){
		char *url;
		if (!strstr(monitor->url, "http://"))
			url = strjoin("http://", monitor->url);
		else
			url = strdup(monitor->url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl = set_options_curl(curl, monitor);		
		if(curl_easy_perform(curl) != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(CURLE_COULDNT_CONNECT));
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
		if (http_status != monitor->status)
			monitor->last_request_status = false;
		else
			monitor->last_request_status = true;
		show_log(monitor);
		curl_easy_cleanup(curl);
	}
}
