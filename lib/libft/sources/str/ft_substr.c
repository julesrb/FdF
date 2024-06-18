#include "libft.h"

void	ft_substr_write(char const *s, unsigned int start, char *sub, int size)
{
	int		i;

	i = 0;
	while (size > 0)
	{
		sub[i] = s[start];
		i++;
		start++;
		size--;
	}
	sub[i] = 0;
}

int	ft_substr_size(char const *s, unsigned int start, size_t len)
{
	int	c;

	c = 0;
	while (s[start] != 0 && len)
	{
		c ++;
		len --;
		start++;
	}
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		size;

	if ((size_t)start + 1 > ft_strlen(s))
	{
		sub = malloc (1);
		if (sub == NULL)
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	size = ft_substr_size(s, start, len);
	sub = malloc (size + 1);
	if (sub == NULL)
		return (NULL);
	ft_substr_write(s, start, sub, size);
	return (sub);
}
