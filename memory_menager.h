#ifndef MEMORY_MANAGER_H
# define MEMORY_MANAGER_H

# include <stdlib.h>
# include "minishell.h"

void	*my_malloc(size_t size, t_memblock **head);
void	free_all_allocations(t_memblock **head);

#endif