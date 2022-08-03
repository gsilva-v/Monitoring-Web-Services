#include "monitoring.h"

void	free_matrix(char **m){
	if (m == NULL)
		return ;
	for (int i = 0; m[i]; i++)
		free(m[i]);
	free(m);
}
