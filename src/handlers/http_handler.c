#include "monitoring.h"
#include <curl/curl.h>

void	http_manager(HTTP_Monitoring **monitor){
	int	i = 0;

		
	while (true){
		if (monitor[i] == NULL){
			i = 0;
			continue;
		}
		if (passed_time(monitor[i]->last_monitoring) > monitor[i]->pause * 1000){
			http_handler(monitor[i]);
			monitor[i]->last_monitoring = current_time();
		}
		i++;
	}
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    return size * nmemb;
}

void	http_handler(HTTP_Monitoring *monitor){
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		char *url;
		if (!strstr(monitor->url, "https://")){
			url = strjoin("https://", monitor->url);
		} else {
			url = strdup(monitor->url);
		}
		curl_easy_setopt(curl, CURLOPT_URL, url);
		

	// Configuram o curl pro modo silencioso
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

	// Define qual o método será usado na request
		if (!strcmp(monitor->method,"GET")){
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		} else if (!strcmp(monitor->method,"POST")){
			curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
		}
		
		res = curl_easy_perform(curl);
	// Pega o status do retorno
		long http_status = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);

		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
		if (http_status != monitor->status){
			monitor->last_request_status = false;
		} else {
			monitor->last_request_status = true;
		}
		printf("Monitored: %s\nStatus: %s\n", monitor->name, (monitor->last_request_status == true ? "OK": "KO"));
		curl_easy_cleanup(curl);
	}
}
