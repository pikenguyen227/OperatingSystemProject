/********** l2u.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
  char * UpperCharacter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  printf("L2UL2U");
  // L2U no argument.
  if(argc == 1)
  {
    char buf1[1024];
    char * newline = "\n";
    while(strcmp("exit",buf1) != 0)
    {
      char * tc  = buf1;
      if(*tc)
      {
        while(*tc)
        {
          if(*tc >= 97 && *tc < 123)
          {
            char converted[1];
            converted[0] = UpperCharacter[*tc - 97];
            printf("%s",converted);
          }
          else
          {
            char current[1];
            current[0] = *tc;
            printf("%s",current);  
          } 
          *tc++;
        }
        printf("%s",newline);
      }
      gets(buf1);
    }  
  }
  else if(argc == 2)
  {
    if(strcmp(argv[1],"|") == 0)
    {     
      char c[1024];
      while(getline(c))
      {
        char * t = c;
        while(*t)
        {
          if(*t >= 97 && *t < 123)
          {
            char converted[1];
            converted[0] = UpperCharacter[*t - 97];
            *t = *converted;
          }
          *t++;
        }
        printf("%s",c);     
      }
    }
    else
    {
      int fileOne = open(argv[1], O_RDONLY);
      char * c = "";
      if(fileOne == -1)
      {
        printf("l2u: %s: No such file or directory \n",argv[1]);
        return;
      }
      else
      {
        while(read(fileOne,c,1) > 0)
        {
          if(*c >= 97 && *c < 123)
          {
            char converted[1];
            converted[0] = UpperCharacter[*c - 97];
            printf("%s",converted);
          }
          else
          {
            printf("%s",c);
          } 
        }
        close(fileOne);
      }
    }
  }
  //L2U 3 arguments
  else if(argc == 3)
  {
    int fileOne = open(argv[1], O_RDONLY);
    char * c = "";
    if(fileOne == -1)
    {
      printf("l2u: %s: No such file or directory \n",argv[1]);
      return;
    }
    else
    {
      int fileTwo = open(argv[2], O_WRONLY);
      if(fileTwo == -1)
      {
        close(fileTwo);
        creat(argv[2]);
      }
      else
      {
        close(fileTwo);
      }
      fileTwo = open(argv[2], O_WRONLY);
      while(read(fileOne,c,1) > 0)
      {
        if(*c >= 97 && *c < 123)
        {
          char converted[1];
          converted[0] = UpperCharacter[*c - 97];
          write(fileTwo,converted,1);
        }
        else
        {
          write(fileTwo,c,1);
        } 
      }
      close(fileTwo);
      close(fileOne);
    }
  }
  
}
