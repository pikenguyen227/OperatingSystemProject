/****************** Algorithm of login  *******************/
//login.c : Upon entry, argv[0] = login, argv[1] = /dev/ttyX
#include "ucode.c"
int in, out, err;
char username[128], password[128];
char buf[1024];
char * c = "";

int console;

main(int argc, char * argv[])
{
	in = open(argv[1], O_RDONLY); //file descriptor 0
	out = open(argv[1],O_WRONLY); // for display to console
	err = open(argv[1], O_RDWR);
	fixtty(argv[1]);
	int file;
	file = open("/etc/passwd", O_RDONLY);
	int i = 0;
	if(file)
	{	
		while(read(file,c,1) > 0)
		{
			buf[i] = *c;
			i++;
		}
	}
	buf[i] = '\0';
	
	//read(file,buf,1024);
	
	//printf("Read data: %s\n",buf);
	char * retry = "Please retry...";
	char * logined = "You have been logging as ";

	int done = 0;

	while(1)
	{
		if(done == 1)
		{
			close(file);
			break;
		}
		printf("Login: ");
		gets(username);
		char * temp = buf;
		char checkusername[1024];
		char checkpasswd[1024];
		char userdirectory[1024];
		int j;
		for(j = 0;j< 1024;j++)
		{
			checkusername[j] = 0;
			checkpasswd[j] = 0;
			userdirectory[j] = 0;
		}
		char cgid[6];
		int gid;
		char cuid[6];
		int uid;
		char * checkU = checkusername;
		char * checkP = checkpasswd;
		
		int iter = 0;
		int found = 0;
		int count = 0;
		while(*temp)
		{
			if(count == 0)
			{
				if(*temp != ':')
				{
					checkusername[iter] = *temp;
					iter++;
				}
				else
				{
					checkusername[iter] = '\0';
					iter = 0;
					count++;
					if(mystrcmp(checkusername,username) == 0)
					{
						found = 1;
						printf("Password: ");
						getsE(password);
					}
				}

			}
			
			else if(count == 1 && mystrcmp(checkusername,username) == 0)
			{	
				if(*temp != ':')
				{
					checkpasswd[iter] = *temp;
					iter++;
				}
				else
				{		
					*temp++;		
					checkpasswd[iter] = '\0';
					iter = 0;
					if(mystrcmp(checkpasswd,password) == 0)
					{
						printf("Correct Password! Logging as %s\n", username);
						count = 0;
						while(*temp)
						{
							if(count == 0)
							{
								if(*temp != ':')
								{
									cgid[iter] = *temp;
									iter++;
								}
								else
								{
									cgid[iter] = '\0';
									gid = atoi(cgid);
									count++;
									iter = 0;
								}
							}
							else if(count == 1)
							{
								if(*temp != ':')
								{
									cuid[iter] = *temp;
									iter++;
								}
								else
								{
									cuid[iter] = '\0';
									uid = atoi(cuid);
									count++;
									iter = 0;
									chuid(uid,gid);
								}
							}
							else if(count == 2)
							{
								*temp++;
								while(*temp != ':')
								{
									*temp++;
								}
								*temp++;
								while(*temp != ':')
								{
									userdirectory[iter] = *temp;
									iter++;
									*temp++;

								}
								break;
							}
							*temp++;
						}
						
						exec("sh");
						
					}
					else
					{
						printf("Incorrect Password! %s\n", retry);
					}
					count++;
				}
			}
			if(*temp == '\n')
			{
				count = 0;
				int i;
				for(i = 0; i < 1024; i++)
				{
					checkusername[i] = 0;
				}
			}
			
			*temp++;
		}
		if(found == 0)
		{
			printf("Invalid User! Loggin failed! %s\n",retry);
		}
	}
}
/*
int parent() //P1’ s code
{
	int pid, status;
	while(1)
	{
		printf("INIT: wait for ZOMBIE child \n");
		pid = wait(&status);
		if (pid == console)
		{
			//if console login process died
			printf("INIT: forks a new console login\n");
			console = fork(); //fork another one
			if(console)
				continue;
			else
				exec("login /dev/tty0"); // new console login process
		}
		printf("INIT: I just buried an orphan child proc %d \n", pid);
	}
}
*/
/*
	if (file) {
    	while ((c = getc(file)) != EOF)
        	putchar(c);
    	fclose(file);
	}*/
	/*
	(1). close file descriptors 0,1 inherited from INIT.
	(2). open argv[1] 3 times as in(0), out(1), err(2).
	(3). settty(argv[ 1]); // set tty name string in PROC.tty
	(4). open /etc/ passwd file for READ;
	while(1)
	{
		(5).printf("login:"); gets(name);
		printf("password:"); gets( password);
		for each line in /etc/ passwd file do
		{
			tokenize user account line;
			(6). if (user has a valid account)
			{
				(7). change uid, gid to user’s uid, gid; // chuid()
				change cwd to user’s home DIR // chdir()
				close opened /etc/ passwd file //close()
				(8). exec to program in user account  //exec()
			}
		}
		printf("login failed, try again \n");
	}*/

