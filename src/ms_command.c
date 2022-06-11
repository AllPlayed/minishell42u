/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:02:11 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 11:41:31 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_path(t_data *data)
{
	int	index;

	index = ft_str_compare(data->env, "PATH");
	if (index == -1)
	{
		printf("bashie: %s: No such file or directory\n", data->cmd[0]);
		exit (127);
	}
	return (ft_split(data->env[index], ':'));
}

int	quit_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmd[0][i])
	{
		if (data->cmd[0][i] == '/')
			j = i;
		i++;
	}
	if (j == 0)
		return (1);
	data->cmd[0] = data->cmd[0] + j + 1;
	return (0);
}

void	search_cmd2(t_data *data)
{
	char	*temp;

	if (access(data->cmd[0], X_OK) == 0)
	{
		temp = ft_substr(data->cmd[0], 0, ft_strlen(data->cmd[0]));
		data->cmd[data->cmd_n] = NULL;
		if (quit_path(data))
			return ;
		execve(temp, data->cmd, data->env);
		exit(0);
	}
}

static void	ft_cmd_not_found(t_data *data)
{
	write(2, "bashie: ", 8);
	ft_putstr_fd(data->cmd[0], 2);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	ft_free_data(data);
	exit (127);
}

void	ft_search_cmd(t_data *data)
{
	char	*temp;
	char	**path;
	int		i;

	i = -1;
	if (data->cmd[0] == NULL)
		exit (0);
	path = ft_get_path(data);
	if (path == NULL)
		exit(0);
	search_cmd2(data);
	while (data->path[++i] != NULL && data->cmd[0][0] != '\0')
	{
		temp = ft_ms_join(data->path[i], "/", ft_strlen(data->path[i]), 1);
		temp = ft_ms_join(temp, data->cmd[0], ft_strlen(temp),
				ft_strlen(data->cmd[0]));
		if (access(temp, X_OK) == 0)
		{
			data->cmd[data->cmd_n] = NULL;
			execve(temp, data->cmd, data->env);
			exit(0);
		}
		free (temp);
	}
	ft_cmd_not_found(data);
}
