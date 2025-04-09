/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/03/29 19:21:35 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_env_node
{
    char                *key_value;
    struct s_env_node   *next;
}   t_env_node;

void    error_handler(char *str);
int     init_env(char **env);

#endif