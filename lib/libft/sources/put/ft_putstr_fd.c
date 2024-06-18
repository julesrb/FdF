#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	if (s == NULL)
	{
		c += ft_putstr_fd("(null)", 1);
		return (c);
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		c++;
	}
	return (c);
}
