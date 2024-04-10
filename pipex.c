#include "pipex.h"

void    pipe_function(char **argv, char **envp, t_pipex *pipex)
{
    pipex->fd = malloc(sizeof(int[2]) * (pipex->cmd_count - 1));
    if (!pipex->fd)
        exit(1); 
	while (pipex->current_cmd < pipex->cmd_count - 1)
    {
        if (pipe(pipex->fd[pipex->current_cmd]) == -1)
        {
			free(pipex->fd);
			exit(1);
		}
        pipex->current_cmd++;
    } 
	pipex->current_cmd = 0;
	fork_function(argv, envp, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.cmd_count = argc - 3;
	pipex.current_cmd = 0;
	if (argc < MIN_ARGC)
		exit(write (2, "Invalid count of argc\n", 22));
		//perror_exit(MIN_ARGC, &pipex);
	if (access(argv[1],F_OK) == -1)
	{
		//stex outfile-@ chenq stugum vortev kara inqy chlni,heto vor open enq anum argv[4]-@ ete chka inqy create kanenq
		write(2, "No such file or directory\n", 26);
	}	
	pipe_function(argv, envp, &pipex);
	//system("leaks pipex");
}
