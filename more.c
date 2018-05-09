
/********** more.c file *************/
#include "ucode.c"

#define SMORE 600

int main(int argc, char * argv[ ])
{
  printf("MOREMORE");
  // More no argument.
  if(argc == 1)
  {
    while(1)
    {
      char input[1024];
      gets(input);
      if(strcmp(input,"exit") == 0)
      {
        exit(0);
      }
      printf("input: %s\n",input);
    }
  }
  // More one argument (file name)
  else if(argc == 2)
  {  
    if(strcmp(argv[1],"|") == 0)
    {
      char c[1024];
      int count = 0;
      char * cmd = "";
      int in = open("/dev/tty0", O_RDONLY);
      while(getline(c))
      {
        if(count > SMORE)
        {
          printf("-------------------------------------------------- %s \n", cmd);
          printf("More: click any key to continue, click e to exit %s \n", cmd);
          read(in,cmd,1); 
          printf("--------------------------------------------------\n", cmd);
          if(*cmd == 'e')
          {
            break;
          }  
          count = 0; 
        }
        else
        {
          count = count + strlen(c);
          printf("%s",c); 
        }    
      }
    }
    else
    {
      struct stat fstat, *sp = &fstat;
      stat(argv[1], sp);
      int total = 0;
      int file = open(argv[1], O_RDONLY);
      char * c = "";
      int i;
      int count = 0;
      if(file != -1)
      {
        i = read(file,c,1);
        while(i > 0)
        {     
          if(count < SMORE)
          {
            printf("%s",c);
            i = read(file,c,1);
            count++;
          }
          else
          {
            while(i > 0 && *c != '\n')
            {
               printf("%s",c);
               i = read(file,c,1);
               count++;
            }
            total = total + count;
            printf("%s\n--------------------------------------\n"," ");
            printf("READ: %d LEFT: %d\n",total,sp->st_size);
            printf("MORE: %s Click enter to continue...\n\n", argv[1]);
            gets(c);
            if(strcmp(c,"exit") == 0)
            {
              return;
            }
            count = 0;
          }
        }
      }
      else
      {
        printf("more: %s: No such file or directory \n",argv[1]);
      }
      close(file); 
    }
  }
}

 /*
      char * input = "";
      char * cmd = "";
      int count = 0;
      int in = open("/dev/tty0", O_RDONLY);
      int out = open("/dev/tty0", O_WRONLY);
      int pipeNumber;
      if(*argv[2] == '0')
      {
        pipeNumber = 0;
      }
      else if(*argv[2] == '1')
      {
         pipeNumber = 1;
      }
      while(read(pd[pipeNumber][0],input,1) > 0)
      {
        if(count == SMORE)
        {  
          while(*input != '\n')
          {
            read(pd[pipeNumber][0],input,1);
            printf("%s",input);
            count++;
          }
          printf("-------------------------------------------------- %s", cmd);
          printf("More: click any key to continue, click e to exit %s", cmd);
          read(in,cmd,1); 
           printf("--------------------------------------------------\n", cmd);
          if(*cmd == 'e')
          {
            break;
          }   
          count = 0; 
        }
        else
        {
          printf("%s",input);
          count++;
        }
      }*/
