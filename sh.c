#include "ucode.c"
/*
int pP;
int sh;
int hS;
int cPID;

char input[128];
// function table structure
typedef struct function_table{
  char *functionName;
  int (*f)();
  char * functionHelp;
  int numberOfParam; // 0 = no, 1 = yes, 2 = has no params
} functionTable;

functionTable ftable[] ={
	{"pwd", pwd, ": Print the current working directory (cwd).", 0},
	{"mkdir", mkdir, ": make a directory with name.", 1},
	{"rmdir", rmdir, ": remove a directory with name.", 1},
	{"creat", creat, ": create a file with name.", 1}
};

int isOpertator(char * op)
{
	if(strcmp(op,">") == 0 || strcmp(op,">>") == 0)
	{
		return 1;
	}
	return 0;
}

int find_and_execute_command(char * c, char * input)
{
	int i;
	int l = LENGTH(ftable);
	char firstParam[128];
	char secondParam[128];
	char thirdParam[128];

	for(i = 0;i< 128;i++)
	{
		firstParam[i] = 0;
		secondParam[i] = 0;
		thirdParam[i] = 0;
	}
	int iter = 0;
	int result = 0;

	while(*input && *input != ' ')
	{
		if(*input == '>')
		{
			break;
		}
		firstParam[iter] = *input;
		*input++;
		iter++;
	}
	firstParam[iter] = '\0';
	if(*input == ' ')
	{
		*input++;
	}
	if(*input)
	{
		iter = 0;
		while(*input && *input != ' ')
		{
			secondParam[iter] = *input;
			*input++;
			iter++;
		}
		secondParam[iter] = '\0';
		if(*input != '\0')
		{
			*input++;
			iter = 0;
			while(*input && *input != '\0')
			{
				thirdParam[iter] = *input;
				*input++;
				iter++;
			}
			thirdParam[iter] = '\0';
		}
	}
	
	for(i = 0; i < l; i++)
	{
		if(strcmp(ftable[i].functionName,c) == 0)
		{
			char * tempf = firstParam;
			char * temps = secondParam;
			if(ftable[i].numberOfParam == 0)
			{	
				ftable[i].f();
			}
			else if(ftable[i].numberOfParam == 1)
			{
				ftable[i].f(firstParam);
			}
			else if(ftable[i].numberOfParam == 2)
			{
				ftable[i].f(firstParam,secondParam);
			}
			else if(ftable[i].numberOfParam == 3)
			{
				ftable[i].f(firstParam,secondParam,thirdParam);
			}
			result = 1;
		}
	}
	for(i = 0;i< 128;i++)
	{
		firstParam[i] = 0;
		secondParam[i] = 0;
		thirdParam[i] = 0;
	}
	return result;
}*/

main()
{
	char command[128];
	char input[128];
	char inFile[128];
	int i;
	int tpid;
	for(i = 0;i< 128;i++)
	{
		command[i] = 0;
		input[i] = 0;
		inFile[i]= 0;
	}
	int pid, status;
	int check;
	isPipe = 0;
	//op = 0;
	int switchP = 0;
	while(1)
	{
		int foundC = 0;
		char * temp = input;
		char * t = input;
		int iter = 0;
		isPipe = 0;
		printf("sh # ");
		gets(input);
		if(*input != 0)
		{
			while(*t)
			{
				if(*t == '|')
				{
					printf("here");
					isPipe = 1;
					break;
				}
				*t++;
			}
			if(strcmp("logout",input) == 0)
			{
				printf("Logging out %s\n","!");
				exit(1);
			}
			//printf("INput: %s\n",input);
		
			pid = fork();
			if (pid==0)
			{
				if(isPipe == 0)
				{
					check = exec(input);
				}
				else
				{
					do_pipe(input);
				}
			}
	        else
	        {
	        	pid = wait(&status);
	        }
    	}
		
		
	}
}
void pipeRecur(char cmd[256][256], int input,int output,int n);

int do_pipe(char * buf)
{
	char cmd[256][256];
	
	int i = 0;
	int j = 0;
	for(i = 0; i < 256; i++)
	{
		for(j= 0; j < 256; j++)
		{
			cmd[i][j] = 0;
		}
	}
	i = 0;
	j = 0;
	char * last;
	int size = 0;
	char * next = "";
	int param = 0;
	char sparam[1];
	while(*buf)
	{
		if(*buf == '|')
		{
			if(param == 0)
			{
				cmd[i][j-1] = '\0';
				j++;
			}
			else 
			{
				cmd[i][j] = '|';
				j++;		
				/*
				cmd[i][j] = ' ';
				j++;
				cmd[i][j] = '0';
				j++;	*/	
				cmd[i][j] = '\0';
			}
			param++;
			j = 0;
			i++;
			size++;
			*buf++;

			while(*buf == ' ')
			{
				*buf++;
			}
			next = buf;
		}
		cmd[i][j] = *buf;
		j++;
		*buf++;
	}
	size++;
	
	cmd[i][j] = ' ';
	j++;
	cmd[i][j] = '|';
	j++;
/*	
	cmd[i][j] = ' ';
	j++;

	if(size == 2)
	{
		//cmd[i][j] = '0';
		//j++;
	}
	else if(size == 3)
	{
		cmd[i][j] = '1';
		j++;
	}*/

	cmd[i][j] = '\0';
	
	int pid;
	int status;
	int z = 0;

	for(z = 0; z < size; z++)
	{
		printf("cmd: %s\n",cmd[z]);
	}

	printf("Size: %d\n",size);
	pipeRecur(cmd,-1,-1,size - 1);
}

void pipeRecur(char cmd[256][256], int input,int output, int n) 
{
	if(n == 0)
	{
		close(input);
		dup2(output,1);
		exec(cmd[n]);
	}
	int pd[2] = {-1,-1};
	pipe(pd);
	pid = fork();
	if(pid)
	{
		if(input != -1)
		{
			dup2(output,1);
		}
		if(pd[1] != -1)
		{
			dup2(pd[0],0);
		}
		exec(cmd[n]);
	}
	else
	{
		pipeRecur(cmd,pd[0],pd[1],n - 1);
	}
	
}




/*

if(n == 0)
	{
		return;
	}
	int pd[2] = {-1,-1};
	pipe(pd);
	pid = fork();
	if(pid)
	{ 
		printf("CMD: %s",cmd[n]);
		printf("here1");

		if(pd[0] != -1)
		{
			printf("here2");
			close(pd[1]);
			dup2(pd[0],0);
		}
		if(input != -1)
		{
			printf("here3");
			close(output);
			dup2(input,0);
		}
		exec(cmd[n]);

	}
	else
	{
		printf("CMD: %s",cmd[n-1]);
		printf("here4");
		if(n > 0)
		{
			printf("here5");
			pipeRecur(cmd,pd[0],pd[1],n - 1);
		}
		printf("here6");
		if(*cmd[n+1] != 0)
		{
			printf("here7");
			close(pd[0]);
			dup2(output,1);
		}
		else
		{
			printf("here8");
			close(pd[0]);
			dup2(pd[1],1);
		}
		exec(cmd[n-1]);
	}
*/


	/*
	int pdd[2] = {-1,-1};

	if(i == 0)
	{
		return;
	}
	
	pipe(pd);
	
	pid = fork();
	if(pid)
	{
		printf("here1");
		close(pd[0]); //close write end
		dup2(pd[1],1); //redirect to read end
		exec(cmd[n-1]);
	}
	else
	{
		//pipeRecur(cmd,);
		printf("here2");
		close(pd[1]); //close read end
		dup2(pd[0],0); // redirect to write end
		exec(cmd[n]);
	}*/




/*
	int pd[2] = {-1,-1};

	if (*cmd[i+1] != 0) 
	{
		pipe(pd);
	}
	if (fork() == 0) 
	{ 
		/* child 
		// READ from child
		if (input != -1) 
		{
		  dup2(input, 0);
		  close(input);
		}
		if (pd[1] != -1) 
		{
		  dup2(pd[1], 1);
		  close(pd[1]);
		}
		if (pd[0] != -1) 
		{
		  close(pd[0]);
		}
		exec(cmd[i]);
	}
	else 
	{ 
		/* parent 
		if (input != -1) 
		{
		  close(input);
		}
		if (pd[1] != -1) 
		{
		  close(pd[1]);
		}
		if (*cmd[i+1] != 0)
		{
		  pipeRecur(cmd, pd[0],i+1);
		}
	}
*/


/*
		if(tpid == 0)
	{
		pipeRecur(cmd,pd[p][0],pd[p][1],n-1,p - 1,size);
		printf("line3");
		printf("p: %d",p);
		printf("line4");
		close(pd[p][0]);
		printf("line5");
		dup2(pd[p][1],1);
		//dup2(pd[p][1],1);
		printf("line6");
		exec(cmd[n-1]);
		printf("line7");
	}
	else
	{
		printf("line8");
		close(pd[p][1]);
		printf("line9");
		dup2(pd[p][0],0);
		printf("line10");
		exec(cmd[n]);
	}
*/

/*
	if(n == 0)
	{
		return;
	}
	int tpid = fork();
	if(tpid)
	{
		close(pd[1]); //close write end
		printf("line2");
		dup2(pd[0],0); //redirect to read end
		printf("line3");
		exec(cmd[n]);
	}
	else
	{

		printf("line4");
		pipeRecur(cmd,n-1);
		printf("line5");
		close(pd[0]); //close read end
		dup2(pd[1],1); // redirect to write end
		exec(cmd[n - 1]);
		//pipeRecur(cmd,n-1);
	}*/






	/*
  int pfds[2] = {-1,-1};

  if (*cmd[i+1] != 0) {
    pipe(pfds);
  }
  if (fork() == 0) { /* child 
    if (input != -1) {
      dup2(input, 0);
      close(input);
    }
    if (pfds[1] != -1) {
      dup2(pfds[1], 1);
      close(pfds[1]);
    }
    if (pfds[0] != -1) {
      close(pfds[0]);
    }
    exec(cmd[i]);
  }
  else { /* parent 
    if (input != -1) {
      close(input);
    }
    if (pfds[1] != -1) {
      close(pfds[1]);
    }
    if (*cmd[i+1] != 0) {
      pipeRecur(cmd, pfds[0],i+1);
    }
  }
}

*/
/*
int pipeRecur(char cmd[256][256],int i,int n)
{
	if(*cmd[i+1])
	{
		pipe(pd);
	}
	int tpid = fork();
	if(tpid == 0)
	{
		if(*cmd[i] != 0)
		{
			dup2(input)
		}
	}
	else
	{

	}
}

/*
	int pfds[2] = { -1, -1 };

  if (cmd->next != NULL) {
    pipe(pfds);
  }
  if (fork() == 0) { /* child 
    if (input != -1) {
      dup2(input, STDIN_FILENO);
      close(input);
    }
    if (pfds[1] != -1) {
      dup2(pfds[1], STDOUT_FILENO);
      close(pfds[1]);
    }
    if (pfds[0] != -1) {
      close(pfds[0]);
    }
    execvp(cmd->argv[0], cmd->argv);
    exit(1);
  }
  else { /* parent 
    if (input != -1) {
      close(input);
    }
    if (pfds[1] != -1) {
      close(pfds[1]);
    }
    if (cmd->next != NULL) {
      run_pipeline(cmd->next, pfds[0]);
    }
  }*/

	/*
	for cmd in cmds
    if there is a next cmd
        pipe(new_fds)
    fork
    if child
        if there is a previous cmd
            dup2(old_fds[0], 0)
            close(old_fds[0])
            close(old_fds[1])
        if there is a next cmd
            close(new_fds[0])
            dup2(new_fds[1], 1)
            close(new_fds[1])
        exec cmd || die
    else
        if there is a previous cmd
            close(old_fds[0])
            close(old_fds[1])
        if there is a next cmd
            old_fds = new_fds
	*/
	/*
	int i;
	for(i = 0; i < n;i++)
	{
		if(i + 1 < n)
		{
			pipe(pd);
		}
		int tpid = fork();
		if(tpid == 0)
		{
			if(i - 1 >= 0)
			{
				dup2(pd[0],0);
				close(pd[0]);
				close(pd[1]);
			}
			if(i + 1 < n)
			{
				close(pd[0]);
            	dup2(pd[1], 1);
            	close(pd[1]);
			}
			exec(cmd[i]);
		}
		else
		{
			close(pd[0]);
			close(pd[1]);
		}
	}
}
	/*
	if(n == 0)
	{
		return;
	}
	printf("line0");
	pipe(pd[p]);
	int tpid = fork();
	if(tpid)
	{
		//printf("N1: %d\n",n - 1);
		//printf("N2: %d\n",n);
		printf("CMD1: %s\n",cmd[n]);
		printf("p1: %d\n",p);
		printf("line1");
		close(pd[p][1]); //close write end
		printf("line2");
		dup2(pd[p][0],0); //redirect to read end
		printf("line3");
		exec(cmd[n]);
	}
	else
	{
		printf("1N1: %d\n",n - 1);
		printf("2N2: %d\n",n);
		printf("CMD2: %s\n",cmd[n-1]);
		printf("p2: %d\n",p);
		/*
		close(pd[n - 1]);
		dup2(pd[n],1);
		printf("line4");
		pipeRecur(cmd,n-1,p - 1);
		printf("line5");
		close(pd[p][0]); //close read end
		dup2(pd[p][1],1); // redirect to write end
		exec(cmd[n - 1]);
		//pipeRecur(cmd,n-1);
	}
}
/*
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          cmd++;
        }
    }

	/*
	if(n == 0)
	{
		return;
	}
	//pipe(pd);
	int tpid = fork();
	if(tpid)
	{
		//printf("N1: %d\n",n - 1);
		//printf("N2: %d\n",n);
		//printf("CMD1: %s\n",cmd[n]);
		close(pd[n]); //close write end
		dup2(pd[n-1],0); //redirect to read end
		exec(cmd[n]);
	}
	else
	{
		//printf("1N1: %d\n",n - 1);
		//printf("2N2: %d\n",n);
		//printf("CMD2: %s\n",cmd[n-1]);
		close(pd[n - 1]);
		dup2(pd[n],1);
		pipeRecur(cmd,n-1);
		close(pd[n-1]); //close read end
		dup2(pd[n],1); // redirect to write end
		exec(cmd[n-1]);
	}
}
	/*
	int tpid;	
	tpid = fork();
	if(tpid)
	{
		close(pd[1]);
		dup2(pd[0],0);
		exec(cmd[1]);
	}
	else
	{
	
		close(pd[0]);
		dup2(pd[1],1);
		exec(cmd[0]);
		
	}*/


	/*
	int i;
	for(i = 0; i < n; i++)
	{
		int tpid;	
		tpid = fork();
		if(tpid)
		{
			close(pd[1]);
			dup2(pd[0],0);
			exec(cmd[i+1]);
		}
		else
		{
			if(i == n - 1)
			{
				close(pd[0]);
				dup2(pd[1],1);
				exec(cmd[i]);
			}
			else
			{
				i++;
			}

		}
	}
}
	/*
	if(n == 0)
	{
		close(pd[n]);
		dup2(pd[n+1],1);
		exec(cmd[n]);
		return;
	}
	//pipe(pd);
	int tpid;	
	tpid = fork();
	if(tpid)
	{
		tpid = fork();
		printf("here1 %d\n",n);
		close(pd[n]);
		dup2(pd[n-1],0);
		exec(cmd[n]);
	}
	else
	{
		pipeRecur(cmd,n-1);
	}
	
}
	/*
	if(n + 1 == size)
	{
		close(pd[1]);
		dup2(pd[0],0);
		exec(cmd[n]);
	}
	else
	{
		int tpid;
		pipe(pd);	
		tpid = fork();
		if(tpid == 0)
		{
			printf("CMD: %s\n",cmd[n]);
			printf("here2");
			close(pd[0]);
			dup2(pd[1],1);
			exec(cmd[n]);
		
		}
		else
		{
			pipeRecur(cmd,n+1,size);	
		}
	}
	*/
	/*
	// working backward
	if(n == 0)
	{
		printf("here1");
		close(pd[0]);
		dup2(pd[1],1);
		exec(cmd[n]);
	}
	int tpid;
	pipe(pd);	
	tpid = fork();
	if(tpid == 0)
	{
		printf("CMD: %s\n",cmd[n]);
		printf("here2");
		close(pd[1]);
		dup2(pd[0],0);
		exec(cmd[n]);
		
	}
	else
	{
		pipeRecur(cmd,n-1);	
	}

	/*
	if(n+1 == size)
	{
		close(pd[0]);
		dup2(pd[1],1);
		printf("cmd2 %s\n",cmd[n]);
		exec(cmd[n]);
	}
	else
	{
		pipe(pd);	
		int tpid = fork();
		if(tpid == 0)
		{
			close(pd[1]);
			dup2(pd[0],0);
			printf("cmd1 %s\n",cmd[n + 1]);
			exec(cmd[n]);
		}
		else
		{
			pipeRecur(cmd,n+1,size);
		}
	}
	
/*	printf("n %d",n);
	int tpid;
	pipe(pd);	
	tpid = fork();
	//pipeRecur(cmd,n-1);
	if(tpid)
	{
		printf("here1");
		close(pd[1]);
		dup2(pd[0],0);
		exec(cmd[n+1]);
	}
	else
	{
		printf("here2");
		close(pd[0]);
		dup2(pd[1],1);
		exec(cmd[n]);	
	}*/


/*
				if(pid == 0)
				{
					printf(" MORE %s \n", " ");
					close(pd[1]); //close pipe WRITE end
					dup2(pd[0],0); // redirect stdin to pipe READ end
					exec("more");
				}
				else
				{
					
					pid = wait(&status);
				
				}
				/*
				pid = fork();
				if(pid)
				{	
					printf(" MORE %s \n", " ");
					close(pd[1]); //close pipe WRITE end
					dup2(pd[0],0); // redirect stdin to pipe READ end
					exec("more");	
				}
				else
				{
					if(!op)
					{
						pid = wait(&status);
						op = 1;
					}
					else
					{	
						pid = fork();
						if(pid)
						{
							printf(" CAT %s \n", " ");
							close(pd[0]); //close pipe WRITE end
							dup2(pd[1],1); // redirect stdin to pipe READ end
							exec("cat f");
						}
						else
						{
							pid = wait(&status);
						}
					}
				}*/


/* /***************** do_pipe Algorithm **************
int pid, pd[2];
pipe(pd); // create a pipe: pd[0] = READ, pd[1] = WRITE
pid = fork(); //fork a child to share the pipe
if (pid)
{
	// parent: as pipe READER
	close(pd[1]); //close pipe WRITE end
	dup2(pd[0],0); // redirect stdin to pipe READ end
	exec(cmd2);
}
else
{
	//child:as pipe WRITER
	close(pd[0]); // close pipe READ end
	dup2(pd[1], 1); // redirect stdout to pipe WRITE end
	exec(cmd1);
}*/


/*
		prompts for a command line, e.g. cmdLine="cat filename"
           if (cmd == "logout") 
              syscall to die;

           // if just ONE cmd:  
           pid = fork();
           if (pid==0)
               exec(cmdLine);
           else
               pid = wait(&status);

/*
		while(*temp != '\0' && *temp != ' ')
		{
			command[iter] = *temp;
			iter++;
			*temp++;
		}
		command[iter] = '\0';
		if(*temp != '\0')
		{
			*temp++;
		}
		int check = find_and_execute_command(command,temp);
		if(check == 0)
		{
			int fd = open(command,O_RDONLY);
			if(fd != -1)
			{
				
				
				int i = 0;
				char executingFile[256];
				for(i = 0; i < 256; i++)
				{
					executingFile[i] = 0;
				}
				i = 0;
				char * tempE = command;
				char * endC = " /dev/tty0";
				while(*tempE != '\0')
				{
					executingFile[i] = *tempE;
					i++;
					*tempE++;
				}
				
				while(*endC)
				{
					executingFile[i] = *endC;
					i++;
					*endC++;

				}
				if(*temp == '<')
				{
					int y;
					while(*temp == '<' || *temp == ' ')
					{
						*temp++;
					}
					if(*temp)
					{
						y = 0;
						while(*temp)
						{
							inFile[y] = *temp;
							y++;
							*temp++;
						}
						inFile[y] = 0;
						int fdinFile = open(inFile,O_RDONLY);
						if(fdinFile != -1)
						{
							char * r = inFile;
							executingFile[i] = ' ';
							i++;
							while(*r)
							{
								if(*r != ' ')
								{
									executingFile[i] = *r;
									i++;
									*r++;
								}
							}
						
						}
						else
						{
							printf("%s file not found\n", "ERROR");
						}
						close(fdinFile);
						cPID = getpid();
					}
					else
					{
						printf("%s missing file name\n", "ERROR");
					}
				}

				executingFile[i] = '\0';
				int pid, status;
				while(1)
				{ 	
					pid = fork();			
					if(pid)
					{ 
						pid = wait(&status);
						
					}
					else
					{
						exec(executingFile);
					}
						  
				}
		
			}
		}*/
		
	//}
//