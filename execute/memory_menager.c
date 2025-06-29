/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_menager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:22:46 by skaynar           #+#    #+#             */
/*   Updated: 2025/06/30 00:23:00 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../memory_menager.h"

void	*my_malloc(size_t size, t_memblock **head)
{
	t_memblock	*new_block;
	void		*data;

	data = malloc(size);
	if (!data)
		exit(1);
	new_block = malloc(sizeof(t_memblock));
	if (!new_block)
		exit(1);
	new_block->data = data;
	new_block->next = *head;
	*head = new_block;
	return (data);
}

void	free_all_allocations(t_memblock **head)
{
	t_memblock *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->data);
		free(tmp);
	}
}
