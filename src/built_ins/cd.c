/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:04:19 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/11 19:54:25 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


int	dir_check(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		if (!access(path, F_OK))
		{
			if (access(path, R_OK) == 0)
				return (error_handler("bash: cd: {path}: Not a directory"), 0);
			else if (!access(path, R_OK) && chdir (path) == -1)
				return (error_handler(strerror(errno)), 0);
		}
		else
			return (error_handler("bash: cd: {path}: No such file or directory"), 0);
	}
	else
	{
		if (access(path, X_OK) == -1)
			return (error_handler("bash: cd: {path}: Permission denied"), closedir (dir), 0);
		else if (!access(path, X_OK) && chdir (path) == -1)
			return (error_handler(strerror(errno)), closedir (dir), 0);
	}
	return (closedir (dir), 1);
}

int	update_pwds(char *path, t_data *data)
{
	t_env_node	*old_pwd;
	t_env_node	*pwd;
	char		*key_value;
	char		*old_pwd_key_value;

	old_pwd = search_env_list(data, "OLDPWD");
	pwd = search_env_list(data, "PWD");
	old_pwd_key_value = ft_strjoin("OLD", pwd->key_value);
	if (!old_pwd_key_value)
		return (0);
	if (!handle_new_node(old_pwd, data, old_pwd_key_value))
		return (0);
	old_pwd = search_env_list(data, "OLDPWD");
	key_value = ft_strjoin("PWD=", path);
	if (!key_value)
		return (0);
	if (!handle_new_node(pwd, data, key_value))
		return (0);
	return (1);
}

char	*replace_tilde(char *input, int ind)
{
	char	*path;
	char	*pre_tilde;
	char	*post_tilde;
	char	*temp;

	pre_tilde = NULL;
	if (ind != 0)
	{
		pre_tilde = ft_substr(input, 0, ft_strlen(input) - ind);
		if (!pre_tilde)
			return (error_handler(strerror(errno)), NULL);
		temp = ft_strjoin(pre_tilde, "$HOME");
		free(pre_tilde);
	}
	else
		temp = ft_strdup("$HOME");
	if (!temp)
		return (error_handler(strerror(errno)), NULL);
	post_tilde = ft_substr(input, ind + 1, ft_strlen(input) - ind - 1);
	if (!post_tilde)
		return (free(temp), error_handler(strerror(errno)), NULL);
	path = ft_strjoin(temp, post_tilde);
	if (!path)
		return (free(temp), free(post_tilde), error_handler(strerror(errno)), NULL);
	return (free(temp), free(post_tilde), path);
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


int	cd(char **input, t_data *data)
{
	char		*path;
	int			status;

	path = NULL;
	if (input[1])
		return (error_handler("bash: cd: too many arguments"), 0);
	if (!input[0] || ((input[0][0] == '~') && ft_strlen(input[0]) == 1))
		path = handle_node(data, "HOME", "bash: cd: HOME not set");
	else if (input[0][0] == '~' && ft_strlen(input[0]) > 1)
		path = extend_env_value(data, replace_tilde(input[0], get_first_ind(input[0], '~', 0)));
	else if (input[0][0] == '-' && ft_strlen(input[0]) == 1)
		path = handle_node(data, "OLDPWD", "bash: cd: OLDPWD not set");
	else
		path = ft_strdup(input[0]);
	if (get_first_ind(input[0], '$', 0) != -1)
		path = extend_env_value(data, ft_strdup(input[0]));
	if (path)
	{
		status = dir_check(path);
		if (status == 1)
			update_pwds(path, data);
		return (free(path), status);
	}
	return (free(path), 0);
}
