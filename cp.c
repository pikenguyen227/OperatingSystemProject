/********** cat.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
	if(argc == 3)
	{
		struct stat fstat, *sp = &fstat;
        stat(argv[2], sp);
        char * c = "";
        if(sp->st_mode == 8612)
        {
        	printf("File name: %s\n",argv[1]);
        	return;
        }
        stat(argv[1], sp);
        int fdOne = open(argv[1],O_RDONLY);
		if(fdOne != -1)
		{      
			int fdTwo = open(argv[2],O_WRONLY);
			if(fdTwo != -1)
			{
			  close(fdTwo);
			}
			else
			{
			  if((sp->st_mode & 0040000) == 0040000)
			  {
			    mkdir(argv[2]);
			  }
			  else if((sp->st_mode & 0100000) == 0100000)
			  {
			    creat(argv[2]);
			  }
			}  
			fdTwo = open(argv[2],O_WRONLY);
			if(fdTwo != -1)
			{
			  while(read(fdOne,c,1) > 0)
			  {
			    write(fdTwo,c,1);    
			  }
			}
			close(fdTwo);
		}
		else
		{
			printf("cp: %s: No such file or directory \n",argv[1]);
		}
		close(fdOne);
	}
}


