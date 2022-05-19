/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:34 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/18 18:01:44 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cases(t_data *data, char **env)
{
	if (data->cmd[1] != NULL && !ft_strncmp(data->cmd[0], "echo", 5)
		&& !ft_strncmp(data->cmd[1], "-n", 3))
		ft_echo(data, 1);
	else if (!ft_strncmp(data->cmd[0], "echo", 5))
		ft_echo(data, 0);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		ft_cd(data);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		ft_pwd();
	// else if (!ft_strncmp(data->cmd[0], "export", 7))
	// 	ft_export(data);
	// else if (!ft_strncmp(data->cmd[0], "unset", 6))
	// 	ft_unset(data);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		ft_env(env);
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

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free (s);
}

void	ft_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("\n%s", env[i]);
		i++;
	}
	printf("\n");
}

void	ft_cd(t_data *data)
{
	if (-1 == chdir(data->cmd[1]))
		printf("bashie: cd: %s: No such file or directory\n", data->cmd[1]);
}
