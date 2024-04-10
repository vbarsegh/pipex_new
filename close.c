#include "pipex.h"

void	close_fds_1st_cmd(t_pipex *pipex)
{
	int	var;

	var = 0;
	while (var < pipex->cmd_count - 1)
	{
		if (var == pipex->current_cmd)
			close(pipex->fd[var][0]);
		else
		{
			close(pipex->fd[var][0]);
			close(pipex->fd[var][1]);
		}
		var++;
	}
}

void	close_fds_mid_cmds(t_pipex *pipex)
{
	int	var;

	var = 0;
	while (var < pipex->cmd_count - 1)
	{
		if (var == pipex->current_cmd)
			close(pipex->fd[var][0]);
		else if (var == pipex->current_cmd - 1)
			close(pipex->fd[var][1]);
		else
		{
			close(pipex->fd[var][0]);
			close(pipex->fd[var][1]);
		}
		var++;
	}
}

void	close_fds_last_cmd(t_pipex *pipex)
{
	int	var;

	var = 0;
	while (var < pipex->cmd_count - 1)
	{
		if (var == pipex->current_cmd - 1)
			close(pipex->fd[var][1]);
		else
		{
			close(pipex->fd[var][0]);
			close(pipex->fd[var][1]);
		}
		var++;
	}
}

void	close_fds_in_parent_proces(t_pipex *pipex)
{
	pipex->current_cmd = 0;
	while(pipex->current_cmd < pipex->cmd_count - 1)
	{
		close(pipex->fd[pipex->current_cmd][0]);
		close(pipex->fd[pipex->current_cmd][1]);
		pipex->current_cmd++;
	}
	free(pipex->fd);
}
