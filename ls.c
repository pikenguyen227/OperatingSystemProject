
/********** ls.c file *************/
#include "ucode.c"

int main(int argc, char * argv[ ])
{
  if(argc == 2)
  {
    ls_file(argv[1]);
  }
  
}

int ls_file(char * fname)
{
  struct stat fstat, *sp = &fstat;
  char *ftime; //* ctime(long * time);
  int r, i;
  char sbuf[4096];
  char * tempd = fname;
  r = stat(fname, sp); // stat the file
  if((sp->st_mode & 0120000) == 0120000)
  {
    char * ch = "l";
    printf("%s",ch);
  }
  else if((sp->st_mode & 0040000) == 0040000)
  {
    char * ch = "d";
    printf("%s",ch);
  }
  else if((sp->st_mode & 0100000) == 0100000)
  {
    char * ch = "-";
    printf("%s",ch);
  }
  for(i = 8; i >= 0; i--)
  {
    if(sp->st_mode & (1<<i))
    {
      char rwx[1];
      rwx[0] = t1[i];
      printf("%s", rwx); //print permission bit as r w x
    }
    else
    {
      char rwx[1];
      rwx[0] = t2[i];
      printf("%s", rwx); //print permission bit as -
    }
  }
  printf(" %d", sp->st_nlink); // link count
  printf("%d", sp->st_uid);
  printf("%d", sp->st_size); // file size
  printf("%d", sp->st_ctime);
  printf(" %s\n", fname);
}
/*
int ls_dir()
{
  int fd = open(".",O_RDONLY);

}*/