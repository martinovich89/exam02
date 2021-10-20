#include <stdio.h>
#include <unistd.h>

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

int putnbr(int nb) 
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
    nb /= 10;
    if (nb > 0)
        ret += putnbr(nb);
	write(1, &c, 1);
    return (ret);
}

int main(void)
{
	int n = 0;
	int ret = putnbr(n);
	printf("%d\n", ret);
}
