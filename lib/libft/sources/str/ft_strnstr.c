#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_b;
	char	*str;

	i = 0;
	str = (char *)big;
	if (little[0] == 0)
		return (str);
	if (len == 0 || big[0] == 0)
		return (0);
	while (str[i] != 0 && len != 0)
	{
		j = 0;
		len_b = len;
		while (little[j] == str[i + j] && len_b-- != 0)
		{
			j++;
			if (little[j] == 0)
				return (&str[i]);
		}
		i++;
		len--;
	}
	return (0);
}
