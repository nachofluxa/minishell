/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   executor.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nachofluxa <nachofluxa@student.42.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/15 10:46:31 by nachofluxa		#+#	#+#			 */
/*   Updated: 2025/04/21 20:55:18 by nachofluxa	   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "executor/executor.h"
#include "libft/libft.h"
#include "freedom/freedom.h"
#include "parser/parser.h"
#include "builtins/builtins.h"
#include "exitno/exitno.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	child(t_command *cmd, int (*auxfd)[2], char **env, int exitno)
{
	if (cmd->output && open_output(cmd->output) == 0)
		exit(1);
	if (cmd->input && open_input(cmd->input, env, exitno) == 0)
		exit(1);
	if (auxfd)
	{
		dup2((*auxfd)[0], STDIN_FILENO);
		close((*auxfd)[0]);
		close((*auxfd)[1]);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->args && cmd->args[0] && (ft_strncmp(cmd->args[0], "cd", 2) == 0
			|| ft_strncmp(cmd->args[0], "exit", 4) == 0
			|| ft_strncmp(cmd->args[0], "export", 6) == 0
			|| ft_strncmp(cmd->args[0], "unset", 5) == 0))
		exit (0);
	if (is_builtin(cmd))
		exit(check_builtins(cmd, env));
	else
		execute_command(cmd, env);
}

static int	init_pipe(int (**pipefd)[2])
{
	int	(*pf)[2];

	pf = malloc(sizeof(int [2]));
	if (!pf || pipe(*pf) < 0)
	{
		if (pf)
			freedom((void **)&pf);
		perror("minishell");
		return (0);
	}
	*pipefd = pf;
	return (1);
}

static int
	parent(t_command *cmd, char **env, int (**auxfd)[2], int (*pipefd)[2])
{
	if (*auxfd)
		free_auxfd(*auxfd);
	*auxfd = pipefd;
	if (cmd->args && cmd->args[0] && (ft_strncmp(cmd->args[0], "cd", 2) == 0
			|| ft_strncmp(cmd->args[0], "exit", 4) == 0
			|| ft_strncmp(cmd->args[0], "export", 6) == 0
			|| ft_strncmp(cmd->args[0], "unset", 5) == 0))
		return (check_builtins(cmd, env));
	return (0);
}

static int
	process_one(t_command **cmd, char **env, int (**auxfd)[2], int *exitno)
{
	int	(*pipefd)[2];
	int	pid;

	if (!init_pipe(&pipefd))
	{
		perror("minishell");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		perror("minishell");
	if (pid == 0)
	{
		if (!(*cmd)->output && (cmd[1]) != NULL)
			dup2((*pipefd)[1], STDOUT_FILENO);
		close((*pipefd)[0]);
		close((*pipefd)[1]);
		child(*cmd, *auxfd, env, *exitno);
	}
	else
		*exitno = parent(*cmd, env, auxfd, pipefd);
	return (pid);
}

int	execute_commands(t_command **cmds, char **envp, int exitno)
{
	size_t	pos;
	int		(*auxfd)[2];
	int		status;
	int		*pids;

	pids = ft_calloc((count_commands(cmds) + 1), sizeof(int));
	if (!pids)
	{
		perror("minishell");
		return (1);
	}
	pos = -1;
	auxfd = NULL;
	while (cmds[++pos])
		pids[pos] = process_one(cmds + pos, envp, &auxfd, &exitno);
	pos = -1;
	while (pids[++pos])
		if (pids[pos] != -1)
			waitpid(pids[pos], &status, 0);
	freedom((void **)&pids);
	close_auxfd(auxfd);
	return (get_exitno(status, pos, cmds[pos - 1], &exitno));
}
