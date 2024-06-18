#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = 0;
	i = 0;
	s = (char *)src;
	while (s[len] != 0)
		len++;
	if (size == 0)
		return (len);
	size--;
	while (s[i] != 0 && size)
	{
		dst[i] = s[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (len);
}
