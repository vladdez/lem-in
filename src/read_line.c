#include "lem-in.h"

t_line	*create_line(char *line)
{
	t_line *input1;

	while (!(input1 = (t_line *)ft_memalloc(sizeof(t_line))))
		terminate(ERR_LINE_INIT);
	input1->data = line;
	input1->next = NULL;
	return (input1);
}

void	link_inputs(t_line **input, t_line *input1)
{	
	t_line *current;

	if (input && *input)
	{
		printf("4\n");
		current = *input;
		while (current->next)
		{
			current = current->next;
			//printf("- %s\n", current->data);
		}
		printf("5\n");
		current->next = input1;
	}
	else if (input)
		*input = input1;
}

t_line  *read_line(t_line **input, int fd)
{
	t_line	*input1;
	char	*line;
	int 	size;

	printf("1\n");
    if ((size = get_next_line(fd, &line) > 0))
	{
		input1 = create_line(line);
		printf("2 %s\n", input1->data);
		link_inputs(input, input1);
		printf("3\n");
	}
	if (size == -1)
		terminate(ERR_READING);
	free(line);  
	return(input1);
}