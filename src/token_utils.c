/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:13:29 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/21 18:36:52 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include <stdlib.h>  // here for the NULL and size_t definitions
#include <string.h> // strdup for testing purposes

t_token	*new_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		error_handler("New token creation failed");
		return (NULL);
	}
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	if (!value)
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	token_append(t_token **head, t_token *new_token)
{
	t_token	*cur;

	if (!*head)
		*head = new_token;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free (tmp);
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->value)
			ft_printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		else
			ft_printf("Type: %d, Value: %s\n", tokens->type, "NULL");
		tokens = tokens->next;
	}
}
