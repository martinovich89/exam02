#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>


void	recurse(char **line, size_t depth, int fd)
{
	char	buf[1];

	buf[0] = '\0';
	read(fd, buf, 1);
	if (buf[0] != '\n' && buf[0] != '\0')
	{
		recurse(line, depth + 1, fd);
	}
	else
	{
		*line = malloc(depth + 1);		//		ATTENTION FAIRE AVEC ET SANS \n.
		if (!*line)
			return ;
		buf[0] = 0;
	}
	(*line)[depth] = buf[0];
}



char	*get_next_line(char **line)
{
	int		fd;
	size_t	depth;

	depth = 0;
	fd = open("/dev/urandom", O_RDONLY);
	recurse(line, depth, fd);
	return (*line);
}

int main(void)
{
	char *line;

	line = get_next_line(&line);
	printf("%s\n", line);
	free(line);
}
