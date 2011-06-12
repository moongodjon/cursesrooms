#include "functions.h"
int main()
{
   oinit();
   finit( 9,14, 0, 2);
   printw(
   "   This game is so interesting and meaningfull\n"
   "and the reasons why are explained in this message...\n"
   "...which may or may not be complete\n"
   "\n"
   "(press any key to continue)\n");
   getch();
   clear();
   while(loop)
   {  switch(z)
      {  case 2 :
            if(lever[2][0].on)
            {  map[2][12][9]='.';
               map[2][14][9]='.';
            }break;
         case 3 :
            if(lever[3][0].on==1)
            {  rev(6);
               rev(5);
               lever[3][0].on=2;
            }
            if(lever[3][1].on==1)
            {  rev(7);
               rev(4);
               lever[3][1].on=2;
            }
            if(lever[3][2].on==1)
            {  rev(7);
               rev(5);
               lever[3][2].on=2;
            }
            if(lever[3][3].on==1)
            {  rev(6);
               rev(4);
               lever[3][3].on=2;
            }
            if(lever[3][4].on==1)
            {  rev(1);
               rev(3);
               lever[3][4].on=2;
            }
            if(lever[3][5].on==1)
            {  rev(0);
               rev(2);
               lever[3][5].on=2;
            }
            if(lever[3][6].on==1)
            {  rev(0);
               rev(3);
               lever[3][6].on=2;
            }
            if(lever[3][7].on==1)
            {  rev(1);
               rev(2);
               lever[3][7].on=2;
            }
            if(lever[3][0].on&&
               lever[3][1].on&&               
               lever[3][2].on&&               
               lever[3][3].on&&               
               lever[3][4].on&&               
               lever[3][5].on&&               
               lever[3][6].on&&               
               lever[3][7].on)
            {  map[2][9][6]='.';
               map[2][9][4]='.';
            }break; 
         case 4 :
            if(lever[4][0].on)
            {  map[4][ crate[4][0].y ][ crate[4][0].x ]='.';
               crate[4][0].x=9;
               crate[4][0].y=9;
               lever[4][0].on=0;
            }
            if(button[4][0].on)
            {  map[4][9][3]='.';
               map[4][9][1]='.';
            }
            else
            {  map[4][9][3]='|';
               map[4][9][1]='|';
            }
      }  
      levers();
      mesages();
      boxes();
      buttons();
      items();
      BlockMessage();
      uncover(1);
      showmap();
      input();
   }

   endwin();
   return 0;
}
