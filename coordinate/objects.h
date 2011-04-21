void oinit()
{
helpmsg=
  "+-----------------------------------+"
  "|                                   |"
  "|            The Tablet             |"
  "|      Of Mystical Guidence II      |"
  "|          Bigger & better          |"
  "|                                   |"
  "|        Now with 50 percent        |"
  "|          more guidence!!!         |"
  "|                                   |"
  "|              movement:            |"
  "|          w                        |"
  "|        a s d  or Arrow Keys       |"
  "|                                   |"
  "|               Menu: M             |"
  "|                                   |"
  "|               Quit: Q             |"
  "|                                   |"
  "|                                   |"
  "+-----------------------------------+";

uroom[0]=1;

   uroom[1]=2;
   droom[1]=0;

droom[2]=1;
sroom[2]=3;
wroom[2]=4;
lever[2][0].x=12;
lever[2][0].y=12;
lever[2][0].hit=
"You hit this lever,\n   Good job!";
   nroom[3]=2;

   lever[3][0].x= 9;
   lever[3][0].y= 7;

   lever[3][1].x= 9;
   lever[3][1].y=11;

   lever[3][2].x= 7;
   lever[3][2].y= 9;
 
   lever[3][3].x=11;
   lever[3][3].y= 9;

   lever[3][4].x= 6;
   lever[3][4].y= 6;

   lever[3][5].x=12;
   lever[3][5].y=12;

   lever[3][6].x= 6;
   lever[3][6].y=12;

   lever[3][7].x=12;
   lever[3][7].y= 6;

eroom[4]=2;
crate[4][0].x=9;
crate[4][0].y=9;
crate[4][0].ch='#';

lever[4][0].x=15;
lever[4][0].y=7;
lever[4][0].hit=
"Did something just move?";

item[4][0].x=11;
item[4][0].y=11;
item[4][0].ch='I';
item[4][0].name="Fredrick";
item[4][0].hit=
"you hame obtained :\nFredrick";

}

