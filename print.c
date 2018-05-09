/********** test.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
	printf("File name: %s\n",argv[2]);
	/*
	printf("Content: %s", " \n");
	int fd = open(argv[2],O_RDONLY);
	char * c = "";
	if(fd != -1)
	{
		printf("here");
		while(read(fd,c,1) > 0)
		{
			printf("%s",c);
		}
	}*/
}
