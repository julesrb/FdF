#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mod;

	if (!s || !f)
		return (NULL);
	mod = (char *) malloc ((unsigned int)ft_strlen(s) + 1);
	if (!mod)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		mod[i] = f(i, s[i]);
		i++;
	}
	mod[i] = 0;
	return (mod);
}
