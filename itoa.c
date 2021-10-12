#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int     nb_len(unsigned int nb, int base)
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

char	*ft_strdup(char *str)
{
	char *ret;
	size_t i;

	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
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

int main(void)
{
	char *str;
	int nb;

	nb = 0;
	str = ft_itoa(nb);
//	printf("%s\n", str);
	printf("%6.7zzt\n", 0);
}
