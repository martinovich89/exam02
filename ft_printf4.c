#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

typedef struct s_vars
{
	va_list	ap;
}	t_vars;

void	ft_memset(void *ptr, size_t size, int value)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
}

int	ft_putnbr(int nb, size_t base)
{
	while (nb > 0)
	{
		c = nb % base;
		write(1, &c, 1);
		nb /= 10;
	}
}

void	start_conversion(t_vars vars, char *str, size_t *i)
{
	(*i)++;
	if (str[*i] == 'd')
	{
		arg = va_arg(vars->ap, int);
		vars->ret += ft_putnbr(arg);
	}
	if (str[*i] == 'x')
	{
		arg = va_arg(vars->ap, unsigned int);
		vars->ret += ft_putxnbr(arg);
	}
	if (str[*i] == 's')
	{
		arg = va_arg(vars->ap, char *);
		vars->ret += ft_putstr();
	}
	write(1, vars->conv, ft_strlen(vars->conv));
}

int	ft_printf(char *str, ...)
{
	t_vars	vars;
	size_t	i;

	ft_memset((void *)&vars, sizeof(t_vars), 0);
	va_start(vars.ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == "%")
		{
			start_conversion(&vars, str, &i);
		}
	}
}

int main(void)
{
	
}
