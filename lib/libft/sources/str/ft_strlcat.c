#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ret;

	i = 0;
	while (*dst && i < size)
	{
		++dst;
		++i;
	}
	ret = ft_strlcpy(dst, src, size - i);
	return (ret + i);
}
