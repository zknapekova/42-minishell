/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:31:41 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/30 16:46:14 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

// moves to the next node in the token list
// reference to the list is passed to change the list
// (we move the start of the list to the next token)
void	advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens=(*tokens)->next;
}

