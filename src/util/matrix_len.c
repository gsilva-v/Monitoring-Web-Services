#include "monitoring.h"

int matrix_len(char **m){
	int i = 0;

	if (m == NULL || m[i] == NULL)
		return 0;
	for (; m[i]; i++)
		;
	return i;
}
