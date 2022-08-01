#include "monitoring.h"

static int	counterwords(const char *s, char c);

char	**split(char *s, char c){
	int		i = 0,	posc = 0, n = 0;
	char	**new_str = (char **) malloc (sizeof(char *) * ((counterwords(s, c) + 1)));

	if (!new_str)
		return (NULL);
	while (s[i] != '\0'){
		while (s[i] == c)
			i++;
		posc = i ;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (i > posc)
			new_str[n++] = strndup(s + posc, i - posc);
	}
	new_str[n] = NULL;
	return (new_str);
}

static int	counterwords(const char *s, char c){
	unsigned int	i = 0;
	int				cntr = 0, findword = 0;

	while (s[i] != '\0')	{
		if (s[i] != c && findword == 0) {
			findword = 1;
			cntr++;
		} else if (s[i] == c && findword == 1)
			findword = 0;
		i++;
	}
	return (cntr);
}
