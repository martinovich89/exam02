#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct s_vars
{
	va_list	ap;
	char	*str;
	char	*ret;
	int		ret;
	int		pre;
	int		spa;
	int		real_pre;
	int		real_spa;
}				t_vars;

int	ft_memalloc(void **ptr, size_t size, size_t count)
{
	size_t i;

	*ptr = malloc(sizeof(size) * count);
	if (!*ptr)
		return (-1);
	i = 0;
	while (i < (count * size))
	{
		(char *)*ptr[i] = 0;
		i++;
	}
	return (0);
}

int	nblen(unsigned int nb, int base)
{
	int nblen;

	nblen = 0;
	while (nb)
	{
		nb /= base;
		nblen++;
	}
	return (nblen);
}

void	final_nblen(t_vars *vars)
{
	size_t i;
	size_t j;

	vars->f_nblen = ft_strlen(vars->ret);
	real_spa = ((vars->spa > vars->f_nblen) * (vars->spa - vars->f_nblen));
	real_pre = ((vars->pre > (vars->f_nblen - (nb < 0))) * (vars->pre - (vars->f_nblen - (nb < 0))));
	vars->f_nblen += (vars->real_pre > 0) * vars->real_pre;
	vars->f_nblen += ((vars->real_spa > vars->f_nblen) * vars->real_spa);
}

char    *ft_itoa(int nb) 
{
    char    *str;
    int     nblen;
    int     sign;

    if (nb == -2147483648)
        return (ft_strdup("-2147483648"));
    if (nb == 0)
        return (ft_strdup("0"));
    nblen = (nb <= 0); 
    sign = (nb >= 0) * 2 - 1;
    nb *= sign;
    nblen += nb_len(nb, 10);
    str = malloc(sizeof(char) * (nblen + 1));
    str[nblen] = '\0';
    while (nb)
    {   
        str[--nblen] = nb % 10 + '0';
        nb /= 10; 
    }   
    if (sign < 0)
        str[0] = '-';
    return (str);
}

char    *xtoa(unsigned int nb)
{
    char *str;
    int nblen;
    unsigned int mod;

    nblen = nb_len(nb, 16);
    str = malloc(sizeof(char) * (nblen + 1));
    str[nblen] = '\0';
    while (nb)
    {   
        mod = nb % 16; 
        if (mod > 9)
            str[--nblen] = mod % 10 + 'a';
        else
            str[--nblen] = mod + '0';
        nb /= 16; 
    }   
    return (str);
}

void	int_conversion(t_vars *vars, char *str)
{
	char	*ret;
	int		arg;
	size_t	i;
	
	arg = va_arg(vars->ap, int);
	vars->ret = ft_itoa(arg);
	final_nblen(vars);
	if (vars->pre = 0 && !strcmp(vars->ret, "0"))
		vars->conv = ft_strdup("");
	ft_memalloc((void **)&vars->conv, sizeof(char), f_nblen);
	i = f_nblen - 1;
	j = ret_len - 1;
	vars->conv[f_nblen] = '\0';
	while (is_digit(vars->ret[i]) && i >= 0 && j >= 0)
	{
		vars->conv[i--] = vars->ret[j--];
	}
	while (vars->real_pre > 0)
	{
		vars->conv[i--] = '0';
	}
	if (vars->ret[j] == '-')
	{
		vars->conv[i--] = '-';
	}
	while (vars->real_spa > 0)
	{
		vars->conv[i--] = ' ';
	}
}

void	str_conversion(char *str, size_t *i)
{

}

void	hex_conversion(char *str, size_t *i)
{

}

void	set_flags(char *str, size_t *i)
{
	
}

int	start_conversion(t_vars vars, char *str, size_t *i)
{
	char *tmp;

	set_flags(str, *i);
	if (is_digit(str[*i]))
		vars->spa = ft_atoi(str + *i);
	*i += ft_skip_charset("1234567890");
	if (!ft_strncmp(str + *i), ".", 1)
		vars->pre = ft_atoi(str + *++i);
	*i += ft_skip_charset("0123456789");
	if (!is_alpha(str[i]))
		*i++;
	if (str[*i] == 'd')
		vars->ret = int_conversion(str, i);
	else if (str[*i] == 's')
		vars->ret = str_conversion(str, i);
	else if (str[*i] == 'x')
		vars->ret = hex_conversion(str, i);
	else if (str[*i] == '%')
	{
		tmp = ft_strjoin(vars->str, "%");
		if (!tmp)
			return (-1);
		free(vars->str);
		vars->str = tmp;
		*i++;
	}
	if (vars->ret)
	{
		tmp = ft_strjoin(vars->str, vars->ret);
		if (!tmp)
			return (-1);
		free(vars->str);
		vars->str = tmp;
		free(vars->ret);
	}
	return (va);
}

int	ft_printf(char *str, ...)
{
	t_vars *vars;
	size_t i;

	if (ft_memalloc((void **)&vars, sizeof(t_vars), 1))
		return (-1);
	va_start(vars->ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%');
			if (start_conversion(vars, str, &i) == -1)
				return (-1);
		i++;
	}
}
