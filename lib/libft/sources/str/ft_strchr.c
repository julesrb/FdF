char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (*str == (char)c)
		return (str);
	while (*str++)
	{
		if (*str == (char)c)
			return (str);
	}
	return (0);
}
