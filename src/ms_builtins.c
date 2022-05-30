/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:34 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/30 15:04:26 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cases(t_data *data, char **env)
{
	(void)env;
	if (data->cmd[1] != NULL && !ft_strncmp(data->cmd[0], "echo", 5)
		&& !ft_strncmp(data->cmd[1], "-n", 3))
		ft_echo(data, 1);
	else if (!ft_strncmp(data->cmd[0], "echo", 5))
		ft_echo(data, 0);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		ft_cd(data);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		ft_export(data);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		ft_unset(data);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		ft_env(data);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
	{
		ft_free_data(data);
		printf("exit\n");
		exit(0);
	}
	else if (!ft_strncmp(data->cmd[0], "$?", 3))
		ft_exitstatus(data);
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
		printf("\n%s", data->env[i]);
		i++;
	}
	printf("\n");
}

void	ft_cd(t_data *data)
{
	if (-1 == chdir(data->cmd[1]))
		printf("bashie: cd: %s: No such file or directory\n", data->cmd[1]);
}
