#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char inputChar()
{
    // rewrite this functioin
    // num = (rand()%(upper - lower + 1)) + lower as described  in https://geeksforgeeks.org/generating-random-number-range-c/
    // create an array of target chars
    char array[14] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']', 'r', 's', 't', 'e', '\0'};
    int lower = 0; 
    int upper = 14; 
    int randomIndex = (rand() % (upper - lower + 1)) + lower; // get a random index from 0 - 14
    char ch = array[randomIndex]; // get the char from the array
    return ch;
}

char *inputString()
{
    // rewrite this function
    char *str; // pointer to char array
    //int size = (rand() % (20 - 15 + 1)) + 15; // size is a random number from 15 to 20
    int size = 6; // target size is an array of 6
    char array[size];
    str = array; // make the pointer-to-string point to first element of array
    int i = 0; // loop control
    for(i = 0; i < size; i++) // create the random string
    {
       str[i] = inputChar();
    }    

    return str;
}


void testme()
{
  time_t waitTime = 299; // 299 seconds, or just under 5 minutes 
  time_t endTime;
  endTime = time(NULL) + waitTime;
 
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  //while (tcCount < 400) // loop 400 times 
  while (time(NULL) < endTime) // loop for 5 min
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
