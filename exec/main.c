#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>

int main ()
{
    pid_t pid = fork(); 
     initscr();                              // Включает ncurses
    if(has_colors() == FALSE)               // Проверка на поддержку цвета терминалом
	{	
        endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
    //raw();                                // Символы вводимые с клавиатуры не буферизируются, а сразу вносятся в ncurses
    cbreak();
    noecho();  

    switch (pid)
    {
        case 0: 
                {
                    long int ttime;
                    ttime = time(NULL);                 // Берем текущее время
                    char* t = ctime(&ttime);
                    printw("%s\n", t);
                    break;
                }
        default:
                {
                    long int ttime;
                    ttime = time(NULL);                 // Берем текущее время
                    char* t = ctime(&ttime);
                    printw("%s\n", t);
                }
    }

    wait();
    //aitpid();
	endwin(); 
    return 0;
}