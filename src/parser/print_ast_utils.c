/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:28:45 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/18 21:34:30 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const char	*node_type_to_str(t_node_type type)
{
	if (type == NODE_COMMAND)
		return ("COMMAND");
	else if (type == NODE_PIPE)
		return ("PIPE");
	else if (type == NODE_AND)
		return ("AND");
	else if (type == NODE_OR)
		return ("OR");
	else if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

const char	*redir_type_to_str(t_redir_type type)
{
	if (type == REDIR_INPUT)
		return ("IN");
	else if (type == REDIR_OUTPUT)
		return ("OUT");
	else if (type == REDIR_APPEND)
		return ("APPEND");
	else if (type == REDIR_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

const char	*quote_type_to_str(t_quote_type type)
{
	if (type == QUOTE_DOUBLE)
		return ("DOUBLE");
	else if (type == QUOTE_SINGLE)
		return ("SINGLE");
	else if (type == QUOTE_NONE)
		return ("NONE");
	return ("UNKNOWN");
}
