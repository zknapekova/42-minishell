/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:52:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/18 21:57:18 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h" //for ft_strdup
#include "token.h"
#include "parser_utils.h"

static void	append_target(t_redir_target **head, \
	const char *value, t_quote_type qtype);

void	append_redir(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*cur;

	if (!new_redir)
		return ;
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

t_redir	*parse_redirection(t_token **tokens)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (error_handler("Failed to allocate redir\n"), NULL);
	redir->type = get_redir_type(tokens);
	advance_token(tokens);
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
		return (free (redir), \
		error_handler("Expected filename or delimiter\n"), NULL);
	redir->target = NULL;
	while ((*tokens)->type == TOKEN_WORD)
	{
		append_target(&redir->target, (*tokens)->value, (*tokens)->quote_type);
		if ((*tokens)->word_join == W_SPLIT)
		{
			advance_token(tokens);
			break ;
		}
		advance_token(tokens);
	}
	redir->fd = -1; // We can further expand it to handle things like 2> error.log
	redir->next = NULL;
	return (redir);
}

t_redir	*collect_redirs(t_token **tokens)
{
	t_redir	*redir_list;
	t_redir	*redir;

	redir_list = NULL;
	while (is_token_redir(*tokens))
	{
		redir = parse_redirection(tokens);
		if (!redir)
			return (error_handler("Failed to parse redirection\n"), NULL);
		append_redir(&redir_list, redir);
	}
	return (redir_list);
}

t_redir_type	get_redir_type(t_token **tokens)
{
	t_redir_type	type;

	if (is_token_redirin(*tokens))
		type = REDIR_INPUT;
	else if (is_token_redirout(*tokens))
		type = REDIR_OUTPUT;
	else if (is_token_append(*tokens))
		type = REDIR_APPEND;
	else if (is_token_heredoc(*tokens))
		type = REDIR_HEREDOC;
	else
		type = REDIR_INVALID;
	return (type);
}

static void	append_target(t_redir_target **head, \
	const char *value, t_quote_type qtype)
{
	t_redir_target	*new_target;
	t_redir_target	*curr;

	new_target = malloc(sizeof(t_redir_target));
	if (!new_target)
		return (error_handler("Failed to allocate new_target\n"));
	new_target->value = ft_strdup(value);
	if (!new_target->value)
		return (free (new_target), \
		error_handler("ft_strdup failed in append_target\n"));
	new_target->quote_type = qtype;
	new_target->next = NULL;
	if (*head == NULL)
	{
		*head = new_target;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_target;
}
