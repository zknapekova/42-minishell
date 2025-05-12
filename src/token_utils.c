/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:13:29 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/12 19:18:58 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include <stdlib.h>  // here for the NULL and size_t definitions
#include <string.h> // strdup for testing purposes

t_token	*new_token(t_token_type type, const char *value, \
	t_quote_type quote_type, t_word_join word_join)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		error_handler("New token creation failed\n");
		return (NULL);
	}
	token->type = type;
	token->value = NULL;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			return (free(token), \
			error_handler("New token creation failed\n"), NULL);
	}
	token->quote_type = quote_type;
	token->word_join = word_join;
	token->next = NULL;
	return (token);
}

void	token_append(t_token **head, t_token *new_token)
{
	t_token	*cur;

	if (!new_token)
		return ;
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

// void	free_token_list(t_token **head)
// {
// 	t_token	*tmp;
// 	int		i = 0;

// 	while (*head)
// 	{
		
// 		tmp = *head;
// 		*head = (*head)->next;
// 		if (tmp->value)
// 			free(tmp->value);
// 		free (tmp);
// 		ft_printf("token freed, %i\n", i);
// 		i++;
// 	}
// 	*head = NULL;
// }

void	free_token_list(t_token **head)
{
	t_token	*tmp;
	int		i = 0;

	if (!(*head))
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		// ft_printf("Freeing token: %p, next: %p\n", (void *)tmp, (void *)(*head));
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		// ft_printf("token freed, %i\n", i);
		i++;
	}
	*head = NULL;
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->value)
			ft_printf("Type: %d, Value: %s, Quote type: %d, word_join: %d\n", \
			tokens->type, tokens->value, tokens->quote_type, tokens->word_join);
		else
			ft_printf("Type: %d, Value: %s, Quote type: %d, word_join: %d\n", \
			tokens->type, "NULL", tokens->quote_type, tokens->word_join);
		tokens = tokens->next;
	}
}
