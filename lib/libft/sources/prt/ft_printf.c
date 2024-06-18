#include "libft.h"

int	print_argument(va_list *args, const char *arg_definer)
{
	int		printed_char;
	char	format;

	format = arg_definer[1];
	printed_char = 0;
	if (format == '%')
		printed_char += ft_putchar_fd('%', 1);
	if (format == 'c')
		printed_char += ft_putchar_fd(va_arg(*args, int), 1);
	if (format == 's')
		printed_char += ft_putstr_fd(va_arg(*args, char *), 1);
	if (format == 'd' || arg_definer[1] == 'i')
		printed_char += ft_putnbr_fd(va_arg(*args, int), 1);
	if (format == 'u')
		printed_char += ft_putnbr_uns_fd(va_arg(*args, unsigned int), 1);
	if (format == 'x' || arg_definer[1] == 'X')
		printed_char += ft_puthex_fd(va_arg(*args, unsigned int), format, 1);
	if (format == 'p')
		printed_char += ft_putadd_fd(va_arg(*args, intptr_t), 1);
	return (printed_char);
}

int	ft_printf(const char *first, ...)
{
	va_list	args;
	int		printed_characters;
	int		i;

	printed_characters = 0;
	i = 0;
	va_start(args, first);
	while (first[i])
	{
		if (first[i] != '%')
		{
			write(1, &first[i], 1);
			printed_characters++;
		}
		if (first[i] == '%')
		{
			printed_characters += print_argument(&args, &first[i]);
			i++;
		}
		i++;
	}
	va_end(args);
	return (printed_characters);
}
