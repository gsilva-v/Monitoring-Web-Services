#include "monitoring.h"

void	error_exit(char *s, int status){
	printf("%s", s);
	exit(status);
}
