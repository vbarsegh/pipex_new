#include "pipex.h"

void fork_for_1st_cmd(char **argv, char **envp, t_pipex *pipex, int i)
{
    int fd1;
    char **split_cmd;
    char *path_plus_cmd;

	path_plus_cmd = NULL;
    split_cmd = ft_split(argv [pipex->current_cmd + 2], 32);
    if (!split_cmd)
        perror_exit(SPLIT_ERR, pipex,split_cmd, path_plus_cmd);
    path_plus_cmd = check_if_cmd_is_X_OK(envp[i],split_cmd, pipex);
    close_fds_1st_cmd(pipex);
    fd1 = open(argv[1],O_RDONLY);
    if(fd1 < 0)
        perror_exit(FD1, pipex, split_cmd, path_plus_cmd);
    if (dup2(fd1,STDIN_FILENO) == -1)
        perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
    if(dup2(pipex->fd[pipex->current_cmd][1],STDOUT_FILENO) == -1)
        perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
    close(fd1);
    close(pipex->fd[pipex->current_cmd][1]);
    if (execve(path_plus_cmd,split_cmd,envp) == -1)
        perror_exit(EXECVE_ERR, pipex,split_cmd, path_plus_cmd);
}

void fork_for_middle_cmds(char **argv, char **envp, t_pipex *pipex, int i)
{
 char **split_cmd;
 char *path_plus_cmd;

	path_plus_cmd = NULL;
    split_cmd = ft_split(argv [pipex->current_cmd + 2], 32);
    if (!split_cmd)
        perror_exit(SPLIT_ERR, pipex,split_cmd, path_plus_cmd);
    path_plus_cmd = check_if_cmd_is_X_OK(envp[i],split_cmd, pipex);
 	close_fds_mid_cmds(pipex);
 	if (dup2(pipex->fd[pipex->current_cmd - 1][0],STDIN_FILENO) == -1)
    	perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
 	if (dup2(pipex->fd[pipex->current_cmd][1], STDOUT_FILENO) == -1)
    	perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
 	close(pipex->fd[pipex->current_cmd - 1][0]);
 	close(pipex->fd[pipex->current_cmd][1]);
 	if (execve(path_plus_cmd,split_cmd,envp) == -1)
    	perror_exit(EXECVE_ERR, pipex, split_cmd, path_plus_cmd);
}

void fork_for_last_cmd(char **argv, char **envp, t_pipex *pipex, int i)
{
    int fd_out;
    char **split_cmd;
    char *path_plus_cmd;

    path_plus_cmd = NULL;
    split_cmd = ft_split(argv [pipex->current_cmd + 2], 32);
    if (!split_cmd)
        perror_exit(SPLIT_ERR, pipex,split_cmd, path_plus_cmd);
    path_plus_cmd = check_if_cmd_is_X_OK(envp[i],split_cmd, pipex);
    close_fds_last_cmd(pipex);
    if (dup2(pipex->fd[pipex->current_cmd - 1][0], STDIN_FILENO) == -1)
        perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
    fd_out = open(argv[pipex->cmd_count + 2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out < 0)
        perror_exit(FD_OUT, pipex, split_cmd, path_plus_cmd);
    if (dup2(fd_out, STDOUT_FILENO) == -1)
        perror_exit(DUP2, pipex, split_cmd, path_plus_cmd);
    close(pipex->fd[pipex->current_cmd - 1][0]);
    close(fd_out);
    if (execve(path_plus_cmd, split_cmd, envp) == -1)
        perror_exit(EXECVE_ERR, pipex, split_cmd, path_plus_cmd);
}

void fork_function(char **argv, char **envp, t_pipex *pipex)
{
    int i;

    i = found_which_line_was_start_with_path(envp, pipex);
    while (pipex->current_cmd < pipex->cmd_count)
    {
        pipex->pid = fork();
        if (pipex->pid == -1)
        {
            close_fds_in_parent_proces(pipex);
            exit(write(2, "fork was failed\n", 16));
        }
        if (pipex->pid == 0)
        {
            if (pipex->current_cmd == 0)
                fork_for_1st_cmd(argv, envp, pipex, i);
            else if (pipex->current_cmd == pipex->cmd_count - 1)
                fork_for_last_cmd(argv, envp, pipex, i);
            else
                fork_for_middle_cmds(argv, envp, pipex, i);
        }
        pipex->current_cmd++;
    }
    close_fds_in_parent_proces(pipex);
	wait_function(pipex);
}

void	wait_function(t_pipex *pipex)
{
	while (pipex->cmd_count > 0)
    {
        if (wait(NULL) == -1)
            exit(EXIT_SUCCESS);
        pipex->cmd_count--;
    }
}