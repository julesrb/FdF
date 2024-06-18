#include "libft.h"

int	ft_putnbr_uns_fd(unsigned int nb, int fd)
{
	int	printed_char;

	printed_char = 0;
	if (nb >= 10)
	{
		printed_char += ft_putnbr_uns_fd(nb / 10, fd);
		printed_char += ft_putnbr_uns_fd(nb % 10, fd);
	}
	else
	{
		printed_char += ft_putchar_fd(nb + 48, fd);
	}
	return (printed_char);
}
