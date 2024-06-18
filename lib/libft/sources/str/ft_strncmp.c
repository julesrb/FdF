#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1p;
	unsigned char	*s2p;

	i = 0;
	if (n == 0)
		return (0);
	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	while (i < n && (s1p[i] != 0 || s2p[i] != 0))
	{
		if (s1p[i] != s2p[i])
			return (s1p[i] - s2p[i]);
		i++;
	}
	return (0);
}
