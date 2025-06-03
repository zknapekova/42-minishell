/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:55:18 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/03 19:02:17 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL

char	**get_argv(t_data *data, t_arg *args)
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
	argv = globe_argv(argv);
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
		else if ((*args)->quote_type != QUOTE_NONE)
			tmp_str = escape_wildcard((*args)->value);
		else
			tmp_str = ft_strdup((*args)->value);
		if (!tmp_str)
			return (error_handler("Error getting arg_str"), NULL);
		arg_str = ft_strjoin_ed(arg_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!arg_str)
			return (error_handler("Error getting arg_str"), NULL);
		if ((*args)->word_join == W_SPLIT)
		{
			(*args) = (*args)->next;
			break ;
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
	if (!argv)
		return ;
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
	char	*redir_target;
	t_redir	*redir;
	char	*path;

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
			argv = get_argv(data, node->cmd_data->args);
			if (!argv)
				return ;
			path = get_exec_path(argv[0], data);
			print_indent(depth + 1);
			ft_printf("**argv: ");
			while (argv[i])
				ft_printf("%s, ", argv[i++]);
			ft_printf("path: %s", path);
			ft_printf("\n");
			free_argv(argv);
			free (path);
		}
		if (node->cmd_data->redirs)
		{
			print_indent(depth + 1);
			ft_printf("**redirs:\n");
			redir = node->cmd_data->redirs;
			while (redir && redir->target)
			{
				redir_target = get_redir_target_str(data, redir->target);
				if (!redir_target)
					return ;
				print_indent(depth + 2);
				ft_printf("typ: %s, target: %s\n", \
					redir_type_to_str(redir->type), redir_target);
				free (redir_target);
				redir = redir->next;
			}
		}
	}
	print_ast_argv(data, node->left, depth + 1);
	print_ast_argv(data, node->right, depth + 1);
}

// adds \ before *
char	*escape_wildcard(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * 2 * (ft_strlen(str) + 1));
	if (!str)
		return (error_handler("Error in escape_wildcard()"), NULL);
	while (str[i])
	{
		if (str[i] == '*')
			result[j++] = '\\';
		result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}