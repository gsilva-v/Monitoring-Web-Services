#include "monitoring.h"

char *get_time_stamp(void){
	time_t current_time = time(NULL);
	struct tm *values = localtime(&current_time);

	char *buffer = calloc(sizeof(char), 20);
	sprintf(buffer, "[%d:%d:%d %d/%d/%d] ", \
		values->tm_hour, values->tm_min, values->tm_sec, \
		values->tm_mday, values->tm_mon + 1 , values->tm_year + 1900);
	return buffer;
}
