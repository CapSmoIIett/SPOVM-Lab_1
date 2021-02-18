#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <time.h>

char phraseN[] = "Hello, i'm procces n.";

WINDOW* createWinTime();                // Создание окна c временем
WINDOW* createWin(char*, int, int, int,...); // Создание окна


int main ()
{
    WINDOW* win1;
    WINDOW* win2;
    initscr();                              // Включает режим работы с библиотекой ncurses
    if(has_colors() == FALSE)               // Проверка на поддержку цвета терминалом
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    raw();                                  // Символы вводимые с клавиатуры не буферизируются, а сразу вносятся в программу 

    start_color(); 
    init_pair(1, COLOR_RED, COLOR_BLACK);                  // Иницилируем комбинацию, черный цвет на розовом фоне
    attron(COLOR_PAIR(1));                                 // Устанавливает пару цветов

    win1 = createWinTime();
    win2 = createWin("Shit this is:", 20, 2, 1, getpid());

    move(12,0);      // Перемещаем курсор

    printw("Do u wont make a clone? (Y/N)");
    char yes = getch();
    if (yes == 'Y' || yes == 'y')
    {
        pid_t pid = fork();                 // Создаем процесс
        switch (pid)
        {
            case 0:
            {  
                printw("\nHey, I'm not true process  My name %d", getpid()); 
                printw("\nDo u wont make a second clone? (Y/N)"); 
                char yes = getch();
                pid = fork(); 
                switch (pid)
                {
                    case 0: printw("\nI'm born. I a %d", getpid()); break;
                    default: printw("\nWhoo. I doit. I'm steel %d", getpid());
                }
                break;
            }
            default: printw("\nMy name %d. And I'm true process", getpid()); 
        }
        // После вывода я предлогаю еще раз создать копию
        
    }
   
    wborder(win1, ' ', ' ', ' ',' ',' ',' ',' ',' '); // Замена стенок квадрата на пробелы
	wborder(win2  , ' ', ' ', ' ',' ',' ',' ',' ',' ');
    getch();
	//wrefresh(win1);
    attroff(COLOR_PAIR(1) | A_STANDOUT | A_UNDERLINE);  // Отключение цветовой пары
    getch();		
	endwin();                      // Выключение режима работы с ncurses
    return 0;
}

WINDOW* createWinTime()
{
    WINDOW *win;
    long int ttime;
    ttime = time(NULL);                 // Берем текущее время
    char* t = ctime(&ttime);

    int i = 0; while (t[i] != '\0') i++;
    t[i - 1] = '\0';                    // Удаляю знак табуляции который создает ctime (он ломает прямоугольник)

	win = newwin(8, 14 + sizeof(phraseN), 2, 2);
	box(win, 0 , 0);		            // Устанавливаем символ поумолчанию для каробки 

    mvwprintw(win, 3, 4, "%s %d", phraseN, getpid());     // Пишем фразу в коробке 
    mvwprintw(win, 4, 4,"Now %s", t);  
    
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
    wrefresh(win);		// Выводим прямоугольник 

    move(starty + 1, startx + 2);
    printw("%s", str);                          // Пишем фразу в коробке 
    while (amount--) printw(" %d", *(pointer));   // Печать дополнительных символов

    getch();
	wrefresh(win);		// Выводим прямоугольник    
    getch();

    return win;
}