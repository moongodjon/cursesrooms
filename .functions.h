#include <curses.h>
#include <math.h>
//#include <stdarg.h>
#include <string.h>
#include <time.h>
                                                  /*!!!! make sure to compile with -lm -lncurses !!!!*/
#include "maps.h"

int loop=1;                                       /* the game continues as long as this is 1 */

int x,                                          /* where the player is */
    y,
    z;                                             /* (on what floor) */

int py=0,                                         /* where the player was */
    px=0;

int nroom,                                        /* what room is to the nrth/sth/e/w/abve/belw */
    sroom,
    eroom,
    wroom,
    uroom,
    droom;
int sw[100];                                         /* an array of switch variables */
int light;                                      /* how far the charecter can see   */
int msgtime;                                    /* how long the last mesage stays up */
//   time_t t;

time_t t;
   
char* wall;                                       /* what to say when you hit a wall */
char* helpmsg=
"Some sort of guidence message should be displayed here.";

int scrw,                                         /* how wide the screen is */
    scrh;                                         /* how tall the screen is */
int mask[100][19][19];                            /* what parts of the map are visible */

int inp;                                          /* player input */

void finit(int nx,int ny,int nz,int nlight)
{ 
   getmaxyx(stdscr,scrh,scrw);                       /* fill the variables scrw & scrh with correct #'s */

   int a,b,c;

   for(a=0;a>=100;a++)
      {
   for(b=0;b>=19 ;b++)
    {
   for(c=0;c>=19 ;c++)
   {
       sw[a]      =0;
     mask[a][b][c]=0;
   }}}
   
   z=nz;
   y=ny;
   x=nx;
   light=nlight;
}
void help()                                       /* tell the user how to play the game */
{
   mvprintw(0,0,"\n\n\n");
   mvprintw(0,0,"%s",helpmsg);
}

void input()                                      /* take input from the player and do his bidding */
{
   py=y;
   px=x;
   timeout(10);
   inp=getch();                                      /* put player input into variable inp */
   timeout(-1);
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
void uncover(int shadow)
{
   int wp,
       hp,
       xp,
       yp,
       pp, // point placement
//     mp, // maximum pp value // (that's what she said)
       pt, // photon test
       lp; // light placement

   #define PHOTON_NUM 32
   struct photon
   {   int x;
       int y;
       float xd; /* direction */
       float yd;
   } ray[PHOTON_NUM];

   for(pp=0;pp<PHOTON_NUM;pp++) /* ready the photon torpedoes */
   {  ray[pp].x =x;
      ray[pp].y =y;
      
      if      (pp<=PHOTON_NUM/4)
      {  ray[pp].xd=pp/(PHOTON_NUM/4);
         ray[pp].yd=1-ray[pp].xd;
      }
      else if (pp<=PHOTON_NUM/2)
      {  ray[pp].xd=(pp-PHOTON_NUM/4)/(PHOTON_NUM/4);
         ray[pp].yd=1-ray[pp].xd;
         ray[pp].yd*=-1;
      }
      else if (pp<=(PHOTON_NUM/4)*3)
      {  ray[pp].xd=(pp-PHOTON_NUM/2)/(PHOTON_NUM/4);
         ray[pp].yd=1-ray[pp].xd;
         ray[pp].yd*=-1;
         ray[pp].xd*=-1;
      }
      else if (pp<=PHOTON_NUM)
      {  ray[pp].xd=(pp-(PHOTON_NUM/4)*3)/(PHOTON_NUM/4);
         ray[pp].yd=1-ray[pp].xd;
         ray[pp].xd*=-1;
      }
      else
      {  printw("PHOTON_NUM EXCEEDED!");
      }
      while(pt==0) /* fireing torpedoes */
      {  switch(map[z][ray[pp].y][ray[pp].x])
          {  case '.':
                printw("testing .");
                mask[z][ray[pp].y][ray[pp].x]=1;
                ray[pp].y*=ray[pp].yd;
                ray[pp].x*=ray[pp].xd;
             default :
                printw("LOLOL");
                pt=1;
          } 
           
      }
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
         if(mask[z][hp][wp]==1)
         {
            if(map[z][hp][wp]=='M')
            {
            }
            else if(map[z][hp][wp]=='o')
            {
               mvaddch((scrh-19)/2+hp,(scrw-38)/2+wp*2,'o'| A_NORMAL);
            }
            switch(map[z][hp][wp])
            {
               case 'M':
                  mvaddch((scrh-19)/2+hp,(scrw-38)/2+wp*2,'o'|A_BLINK|COLOR_PAIR(2));
                  break; 
               case '+':
               case '-':
               case '|':
               case 'X':
               case 'x':
                  attron (COLOR_PAIR(3)|A_BOLD);
                  mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
                  attroff(COLOR_PAIR(3)|A_BOLD);
                  break; 
               case '^':
               case 'V':
                  attron (COLOR_PAIR(4)|A_BOLD);
                  mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
                  attroff(COLOR_PAIR(4)|A_BOLD);
                  break; 
               default:
                  mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
                  break; 
            }
   
         }
         else
         {
            //attron (A_REVERSE);
            mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"  ");   /* print what is at this spot (nothing) */
            //attroff(A_REVERSE);
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
   mvprintw((scrh-1),9,"%i ",msgtime);
   if(msgtime==0)
      {mvprintw(0,0,"\n\n\n");}
   else if(time(NULL)>t)
      {msgtime--;}
   t=time(NULL);

   move(scrh-1,scrw-1);
   refresh();                                        /* display all the changes to the screen */
}


void unmove()
{
   char file[10];
   if(x>=19||x<=-1||y>=19||y<=-1)
   {
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
   }
   switch(map[z][y][x])
   {  
      case '-': /* make it solid and show wall[]  */
      case '|':
      case '+':
      case 'X':
         y=py;
         x=px;
         mvprintw(0,0,"\n\n\n");
         mvprintw(0,0,"%s",wall);
         msgtime=5;
         break;
      case '^': /* go up  */
      case 'U':
         if(inp!=ERR) /*the player has to WANT to go up*/
            z=uroom;
         break;
      case 'V': /* go down */
      case 'D':
         if(inp!=ERR)
            z=droom;
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
      msgtime=5;
      mvprintw(0,0,"\n\n\n");
      move(0,0);
      
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
   if(lx==x && ly==y && inp!=ERR)
   {

      WINDOW *my_win;
      my_win=newwin(19,37,(scrh-19)/2,(scrw-38)/2);
     // wborder(my_win,'|','|','-','-','/','\\','/','\\');
      wprintw(my_win,"%s",msg);
      wrefresh(my_win);
      getch();
      showmap();
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
void mlvr(lx,ly,n)
{
   if(sw[n])
      map[z][ly][lx]='M';
   else
      map[z][ly][lx]='o';
}
void flip(int n)
{
   if(sw[n])
     {sw[n]=0;}
   else
     {sw[n]=2;}
}

