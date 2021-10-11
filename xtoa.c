#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
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

char    *ft_strdup(char *str)
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

char    *xtoa(unsigned int nb, char *base) 
{
    char *str;
    int nblen;
	unsigned int tmp;
	int base_len;

	nblen = nb_len(nb, 16);
    str = malloc(sizeof(char) * (nblen + 1));
    str[nblen] = '\0';
    while (nb)
    {
		tmp = nb % 16;
		if (tmp > 9)
			str[--nblen] = tmp % 10 + 'a';
		else
        	str[--nblen] = tmp + '0';
        nb /= 16; 
    }
    return (str);
}

int main(void)
{
	char *str;
	int nb;

	nb = -42;
	str = xtoa((unsigned int)nb, "");
	printf("%s\n", str);
	printf("%4.5x\n", -42);
}
