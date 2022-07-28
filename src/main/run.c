#include "monitoring.h"

int run(char *file_conf){
	HTTP_Monitoring **http = parse_http(file_conf);
	http_manager(http);

}
