/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:18:00 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/15 16:30:03 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h" //for ft_strdup
#include "parser_utils.h"

void	append_arg(t_arg **head, const char *value, \
	t_quote_type qtype, t_word_join wjoin)
{
	t_arg	*new_arg;
	t_arg	*curr;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (error_handler("Failed to allocate new_arg\n"));
	new_arg->value = ft_strdup(value);
	if (!new_arg->value)
		return (free (new_arg), \
		error_handler("ft_strdup failed in append_arg\n"));
	new_arg->quote_type = qtype;
	new_arg->word_join = wjoin;
	new_arg->next = NULL;
	if (*head == NULL)
	{
		*head = new_arg;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_arg;
}

void	free_args(t_arg *head)
{
	t_arg	*next;

	while (head)
	{
		next = head->next;
		free (head->value);
		free (head);
		head = next;
	}
}

t_cmd_data	*init_cmd_data(t_redir *leading_redir)
{
	t_cmd_data	*cmd_data;

	cmd_data = malloc(sizeof(t_cmd_data));
	if (!cmd_data)
		return (error_handler("Failed to allocate cmd_data\n"), NULL);
	cmd_data->argv = NULL;
	cmd_data->redirs = leading_redir;
	return (cmd_data);
}
