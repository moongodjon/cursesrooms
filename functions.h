#include <curses.h>
#include <math.h>
#include <stdarg.h>
                                                  /*!!!! make sure to compile with -lm -lncurses !!!!*/
#include "maps.h"

int loop=1;                                       /* the game continues as long as this is 1 */

int x=9,                                          /* where the player is */
    y=9,
    z=0;                                             /* (on what floor) */

int py=9,                                         /* where the player was */
    px=9;

int nroom,                                        /* what room is to the nrth/sth/e/w/abve/belw */
    sroom,
    eroom,
    wroom,
    uroom,
    droom;

char* wall;                                       /* what to say when you hit a wall */
char* helpmsg=
"Some sort of guidence message should be displayed here.";

void help()                                       /* tell the user how to play the game */
{
   mvprintw(0,0,"\n\n\n");
   mvprintw(0,0,"%s",helpmsg);
}

void input()                                      /* take input from the player and do his bidding */
{
   int inp;
   py=y;
   px=x;
   inp=getch();                                      /* put player input into variable inp */
   switch(inp)
   {
      case 'w':
      case KEY_UP:
      y--;     break;                                /* if the input is 'w' or 'k' y is 1 less (you go up) */
      case 'a':
      case KEY_LEFT:
      x--;     break;                                /* 'a' or 'h': x is 1 less (left) */
      case 's':
      case KEY_DOWN:
      y++;     break;                                /* 's' or 'j': y is 1 more (down) */
      case 'd':
      case KEY_RIGHT:
      x++;     break;                                /* 'd' or 'l': x is 1 more (right)*/
      case 'Q':
      loop--;  break;                                /* 'Q': loop is 1 less (0) and the game ends :( */
      case 'h':
      case '/':
      case '?':
      help();  break;                                /* 'H' '/' or '?': display help */
   }                           

}

void showmap()                    /* show the map */
{


   int wp,                                           /* used in the for loop, (width placement) */
       hp;                                           /* (height placement) */
      
   int scrw,                                         /* how wide the screen is */
       scrh;                                         /* how tall the screen is */

   getmaxyx(stdscr,scrh,scrw);                       /* fill the variables scrw & scrh with correct #'s */

   for(hp=0; hp<19; hp++)                            /* for each spot on the map */
   {
      for(wp=0; wp<19; wp++)                            /* || */
      {
         if(sqrt((wp-x)*(wp-x)+(hp-y)*(hp-y)) <= 3)
         mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
         if(wp==x && hp==y)                                            /* if the charecter is at this spot... */
         {mvaddch((scrh-19)/2+hp,(scrw-38)/2+wp*2,'A'| COLOR_PAIR(1));}               /* ...print him */
      }
   }
   mvprintw((scrh-1),0,"%i ",x);
   mvprintw((scrh-1),3,"%i ",y);
   mvprintw((scrh-1),6,"%i ",z);
   refresh();                                        /* display all the changes to the screen */
}


void unmove()
{
   char file[10];                                                     /* make a string .<z> */
   int scrw,                                         /* how wide the screen is */
       scrh;                                         /* how tall the screen is */

   if(x>=19)                                                          /* go from 1 room to another */
     {x=0 ;z=eroom;clear();}
   if(x<=-1)
     {x=18;z=wroom;clear();}
   if(y>=19)
     {y=0 ;z=sroom;clear();}
   if(y<=-1)
     {y=18;z=nroom;clear();}
   
   switch(map[z][y][x])
   {  
      case '-':
      case '|':
      case '+':
         y=py;
         x=px;
         mvprintw(0,0,"\n\n\n");
         mvprintw(0,0,"%s",wall);
         break;
      case '^':
      case 'U':
         z=uroom;clear();
         break;
      case 'V':
      case 'D':
         z=droom;clear();
         break;
      case 'o':
         y=py;x=px;
         break;
   }

}
void msg(int lx,int ly, char* msg)
{
   if(x==lx && y==ly)
   {
      mvprintw(0,0,"\n\n\n");
      mvprintw(0,0,"%s\n\n",msg);
   }

}

void smsg(int lx, int ly,int num, ...)
{
   if(lx==x && ly==y)
   {

      int scrw,                                         /* how wide the screen is */
          scrh;                                         /* how tall the screen is */

      getmaxyx(stdscr,scrh,scrw);                       /* fill the variables scrw & scrh with correct #'s */

      char file[10];
      sprintf(file, "%s%d", ".", z);
      
      scr_dump(file);
      clear();
      
      va_list  ap;
      va_start(ap,num);
      int pos;

      for(pos=0; pos<num; pos++)
      {
         mvprintw((scrh-19)/2+pos,(scrw-38)/2,"%s",va_arg(ap,char*));
      }
      va_end(ap);
      getch();
      scr_restore(file);
   }
}

void lvr()
{
}
