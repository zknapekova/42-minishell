/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:13:29 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/23 16:12:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include <stdlib.h>  // here for the NULL and size_t definitions
#include <string.h> // strdup for testing purposes

t_token	*new_token(t_token_type type, const char *value, t_quote_type quote_type)
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
	token->quote_type = quote_type;
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
			ft_printf("Type: %d, Value: %s, Quote type: %d\n", tokens->type, \
				tokens->value, tokens->quote_type);
		else
			ft_printf("Type: %d, Value: %s, Quote type: %d\n", tokens->type, \
				"NULL", tokens->quote_type);
		tokens = tokens->next;
	}
}
