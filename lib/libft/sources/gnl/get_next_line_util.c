#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*buffer;

	buffer = (char *) malloc ((ft_strlen(s) + 1) * sizeof (char));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		buffer[i] = s[i];
		i++;
	}
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	size_t	bits;
	char	*buffer;

	if (size == 0 || nmemb == 0)
	{
		buffer = malloc (0);
		if (!buffer)
			return (NULL);
		return (buffer);
	}
	bits = nmemb * size;
	buffer = malloc (bits);
	if (!buffer)
		return (NULL);
	i = 0;
	while (bits--)
	{
		buffer[i] = 0;
		i++;
	}
	return (buffer);
}
