/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:33:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 00:15:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_address(unsigned long nbr, int fd)
{
	static int		written;

	if (written == 0)
	{
		ft_putstr_fd("0x", fd);
		written += 2;
	}
	if (nbr >= 16)
	{
		written += ft_print_address(nbr / 16, fd);
		return (written += ft_print_address(nbr % 16, fd));
	}
	else
	{
		ft_putchar_fd("0123456789abcdef"[nbr], fd);
		written++;
	}
	return (written);
}

static int	ft_putnbr_base(long nbr, int base, unsigned char is_upper, int fd)
{
	char	*arr;
	int		written;

	written = 0;
	arr = "0123456789ABCDEF";
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		written++;
		nbr = -nbr;
	}
	if (nbr >= base)
	{
		written += ft_putnbr_base(nbr / base, base, is_upper, fd);
		return (written += ft_putnbr_base(nbr % base, base, is_upper, fd));
	}
	else
	{
		if (is_upper)
			ft_putchar_fd(arr[nbr], fd);
		else
			ft_putchar_fd(ft_tolower(arr[nbr]), fd);
		written++;
	}
	return (written);
}

static int	check_format(char format, va_list args, int fd)
{
	char	*str;

	if (format == 'd' || format == 'i')
		return (ft_putnbr_base(va_arg(args, int), 10, 0, fd));
	else if (format == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), 10, 0, fd));
	else if (format == 'x')
		return (ft_putnbr_base((long)va_arg(args, unsigned int), 16, 0, fd));
	else if (format == 'X')
		return (ft_putnbr_base((long)va_arg(args, unsigned int), 16, 1, fd));
	else if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd), 1);
	else if (format == '%')
		return (ft_putchar_fd('%', fd), 1);
	else if (format == 'p')
		return (ft_print_address((unsigned long)va_arg(args, void *), fd) + 2);
	else if (format == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		return (ft_putstr_fd(str, fd), ft_strlen(str));
	}
	else
		return (ft_putchar_fd(format, fd), 1);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	int		written;
	va_list	args;

	if (write(fd, "", 0) < 0)
		return (-1);
	va_start(args, s);
	written = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
			written += check_format(*++s, args, fd);
		else
			written += write(fd, s, 1);
		s++;
	}
	va_end(args);
	return (written);
}
