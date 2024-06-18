#include "libft.h"

int	ft_putadd_fd(intptr_t adress, int fd)
{
	int		printed_char;

	printed_char = 0;
	if (adress == 0)
	{
		printed_char += ft_putstr_fd("(nil)", 1);
		return (printed_char);
	}
	printed_char += ft_putchar_fd('0', 1);
	printed_char += ft_putchar_fd('x', 1);
	printed_char += ft_puthex_fd(adress, 'x', fd);
	return (printed_char);
}
