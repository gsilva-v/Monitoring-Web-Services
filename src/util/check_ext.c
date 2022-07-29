#include "monitoring.h"

int	check_ber(char *what_map, char *extension){
	int	len_map = strlen(what_map);
	int	len_ext = strlen(extension);
	int	comp = 0;

	while (len_ext > 0){
		if (extension[--len_ext] == what_map[--len_map])
			comp++;
		else
			return false;
	}
	return true;
}