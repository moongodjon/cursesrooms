#include "functions.h"
int main()
{
   initscr();
   keypad(stdscr, TRUE);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN,   COLOR_BLACK);
   init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
   init_pair(4, COLOR_BLUE,    COLOR_BLACK);

   finit( 9,14, 0, 2);
   
   printw(
   "   This game is so interesting and meaningfull\n"
   "and the reasons why are explained in this message...\n"
   "...which may or may not be complete\n"
   "\n"
   "(press any 3 keys to continue)\n");
   getch();
   getch();
   getch();
   //helpmsg="..."
   clear();

   while(loop)
   {  
      switch(z)
      { case 0:
          uroom=1;
          break;
        case 1:
          droom=0;
          uroom=2;
          break;
 
      }
      unmove();
      uncover(1);
      showmap();
      input();
   }

   endwin();
   return 0;
}
