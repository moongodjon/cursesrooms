#include <curses.h>
#include <math.h>
//#include <stdarg.h>
#include <string.h>
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
int sw[100];                                         /* an array of switch variables */
int light=3;                                      /* how far the charecter can see   */
char* wall;                                       /* what to say when you hit a wall */
char* helpmsg=
"Some sort of guidence message should be displayed here.";

int scrw,                                         /* how wide the screen is */
    scrh;                                         /* how tall the screen is */
int mask[100][19][19];                            /* what parts of the map are visible */

void finit()
{ 
   getmaxyx(stdscr,scrh,scrw);                       /* fill the variables scrw & scrh with correct #'s */

   int a,b,c;

   for(a=0;a>=100;a++)
      {
   for(b=0;b>=19 ;b++)
    {
   for(c=0;c>=19 ;c++)
   {
      mask[a][b][c]=0;
   }}}

}
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
      

   for(hp=0; hp<19; hp++)                            /* for each spot on the map */
   {
      for(wp=0; wp<19; wp++)                            /* || */
      {
         if(sqrt((wp-x)*(wp-x)+(hp-y)*(hp-y)) <= light)
         {
            if(map[z][hp][wp]=='M')
            {
               mvaddch((scrh-19)/2+hp,(scrw-38)/2+wp*2,'o'|A_BLINK|COLOR_PAIR(2));
            }
            else if(map[z][hp][wp]=='o')
            {
               mvaddch((scrh-19)/2+hp,(scrw-38)/2+wp*2,'o'| A_NORMAL);
            }
            else
            {
               mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
            }
         }
         if(wp==x && hp==y)                                            /* if the charecter is at this spot... */
         {
            mvaddch((scrh-19)/2+y,(scrw-38)/2+x*2,'A'| COLOR_PAIR(1));               /* ...print him */
         }
      }
   }
   mvprintw((scrh-1),0,"%i ",x);
   mvprintw((scrh-1),3,"%i ",y);
   mvprintw((scrh-1),6,"%i ",z);
   refresh();                                        /* display all the changes to the screen */
}


void unmove()
{
   char file[10];
   if(x>=19||x<=-1||y>=19||y<=-1)
   {
     sprintf(file, "%s%d", ".", z); 
     mvprintw(0,0,"\n\n\n");
     mvaddch((scrh-19)/2+py,(scrw-38)/2+px*2,' ');               /* ...print him */
     refresh();
     scr_dump(file);
     if(x>=19)                                                          /* go from 1 room to another */
     {
        x=0;
        z=eroom;
     }
     if(x<=-1)
     {
        x=18;
        z=wroom;
     }
     if(y>=19)
     {
        y=0;
        z=sroom;
     }
     if(y<=-1)
     {
        y=18;
        z=nroom;
     }   
     sprintf(file, "%s%d", ".", z); 
     clear();                                     /* refresh needs a bit of coaxing to work right */
     refresh();
     scr_restore(file);
     refresh();
   }
   switch(map[z][y][x])
   {  
      case '-': /* make it solid and show wall[]  */
      case '|':
      case '+':
         y=py;
         x=px;
         mvprintw(0,0,"\n\n\n");
         mvprintw(0,0,"%s",wall);
         break;
      case '^': /* go up  */
      case 'U':
         sprintf(file, "%s%d", ".", z); 
         mvprintw(0,0,"\n\n\n");
         mvaddch((scrh-19)/2+py,(scrw-38)/2+px*2,' ');               /* ...print him */
         refresh();
         scr_dump(file);
         z=uroom;
         sprintf(file, "%s%d", ".", z); 
         clear();                                     /* restore needs a bit of coaxing to work right */
         refresh();
         scr_restore(file);
         refresh();
         break;
      case 'V': /* go down */
      case 'D':
         sprintf(file, "%s%d", ".", z); 
         mvprintw(0,0,"\n\n\n");
         mvaddch((scrh-19)/2+py,(scrw-38)/2+px*2,' ');               /* ...print him */
         refresh();
         scr_dump(file);
         z=droom;
         sprintf(file, "%s%d", ".", z); 
         clear();                                     /* restore needs a bit of coaxing to work right */
         refresh();
         scr_restore(file);
         refresh();
         break;
      case 'o': /* make solid, but no mesage */
      case 'M':
      case '#':
         y=py;x=px;
         break;
   }
}
void msg(int lx,int ly, char* msg)
{
   if(x==lx && y==ly)
   {
      mvprintw(0,0,"\n\n\n");
      move(0,0);
      //mvprintw(0,0,"%c\n\n",msg[0]);
      int i;
      int color=0;
      for(i=0; i<strlen(msg); i++)
      {
         if     (msg[i]=='\'' && color==0)
         {
            color=1;
            addch(msg[i]);
            attron(COLOR_PAIR(1));
         }
         else if(msg[i]=='\'' && color==1)
         {
            color=0;
            attroff(COLOR_PAIR(1));
            addch(msg[i]);
         }
         else if(msg[i]=='<')
            {attron (A_BOLD);}
         else if(msg[i]=='>')
            {attroff(A_BOLD);}
         else
         {
            addch(msg[i]);
         }
      
      }

   }

}

void smsg(int lx, int ly,char* msg)
{
   if(lx==x && ly==y)
   {

      char file[10];
      sprintf(file, "%s%d", ".", z);
      scr_dump(file); 
      WINDOW *my_win;
      my_win=newwin(19,37,(scrh-19)/2,(scrw-38)/2);
     // wborder(my_win,'|','|','-','-','/','\\','/','\\');
      wprintw(my_win,"%s",msg);
      wrefresh(my_win);
      getch();
      wclear(my_win);
      wrefresh(my_win);
      delwin(my_win);
      scr_restore(file);
      refresh();
   }
}

void lvr(lx,ly,n)
{
   if(lx==x && ly==y && sw[n]==0)
     {sw[n]=1;}
   if(sw[n])
      map[z][ly][lx]='M';
   else
      map[z][ly][lx]='o';
}
