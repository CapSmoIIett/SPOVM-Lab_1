#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <time.h>

char phraseN[] = "Hello, i'm procces n.";

WINDOW* createWinTime();                     // Создание окна c временем
WINDOW* createWin(char*, int, int, int,...); // Создание окна с надписью

char* getTime();

int main ()
{
    WINDOW* win1;
    WINDOW* win2;
    initscr();                              // Включает режим работы с библиотекой ncurses
    if(has_colors() == FALSE)               // Проверка на поддержку цвета терминалом
	{	
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    raw();                                  // Символы вводимые с клавиатуры не буферизируются, а сразу вносятся в программу 

    start_color();                          // Включаем цвета
    init_pair(1, COLOR_RED, COLOR_BLACK);   // Иницилируем комбинации цветов
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(3));                  // Устанавливает пару цветов

    win1 = createWinTime();
    win2 = createWin("This is:", 20, 2, 1, 100);

    move(12,0);      // Перемещаем курсор

    printw("Do you want create second process? (Y/N) ");
    attroff(COLOR_PAIR(3));
    char yes = getch();
    if (yes == 'Y' || yes == 'y')
    {
        pid_t pid = fork();                 // Создаем процесс
        switch (pid)
        {
            case 0:
            {  
                attron(COLOR_PAIR(2));
                printw("\nI'm not main process  My name %d", getpid()); 
                printw("\nDo you want create another process? (Y/N) ");           // Предлогаю создать еще один процесс
                attroff(COLOR_PAIR(2));

                char yes = getch();
                if (yes == 'Y' || yes == 'y')
                {
                    pid = fork();
                    switch (pid)
                    {
                        case 0: attron(COLOR_PAIR(4));
                                printw("\nI'm the third process. My name %d", getpid()); 
                                attroff(COLOR_PAIR(4));break;
                                
                        default: attron(COLOR_PAIR(2)); 
                                 printw("\nI'm the second process. My name %d", getpid());
                                 attroff(COLOR_PAIR(2));
                    }
                }
                getch();
                break;
            }
            default: 
            {
                attron(COLOR_PAIR(1));
                printw("\nI'm main process. My name %d.", getpid());
                attroff(COLOR_PAIR(1)); 
            }
        }
    }
    getch();
   
    wborder(win1, ' ', ' ', ' ',' ',' ',' ',' ',' '); // Замена стенок квадрата на пробелы
	wborder(win2  , ' ', ' ', ' ',' ',' ',' ',' ',' ');
    attroff(COLOR_PAIR(1));  // Отключение цветовой пары
    getch();		
	endwin();                      // Выключение режима работы с ncurses
    return 0;
}

WINDOW* createWinTime()
{
    WINDOW *win;
    
	win = newwin(8, 36, 2, 2);
	box(win, 0 , 0);		            // Устанавливаем символ для каробки 

    mvwprintw(win, 3, 4, "Hello, i'm procces n. %d", getpid());     // Пишем фразу в коробке 
    mvwprintw(win, 4, 4,"Now %s", getTime());  
    
    getch();
	wrefresh(win);		                // Выводим прямоугольник    
    getch();
	return win;
}

WINDOW* createWin( char* str, int starty, int startx, int amount, ...)
{
    WINDOW* win;
    int height = 3;
    int width  = 14 + sizeof(str)+ amount * 5;
    int* pointer = &amount; pointer++;

    win = newwin(height, width, starty, startx);
	box(win, 0 , 0);		                    // Устанавливаем символ поумолчанию для каробки 
    wrefresh(win);		                        // Выводим прямоугольник 

    move(starty + 1, startx + 2);
    printw("%s", str);                          // Пишем фразу в коробке 
    while (amount--) printw(" %d", *(pointer)); // Печать дополнительных символов

    getch();
	wrefresh(win);		// Выводим прямоугольник    
    getch();

    return win;
}

char* getTime()
{
    long int ttime;
    ttime = time(NULL);                 // Берем текущее время
    char* t = ctime(&ttime);

    int i = 0; while (t[i] != '\0') i++;
    t[i - 1] = '\0';                    // Удаляю знак табуляции который создает ctime (он ломает прямоугольник)
    return t;
}