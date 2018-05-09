/********** test.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
	if(argc == 3 && strcmp(argv[1],"<") == 0)
	{
		int pid, status;
		printf("inFile: %s\n",argv[2]);
		int fd = open(argv[2],O_RDONLY);
		if(fd != -1)
		{
			char buf[1024];
			int i;
			for(i = 0; i < 1024; i++)
			{
				buf[i] = 0;
			}
			char * c = "";
			i = 0;
			while(read(fd,c,1) > 0)
			{
				if(*c != '\n')
				{
					buf[i] = *c;
					i++;
				}
				else
				{
					buf[i] = '\0';
					printf("Line %s\n",buf);
					pid = fork();
					if (pid==0)
					{
			        	exec(buf);
					}
			        else
			        {
			        	pid = wait(&status);
			        }
					for(i = 0; i < 1024; i++)
					{
						buf[i] = 0;
					}
					i = 0;
				}
			}
		}
		else
		{
			printf("a.out: %s: No such file or directory \n",argv[2]);
		}
	}
	
}
