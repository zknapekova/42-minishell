#include "libft.h"
#include "main.h"
#include "exec.h"

char	*rm_escape_char(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (error_handler("Error allocating new str in rm_escape_char"), NULL);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	is_hidden_file(char *str)
{
	return (str[0] == '.');
}

t_file	*sort_file_list(t_file *head)
{
	t_file	*sorted;
	t_file	*next;

	sorted = NULL;
	while (head)
	{
		next = head->next;
		head->next = NULL;
		sorted = sorted_insert(sorted, head);
		head = next;
	}
	return (sorted);
}

t_file	*sorted_insert(t_file *head, t_file *new_node)
{
	t_file	*current;

	if (!head || ft_strncmp(new_node->name, head->name, longer_strlen(new_node->name, head->name)) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && ft_strncmp(new_node->name, current->next->name, longer_strlen(new_node->name, current->next->name)) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

int	longer_strlen(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) >= ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}