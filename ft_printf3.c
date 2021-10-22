#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

typedef struct	s_vars
{
	va_list	ap;
	size_t ret;
}	t_vars;

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

/*int	ft_putstr(char *str)
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
}*/

int	ft_putnbr(int nb)
{
	size_t ret;
	int sign;
	char c;

	ret = 1;
	if (nb == INT_MIN)
		return (write(1, "-2147483648", 11));
	sign = (nb >= 0) * 2 - 1;
	nb *= sign;
	ret += (nb < 0) && write(1, "-", 1);
	c = nb % 10 + '0';
	nb /= 10;
	if (nb > 0)
		ret += ft_putnbr(nb);
	write(1, &c, 1);
	return (ret);
}

int	ft_putxnbr(unsigned int nb)
{
	size_t ret;
	char c;

	ret = 1;
	c = nb % 16 + '0';
	if (nb % 16 > 9)
		c = nb % 16 % 10 + 'a';
	nb /= 16;
	if (nb > 0)
		ret += ft_putxnbr(nb);
	write(1, &c, 1);
	return (ret);
}

int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	start_conversion(t_vars *vars, char *str, size_t *i)
{
	int	a;
	unsigned int b;
	char *s;

	(*i)++;
	if (str[*i] == 'd')
	{
		a = va_arg(vars->ap, int);
		vars->ret += ft_putnbr(a);
	}
	else if (str[*i] == 'x')
	{
		b = va_arg(vars->ap, unsigned int);
		vars->ret += ft_putxnbr(b);
	}
	else if (str[*i] == 's')
	{
		s = va_arg(vars->ap, char *);
		vars->ret += ft_putstr(s);
	}
	return (0);
}

void	ft_memset(char *ptr, size_t size, char value)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		ptr[i] = value;
		i++;
	}
}

int	ft_printf(char *str, ...)
{
	size_t	i;

	t_vars vars;
	ft_memset((char *)&vars, sizeof(t_vars), 0);
	va_start(vars.ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			start_conversion(&vars, str, &i);
		else
			vars.ret += ft_putchar(str[i]);
		i++;
	}
	return (vars.ret);
}

int main(void)
{
	printf("bonjour %s\n", "au revoir");
	ft_printf("bonjour %s\n", "au revoir");
}
