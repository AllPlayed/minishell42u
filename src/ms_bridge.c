/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bridge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:54:37 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/13 10:10:58 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_spacesremover(char *str, int frnt, int bck, int fill)
{
	char	*fnl_cmd;

	while (str[frnt] == 32)
		frnt++;
	bck = ft_strlen(str);
	while (bck > 0 && str[bck - 1] == 32)
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
		fnl_cmd[bck] = str[fill];
		bck--;
		frnt++;
		fill--;
	}
	fnl_cmd[frnt] = '\0';
	free(str);
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

static int	check_bridge(char *str, int i, int r)
{
	if ((str[i] == '\'' || str[i] == '\"') && r == 1)
		i += ft_pass_2(str + i, str[i]);
	return (i);
}

void	ft_bridge(t_data *data, int i, int j, int r)
{
	int	index;

	while (j + 1 <= count_ms(data->str, '|'))
	{
		i = check_bridge(data->str, i, r);
		if (data->str[i] != '|' && r == 0)
		{
			index = i;
			r = 1;
			if (data->str[i] == '\'' || data->str[i] == '\"')
				i += ft_pass_2(data->str + i, data->str[i]);
		}
		else if ((data->str[i] == '|' || data->str[i] == '\0') && r == 1)
		{
			ft_process(ft_substr(data->str, index,
					(i - index)), data, j, count_ms(data->str, '|'));
			r = 0;
			if (data->str[i] == '|')
				i++;
			j++;
		}
		else if ((data->str[i] != '\0' && data->str[i] != '|' && data->str[i]
				!= '\'' && data->str[i] != '\"') || data->str[i] == ' ')
			i++;
	}
}

void	ft_minishell(t_data *data)
{
	while (1)
	{
		data->stdin = 0;
		data->stdout = 0;
		data->str = readline("bashie > ");
		add_history(data->str);
		if (data->str == NULL)
		{
			exit (0);
		}
		if (data->str[0] == '\0' || ft_checker(data->str, data))
		{
			free(data->str);
			continue ;
		}
		g_child = 0;
		data->str = ft_spacesremover(data->str, 0, 0, 0);
		data->inpipe = -1;
		data->outpipe = -1;
		ft_bridge(data, 0, 0, 0);
		free(data->str);
	}
}
