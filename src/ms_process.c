/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:39:14 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 11:30:35 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_builtinpipe(data);
			return (1);
		}
	}
	else
	{
		(void)index;
	}
	return (0);
}

void	ft_check_pipes(t_data *data, int index, int end)
{
	if (index == 0 && index + 1 != end)
		ft_start_pipes(data);
	if (index != 0 && index + 1 != end)
		ft_mid_pipes(data);
	if (index + 1 == end)
		ft_end_pipes(data);
}

void	ft_finish_pipes(t_data *data, int index, int end)
{
	if (data->inpipe != -1)
		close(data->inpipe);
	data->inpipe = data->fd2[0];
	close(data->fd2[1]);
	if (index + 1 == end)
		close(data->fd2[0]);
	g_child = 0;
	data->outpipe = -1;
	ft_free_data(data);
	rl_catch_signals = 0;
}

void	ft_process(char *str, t_data *data, int index, int end)
{
	int	pid;
	int	status;

	if (check_process(ft_spacesremover(str, 0, 0, 0), data, index, end))
		return ;
	g_child = 1;
	pipe(data->fd2);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		ft_outfile(data, 0);
		ft_infile(data, 0);
		ft_check_pipes(data, index, end);
		if (!ft_cmd_cases(data))
			ft_search_cmd(data);
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_finish_pipes(data, index, end);
		data->status = WEXITSTATUS(status);
	}
}
