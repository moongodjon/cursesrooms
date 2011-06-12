#include <curses.h>
#include <math.h>
//#include <stdarg.h>
#include <string.h>
#include <time.h>
                                                  /*!!!! make sure to compile with -lm -lncurses !!!!*/
#include "maps.h"
#define FLOORS 100
#define SWITCHES 100

int loop=1;                                       /* the game continues as long as this is 1 */

int x,                                          /* where the player is */
    y,
    z;                                             /* (on what floor) */

int py=0,                                         /* where the player was */
    px=0;

int nroom[FLOORS],                                       /* what room is to the nrth/sth/e/w/abve/belw */
    sroom[FLOORS],
    eroom[FLOORS],
    wroom[FLOORS],
    uroom[FLOORS],
    droom[FLOORS];

int sw[SWITCHES];                                         /* an array of switch variables */

struct s
{  int   x,
         y;
   int   on;
   char* hit;
} *lever[FLOORS];

struct it
{  int   x,
         y;
   char  ch;
   char* name;
   char* hit;
}item[FLOORS][10]; /*100 floors 10 items/floor*/

struct bx
{  int    x,
          y;
   char  ch;
   char* hit;
}crate[FLOORS][10]; /*100 floors 10 boxes/floor*/

struct m
{  int   x,
         y;
   char  ch;
   char *hit;
}mesage[FLOORS][10];

struct bt
{  int   x,
         y,
        on;
   char ch;
}button[FLOORS][10];     

char *bag [3]={"Empty",
               "Empty",
               "Empty"};  /*all items in your 'bag' */


int light;                                      /* how far the charecter can see   */
   
char* wall;                                       /* what to say when you hit a wall */
char* helpmsg=
"Some sort of guidence message should be displayed here.";

int scrw,                                         /* how wide the screen is */
    scrh;                                         /* how tall the screen is */
int mask[FLOORS][19][19];                            /* what parts of the map are visible */

int inp;                                          /* player input */

//#include "objects.h"

void finit(int nx,int ny,int nz,int nlight)
{  initscr();
   keypad(stdscr, TRUE);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN,   COLOR_BLACK);
   init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
   init_pair(4, COLOR_BLUE,    COLOR_BLACK);
   init_pair(5, COLOR_RED,     COLOR_BLACK);
 
   getmaxyx(stdscr,scrh,scrw);                       /* fill the variables scrw & scrh with correct #'s */
   if(scrh<25)
   {  printw("the terminal height is %i,\n"\
             "it should be >25:\n"\
             "Minor Graphical Errors will occur.",scrh);
      refresh();
      getch();
      clear();
   }
//   if(scrw<20);
   int a,b,c;

   for(a=0;a>=FLOORS;a++)
   for(b=0;b>=19 ;b++)
   for(c=0;c>=19 ;c++)
   {   sw[a]      =0;
     mask[a][b][c]=0;
   }
   
   z=nz;
   y=ny;
   x=nx;
   light=nlight;
}

void help();                                       /* tell the user how to play the game */
void menu();

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
         help();  break;
      case 'm':
         menu();  break;
   }                           
}
void uncover(int shadow)
{
   int wp,
       hp,
       xp,
       yp,
       pp, // point placement
       mp, // maximum pp value // (that's what she said)
       lp; // light placement

   struct point
   {  int x;
      int y;
   } plist[100];

   pp=0;
   if(shadow==1)
   {
      for(hp=0; hp<19; hp++)                            /* first pass gets blocking points... */
      for(wp=0; wp<19; wp++)                            /* || */
      {
        if(sqrt((wp-x)*(wp-x)+(hp-y)*(hp-y)) <= light ) /* if the spot is neer the player and its not already visible */
        {
           if(map[z][hp][wp]!='.'&&
              map[z][hp][wp]!='*')
           {
              plist[pp].x=wp;
              plist[pp].y=hp;
              pp++;
           }
        }
      }
   }
   mp=pp;
   int inspection;                                 /* inspection =1 if passed 0 if failed */
   for(hp=0; hp<19; hp++)                            /*...second pass tests if points are within their shadow. */
     {
   for(wp=0; wp<19; wp++)                            /* || */
    {
   inspection=1;       /* next inspection is innocent until proven guilty */
   for(pp=0; pp<mp; pp++)
   {
      double const dxs2p=(double)(x-wp); //diff x source 2 point 
      double const dys2p=(double)(y-hp);
      double const ds2p=sqrt(dxs2p*dxs2p+dys2p*dys2p);

      double dxo2p=(double)(plist[pp].x-wp); //diff x object2point
      double dyo2p=(double)(plist[pp].y-hp);
      double do2p=sqrt(dxo2p*dxo2p+dyo2p*dyo2p);
      

      if (x == wp && y == hp)
        continue;
      if (plist[pp].x== x && plist[pp].y ==y)
        continue;

      if(do2p>ds2p+0.5||do2p<0.5)
         continue; /* pass inspecion */
      double px=dxo2p*ds2p/do2p;
      double py=dyo2p*ds2p/do2p;
      double pr=0.5*(ds2p/do2p);
      if(px<dxs2p-pr
         ||
         px>dxs2p+pr
         ||
         py<dys2p-pr
         ||
         py>dys2p+pr
        )
        continue;
        
         inspection=0;

   }
   if(sqrt((wp-x)*(wp-x)+(hp-y)*(hp-y)) > light ) /* if the spot is far from the player  */
   {
      inspection=0;
   }
   if(inspection==1)
   {  mask[z][hp][wp]=1;
   }
   }}
 
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
               case '@':
                  attron (COLOR_PAIR(5)|A_BOLD);
                  mvprintw((scrh-19)/2+hp,(scrw-38)/2+wp*2,"%c ",map[z][hp][wp]);   /* print what is at this spot */
                  attroff(COLOR_PAIR(5)|A_BOLD);
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
   move(scrh-1,scrw-1);
   refresh();                                        /* display all the changes to the screen */
}


void BlockMessage()
{
   if(inp!=ERR)
     {mvprintw(0,0,"\n\n\n");}
   if(x>=19||x<=-1||y>=19||y<=-1)
   {
     if(x>=19)                                                          /* go from 1 room to another */
     {
        x=0;
        z=eroom[z];
     }
     if(x<=-1)
     {
        x=18;
        z=wroom[z];
     }
     if(y>=19)
     {
        y=0;
        z=sroom[z];
     }
     if(y<=-1)
     {
        y=18;
        z=nroom[z];
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
         break;
      case '^': /* go up  */
      case 'U':
         if(inp!=ERR) /*the player has to WANT to go up*/
            z=uroom[z];
         break;
      case 'V': /* go down */
      case 'D':
         if(inp!=ERR)
            z=droom[z];
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

char smsg(int lx, int ly,char* msg)
{
   if(lx==x && ly==y && inp!=ERR)
   {  WINDOW *my_win;
      my_win=newwin(19,37,(scrh-19)/2,(scrw-38)/2);
     // wborder(my_win,'|','|','-','-','/','\\','/','\\');
      wprintw(my_win,"%s",msg);
      wrefresh(my_win);
      char r=getch();
      showmap();
      refresh();
      return r;
   }
}
void mesages()
{  int n;
   for(n=0;n<=9;n++)
   {  if(mesage[z][n].hit!=NULL)
         map[z][ mesage[z][n].y ][ mesage[z][n].x ]=mesage[z][n].ch; // set map = to msg char.
      if(x==mesage[z][n].x&&y==mesage[z][n].y&&inp!=ERR)           // show msg if player ay that spot.
      {  WINDOW *my_win;
         my_win=newwin(19,37,(scrh-19)/2,(scrw-38)/2);
         wprintw(my_win,"%s",mesage[z][n].hit);
         wrefresh(my_win);
         getch();
         refresh();
      }
   }
}
void event(int lx,int ly,int n,char* msg)
{  
   if(lx==x && ly==y && sw[n]==0 )
   { smsg(lx,ly,msg);
     sw[n]=1;
   }
}
void levers()
{  int n;
   for(n=0;lever[z][n].x>=0;n++)
   {  if(lever[z][n].on)
         map[z][ lever[z][n].y ][ lever[z][n].x ]='M';
      else
         map[z][ lever[z][n].y ][ lever[z][n].x ]='o'; // set map = to msg char.
      if(x==lever[z][n].x&&y==lever[z][n].y&&lever[z][n].on==0)           // show msg && on=1 if player ay that spot.
      {  lever[z][n].on=1;
         if(lever[z][n].hit!=NULL)
            smsg(lever[z][n].x,lever[z][n].y,lever[z][n].hit);
      }   
   }
}
void boxes()
{  int n;
   for(n=0;n<=9;n++)
   {  if(x==crate[z][n].x&&y==crate[z][n].y)
      {       if(px<x&&(map[z][y][x+1]=='.'||map[z][y][x+1]=='*')&&x+1<18)
         {  crate[z][n].x++;
            map[z][y][x]='.';
         }
         else if(px>x&&(map[z][y][x-1]=='.'||map[z][y][x-1]=='*')&&x-1>=1)
         {  crate[z][n].x--;
            map[z][y][x]='.';
         }
         else if(py<y&&(map[z][y+1][x]=='.'||map[z][y+1][x]=='*')&&y+1<18)
         {  crate[z][n].y++;
            map[z][y][x]='.';
         }
         else if(py>y&&(map[z][y-1][x]=='.'||map[z][y-1][x]=='*')&&y-1>=1)
         {  crate[z][n].y--;
            map[z][y][x]='.';
         }
         else
         {  x=px;
            y=py;
            smsg(x,y,"you can't push this block");
         }
      }
   map[z][ crate[z][n].y ][ crate[z][n].x ]=crate[z][n].ch;
   }
}
void buttons()
{  int m;
   int n;
   for(n=0;n<=9;n++)
   {  map[z][ button[z][n].y ][ button[z][n].x ]=button[z][n].ch;
      button[z][n].on=0;
      for(m=0;m<=9;m++)
      {  if(x==button[z][n].x&&y==button[z][n].y)
         {  button[z][n].on=1;
         }
         if(crate[z][m].x==button[z][n].x&&crate[z][m].y==button[z][n].y)
         {  button[z][n].on=1;
            map[z][ crate[z][m].y ][ crate[z][m].x ]=crate[z][m].ch;
         }
      }
   }
}
void items()
{  int n;
   for(n=0;n<=9;n++)
   {  map[z][ item[z][n].y ][ item[z][n].x ]=item[z][n].ch;
      if(x==item[z][n].x&&y==item[z][n].y)
      {  if     (bag[0]=="Empty")
            bag[0]=item[z][n].name;
         else if(bag[1]=="Empty")
            bag[1]=item[z][n].name;
         else if(bag[2]=="Empty")
            bag[2]=item[z][n].name;
         else
            smsg(x,y,"your bag is full you cannot pick up this item");
         smsg(x,y,item[z][n].hit);
      } 
   }
}
void menu()
{
   int n=1;
   while(n==1)
   {char sel=smsg(x,y,"\n"\
    "\n   1) Help,\n"
    "\n   2) Inventory,\n"
    "\n   3) Exit.\n");
    switch(sel)
    {  case '1':
         help(); break;
       case '2':
         smsg(x,y,\
         "+ - - - - - - - - - - - - - - - - - +"\
         "|                                   |"\
         "|  The Tablet of Upcoming Features  |"\
         "|            (T.U.F)                |"\
         "|  Like Unswers, Chuckles and Kicks |"\
         "|           (L.U.C.K)               |"\
         "|                                   |"\
         "|  1) a list of upcoming features.  |"\
         "+ - - - - - - - - - - - - - - - - - +");
         WINDOW *my_win;
         my_win=newwin(19,37,(scrh-19)/2,(scrw-38)/2);
         wprintw(my_win,
         "   1) %s\n"
         "   2) %s\n"
         "   3) %s\n",
         bag[0],bag[1],bag[2]);
         wrefresh(my_win);
         getch(); break;
       case '3':
         n=0; break;
       default :
         smsg(x,y,\
         "Please type the number of your desired option.");
         break;
    }
   }
}
void help()
{
   smsg(x,y,helpmsg);
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
void rev(int n)
{  if(lever[z][n].on)
      lever[z][n].on=0;
   else
      lever[z][n].on=2;
}
