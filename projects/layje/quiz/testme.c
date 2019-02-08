#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//generate random character in range of ASCII 
//keyboard characters
char inputChar()
{  
    return rand() % (127 - 32) + 32;
}

//generate a random string
char *inputString()
{
    int NUM_CHARS = 10, i = -5;

    static int first = 1, second = 1;

    static char strArr[6];

    char charArr[] = {'c', 'e', 'f', 's', 't',
                      'j', 'l', 'm', 'r', '\0'}; 

    if (!(first || second)){
        for (i = 0; i < 6; i++){
        
        strArr[i] = charArr[rand() % NUM_CHARS];
      }
    }
    
    else if (first){
      
       first = 0;
       strArr[0] = 'r';
       strArr[1] = 'e';
       strArr[2] = 's';
       strArr[3] = 'e';
       strArr[4] = 't';
       strArr[5] = '\0';

    }
    else{
       second = 0;
       strArr[0] = 'r';
       strArr[1] = 'e';
       strArr[2] = 's';
       strArr[3] = 'e';
       strArr[4] = 't';
       strArr[5] = 't';
    }

    return strArr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
  
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
