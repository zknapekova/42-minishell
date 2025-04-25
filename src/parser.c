/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/24 22:00:24 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"

int	check_tokens(t_token *tokens);


t_ast	*parser(t_token *tokens)
{
	// t_ast	*ast;

	if (!check_tokens(tokens))
		return (NULL);
	return (NULL);
}

