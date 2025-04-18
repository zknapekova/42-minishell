/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:32:07 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/17 17:45:47 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "main.h"

t_token	*new_token(t_token_type type, const char *value);
void	token_append(t_token **head, t_token *new_token);
void	free_token_list(t_token *head);

#endif