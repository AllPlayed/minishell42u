/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:34 by ullorent          #+#    #+#             */
/*   Updated: 2022/04/26 19:08:31 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cases(t_data *data)
{
	if (data->cmd[1] != NULL && !ft_strncmp(data->cmd[0], "echo", 5)
		&& !ft_strncmp(data->cmd[1], "-n", 3))
		ft_echo(data, 1);
	else if (!ft_strncmp(data->cmd[0], "echo", 5))
		ft_echo(data, 0);
	// else if (!ft_strncmp(data->cmd[0], "cd", 3))
	// 	ft_cd(data);
	// else if (!ft_strncmp(data->cmd[0], "pwd", 4))
	// 	ft_pwd(data);
	// else if (!ft_strncmp(data->cmd[0], "export", 7))
	// 	ft_export(data);
	// else if (!ft_strncmp(data->cmd[0], "unset", 6))
	// 	ft_unset(data);
	// else if (!ft_strncmp(data->cmd[0], "env", 4))
	// 	ft_env(data);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		exit(0);
	else
		return (0);
	return (1);
}

void	ft_echo(t_data *data, int boo)
{
	int		i;

	i = 1;
	if (boo)
		i = 2;
	while (data->cmd[i] != NULL)
	{
		ft_putstr(data->cmd[i]);
		i++;
	}
	if (boo == 0 || data->cmd[1] == NULL)
		write(1, "\n", 1);
}
