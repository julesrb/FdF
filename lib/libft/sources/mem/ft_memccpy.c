#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == c)
			return ((void *)&d[++i]);
		i++;
	}
	return (NULL);
}
