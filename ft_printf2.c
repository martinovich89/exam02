#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

typedef struct	s_vars
{
	va_list	ap;
	char	*str;
	char	*conv;
}	t_vars;

int	ft_ischarset(char *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset[i] && charset[i] != c)
		i++;
	return (charset[i] == c);
}

int	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_memdel(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_clear_vars(t_vars *vars)
{
	if (vars)
	{
		if (vars->conv)
			ft_memdel((void **)&vars->conv);
		if (vars->str)
			ft_memdel((void **)&vars->str);
	}
}

int	ft_error(t_vars *vars, int ret)
{
	write(2, "Error\n", 6);
	ft_clear_vars(vars);
	return (ret);
}

int	ft_memalloc(void **ptr, size_t size, size_t count)
{
	*ptr = malloc(size * count);
	if (!ptr)
		return (-1);
}

char	*ft_strndup(char *src, size_t len)
{
	char *dst;
	size_t i;

	ft_memalloc((void **)&dst, sizeof(char), len + 1);
	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	if (ft_memalloc((void **)&str, sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1) < 0)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	return (str);
}

size_t	ft_nblen(size_t nb, size_t base)
{
	size_t len;

	len = (nb == 0);
	while (nb > 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	size_t	i;
	int	sign;
	size_t len;

	if (!nb)
		return (ft_strndup("0", 1));
	if (nb == INT_MIN)
		return (ft_strndup("-2147483648", 11));
	sign = (nb < 0) * 2 - 1;
	len = (nb < 0);
	nb *= sign;
	len += ft_nblen(nb, 10);
	if (ft_memalloc((void **)&str, sizeof(char), len + 1) < 0)
		return (NULL);
	i = len;
	str[i--] = '\0';
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}

char	*ft_xtoa(size_t nb)
{
	char *str;
	size_t i;
	size_t len;

	if (!nb)
		return (ft_strndup("0", 1));
	len = ft_nblen(nb, 16);
	if (ft_memalloc((void **)&str, sizeof(char), len + 1) < 0)
		return (NULL);
	i = len;
	str[i--] = '\0';
	while (nb > 0)
	{
		if (nb % 16 > 9)
			str[i] = nb % 16 + '0';
		else
			str[i] = nb % 16 % 10 + 'a';
		nb /= 16;
	}
	return (str);
}

int	int_conversion(t_vars *vars, char *str)
{
	int arg;

	arg = va_arg(vars->ap, int);
	vars->conv = ft_itoa(arg);
	if (!vars->conv)
		return (-1);
	return (0);
}

int	hex_conversion(t_vars *vars, char *str)
{
	unsigned int arg;

	arg = va_arg(vars->ap, unsigned int);
	vars->conv = ft_xtoa(arg);
	if (!vars->conv)
		return (-1);
	return (0);
}

int str_conversion(t_vars *vars, char *str)
{
	char * arg;

	arg = va_arg(vars->ap, char *);
	vars->conv = ft_strndup(str, ft_strlen(str));
	if (!vars->conv)
		return (-1);
	return (0);
}

int	start_conversion(t_vars *vars, char *str, size_t *i)
{
	char *tmp;

	(*i)++;
	if (str[*i] == 'd')
		if (int_conversion(vars, str + *i) < 0)
			ft_error(vars, -1);
	else if (str[*i] == 'x')
		if (hex_conversion(vars, str + *i))
			ft_error(vars, -1);
	else if (str[*i] == 's')
		if (str_conversion(vars, str + *i))
			ft_error(vars, -1);
	else if (str[*i] == '%')
	{
		vars->conv = ft_strndup("%", 1);
		if (!vars->conv)
			return (ft_error(vars, -1));
	}
	if (vars->conv)
	{
		tmp = ft_strjoin(vars->str, vars->conv);
		ft_memdel((void **)&vars->str);
		ft_memdel((void **)&vars->conv);
	}
	(*i)++;
	return (0);
}

int	ft_printf(char *str, ...)
{
	t_vars	*vars;
	char	buf[2];
	char	*tmp;
	size_t	i;

	buf[0] = '\0';
	buf[1] = '\0';
	ft_memalloc((void **)&vars, sizeof(t_vars), 1);
	if (!vars)
	{
		return (ft_error(vars, -1));
	}
	if (ft_memalloc((void **)&vars->str, sizeof(char), 1) < 0)
		return (ft_error(vars, -1));
	va_start(vars->ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			start_conversion(vars, str + i, &i);
			if (!vars->conv)
				return (ft_error(vars, -1));
		}
		if (vars->conv)
		{
			tmp = ft_strjoin(vars->str, vars->conv);
			if (!tmp)
			{
				return (ft_error(vars, -1));
			}
			ft_memdel((void **)&vars->str);
			vars->str = tmp;
			tmp = NULL;
			ft_memdel((void **)&vars->conv);
		}
		else
		{
			buf[0] = str[i];
			printf("vars->str = %s\n", vars->str);
			tmp = ft_strjoin(vars->str, buf);
			if (!tmp)
			{
				return (ft_error(vars, -1));
			}
			ft_memdel((void **)&vars->str);
			vars->str = tmp;
			tmp = NULL;
			buf[0] = '\0';
		}
		i++;
	}
	ft_clear_vars(vars);
	va_end(vars->ap);
	return (0);
}

int main(void)
{
	ft_printf("bonjour %d\n", 42);
	printf("bonjour %d\n", 42);
}
