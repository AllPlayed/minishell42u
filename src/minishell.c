/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/11 11:55:46 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	struct sigaction	sa;
	t_data				data;

	(void)argc;
	(void)argv;
	g_child = 0;
	sa.sa_flags = 0;
	data.status = 0;
	sa.sa_mask = 0;
	data.env = ft_dup_2d(env);
	data.o_env = env;
	data.path = ft_split(getenv("PATH"), ':');
	sa.sa_sigaction = sighandler;
	rl_catch_signals = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	ft_minishell(&data);
	ft_freeo(data.env, 1);
	return (0);
}

void	ft_new_line(void)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(int signal, siginfo_t *a, void *b)
{
	(void)a;
	(void)b;
	if (signal == 0)
		exit (0);
	if (signal == 2 && g_child == 0)
	{
		ft_new_line();
	}
	if (signal == 2 && g_child == 1)
	{
		printf("\n");
	}
}
