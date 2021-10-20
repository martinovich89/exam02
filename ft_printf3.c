#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

typedef struct	s_vars
{
	va_list	ap;
}	t_vars;

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_nblen(size_t nb, size_t base)
{
	size_t len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb > 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	size_t	i;
	size_t	ret;

	ret = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		ret += ft_putchar(str[i]);
		i++;
	}
	return (ret);
}



int	putnbr(int nb)
{
	size_t len;
	size_t ret;
	int sign;
	char c;

	ret = 1;
	len = (nb < 0);
	sign = (nb >= 0) * 2 - 1;
	nb *= sign;
	len += ft_nblen(nb, 10);
	c = nb % 10 + '0';
	nb /= 0;
	if (nb > 0)
		ret += putnbr(nb);
	return (ret);
}

int	start_conversion(t_vars *vars, char *str, size_t *i)
{
	int	a;
	unsigned int b;
	char *s;

	i++;
	if (str[*i] == 'd')
	{
		a = va_arg(vars->ap, int);
		vars->ret += ft_putnbr(a);
	}
	else if (str[i] == 'x')
	{
		b = va_arg(vars->ap, unsigned int);
		vars->ret += ft_putxnbr(b);
	}
	else if (str[i] == 's')
	{
		s = va_arg(vars->ap, char *);
		vars->ret += ft_putstr(s);
	}
}

int	ft_printf(char *str, ...)
{
	size_t	i;

	t_vars vars;
	i = 0;
	while (str[i])
	{
		if (str[i] = '%')
			start_conversion(&vars, str, &i);
		else
			vars.ret += ft_putchar(str[i]);
		i++;
	}
}

int main(void)
{
	
}
