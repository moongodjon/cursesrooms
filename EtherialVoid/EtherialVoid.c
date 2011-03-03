#include "functions.h"

int main()
{
   initscr();
   keypad(stdscr, TRUE);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN,   COLOR_BLACK);
   init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
   clear();
   printw(
   "      Etherial Void   \n\n"
   "Is it that all exists only in the\n"
   "etherial landscape of the mind?\n\n"
   "The past is uncertian,\n\n"
   "The present is now the past,\n\n"
   "The future might only be thought of,\n\n"
   "Is then not our mind's eye\n"
   "the root of reality?\n\n"
   "But should that eye be blind,\n"
   "where then would rest the soul?"
   "\n\n"
   "(press any key to continue)\n");
   getch();
   clear();
   printw(
   "   I look,\n"
   "but I see nothing.");
   getch();
   clear();
   getch();
   printw(
   "   Perhaps,\n"
   "there is nothing to see.");
   getch();
   helpmsg="Use the arrow keys or WASD to move the charecter.";
   
   clear();
   while(loop)
   {  
      switch(z)
      {  
         case 0:
            nroom=1;
            eroom=2;
            sroom=3;
            wroom=4;
            light=2;
            msg(9,6,
            "There <is> something...\n"
            "dimly glowing etchings on the ground:\n"
            "'There is naught in this place to the north.'");
            wall=
            "Some sort of wall mesage should be displayed here,\n"
            "It should inform the player of the solidity of this wall,\n"
            "and it should warn that attempts to surpass this fact are admonishable.";
            if(sw[0]&&sw[1]&&sw[2]&&sw[3])
            {
               map[0][9][9]='^';
               smsg(9,9,
               "This is a new stairwell.");
            }
            break;
         case 1:
            sroom=0;
            lvr(9,9,0);
            break;
         case 2:
            wroom=0;
            lvr(9,9,1);
            break;
         case 3:
            nroom=0;
            lvr(9,9,2);
            break;
         case 4:
            eroom=0;
            lvr(9,9,3);
            break;
         default:
            endwin();
            printf("ERROR THE PROGGRAMMER HAS YET TO MAKE THIS LEVEL!!!\n");
            loop=0;
            return 1;
      }
      unmove();
      showmap();
      input();
   }

   endwin();
   return 0;
}
