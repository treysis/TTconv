#include <stdio.h>

int main (int argc, char argv[])
{
  char buf[1024];
  int n;

  do {
    n = fread(buf, sizeof(char), sizeof(buf), stdin);
    fwrite (buf, sizeof(char), n, stdout);
  } while (n > 0);
}

