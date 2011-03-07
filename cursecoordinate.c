#include "functions.h"

int main()
{
   initscr();
   keypad(stdscr, TRUE);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN,   COLOR_BLACK);
   init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
   finit( 9, 9, 0, 3);
   int n; /* having a spare int is useful. */
   
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
      {  
         case 0:
            uroom=5;
            wroom=1;
           
            wall=
            "Some sort of wall mesage should be displayed here,\n"
            "It should inform the player of the solidity of this wall,\n"
            "and it should warn that attempts to surpass this fact are admonishable.";
           
            msg(8,9,
            "THIS SPOT IS IMPORTANT FOR THIS REASON");
            smsg(2,9,
               "   This spot is UBER important :)\n"
               "It clears the screen to show you something!!!! \n");
            smsg(2,9,
               "   And it can do it twice!!!\n");
            smsg(2,9,
               "\n"
               "And thrice as well!!! :)");
            if(sw[0])
            {
               smsg(9,9,
               "This is a new stairwell.");
            }
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
            "in room 3, the wall is so interesting, it's unsurpassable...";
            nroom=2;
            break;
         case 4:
            wall=
            "...when it's not compared to these walls in room 4\n"
            "(see room 3's walls)";
            
            smsg(6,14,
            "   this is an object of\n"
            "INSURMOUNTABLE POWER...\n"
            "It will somehow help you on your\n"
            "QUEST,\n"
            "(which has neither been defined nor\n"
            "ACCEPTED)...\n"
            "\n"
            "...once the master programmer imbues\n"
            "it with the power to do such.\n"
            "\n"
            "Until then, walk from here back to\n"
            "THE BEGINING,\n"
            "and from there to here 9 times 7.\n"
            "\n");
             
            smsg(6,14,
            "+-----------------------------------+"
            "|                                   |"
            "|                                   |"
            "|            ????                   |"
            "|          ??  ? ???                |"
            "|            ??     ??              |"
            "|             ####    ?   ####      |"
            "|          ###    ##   ? ##  ##     |"
            "|        ##     ?   #  ?     ##     |"
            "|      ##     ?   o   ?     ##      |"
            "|     ##     ?  #   ?     ##        |"
            "|     ##  ## ?   ##    ###          |"
            "|      ####   ?    ####             |"
            "|              ??     ??            |"
            "|                ??? ?  ??          |"
            "|                   ????            |"
            "|                                   |"
            "|                                   |"
            "+-----------------------------------+");

            smsg(6,14,
            "   The Master Programmer hath spoken."
            "He hath declared that the way forth  "
            "shall become clear if you retrace    "
            "your steps to your point of origin.  ");

            lvr(6,14,0);
            if(sw[0]==1)
            {
               map[0][9][9]='^';
               sw[0]==2;
            }
            nroom=1;
            break;
         case 5:
            wall=
            "there is nothing extra-ordinary about these walls";
            droom=0;
            nroom=6;
            smsg(9,8,
            "\n\n\n   Time:\n"
            "all encompasing,\n"
            "inescapable...\n");
            
            smsg(9,1,
            "\n\n\n...incorporeal.\n\n"
            "   In Time\n" /* "Time" which refers to the clock, is a proper noun in this case*/
            "The Trinity will point forward...");

            lvr(9 , 4,1);
            lvr(13, 5,2);
            lvr(14,9 ,3);
            lvr(13,13,4);
            lvr(9 ,14,5);
            lvr(5 ,13,6);
            lvr(4 , 9,7);
            lvr(5 , 5,8);

            if(sw[1]&&sw[3]&&sw[5]&&sw[7]||sw[2]&&sw[4]&&sw[6]&&sw[8])
            {
               sw[1]=0;
               sw[2]=0;
               sw[3]=0;
               sw[4]=0;
               sw[5]=0;
               sw[6]=0;
               sw[7]=0;
               sw[8]=0;
            }
            if(sw[1]&&sw[4]&&sw[6]||sw[2]&&sw[5]&&sw[7]||sw[8]&&sw[5]&&sw[3])
            {
               map[5][0][ 8]=' ';
               map[5][0][ 9]=' ';
               map[5][0][10]=' ';
            }
            else
            {
               map[5][0][ 8]='-';
               map[5][0][ 9]='-';
               map[5][0][10]='-';
            }
            switch(sw[1])
            {
               case 2:
                  sw[1]=0;
                  sw[2]=1;
                  break;
               case 1:
                  sw[1]=2;
                  break;
            }
            switch(sw[2])
            {
               case 2:
                  sw[2]=0;
                  sw[3]=1;
                  break;
               case 1:
                  sw[2]=2;
                  break;
            }
            switch(sw[3])
            {
               case 2:
                  sw[3]=0;
                  sw[4]=1;
                  break;
               case 1:
                  sw[3]=2;
                  break;
            }
            switch(sw[4])
            {
               case 2:
                  sw[4]=0;
                  sw[5]=1;
                  break;
               case 1:
                  sw[4]=2;
                  break;
            }
            switch(sw[5])
            {
               case 2:
                  sw[5]=0;
                  sw[6]=1;
                  break;
               case 1:
                  sw[5]=2;
                  break;
            }
            switch(sw[6])
            {
               case 2:
                  sw[6]=0;
                  sw[7]=1;
                  break;
               case 1:
                  sw[6]=2;
                  break;
            }
            switch(sw[7])
            {
               case 2:
                  sw[7]=0;
                  sw[8]=1;
                  break;
               case 1:
                  sw[7]=2;
                  break;
            }
            switch(sw[8])
            {
               case 2:
                  sw[8]=0;
                  sw[1]=2; // in each other transition the the switch is transitioned from 1 to 2 */
                  break;   /* immediately after because the next switch statemet follows it, */
               case 1:     /* switch 8 is not followed by 1 so it must be manualy transitioned to 2 */
                  sw[8]=2; /* (if that makes any sense) */
                  break;
            }
            break;
         case 6:
            sroom=5;
            uroom=7;

            map[5][0][ 8]=' ';
            map[5][0][ 9]=' ';
            map[5][0][10]=' ';

            msg( 9, 9,
            "...all will be of one substance...");

            lvr( 6, 6, 9);
            lvr(12, 6,10);
            lvr( 9, 7,11);
            lvr( 7, 9,12);
            lvr(11, 9,13);
            lvr( 9,11,14);
            lvr( 6,12,15);
            lvr(12,12,16);

            if(sw[ 9]==1)
            {
               flip(13);
               flip(14);
               sw[ 9]=2;
            }
            if(sw[10]==1)
            {
               flip(12);
               flip(14);
               sw[10]=2;
            }
            if(sw[11]==1)
            {
               flip(15);
               flip(16);
               sw[11]=2;
            }
            if(sw[12]==1)
            {
               flip(10);
               flip(16);
               sw[12]=2;
            } 
            if(sw[13]==1)
            {
               flip( 9);
               flip(15);
               sw[13]=2;
            }
            if(sw[14]==1)
            {
               flip( 9);
               flip(10);
               sw[14]=2;
            }
            if(sw[15]==1)
            {
               flip(13);
               flip(11);
               sw[15]=2;
            }
            if(sw[16]==1)
            {
               flip(11);
               flip(12);
               sw[16]=2;
            }
            lvr( 6, 6, 9);
            lvr(12, 6,10);
            lvr( 9, 7,11);
            lvr( 7, 9,12);
            lvr(11, 9,13);
            lvr( 9,11,14);
            lvr( 6,12,15);
            lvr(12,12,16);
            if(sw[9]&&sw[10]&&sw[11]&&sw[12]&&sw[13]&&sw[14]&&sw[15]&&sw[16])
              {map[6][9][9]='^';}
            
            break;
         case 7:
            uroom=8;
            droom=6;
            lvr( 5, 5,17);
            lvr(13, 5,18);
            lvr(13,13,19);
            lvr(5 ,13,20);
            
            for(n=17;n<20;n++)
            {
               if(sw[n]==1)
               {
                  flip(n+1);
                  flip(n);
               }
            }
            if(sw[20]==1)
            {
               flip(17);
               flip(20);
            }
            mlvr( 5, 5,17);
            mlvr(13, 5,18);
            mlvr(13,13,19);
            mlvr(5 ,13,20);

            break;
         case 8:
            uroom=9;
            droom=7;

            lvr( 9, 9,30);

            lvr( 5, 5,21);
            lvr(13, 5,22);
            lvr(13,13,23);
            lvr(5 ,13,24);
            
            for(n=22;n<=24;n++)
            {
               if(sw[n]==1)
               {
                  flip(n-1);
                  flip(n);
               }
            }
            if(sw[21]==1)
            {
               flip(24);
               flip(21);
            }
            if(sw[30]==1)
            {
               flip(21);
               flip(22);
               flip(23);
               flip(24);
               flip(30);
            }

            mlvr( 5, 5,21);
            mlvr(13, 5,22);
            mlvr(13,13,23);
            mlvr(5 ,13,24);
            break;
         case 9:
            droom=8;

            lvr( 9, 9,29);

            lvr( 5, 5,25);
            lvr(13, 5,26);
            lvr(13,13,27);
            lvr(5 ,13,28);
            
            for(n=25;n<28;n++)
            {
               if(sw[n]==1)
               {
                  flip(n+1);
                  flip(n);
               }
            }
            if(sw[28]==1)
            {
               flip(25);
               flip(28);
            }
            if(sw[29]==1)
            {
               flip(25);
               flip(26);
               flip(27);
               flip(28);
               flip(29);
            }
            mlvr( 5, 5,25);
            mlvr(13, 5,26);
            mlvr(13,13,27);
            mlvr(5 ,13,28);

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
