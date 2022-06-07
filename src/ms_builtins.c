/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:34 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/07 12:05:31 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd[1] && data->cmd[1] != NULL)
		i = ft_atoi(data->cmd[1]);
	ft_free_data(data);
	exit(i);
}

int	ft_cmd_cases(t_data *data)
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

/*
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
}*/

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
		printf("\n%s", data->env[i]);
		i++;
	}
	printf("\n");
}

void	ft_changepwd(t_data *data, int index1, int index2)
{
	char	*hold;
	char	*final;
	int		len;
	
	
	free (data->env[index2]);
	len = ft_findequal(data->env[index1]);
	hold = ft_substr(data->env[index1], len + 1, ft_strlen(data->env[index1] + len + 1));
	final = ft_strjoin("OLDPWD=", hold);
	free (hold);
	data->env[index2] = final;
	hold = getcwd(NULL, 0);
	data->env[index1] = ft_strjoin("PWD=", hold);
	free (hold);
}

void	ft_reversepwd(t_data *data, int index1, int index2)
{
	char	*hold;
	char	*final;
	char	*hold2;
	int		len;
	

	hold2 = data->env[index1];
	len = ft_findequal(data->env[index2]);
	hold = ft_substr(data->env[index2], len + 1, ft_strlen(data->env[index2] + len + 1));
	chdir(hold);
	final = ft_strjoin("PWD=", hold);
	free (hold);
	data->env[index1] = final;
	len = ft_findequal(hold2);
	hold = ft_substr(hold2, len + 1, ft_strlen(hold2 + len + 1));
	data->env[index2] = ft_strjoin("OLDPWD=", hold);
	free (hold);
	free (hold2);
}


void	ft_cd(t_data *data)
{
	int		index1;
	int		index2;
	int		boo;

	if (!ft_strncmp(data->cmd[1], "-", 2))
	{
		index1 = ft_str_compare(data->env, "PWD");
		index2 = ft_str_compare(data->env, "OLDPWD");
		if (index1 != -1 && index2 != -1)
		{
			ft_reversepwd(data, index1, index2);
			ft_pwd();
		}
	}
	else
	{
		boo = chdir(data->cmd[1]);
		if (boo == -1)
			printf("bashie: cd: %s: No such file or directory\n", data->cmd[1]);
		else
		{
			index1 = ft_str_compare(data->env, "PWD");
			index2 = ft_str_compare(data->env, "OLDPWD");
			if (index1 != -1 && index2 != -1)
				ft_changepwd(data, index1, index2);
		}
	}
}
