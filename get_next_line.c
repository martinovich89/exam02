#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>




/*
	on va faire du recurse.
	Il faut une condition d'arret.
	Ce sera qu'on rencontre '\n' ou 'EOF'.
	donc :
	-----------------
	recurse(depth)
	{
		buf[0] == '\0';
		read(0, buf, 1);
		if (buf[0] != '\n' && buf[0] != '\0')
			recurse(depth + 1);
		else 
			line = malloc(depth + 1);				ATTENTION FAIRE AVEC ET SANS \n.
		line[depth] = buf[0];
		return ();
	}
	-----------------
*/

char	*get_next_line(char **line)
{
	int fd;

	fd = open(0, O_RDNLY)
	recurse(depth, fd);
}

int main(void)
{
	
}
