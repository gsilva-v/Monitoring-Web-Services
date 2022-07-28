#include "monitoring.h"

char	*strjoin(const char *s1, const char *s2)
{
	char	*new;
	int		n;
	int		s;

	s = 0;
	n = 0;
	new = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[n] != '\0')
	{	
		new[n] = s1[n];
		n++;
	}
	while (s2[s] != '\0')
	{
		new[n + s] = s2[s];
		s++;
	}
	new[n + s] = '\0';
	return (new);
}