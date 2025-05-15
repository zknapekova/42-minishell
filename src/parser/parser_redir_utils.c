/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:52:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/15 16:30:41 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h" //for ft_strdup
#include "token.h"
#include "parser_utils.h"

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

t_redir	*parse_redirection(t_token **tokens)
{
	t_redir	*redir;

	if (!is_token_redir(*tokens) || !(*tokens)->next)
		return (error_handler("Invalid token in parse_redirection()\n"), NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (error_handler("Failed to allocate redir\n"), NULL);
	redir->type = get_redir_type(tokens);
	if (redir->type == REDIR_INVALID)
		return (free (redir), error_handler("Unknown redirection type"), NULL);
	advance_token(tokens);
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
		return (free (redir), \
		error_handler("Expected filename or delimiter\n"), NULL);
	redir->target = ft_strdup((*tokens)->value);
	if (!redir->target)
		return (free(redir), error_handler("Failed to copy \
filename in parse_redirection\n"), NULL);
	redir->fd = -1; // We can further expand it to handle things like 2> error.log
	redir->next = NULL;
	advance_token(tokens);
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
