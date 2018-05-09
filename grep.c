/********** grep.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{

   printf("GREPGREP");
   printf("argc: %d\n",argc);
  // GREP 2 argument
  if(argc == 2)
  {
    char buf1[1024];
    char buf2[1024];
    int i;
    for(i = 0; i < 1024; i++)
    {
      buf1[i] = 0;
      buf2[i] = 0;
    }
    while(strcmp("exit",buf1) != 0)
    {
      gets(buf1);
      char * temp = buf1;
      while(*temp)
      {
        char * tc = temp;
        int count = 0;
        while(count < strlen(argv[1]))
        {
          buf2[count] = *tc;
          *tc++;
          count++;
        }
        buf2[count] = '\0';
        if(strcmp(buf2,argv[1]) == 0)
        {
          printf(" %s\n",buf1);
          break;
        }
        *temp++;
      }
    }
  }
  // Grep 3 argment
  else if (argc == 3)
  {
    if(strcmp(argv[2],"|") == 0)
    {
      char buf1[1024];
      char buf2[1024];
      int i;
      for(i = 0; i < 1024; i++)
      {
        buf1[i] = 0;
        buf2[i] = 0;
      }
      i= 0;
      int j;
      while(getline(buf1))
      {
        //   printf("Line: %s\n",buf1);
          char * temp = buf1;
          while(*temp)
          {
            char * tc = temp;
            int count = 0;
            while(count < strlen(argv[1]))
            {
              buf2[count] = *tc;
              *tc++;
              count++;
            }
            buf2[count] = '\0';
            if(strcmp(buf2,argv[1]) == 0)
            {
              printf("%s",buf1);
              break;
            }
            *temp++;
          }
          for(i = 0; i < 1024; i++)
          {
            buf2[i] = 0;
          }
          i= 0;
        }
    }
    else
    {
      char buf1[1024];
      char buf2[1024];
      int i;
   
      for(i = 0; i < 1024; i++)
      {
        buf1[i] = 0;
        buf2[i] = 0;
      }
      int file = open(argv[2],O_RDONLY);
      if(file == -1)
      {
         printf("grep: %s: No such file or directory \n",argv[2]);
      }
      else
      {
        i= 0;
        int j;
        char * c = "";
        while(read(file,c,1) > 0)
        {
           if(*c != '\n')
           {
              buf1[i] = *c;
              i++;
           }
           else
           {
              buf1[i] = '\0';
              i = 0;
           //   printf("Line: %s\n",buf1);
              char * temp = buf1;
              while(*temp)
              {
                char * tc = temp;
                int count = 0;
                while(count < strlen(argv[1]))
                {
                  buf2[count] = *tc;
                  *tc++;
                  count++;
                }
                buf2[count] = '\0';
                if(strcmp(buf2,argv[1]) == 0)
                {
                  printf(" %s\n",buf1);
                  break;
                }
                *temp++;
              }
              for(i = 0; i < 1024; i++)
              {
                buf1[i] = 0;
                buf2[i] = 0;
              }
              i= 0;
           }

        }
      }
      close(file);
    }
  }
}
/*
int count = 0;
      while(1)
      {
        char buf[1024];
        int i;
        for(i = 0; i < 1024; i++)
        {
          buf[i] = 0;
        }
        char c = getc();
        i = 0;
        while (c!= EOF && c != '\r' && c != '\n')
        {
          buf[i] = c;
          i++;
          c = getc();
        }
        if(strcmp(buf,"EOF") == 0)
        {
          break;
        }
        buf[i] = '\n';
        buf[i+1] = '\0';
        for(i = 0; i < strlen(buf);i++)
        {
           if(buf[i] >= 97 && buf[i] < 123)
          {
            char converted[1];
            converted[0] = UpperCharacter[buf[i] - 97];
            buf[i] = *converted;
          }
        }
        if(*buf != '\n')
        {
          printf("%s",buf);
        }
      }
*/