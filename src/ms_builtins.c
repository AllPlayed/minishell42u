/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:34 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/13 09:05:30 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cases(t_data *data)
{
	if (data->cmd[0] == NULL)
		return (0);
	if (data->cmd[1] != NULL && !ft_strncmp(data->cmd[0], "echo", 5)
		&& !ft_strncmp(data->cmd[1], "-n", 3))
		ft_echo(data, 1);
	else if (!ft_strncmp(data->cmd[0], "echo", 5))
		ft_echo(data, 0);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		ft_cd(data, 0, 0, 0);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		ft_export(data);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		ft_unset(data);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		ft_env(data);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		ft_exit(data);
	else if (!ft_strncmp(data->cmd[0], "$?", 3))
		ft_exitstatus(data);
	else
		return (0);
	return (1);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd[1] && data->cmd[1] != NULL)
	{
		while (ft_isdigit(data->cmd[1][i]))
			i++;
		if (data->cmd[1][i] != '\0')
		{
			ft_putstr_fd("exit\nbashie: exit: ", 2);
			ft_putstr_fd(data->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (255);
		}
		if (data->cmd[2] != NULL)
		{
			ft_putstr_fd("exit\nbashie: exit: too many arguments\n", 2);
			data->status = 1;
			return ;
		}
	}
	if (data->cmd[1] && data->cmd[1] != NULL)
		i = ft_atoi(data->cmd[1]);
	ft_free_data(data);
	exit(i);
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
		if (data->cmd[i] != NULL)
			write(1, " ", 1);
	}
	if (boo == 0 || data->cmd[1] == NULL)
		write(1, "\n", 1);
}

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free (s);
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}
