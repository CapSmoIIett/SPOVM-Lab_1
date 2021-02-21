#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>

int main ()
{
    long int ttime;
    ttime = time(NULL);                 // Берем текущее время
    char* t = ctime(&ttime);
    printf("%s", t);
    return 0;
}