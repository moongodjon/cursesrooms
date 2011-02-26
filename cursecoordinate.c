#include "functions.h"

int main()
{
   initscr();
   keypad(stdscr, TRUE);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN, COLOR_BLACK);
   clear();
   smsg(x,y,5,
   "   This game is so interesting and meaningfull",
   "and the reasons why are explained in this message...",
   "...which may or may not be complete",
   "",
   "(press any 3 keys to continue)");
   getch();
   //helpmsg="..."

   while(loop)
   {  
      input();
      switch(z)
      {  
         case 0:
            uroom=1;
            wroom=1;
           
            wall=
            "Some sort of wall mesage should be displayed here,\n"
            "It should inform the player of the solidity of this wall,\n"
            "and it should warn that attempts to surpass this fact are admonishable.";
           
            msg(9,9,
            "THIS SPOT IS IMPORTANT FOR THIS REASON");
            smsg(2,9,2,
               "   This spot is UBER important :)",
               "It clears the screen to show you something!!!! ");
            smsg(2,9,1,
               "   And it can do it twice!!!");
            smsg(2,9,2,
               "",
               "And thrice as well!!! :)");
            break;
         case 1:
            wall=
            "this is a wall in room 1";
            droom=2;
            eroom=0;
            sroom=4;
            break;
         case 2:
            wall=
            "this is a more interesting wall in room 2";
            sroom=3;
            uroom=1;
            break;
         case 3:
            wall=
            "in room 3, the wall is so iteresting, it's unsurpassable...";
            nroom=2;
            break;
         case 4:
            wall=
            "...surpassed only by these walls in woof 4\n"
            "(see room 3's walls)";
            smsg(6,14,11,
            "   this is an object of unsermountable power...",
            "It will somehow help you on your quest,",
            "which has neither been defined or accepted...",
            "",
            "...once the master programmer imbues it with ",
            "the power to do such.",
            "",
            "Until then, walk from here back to begining,",
            "and from there to here 9 times 7.",
            "",
            "(that wont work either :( )");
            nroom=1;
            break;
         default:
            loop=0;
            return 1;
      }
      unmove();
      showmap();
   }

   endwin();
   return 0;
}
