#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_p;
	unsigned char	*src_p;

	i = 0;
	dest_p = (unsigned char *)dest;
	src_p = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		dest_p[i] = src_p[i];
		i++;
	}
	return (dest);
}
