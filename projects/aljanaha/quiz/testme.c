#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *all = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

const int maxTime = 5;
char inputChar()
{
  // TODO: rewrite this function
  int chosen = rand() % 96;
  return all[chosen];
}

char *inputString()
{
  // TODO: rewrite this function
  if (rand() % 101 >= 99)
  {
    return "reset";
  }
  char *generated = NULL;
  int length = 5;
  generated = malloc(sizeof(char) * (length + 1));
  for (int i = 0; i < length; i++)
  {
    generated[i] = inputChar();
  }
  return generated;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  int keep = 1;
  while (keep)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0)
      state = 1;
    if (c == '(' && state == 1)
      state = 2;
    if (c == '{' && state == 2)
      state = 3;
    if (c == ' ' && state == 3)
      state = 4;
    if (c == 'a' && state == 4)
      state = 5;
    if (c == 'x' && state == 5)
      state = 6;
    if (c == '}' && state == 6)
      state = 7;
    if (c == ')' && state == 7)
      state = 8;
    if (c == ']' && state == 8)
      state = 9;
    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
    {
      printf("error ");
      keep = 0;
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}
