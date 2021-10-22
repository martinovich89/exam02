#include <stdio.h>
#include <unistd.h>

int putnbr(int nb) 
{
    size_t ret;
    int sign;
    char c;

    ret = 1;
    sign = (nb >= 0) * 2 - 1;
    nb *= sign;
	ret += (sign < 0) && write(1, "-", 1);
    c = nb % 10 + '0';
    nb /= 10;
    if (nb > 0)
        ret += putnbr(nb);
	write(1, &c, 1);
    return (ret);
}

int main(void)
{
	int n = -42;
	int ret = putnbr(n);
	printf("%d\n", ret);
}
