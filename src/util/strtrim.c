#include "monitoring.h"

static int	char_in_set(char c, char const *set);

char	*strtrim(char *s1, char const *set){
	char	*str;
	size_t	i = 0, start = 0, len;

	while (s1[start] && char_in_set (s1[start], set))
		start ++;
	len = strlen(s1);
	while (len > start && char_in_set (s1[len - 1 ], set))
		len--;
	str = (char *) malloc (sizeof(*s1) * (len - start + 1));
	while (start < len)
		str[i ++] = s1[start ++];
	str[i] = 0;
	free(s1);
	return (str);
}

static int	char_in_set(char c, char const *set){
	for (size_t i = 0 ; set[i]; i++){
		if (set[i] == c)
			return 1;
	}
	return 0;
}