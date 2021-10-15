#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_vars
{
	va_list	ap;
	char	*str;
	char	*conv;
	char	*itoa_str;
	char	*itoa_ret;
	int		pre;
	int		spa;
	int		real_pre;
	int		real_spa;
	size_t	f_nblen;
	size_t	nblen;
}				t_vars;

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c >= 'z'));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isinstr(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_skip_charset(char *str, char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isinstr(charset, str[i]))
	{
		i++;
	}
	return (i);
}

void	ft_memdel(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_memalloc(void **ptr, size_t size, size_t count)
{
	size_t	i;
	char	*str;

	*ptr = malloc(size * count);
	str = *ptr;
	if (!*ptr)
		return (-1);
	i = 0;
	while (i < (count * size))
		str[i++] = 0;
	return (0);
}

char	*ft_strdup(char *src)
{
	char *dst;
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(src); 
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < len)
		dst[i++] = src[i];
	dst[i] = '\0';
	return (dst);
}

void	clear_vars(t_vars *vars)
{
	if (vars)
	{
		if (vars->conv)
			free(vars->conv);
		if (vars->itoa_ret)
			free(vars->itoa_ret);
		if (vars->itoa_str)
			free(vars->itoa_str);
		if (vars->str)
			free(vars->str);
		free(vars);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int ft_ischarset(char c, char *charset)
{
	size_t i;
	
	i = 0;
	while (charset[i] && charset[i] != c)
		i++;
	return (charset[i] == c);
}

int	nb_len(unsigned int nb, int base)
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

void	final_nblen(t_vars *vars, int nb)
{
	size_t i;
	size_t j;

	vars->f_nblen = ft_strlen(vars->itoa_ret);
	vars->real_spa = ((vars->spa > vars->f_nblen) * (vars->spa - vars->f_nblen));
	vars->real_pre = ((vars->pre > (vars->f_nblen - (nb < 0))) * (vars->pre - (vars->f_nblen - (nb < 0))));
	vars->f_nblen += (vars->real_pre > 0) * vars->real_pre;
	vars->f_nblen += ((vars->real_spa > vars->f_nblen) * vars->real_spa);
}

int		ft_atoi(char *str)
{
	char *charset = " ";
	int nb;
	int	sign;
	size_t i;

	nb = 0;
	i = ft_skip_charset(str, charset);
	sign = ((str[i] == '-') + 1) / 2;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb *= 10;
		nb += (int)str[i] - '0';
		i++;
	}
	return (nb);
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

	if (nb == 0)
        return (ft_strdup("0"));
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

void	int_conversion(t_vars *vars, char *str, char *charset)
{
	char	*ret;
	int		arg;
	int	i;
	int	j;
	
	arg = va_arg(vars->ap, int);
	if (vars->itoa_ret)
		ft_memdel((void **)&vars->itoa_ret);
	vars->itoa_ret = ft_itoa(arg);
	vars->nblen = ft_strlen(vars->itoa_ret);
	final_nblen(vars, arg);

	if (vars->pre = 0 && !ft_strcmp(vars->itoa_ret, "0"))
	{
		vars->conv = ft_strdup("");
		return ;
	}
	printf("%zu\n", vars->f_nblen);
	ft_memalloc((void **)&vars->conv, sizeof(char), vars->f_nblen + 1);
	i = vars->f_nblen - 1;
	j = vars->nblen - 1;
	vars->conv[vars->f_nblen] = '\0';
	printf("itoa_ret = %s\n", vars->itoa_ret);
	fflush(stdout);
	while (j >= 0 && ft_ischarset(vars->itoa_ret[j], charset))
	{
		vars->conv[i] = vars->itoa_ret[j];
		printf("i = %i, j = %i, conv[i] = %c, itoa_ret[j] = %c\n", i, j, vars->conv[i], vars->itoa_ret[j]);
		fflush(stdout);
		i--;
		j--;
	}
	if (vars->itoa_ret[0] == '-')
	{
		vars->conv[i] = '-';
	}
	printf("%s\n", vars->conv);
	while (vars->real_pre > 0)
	{
		vars->conv[i--] = '0';
	}
	if (vars->itoa_ret[0] == '-')
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

void	hex_conversion(t_vars *vars, char *str, char *charset)
{
	char	*ret;
	int		arg;
	int	i;
	int	j;
	arg = va_arg(vars->ap, int);
	if (vars->itoa_ret)
		ft_memdel((void **)&vars->itoa_ret);
	vars->itoa_ret = xtoa(arg);
	vars->nblen = ft_strlen(vars->itoa_ret);
	final_nblen(vars, arg);
	if (vars->pre = 0 && !ft_strcmp(vars->itoa_ret, "0"))
	{
		vars->conv = ft_strdup("");
		return ;
	}
	printf("%zu\n", vars->f_nblen);
	ft_memalloc((void **)&vars->conv, sizeof(char), vars->f_nblen + 1);
	i = vars->f_nblen - 1;
	j = vars->nblen - 1;
	vars->conv[vars->f_nblen] = '\0';
	printf("itoa_ret = %s\n", vars->itoa_ret);
	fflush(stdout);
	while (j >= 0 && ft_ischarset(vars->itoa_ret[j], "0123456789abcdef"))       // ft_ischarset() !!!!
	{
		vars->conv[i] = vars->itoa_ret[j];
		printf("i = %i, j = %i, conv[i] = %c, itoa_ret[j] = %c\n", i, j, vars->conv[i], vars->itoa_ret[j]);
		fflush(stdout);
		i--;
		j--;
	}
	if (vars->itoa_ret[0] == '-')
	{
		vars->conv[i] = '-';
	}
	printf("%s\n", vars->conv);
	while (vars->real_pre > 0)
	{
		vars->conv[i--] = '0';
	}
	if (vars->itoa_ret[0] == '-')
	{
		vars->conv[i--] = '-';
	}
	while (vars->real_spa > 0)
	{
		vars->conv[i--] = ' ';
	}
}

void	set_flags(t_vars *vars, char *str, size_t *i)
{
}

int	ft_strncmp(char *str, char *charset, size_t nb)
{
	size_t i;
	
	i = 0;
	while (str[i] && str[i] == charset[i] && i < nb)
	{
		i++;
	}
	return (charset[i] - str[i]);
}

char	*ft_strjoin(char *src1, char *src2)
{
	char	*dst;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!src1)
		return (ft_strdup(src2));
	len = ft_strlen(src1) + ft_strlen(src2);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src1[i])
	{
		dst[i] = src1[i];
		i++;
	}
	j = 0;
	while (src2[j])
	{
		dst[i + j] = src2[j];
		j++;
	}
	dst[len] = 0;
	return (dst);
}

int	start_conversion(t_vars *vars, char *str, size_t *i)
{
	char *tmp;

//	set_flags(str, i);
	if (ft_isdigit(str[*i]))
		vars->spa = ft_atoi(str + *i);
	*i += ft_skip_charset(str, "1234567890");
	if (!ft_strncmp(str + *i, ".", 1))
	{
		(*i)++;
		vars->pre = ft_atoi(str + *i);
	}
	*i += ft_skip_charset(str, "0123456789");
	printf("%c\n", str[*i]);
	if (str[*i] == 'd')
	{
		int_conversion(vars, str, "0123456789");
	}
	else if (str[*i] == 's')
		str_conversion(str, i);
	else if (str[*i] == 'x')
	{
		hex_conversion(vars, str, "0123456789abcdef");
	}
	else if (str[*i] == '%')
	{
		tmp = ft_strjoin(vars->str, "%");
		if (!tmp)
			return (-1);
		ft_memdel((void **)&vars->str);
		vars->str = tmp;
		(*i)++;
	}
	else
		return (0);
	(*i)++;
/*	if (vars->itoa_ret)
	{
		tmp = ft_strjoin(vars->str, vars->itoa_ret);
		if (!tmp)
			return (-1);
		ft_memdel((void **)&vars->str);
		vars->str = tmp;
		ft_memdel((void **)&vars->itoa_ret);
	}*/
	return (0);
}

int	ft_printf(char *str, ...)
{
	t_vars *vars;
	char	buf[2];
	char	*tmp;
	size_t i;

	buf[0] = '\0';
	buf[1] = '\0';
	if (ft_memalloc((void **)&vars, sizeof(t_vars), 1))
		return (-1);
	va_start(vars->ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			buf[0] = str[i];
			i++;
			if (start_conversion(vars, str, &i) < 0)
				return (-1);
			tmp = vars->str;
			printf("%s | %s\n", vars->str, vars->conv);
			vars->str = ft_strjoin(vars->str, vars->conv);
			ft_memdel((void **)&tmp);
			ft_memdel((void **)&vars->conv);
			if (!vars->str)
				return (-1);
		}
		buf[0] = str[i];
		tmp = vars->str;
		vars->str = ft_strjoin(vars->str, (char *)buf);
		ft_memdel((void **)&tmp);
		if (!vars->str)
			return (-1);
		i++;
	}
	write(1, vars->str, ft_strlen(vars->str));
	clear_vars(vars);
}

int main(void)
{
	ft_printf("bonjour %4x\n", 42);
	printf("bonjour %4x\n", 42);
	return (0);
}
