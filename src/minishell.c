/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/19 19:24:31 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_spacesremover(char *init)
{
	int		frnt;
	int		bck;
	int		fill;
	char	*fnl_cmd;

	if (!init)
		return (NULL);
	frnt = 0;
	while (init[frnt] == 32)
		frnt++;
	bck = ft_strlen(init);
	while (bck > 0 && init[bck - 1] == 32)
		bck--;
	if (bck == 0)
		return (NULL);
	fill = (bck - 1);
	bck = (bck - frnt);
	frnt = 0;
	fnl_cmd = (char *)malloc(sizeof(char) * (bck + 1));
	bck--;
	while (bck >= 0)
	{
		fnl_cmd[bck] = init[fill];
		bck--;
		frnt++;
		fill--;
	}
	fnl_cmd[frnt] = '\0';
	return (fnl_cmd);
}

int	count_ms(char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	j = 0;
	c = 0;
	while (s[k] != '\0')
	{
		if (s[k] == '\'' || s[k] == '\"')
			k += ft_pass_2(s + k, s[k]);
		if (s[k] == '|')
			i++;
		if (s[k] != '\0')
			k++;
	}
	return (i);
}

void	ft_bridge(char *str, t_data *data, int i, int j, char **env)
{
	int	index;
	int	r;

	r = 0;
	while (j + 1 <= count_ms(str, '|'))
	{
		if ((str[i] == '\'' || str[i] == '\"') && r == 1)
				i += ft_pass_2(str + i, str[i]);
		else if (str[i] != '|' && r == 0)
		{
			index = i;
			r = 1;
			if (str[i] == '\'' || str[i] == '\"')
				i += ft_pass_2(str + i, str[i]);
		}
		else if ((str[i] == '|' || str[i] == '\0') && r == 1)
		{
			ft_process(ft_substr(str, index,
					(i - index)), data, j, count_ms(str, '|'), env);
			r = 0;
			if (str[i] == '|')
				i++;
			j++;
		}
		if (str[i] != '\0' && str[i] != '|')
			i++;
		if (str[i] == ' ')
			i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = ft_dup_2d(env);
	data.path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		str = readline("bashie > ");
		add_history(str);
		if (str == NULL || str[0] == '\0' || ft_checker(str))
		{
			free (str);
			continue ;
		}
		str = ft_spacesremover(str);
		ft_init_pipes(&data);
		ft_bridge(str, &data, 0, 0, env);
		ft_close_pipes(&data);
		free (str);
		dup2(1, STDIN_FILENO);
	}
	//ft_freeo(data.env, 1);
	return (0);
}
