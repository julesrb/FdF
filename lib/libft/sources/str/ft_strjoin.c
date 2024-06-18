#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		a;
	int		b;
	int		i;

	a = 0;
	b = 0;
	i = 0;
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		buffer = (char *) malloc (1);
		if (buffer == NULL)
			return (NULL);
		buffer[0] = 0;
		return (buffer);
	}
	buffer = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) +1);
	if (buffer == NULL)
		return (NULL);
	while (s1[a] != 0)
		buffer[i++] = s1[a++];
	while (s2[b] != 0)
		buffer[i++] = s2[b++];
	buffer[i] = 0;
	return (buffer);
}

char	*ft_join_gnl(char const *s1, char const *s2)
{
	char	*buffer;
	int		a;
	int		i;

	a = 0;
	i = 0;
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		buffer = (char *) malloc (1);
		if (buffer == NULL)
			return (NULL);
		buffer[0] = 0;
		return (buffer);
	}
	buffer = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) +1);
	if (buffer == NULL)
		return (NULL);
	while (s1[a] != 0)
		buffer[i++] = s1[a++];
	a = 0;
	while (s2[a] != 0)
		buffer[i++] = s2[a++];
	buffer[i] = 0;
	free((void *)s1);
	return (buffer);
}
