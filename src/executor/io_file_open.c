/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunhole <hyunhole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:11:06 by hyunhole          #+#    #+#             */
/*   Updated: 2022/09/23 14:32:48 by hyunhole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* infile_open(), outfile_open_trim(), fork_heredoc()에서 호출됨
 */
void	trim_cmd_argv(t_cmd *cmd, const char *set, int size)
{
	int i;
	int tmp;
	int tmp_argc;

	i = -1;
	tmp_argc = cmd->argc;
	while (++i < cmd->argc)
		if (!ft_strcmp(cmd->argv[i], set))
			break;
	if (i == cmd->argc)
		return;
	tmp = i;
	cmd->argc -= size;
	while (size--)
	{
		free(cmd->argv[i]);
		while (i < tmp_argc)
		{
			cmd->argv[i] = cmd->argv[i + 1];
			++i;
		}
		i = tmp;
	}
}

static void	infile_open(t_cmd *cmd)
{
	int i;
	const char redir_in[2] = {-74, '\0'};

	while (1)
	{
		i = -1;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], redir_in))
				break;
		if (cmd->argv[i] == NULL)
			break;
		if (cmd->infile > 0)
			close(cmd->infile);
		cmd->infile = open(cmd->argv[i + 1], O_RDONLY, 0644);
		if (cmd->infile == -1)
			print_err3(cmd->argv[i + 1], NULL, "No such file or directory");
		trim_cmd_argv(cmd, redir_in, 2);
	}
	return;
}

/* 
 * 왜??
 * -76을 배열에 넣는 이유가 무엇인지 확인 필요
 */
static void	outfile_open_trim(t_cmd *cmd, int i)
{
	int o_flag;
	const char r_o[2] = {-76, '\0'};
	const char r_a[3] = {-76, -76, '\0'};

	if (ft_strcmp(cmd->argv[i], r_o) == 0)
	{
		o_flag = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->outfile = ft_open(cmd->argv[i + 1], o_flag, 0644);
		trim_cmd_argv(cmd, r_o, 2);
	}
	else if (ft_strcmp(cmd->argv[i], r_a) == 0)
	{
		o_flag = O_WRONLY | O_CREAT | O_APPEND;
		cmd->outfile = ft_open(cmd->argv[i + 1], o_flag, 0644);
		trim_cmd_argv(cmd, r_a, 2);
	}
}

/* 
 * 왜??
 * -76을 배열에 넣는 이유가 무엇인지 확인 필요
 */
static void	outfile_open(t_cmd *cmd)
{
	int i;
	const char r_o[2] = {-76, '\0'};
	const char r_a[3] = {-76, -76, '\0'};

	while (1)
	{
		i = -1;
		while (cmd->argv[++i])
			if (!ft_strcmp(cmd->argv[i], r_o) || !ft_strcmp(cmd->argv[i], r_a))
				break;
		if (cmd->argv[i] == NULL)
			break;
		if (cmd->outfile > 0)
			close(cmd->outfile);
		outfile_open_trim(cmd, i);
	}
}

/* executor()에서 호출되어 cmd에 pipefd[2]와 infile, outfile 대입
 * 
 * 외부함수
 * io_file_open.c(self)
 * 		infile_open()
 * 		outfile_open()
 * path.c
 * 		get_cmd_path()
 * ft_pipe()
 */
int	io_file_open(t_cmd *cmd, t_env *env_head)
{
	ft_pipe(cmd->fd);
	infile_open(cmd);
	if (cmd->infile == -1)
	{
		g_exit_code = EXIT_FAILURE;
		return (-1);
	}
	outfile_open(cmd);
	cmd->cmd_path = get_cmd_path(cmd, env_head);
	return (0);
}