#include "libft.h"

int	ft_puthex_fd(unsigned long long nb, char x, int fd)
{
	int	printed_char;

	printed_char = 0;
	if (nb >= 16)
	{
		printed_char += ft_puthex_fd(nb / 16, x, fd);
		printed_char += ft_puthex_fd(nb % 16, x, fd);
	}
	else
	{
		if (nb <= 9)
			printed_char += ft_putchar_fd(nb + '0', fd);
		else
		{
			if (x == 'x')
				printed_char += ft_putchar_fd(nb - 10 + 'a', fd);
			if (x == 'X')
				printed_char += ft_putchar_fd(nb - 10 + 'A', fd);
		}
	}
	return (printed_char);
}
