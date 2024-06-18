#include "libft.h"

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
