#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>

char phraseN[] = "Hello, i'm procces n.";

WINDOW* createWin(int, int , int , int);      // Создание окна



int main ()
{
    
    char phrase1[] = "And I'm true process";
    char phrase2[] = "Hey Dude";
    unsigned len1 = sizeof(phrase1);
    unsigned len2 = sizeof(phrase2);

    initscr();                      // Включает режим работы с библиотекой ncurses
    raw();                          // Символы вводимые с клавиатуры не буферизируются, а сразу вносятся в программу 

    cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/



/*
    printw ("Do u wont make a clone? (Y/N)");
    char yes = getch();
    if (yes == 'Y' || yes == 'y' ||
        yes == 'Д' || yes == 'l')
    {
        pid_t pid = fork();
        switch (pid)
        {
            case 0:  printw("My name \t%d\t And I'm true process\n", getpid()); break;
            default: printw("Hey Dude My name\t%d\n", getpid());
        }
    }
 */   
    WINDOW *my_win;

	my_win = createWin(7, 13 + sizeof(phraseN), 2, 2);
    


    wborder(my_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');             // Замена стенок квадрата на пробелы
	getch();
	wrefresh(my_win);
	delwin(my_win);
    getch();

    //wait();
   // refresh();	                   // Выводит все на экран
    //halfdelay(10);		           // Ждет ввода в течении некоторого времени, после продолжает работу
    //	getch();		
	endwin();                      // Выключение режима работы с ncurses
    return 0;
}

WINDOW* createWin(int height, int width, int starty, int startx)
{
    WINDOW *win;
	win = newwin(height, width, starty, startx);
	box(win, 0 , 0);		// Устанавливаем символ поумолчанию для каробки 
    mvwprintw(win, starty + 1, startx + 2, "%s %d", phraseN, getpid());     // Пишем фразу в коробке 
    getch();
	wrefresh(win);		/* Show that box 		*/
    getch();
	return win;
}