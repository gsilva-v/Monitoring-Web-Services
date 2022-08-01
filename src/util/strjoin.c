#include "monitoring.h"

char	*strjoin(const char *s1, const char *s2){
	int		n = 0, s = 0;
	char	*new = (char *) malloc (sizeof(char) * (strlen(s1) + strlen(s2)) + 1);

	if (!new)
		return (NULL);
	while (s1[n] != '\0'){	
		new[n] = s1[n];
		n++;
	}
	while (s2[s] != '\0'){
		new[n + s] = s2[s];
		s++;
	}
	new[n + s] = '\0';
	return (new);
}
