/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:44 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/21 20:08:00 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL

int		get_list_len(t_arg *args);
char	*get_arg_str(t_data *data, t_arg **args);
void	free_argv(char **argv);
char	*get_redir_target_str(t_data *data, t_redir_target *target);

char	**get_arg_list(t_data *data, t_arg *args)
{
	char	**argv;
	char	*arg_str;
	int		list_len;
	int		i;
	t_arg	*args_copy;

	args_copy = args;
	list_len = get_list_len(args_copy);
	if (list_len <= 0)
		return (error_handler("Error: empty command"), NULL);
	argv = malloc(sizeof(char *) * (list_len + 1));
	if (!argv)
		return (error_handler("failed to allocate argv list"), NULL);
	i = 0;
	while (i < list_len)
	{
		arg_str = get_arg_str(data, &args_copy);
		if (!arg_str)
			return (free_argv(argv), NULL);
		argv[i] = arg_str;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*get_arg_str(t_data *data, t_arg **args)
{
	char	*arg_str;
	char	*tmp_str;

	arg_str = NULL;
	while ((*args)->value)
	{
		if (get_first_ind((*args)->value, '$', 0) != -1 \
		&& (*args)->quote_type != QUOTE_SINGLE)
			tmp_str = extend_env_value_nf(data, (*args)->value);
		else
			tmp_str = ft_strdup((*args)->value);
		if (!tmp_str)
			return (error_handler("Error getting arg_str"), NULL);
		ft_printf("%s\n", tmp_str);
		arg_str = ft_strjoin_ed(arg_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!arg_str)
			return (error_handler("Error getting arg_str"), NULL);
		if ((*args)->word_join == W_SPLIT)
		{
			(*args) = (*args)->next;
			break;
		}
		(*args) = (*args)->next;
	}
	return (arg_str);
}

int	get_list_len(t_arg *args)
{
	t_arg	*curr;
	int		len;

	len = 0;
	if (!args)
		return (0);
	curr = args;
	while (curr)
	{
		if (curr->word_join == W_SPLIT)
			len++;
		curr = curr->next;
	}
	return (len);
}

void	free_argv(char **argv)
{
	int	i;
	
	i = 0;
	if  (!argv)
		return;
	while (argv[i])
	{
		free (argv[i]);
		i++;
	}
	free (argv);
}

void	print_ast_argv(t_data *data, t_ast *node, int depth)
{
	char	**argv;
	int		i;
	char 	*redir_target;
	
	i = 0;
	if (!node)
		return ;
	print_indent(depth);
	ft_printf("**node type: %s\n", node_type_to_str(node->type));
	if ((node->type == NODE_COMMAND || node->type == NODE_SUBSHELL) \
	&& node->cmd_data)
	{
		if (node->cmd_data->args)
		{
			argv = get_arg_list(data, node->cmd_data->args);
			if (!argv)
				return ;
			print_indent(depth+1);
			ft_printf("**argv: ");
			while (argv[i])
			{
				ft_printf("%s, ", argv[i]);
				i++;
			}
			ft_printf("\n");
			free_argv(argv);
		}
		if  (node->cmd_data->redirs)
		{
			print_indent(depth+1);
			ft_printf("**redir: ");
		}
		while (node->cmd_data->redirs && node->cmd_data->redirs->target)
		{
			redir_target = get_redir_target_str(data, node->cmd_data->redirs->target);
			if (!redir_target)
				return ;
			print_indent(depth+2);
			ft_printf("type %s, target %s\n", redir_type_to_str(node->cmd_data->redirs->type), redir_target);
			free (redir_target);
			node->cmd_data->redirs = node->cmd_data->redirs->next;
		}
		
		
	}
	// 	print_cmd_data(node->cmd_data, depth + 1);
	// ft_printf("\n");
	print_ast_argv(data, node->left, depth + 1);
	print_ast_argv(data, node->right, depth + 1);
}

char	*get_redir_target_str(t_data *data, t_redir_target *target)
{
	char	*target_str;
	char	*tmp_str;

	target_str = NULL;
	while (target->value)
	{
		if (get_first_ind(target->value, '$', 0) != -1 \
		&& target->quote_type != QUOTE_SINGLE)
			tmp_str = extend_env_value_nf(data, target->value);
		else
			tmp_str = ft_strdup(target->value);
		if (!tmp_str)
			return (error_handler("Error getting target_str"), NULL);
		ft_printf("%s\n", tmp_str);
		target_str = ft_strjoin_ed(target_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!target_str)
			return (error_handler("Error getting target_str"), NULL);
		target = target->next;
	}
	return (target_str);
}