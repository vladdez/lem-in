#include "lem-in.h"
#include <errno.h>

void	*terminate(char *er)
{
	if (errno == 0)
		ft_putendl_fd(er, 2);
	else
		perror(er);
	exit(1);
}