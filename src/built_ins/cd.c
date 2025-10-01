/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:04:19 by zuknapek          #+#    #+#             */
/*   Updated: 2025/07/02 18:51:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int	update_pwds(t_data *data)
{
	t_env_node	*old_pwd;
	t_env_node	*pwd;
	char		*key_value;
	char		*old_pwd_key_value;
	char		*cwd;

	old_pwd = search_env_list(data, "OLDPWD");
	pwd = search_env_list(data, "PWD");
	old_pwd_key_value = ft_strjoin("OLD", pwd->key_value);
	if (!old_pwd_key_value)
		return (0);
	if (!handle_new_node(old_pwd, data, old_pwd_key_value))
		return (0);
	old_pwd = search_env_list(data, "OLDPWD");
	cwd = malloc(1024 * sizeof(char));
	if (!cwd)
		return (error_handler("malloc error"), 0);
	getcwd(cwd, 1024);
	key_value = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!key_value || !cwd)
		return (0);
	if (!handle_new_node(pwd, data, key_value))
		return (0);
	return (1);
}

char	*replace_tilde(char *input, int ind)
{
	char	*path;
	char	*pre_tilde;
	char	*p;
	char	*temp;

	if (ind == -1)
		return (input);
	if (ind != 0)
	{
		pre_tilde = ft_substr(input, 0, ind);
		temp = ft_strjoin(pre_tilde, "$HOME");
		free(pre_tilde);
	}
	else
		temp = ft_strdup("$HOME");
	if (!temp)
		return (error_handler("malloc error"), NULL);
	p = ft_substr(input, ind + 1, ft_strlen(input) - ind - 1);
	if (!p)
		return (free(temp), error_handler("malloc error"), NULL);
	path = ft_strjoin(temp, p);
	if (!path)
		return (free(temp), free(p), error_handler("malloc error"), NULL);
	return (free(temp), free(p), path);
}

char	*handle_node(t_data *data, char *var_name, char *message)
{
	t_env_node	*node;
	char		*path;

	node = search_env_list(data, var_name);
	if (!node)
		return (error_handler(message), NULL);
	path = ft_strdup(node->value);
	return (path);
}

char	*get_cd_path(char **input, t_data *data, int fd)
{
	char	*path;

	if (input[1][0] == '~' && ft_strlen(input[1]) == 1)
		path = handle_node(data, "HOME", "minishell: cd: HOME not set");
	else if ((input[1][0] == '~' && ft_strlen(input[1]) > 1)
		|| get_first_ind(input[1], '~', 0) != -1)
		path = extend_env_value(data, replace_tilde(input[1],
					get_first_ind(input[1], '~', 0)));
	else if (input[1][0] == '-' && ft_strlen(input[1]) == 1)
	{
		path = handle_node(data, "OLDPWD", "minishell: cd: OLDPWD not set");
		if (path)
		{
			write(fd, path, ft_strlen(path));
			write(fd, "\n", 1);
		}
	}
	else
		path = ft_strdup(input[1]);
	if (get_first_ind(input[1], '$', 0) != -1)
		path = extend_env_value(data, ft_strdup(input[1]));
	return (path);
}

int	cd(char **input, t_data *data, t_ast *node)
{
	char		*path;
	int			status;
	int			fd;

	path = NULL;
	fd = echo_set_fd(node);
	if (arr_size(input) > 2)
		return (error_handler("minishell: cd: too many arguments"), 1);
	if (!input[1])
		path = handle_node(data, "HOME", "minishell: cd: HOME not set");
	else
		path = get_cd_path(input, data, fd);
	if (path)
	{
		status = dir_check(path, " cd:");
		if (status == EXIT_SUCCESS)
			update_pwds(data);
		return (free(path), status);
	}
	return (free(path), EXIT_SUCCESS);
}
