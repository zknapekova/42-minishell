/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:52:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/05 18:43:53 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h" //for ft_strdup
#include "../include/token.h"
#include "../include/parser_utils.h"

void	append_redir(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*cur;
	
	if (!*redir_list)
	{
		*redir_list = new_redir;
		return ;
	}
	cur = *redir_list;
	while (cur->next)
		cur = cur->next;
	cur->next = new_redir;
}

void	free_redir(t_redir *head)
{
	t_redir	*next;
	while (head)
	{
		next = head->next;
		free (head->target);
		free (head);
		head = next;
	}
}
