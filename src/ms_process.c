/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:39:14 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/10 12:21:11 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_infile2(t_data *data, int i)
{
	if (data->infile.files[i] != NULL)
		ft_infile(data, i);
	else
		dup2(data->fd[0][0], STDIN_FILENO);
	close(data->fd[0][1]);
	close(data->fd[0][0]);
}

void	ft_infile(t_data *data, int i)
{
	char	*str;
	char	*temp;
	char	*jump;
	int		fd;

	str = NULL;
	jump = "\n";
	if (data->infile.files[i] == NULL)
		return ;
	if (data->infile.modes[i] == 1)
	{
		while (!ft_strnstr(str, data->infile.files[i], ft_strlen(str)))
		{
			//dup2(1, STDIN_FILENO);
			temp = readline("> ");
			if (ft_strnstr(temp, data->infile.files[i], ft_strlen(temp)))
				break ;
			str = ft_ms_join(str, temp, ft_strlen(str), ft_strlen(temp));
			str = ft_ms_join(str, jump, ft_strlen(str), 1);
			free (temp);
		}
		if (data->infile.files[i + 1] == NULL)
		{
			write(data->fd[0][1], str, ft_strlen(str));
			//lose(fd);
		}
	}
	else
	{
		fd = open(data->infile.files[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("bashie: ", 2);
			ft_putstr_fd(data->infile.files[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			data->fd[0][0] = fd;
		}
		else
			data->fd[0][0] = fd;
	}
	ft_infile2(data, i + 1);
}

void	ft_open_outfile(t_data *data, int i)
{
	int	fd;

	open(data->outfile.files[i], O_TRUNC);
	fd = open(data->outfile.files[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

int	ft_outfile(t_data *data, int i)
{
	int	fd;

	if (data->outfile.files[i] == NULL)
		return (0);
	if (data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		ft_open_outfile(data, i);
		return (0);
	}
	else if (data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		fd = open(data->outfile.files[i], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return (0);
	}
	i++;
	if (data->outfile.files[i] != NULL)
		ft_outfile(data, i);
	return (0);
}

int	ft_builtin(t_data *data)
{
	if (data->cmd[0] == NULL)
		return (0);
	if (data->cmd[1] != NULL && !ft_strncmp(data->cmd[0], "echo", 5)
		&& !ft_strncmp(data->cmd[1], "-n", 3))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "$?", 3))
		return (1);
	else
		return (0);
}


static int	check_process(char *str, t_data *data, int index, int end)
{
	ft_input(str, data, 0, 0);
	//ft_putnbr_fd(index, 2);
	//ft_putnbr_fd(end, 2);
	if (end == 1)
	{
		if (ft_builtin(data))
		{
			ft_infile(data, 0);
			ft_outfile(data, 0);
		}
		if (ft_cmd_cases(data))
		{
			ft_free_data(data);
			ft_end_pipes(data);
			return (1);
		}
	}
	else
	{
		if (index == 0 && index + 1 != end)
			ft_start_pipes(data);
		if (index != 0)
			ft_mid_pipes(data);
		if (index + 1 == end)
			ft_end_pipes(data);
	}
	return (0);
}

void	ft_process(char *str, t_data *data, int index, int end)
{
	int	pid;
	int	status;

	str = ft_spacesremover(str, 0, 0, 0);
	if (check_process(str, data, index, end))
		return ;
	g_child = 1;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		/*if (index == 0 && index + 1 != end)
			ft_start_pipes(data);
		if (index != 0)
			ft_mid_pipes(data);
		if (index + 1 == end)
			ft_end_pipes(data);*/
		ft_outfile(data, 0);
		ft_infile(data, 0);
		if (!ft_cmd_cases(data))
			ft_search_cmd(data);
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_child = 0;
		data->status = WEXITSTATUS(status);
		ft_free_data(data);
		rl_catch_signals = 0;
	}
}

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
		ft_close_pipes(data);
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

	i = 0;
	if (data->cmd[0] == NULL || data->fd[0][0] == -1)
		exit (0);
	path = ft_get_path(data);
	if (path == NULL)
		exit(0);
	search_cmd2(data);
	while (data->path[i] != NULL && data->cmd[0][0] != '\0')
	{
		temp = ft_ms_join(data->path[i], "/", ft_strlen(data->path[i]), 1);
		temp = ft_ms_join(temp, data->cmd[0], ft_strlen(temp),
				ft_strlen(data->cmd[0]));
		if (access(temp, X_OK) == 0)
		{
			data->cmd[data->cmd_n] = NULL;
			ft_close_pipes(data);
			execve(temp, data->cmd, data->env);
			exit(0);
		}
		free (temp);
		i++;
	}
	ft_cmd_not_found(data);
}
