#include "libft.h"

int	find_word(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i] != 0)
	{
		while (s[i] != 0 && s[i] == c)
			i++;
		if (s[i] != 0 && s[i] != c)
			word++;
		while (s[i] != 0 && s[i] != c)
			i++;
		while (s[i] != 0 && s[i] == c)
			i++;
	}
	return (word);
}

void	copy_str(char const *s, char c, char **arr)
{
	int	z;
	int	j;
	int	i;

	z = 0;
	j = 0;
	while (s[z] != 0)
	{
		i = 0;
		while (s[z] != 0 && s[z] == c)
			z++;
		while (s[z] != 0 && s[z] != c)
		{
			arr[j][i] = s[z];
			z++;
			i++;
		}
		if (c != 0)
			while (s[z] == c)
				z++;
		arr[j][i] = '\0';
		j++;
		i = 0;
	}
}

char	*malloc_row(char **arr, int len, int r)
{
	arr[r] = (char *) malloc ((len + 1) * sizeof(char));
	if (arr[r] == NULL)
		return (NULL);
	return (arr[r]);
}

void	malloc_words(char const *s, char c, char **arr)
{
	int	r;
	int	i;
	int	len;

	r = 0;
	i = 0;
	while (s[i] != 0)
	{
		len = 0;
		while (s[i] != 0 && s[i] == c)
			i++;
		if (s[i] != 0 && s[i] != c)
		{
			while (s[i] != 0 && s[i] != c)
			{
				len++;
				i++;
			}
			malloc_row(arr, len, r);
		}
		while (s[i] != 0 && s[i] == c)
			i++;
		r++;
	}
	arr[r] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	words = find_word(s, c);
	if (words == 0)
	{
		arr = (char **) malloc (1 * sizeof(char *));
		if (arr == NULL)
			return (NULL);
		arr[0] = 0;
		return (arr);
	}
	else
	{
		arr = (char **) malloc ((words + 1) * sizeof(char *));
		if (arr == NULL)
			return (NULL);
	}
	malloc_words(s, c, arr);
	copy_str(s, c, arr);
	return (arr);
}
