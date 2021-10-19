#include <stdlib.h>
#include <stdio.h>

typedef struct s_env
{
	int toto;
}	t_env;

t_env *env(void)
{
	static t_env env;

	return (&env);
}

int main(void)
{
	env()->toto = 5;
	printf("%d\n", env()->toto);
}
