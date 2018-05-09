/********** cat.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
	printf("CATCAT");
	// CAT no argument.
	if(argc == 1)
	{
		char * input = "";
		while(1)
		{
			gets(input);
			if(strcmp(input,"exit") == 0)
			{
				exit(0);
			}
			printf("input: %s\n",input);
		}
	}
	// CAT one argument (file name)
	else if(argc == 2 && strcmp(argv[1],">") != 0 && strcmp(argv[1],">>") != 0)
	{
		int file = open(argv[1], O_RDONLY);
		char * c = "";
		if(file != -1)
		{
			while(read(file,c,1) > 0)
			{
				printf("%s",c);
			}
			
		}
		else
		{
			printf("cat: %s: No such file or directory \n",argv[1]);
		}
		close(file);
	}
	// CAT 1 argument "">""
	else if(argc == 3 && strcmp(argv[1],">") == 0)
	{
		int file = open(argv[2], O_WRONLY);
		if(file == -1)
		{
			close(file);
			creat(argv[2]);
		}
		else
		{
			close(file);	
		}
		file = open(argv[2], O_WRONLY);
		char buf[1024];
		int i;
		for(i = 0; i < 1024; i++)
		{
			buf[i] = 0;
		}
		while(strcmp("exit",buf) != 0)
		{
			if(*buf != 0)
			{
			  	write(file,buf,strlen(buf));
			  	write(file,"\n",1);
			}
			gets(buf);
		}
		write(file,"EOF",3);
		write(file,"\n",1);
		close(file);

	}
	// CAT 2 argument "">>""
	else if(argc == 3 && strcmp(argv[1],">>") == 0)
	{
		struct stat fstat, *sp = &fstat;
        stat(argv[2], sp);

		int file = open(argv[2], O_RDWR);
		if(file == -1)
		{
			close(file);
			printf("cat: %s: No such file or directory \n",argv[2]);
			return;
		}	
		
		char buf[1024];
		int i;
		for(i = 0; i < 1024; i++)
		{
			buf[i] = 0;
		}
		lseek(file,sp->st_size,0);
		while(strcmp("exit",buf) != 0)
		{
			if(*buf != 0)
			{
				write(file,buf,strlen(buf));
			  	write(file,"\n",1);
			}
			gets(buf);
		}
		close(file);
	}
	// CAT 3 arguments "">""
	else if(argc == 4 && strcmp(argv[2],">") == 0)
	{
		struct stat fstat, *sp = &fstat;
        stat(argv[3], sp);

        if(sp->st_mode == 8612)
        {
        	printf("File name: %s\n",argv[1]);
        	return;
        }
        
		int fileOne = open(argv[1], O_RDONLY);
		if(fileOne == -1)
		{
			close(fileOne);
			printf("cat: %s: No such file or directory \n",argv[1]);
		}
		else
		{
			int fileTwo = open(argv[3], O_WRONLY);
			if(fileTwo == -1)
			{
				close(fileTwo);
				creat(argv[3]);
			}
			else
			{
				close(fileTwo);	
			}
			fileTwo = open(argv[3], O_WRONLY);
			
			char * c = "";
			while(read(fileOne,c,1) > 0)
			{
				write(fileTwo,c,1);
			}
			close(fileOne);
			close(fileTwo);
		}
	}
	// CAT 3 arguments "">>""
	else if(argc == 4 && strcmp(argv[2],">>") == 0)
	{
		struct stat fstat, *sp = &fstat;
        stat(argv[3], sp);
		int fileOne = open(argv[1], O_RDONLY);
		if(fileOne == -1)
		{
			close(fileOne);
			printf("cat: %s: No such file or directory \n",argv[1]);
		}
		else
		{
			int fileTwo = open(argv[3], O_RDWR);
			if(fileTwo == -1)
			{
				close(fileTwo);	
				printf("cat: %s: No such file or directory \n",argv[3]);
				return;
			}
			char * c = "";
			lseek(fileTwo,sp->st_size,0);
			while(read(fileOne,c,1) > 0)
			{
				write(fileTwo,c,1);
			}
			close(fileOne);
			close(fileTwo);

		}
	}
	exit(0);
}
