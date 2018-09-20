/*<-----------------------------HEADER FILES-----------------------------%>*/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<iostream.h>
#include<string.h>
#include<time.h>
/*<----------------------------------------------------------------------%>*/






/*<----------------------------GLOBAL VARIABLES--------------------------%>*/
int a1,b1,a2,b2,d1,d2;
/*
	a1,b1	:	x and y coordinates of player 1
	a2,b2	:	x and y coordinates of player 2
	d1	:	direction of player 1
	d2	:	direction of player 2
*/
/*<----------------------------------------------------------------------%>*/





/*<---------------------PROTOTYPE DECLARATION OF FUNCTIONS---------------%>*/
void play();
	int roll_dice();
	void exit_menu(int);
	void create_player1(int,int);
	void create_player2(int,int);
	void translate1(int ,int ,int ,int);
	void translate2(int ,int ,int ,int);
		void snake_bite(int);
		void climb_ladder(int);
		void game_over(int ,int ,int ,int);
	void create_board();
		void text();
		void grid();
		void snake();
		void ladder();
		void numbers();
/*<----------------------------------------------------------------------%>*/





/*<---------------------MAIN FUNCTION------------------------------------%>*/
int main()
{
	int gd=DETECT ,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
		cleardevice();
		play();
	getch();
	closegraph();
	return 0;
}
/*<----------------------------------------------------------------------%>*/





/*<------FUNCTION THAT HANDLES THE GAME PLAY-----------------------------%>*/
void play()
{
	//initializing the values of global variables
	::a1=15;
	::b1=435;
	::a2=15;
	::b2=435;
	::d1=0;
	::d2=0;

	cleardevice();
	srand(time(0));

	int choice,chance=1,k1=0,k2=0;
	/*
		choice	:	number that appears on dice
		chance	:	player having the current chance
		k1	:	k1=0 means player1 hasn't moved from home yet
		k2	:	k2=0 means player2 hasn't moved from home yet
	*/

	create_board();
	create_player1(a1,b1);
	create_player2(a2,b2);
	setcolor(LIGHTBLUE);
	outtextxy(500,135,"Player 1");
	outtextxy(500,145,"roll the dice");
	while(1) //infinite loop
	{
		if(kbhit) //take button input
		{
			char ch=getch(); //button input is stored in ch
			if(ch==32) //if player hits spacebar
			{
				choice=roll_dice();
			}
			if(ch==27) //if player hits escape
			{
				exit(0);
			}
		}
		if(chance==1) //player 1's chance
		{
			settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
			if(k1==0) //first chance
			{
				if(choice==1 || choice==6) //six or one on dice
				{
					k1++;
					setcolor(LIGHTBLUE);
					outtextxy(500,135,"Player 1 can ");
					outtextxy(500,145,"go ahead");
					delay(500);
					translate1(::a1,::b1,2,chance);
					chance=2;
					setcolor(LIGHTGREEN);
					outtextxy(500,135,"Player 2");
					outtextxy(500,145,"roll the dice");
					continue;
				}
				else
				{
					chance=2;
					setcolor(LIGHTGREEN);
					outtextxy(500,135,"Player 2");
					outtextxy(500,145,"roll the dice");
					continue;
				}
			}
			if(choice==6) //six on dice
			{
				translate1(::a1,::b1,choice+1,chance);
				setcolor(LIGHTBLUE);
				outtextxy(500,125,"It's a SIX!");
				outtextxy(500,135,"Player 1");
				outtextxy(500,145,"play again");
				continue;
			}
			else
			{
				translate1(a1,b1,choice+1,chance);
				chance=2;
				setcolor(LIGHTGREEN);
				outtextxy(500,135,"Player 2");
				outtextxy(500,145,"roll the dice");
				continue;
			}
		}
		if(chance==2) //player 2's chance
		{
			settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
			if(k2==0) //first chance
			{
				if(choice==1 || choice==6) //one or six on dice
				{
					k2++;
					setcolor(LIGHTGREEN);
					outtextxy(500,135,"Player 2 can");
					outtextxy(500,145,"go ahead");
					delay(500);
					translate2(a2,b2,2,chance);
					chance=1;
					setcolor(LIGHTBLUE);
					outtextxy(500,135,"Player 1");
					outtextxy(500,145,"roll the dice");
					continue;
				}
				else
				{
					chance=1;
					setcolor(LIGHTBLUE);
					outtextxy(500,135,"Player 1");
					outtextxy(500,145,"roll the dice");
					continue;
				}
			}
			if(choice==6) //six on dice
			{
				translate2(a2,b2,choice+1,chance);
				setcolor(LIGHTGREEN);
				outtextxy(500,125,"It's a SIX!");
				outtextxy(500,135,"Player 2");
				outtextxy(500,145,"play again");
				continue;
			}
			else
			{
				translate2(a2,b2,choice+1,chance);
				setcolor(LIGHTBLUE);
				outtextxy(500,135,"Player 1");
				outtextxy(500,145,"roll the dice");
				chance=1;
				continue;
			}
		}
	}
}
/*<----------------------------------------------------------------------%>*/





/*<-----------FUNCTION HANDLING THE MOVEMENT OF PLAYER 1-----------------%>*/
void translate1(int a1,int b1,int choice,int player)
{
	for(int a=0;a<choice-1;a++)
	{
		delay(500);
		cleardevice();
		create_board();
		if(a1==465 && b1%10!=0)
		{
			b1=b1-45;
			d1=1;
			create_player2(a2,b2);
			create_player1(a1,b1);
			continue;
		}
		else
		{
			if(a1==60 && b1%10==0)
			{
				b1=b1-45;
				d1=2;
				create_player2(a2,b2);
				create_player1(a1,b1);
				continue;
			}
		}
		if(d1==1)
		{
			a1=a1-45;
		}
		if(d1==0 || d1==2)
		{
			a1=a1+45;
		}
		create_player2(a2,b2);
		create_player1(a1,b1);
		game_over(a1,b1,a2,b2);
	}
	::a1=a1;
	::b1=b1;
	::d1=d1;
	snake_bite(player);
	climb_ladder(player);
}
/*<----------------------------------------------------------------------%>*/





/*<-----------FUNCTION HANDLING THE MOVEMENT OF PLAYER 2-----------------%>*/
void translate2(int a2,int b2,int choice,int player)
{
	for(int a=0;a<choice-1;a++)
	{
		delay(500);
		cleardevice();
		create_board();
		if(a2==465 && b2%10!=0)
		{
			b2=b2-45;
			d2=1;
			create_player1(a1,b1);
			create_player2(a2,b2);
			continue;
		}
		else
		{
			if(a2==60 && b2%10==0)
			{
				b2=b2-45;
				d2=2;
				create_player1(a1,b1);
				create_player2(a2,b2);
				continue;
			}
		}
		if(d2==1)
		{
			a2=a2-45;
		}
		if(d2==0 || d2==2)
		{
			a2=a2+45;
		}
		create_player1(a1,b1);
		create_player2(a2,b2);
		game_over(a1,b1,a2,b2);
	}
	::a2=a2;
	::b2=b2;
	::d2=d2;
	snake_bite(player);
	climb_ladder(player);
}
/*<----------------------------------------------------------------------%>*/





/*<-----FUNCTION TO HANDLE THE CONDITION OF SNAKE BITE--------------------%>*/
void snake_bite(int player)
{
	if(player==1)
	{
		//18 to 5
		if(a1==150 && b1==390)
		{
			cleardevice();
			create_board();
			create_player1(240,435);
			::a1=240;
			::b1=435;
			::d1=0;
			create_player2(a2,b2);
			return;
		}
		//43 to 23
		if(a1==150 && b1==255)
		{
			cleardevice();
			create_board();
			create_player1(150,345);
			::a1=150;
			::b1=345;
			::d1=2;
			create_player2(a2,b2);
			return;
		}
		//65 to 44
		if(a1==240 && b1==165)
		{
			cleardevice();
			create_board();
			create_player1(195,255);
			::a1=195;
			::b1=255;
			::d1=2;
			create_player2(a2,b2);
			return;
		}
		//56 to 26
		if(a1==240 && b1==210)
		{
			cleardevice();
			create_board();
			create_player1(285,345);
			::a1=285;
			::b1=345;
			::d1=2;
			create_player2(a2,b2);
			return;
		}
		//99 to 35
		if(a1==105 && b1==30)
		{
			cleardevice();
			create_board();
			create_player1(285,300);
			::a1=285;
			::b1=300;
			::d1=1;
			create_player2(a2,b2);
			return;
		}
		//50 to 33
		if(a1==465 && b1==255)
			{
			cleardevice();
			create_board();
			create_player1(375,300);
			::a1=375;
			::b1=300;
			::d1=1;
			create_player2(a2,b2);
			return;
		}
		//92 to 71
		if(a1==420 && b1==30)
		{
			cleardevice();
			create_board();
			create_player1(465,120);
			::a1=465;
			::b1=120;
			::d1=1;
			create_player2(a2,b2);
			return;
		}
		//87 to 54
		if(a1==330 && b1==75)
		{
			cleardevice();
			create_board();
			create_player1(330,210);
			::a1=330;
			::b1=210;
			::d1=1;
			create_player2(a2,b2);
			return;
		}
	}

	if(player==2)
	{
		//18 to 5
		if(a2==150 && b2==390)
		{
			cleardevice();
			create_board();
			create_player2(240,435);
			::a2=240;
			::b2=435;
			::d2=0;
			create_player1(a1,b1);
			return;
		}
		//43 to 23
		if(a2==150 && b2==255)
		{
			cleardevice();
			create_board();
			create_player2(150,345);
			::a2=150;
			::b2=345;
			::d2=2;
			create_player1(a1,b1);
			return;
		}
		//65 to 44
		if(a2==240 && b2==165)
		{
			cleardevice();
			create_board();
			create_player2(195,255);
			::a2=195;
			::b2=255;
			::d2=2;
			create_player1(a1,b1);
			return;
		}
		//56 to 26
		if(a2==240 && b2==210)
		{
			cleardevice();
			create_board();
			create_player2(285,345);
			::a2=285;
			::b2=345;
			::d2=2;
			create_player1(a1,b1);
			return;
		}
		//99 to 35
		if(a2==105 && b2==30)
		{
			cleardevice();
			create_board();
			create_player2(285,300);
			::a2=285;
			::b2=300;
			::d2=1;
			create_player1(a1,b1);
			return;
		}
		//50 to 33
		if(a2==465 && b2==255)
			{
			cleardevice();
			create_board();
			create_player2(375,300);
			::a2=375;
			::b2=300;
			::d2=1;
			create_player1(a1,b1);
			return;
		}
		//92 to 71
		if(a2==420 && b2==30)
		{
			cleardevice();
			create_board();
			create_player2(465,120);
			::a2=465;
			::b2=120;
			::d2=1;
			create_player1(a1,b1);
			return;
		}
		//87 to 54
		if(a2==300 && b2==75)
		{
			cleardevice();
			create_board();
			create_player2(330,210);
			::a2=330;
			::b2=210;
			::d2=1;
			create_player1(a1,b1);
			return;
		}
	}
}
/*<----------------------------------------------------------------------%>*/





/*<-----FUNCTION TO HANDLE THE CONDITION OF LADDER CLIMB-----------------%>*/
void climb_ladder(int player)
{
	if(player==1)
	{
		//9 to 31
		if(a1==420 && b1==435)
		{
			cleardevice();
			create_board();
			create_player1(465,300);
			::a1=465;
			::b1=300;
			::d1=1;
			create_player2(a2,b2);
		}
		//16 to 58
		if(a1==240 && b1==390)
		{
			cleardevice();
			create_board();
			create_player1(150,210);
			::a1=150;
			::b1=210;
			::d1=1;
			create_player2(a2,b2);
		}
		//19 to 38
		if(a1==105 && b1==390)
		{
			cleardevice();
			create_board();
			create_player1(150,300);
			::a1=150;
			::b1=300;
			::d1=1;
			create_player2(a2,b2);
		}
		//21 to 79
		if(a1==60 && b1==345)
		{
			cleardevice();
			create_board();
			create_player1(105,120);
			::a1=105;
			::b1=120;
			::d1=1;
			create_player2(a2,b2);
		}
		//28 to 84
		if(a1==375 && b1==345)
		{
			cleardevice();
			create_board();
			create_player1(195,75);
			::a1=195;
			::b1=75;
			::d1=2;
			create_player2(a2,b2);
		}
		//72 to 93
		if(a1==420 && b1==120)
		{
			cleardevice();
			create_board();
			create_player1(375,30);
			::a1=375;
			::b1=30;
			::d1=1;
			create_player2(a2,b2);
		}
	}

	if(player==2)
	{
		//9 to 31
		if(a2==420 && b2==435)
		{
			cleardevice();
			create_board();
			create_player2(465,300);
			::a2=465;
			::b2=300;
			::d2=1;
			create_player1(a1,b1);
		}
		//16 to 58
		if(a2==240 && b2==390)
		{
			cleardevice();
			create_board();
			create_player2(150,210);
			::a2=150;
			::b2=210;
			::d2=1;
			create_player1(a1,b1);
		}
		//19 to 38
		if(a2==105 && b2==390)
		{
			cleardevice();
			create_board();
			create_player2(150,300);
			::a2=150;
			::b2=300;
			::d2=1;
			create_player1(a1,b1);
		}
		//21 to 79
		if(a2==60 && b2==345)
		{
			cleardevice();
			create_board();
			create_player2(105,120);
			::a2=105;
			::b2=120;
			::d2=1;
			create_player1(a1,b1);
		}
		//28 to 84
		if(a2==375 && b2==345)
		{
			cleardevice();
			create_board();
			create_player2(195,75);
			::a2=195;
			::b2=75;
			::d2=2;
			create_player1(a1,b1);
		}
		//72 to 93
		if(a2==420 && b2==120)
		{
			cleardevice();
			create_board();
			create_player2(375,30);
			::a2=375;
			::b2=30;
			::d2=1;
			create_player1(a1,b1);
		}
	}

}
/*<----------------------------------------------------------------------%>*/





/*<-----FUNCTION TO HANDLE THE CONDITION OF COMPLETION OF THE GAME-------%>*/
void game_over(int a1 ,int b1 ,int a2 ,int b2)
{
	if(a2==60 && b2==30)
	{
		exit_menu(2);
	}
	if(a1==60 && b1==30)
	{
		exit_menu(1);
	}
}
/*<----------------------------------------------------------------------%>*/





/*<-----------------------FUNCTION TO CREATE DICE------------------------%>*/
int roll_dice()
{
	int chance=(rand() % 6) + 1;
	cleardevice();
	setcolor(BROWN);
	create_board();
	create_player1(a1,b1);
	create_player2(a2,b2);
	setcolor(BROWN);
	rectangle(550,190,630,270);//dice
	line(550,190,530,170);//left upper
	line(530,170,530,250);//left
	line(530,170,610,170);//upper
	line(610,170,630,190);//right upper
	line(530,250,550,270);//left lower
	char output[10];
	sprintf(output,"%d",chance);
	setcolor(BROWN);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,1);
	outtextxy(580,210,output);//text on dice
	delay(500);
	return chance;
}
/*<----------------------------------------------------------------------%>*/





/*<---------------------FUNCTION TO CREATE PLAYER 1----------------------%>*/
void create_player1(int x,int y)
{
	setcolor(LIGHTBLUE);
	circle(x,y,10);//1st token
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	floodfill(x,y,LIGHTBLUE);
}
/*<----------------------------------------------------------------------%>*/





/*<---------------------FUNCTION TO CREATE PLAYER 2----------------------%>*/
void create_player2(int x,int y)
{
	setcolor(LIGHTGREEN);
	circle(x,y,10);//2nd token
	setfillstyle(SOLID_FILL,LIGHTGREEN);
	floodfill(x,y,LIGHTGREEN);
}
/*<----------------------------------------------------------------------%>*/





/*<--------FUNCTION TO CREATE PLAYER THE BOARD---------------------------%>*/
void create_board()
{
	text();
	grid();
	ladder();
	snake();
	numbers();
}
/*<----------------------------------------------------------------------%>*/





/*<----------------TEXT--------------------------------------------------%>*/
void text()
{
	setcolor(LIGHTRED);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,1);
	outtextxy(505,20,"SNAKE");
	outtextxy(505,50,"AND");
	outtextxy(505,80,"LADDER");

	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(BROWN);
	outtextxy(505,340,"-->SPACEBAR:");
		setcolor(LIGHTRED);
		outtextxy(545,350,"ROLL DICE");
	setcolor(BROWN);
	outtextxy(505,400,"-->ESC:");
		setcolor(LIGHTRED);
		outtextxy(545,410,"LEAVE GAME");

}
/*<----------------------------------------------------------------------->*/





/*<------------FUNCTION TO CREATE THE GRID OF THE BOARD------------------%>*/
void grid()
{
	setcolor(BROWN);

	rectangle(45,10,495,460);//board
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(315,270,BROWN);

	rectangle(550,190,630,270);//dice
	outtextxy(570,200,"");
	line(550,190,530,170);//left upper
	line(530,170,530,250);//left
	line(530,170,610,170);//upper
	line(610,170,630,190);//right upper
	line(530,250,550,270);//left lower


	//vertical lines drawn from top to bottom starting from the left
	line(90,10,90,460);//1st vline
	line(135,10,135,460);//2nd vline
	line(180,10,180,460);//3rd vline
	line(225,10,225,460);//4th vline
	line(270,10,270,460);//5th vline
	line(315,10,315,460);//6th vline
	line(360,10,360,460);//7th vline
	line(405,10,405,460);//8th vline
	line(450,10,450,460);//9th vline

	//horizontal lines drawn from left to right strting from the top
	line(45,55,495,55);//1st hline
	line(45,100,495,100);//2nd hline
	line(45,145,495,145);//3rd hline
	line(45,190,495,190);//4th hline
	line(45,235,495,235);//5th hline
	line(45,280,495,280);//6th hline
	line(45,325,495,325);//7th hline
	line(45,370,495,370);//8th hline
	line(45,415,495,415);//9th hline
}
/*<----------------------------------------------------------------------%>*/





/*<--------------FUNCTION TO CREATE SNAKES ON THE BOARD------------------%>*/
void snake()
{
	setcolor(RED);

	//18 to 5
	circle(170,405,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(170,405,RED);
	line(170,405,235,440);
	line(235,440,225,440);
	line(235,440,225,430);

	//43 to 23
	circle(170,270,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(170,270,RED);
	line(170,270,170,360);
	line(170,360,165,355);
	line(170,360,175,355);

	//65 to 44
	circle(260,180,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(260,180,RED);
	line(260,180,215,270);
	line(215,270,215,260);
	line(215,270,225,260);

	//56 to 26
	circle(260,225,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(260,225,RED);
	line(260,225,280,335);
	line(280,335,270,327);
	line(280,335,285,327);

	//99 to 35
	circle(125,45,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(125,45,RED);
	line(125,45,280,290);
	line(280,290,270,285);
	line(280,290,280,283);

	//50 to 33
	circle(460,270,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(460,270,RED);
	line(460,270,395,290);
	line(395,290,397,285);
	line(395,290,400,293);

	//92 to 71
	circle(440,45,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(440,45,RED);
	line(440,45,460,110);
	line(460,110,453,107);
	line(460,110,463,105);

	//87 to 54
	circle(353,90,5);
	setfillstyle(SOLID_FILL,RED);
	floodfill(353,90,RED);
	line(353,90,353,200);
	line(353,200,350,195);
	line(353,200,356,195);
}
/*<----------------------------------------------------------------------%>*/





/*<--------------FUNCTION TO CREATE LADDERS ON THE BOARD-----------------%>*/
void ladder()
{
	setcolor(GREEN);

	//9 to 31
	line(440,425,460,315);
	line(460,315,455,320);
	line(460,315,465,320);

	//16 to 58
	line(235,380,170,225);
	line(170,225,168,230);
	line(170,225,178,230);

	//19 to 38
	line(125,380,145,315);
	line(145,315,138,320);
	line(145,315,148,320);

	//28 to 84
	line(370,335,215,90);
	line(215,90,213,95);
	line(215,90,223,95);

	//21 to 79
	line(80,335,100,135);
	line(100,135,95,140);
	line(100,135,105,140);

	//72 to 93
	line(415,110,395,45);
	line(395,45,390,50);
	line(395,45,400,50);
}
/*<----------------------------------------------------------------------%>*/





/*<---------------FUNCTION TO PRINT NUMBERS ON THE BOARD-----------------%>*/
void numbers()
{
	setcolor(LIGHTGRAY);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	int j=0,m=0,n=0,k=0,x=65,y=435;

	const char *s[]
	={
		"1","2","3","4","5","6","7","8","9","10",
		"11","12","13","14","15","16","17","18","19","20",
		"21","22","23","24","25","26","27","28","29","30",
		"31","32","33","34","35","36","37","38","39","40",
		"41","42","43","44","45","46","47","48","49","50",
		"51","52","53","54","55","56","57","58","59","60",
		"61","62","63","64","65","66","67","68","69","70",
		"71","72","73","74","75","76","77","78","79","80",
		"81","82","83","84","85","86","87","88","89","90",
		"91","92","93","94","95","96","97","98","99","100"
	 };

	for(int i=0;i<100;i++)
	{
		if(j==0)
		{
			outtextxy(x,y,s[i]);
			x=x+45;
		}
		if(j!=0 && j%2!=0)
		{
			if(m==0)
			{
				y=y-45;
				x=x-45;
				m++;
			}
			outtextxy(x,y,s[i]);
			x=x-45;
		}
		if(j!=0 && j%2==0)
		{
			if(n==0)
			{
				y=y-45;
				x=x+45;
				n++;
			}
			outtextxy(x,y,s[i]);
			x=x+45;
		}
		if(i+1-10==k)
		{
			j++;
			k=k+10;
			m=0;
			n=0;
		}
	}
}
/*<----------------------------------------------------------------------%>*/





/*<------------------------EXIT MENU-------------------------------------%>*/
void exit_menu(int player)
{
	cleardevice();
	if(player==1)
	{
		 setcolor(LIGHTBLUE);
		 settextstyle(7,HORIZ_DIR,5);
		 outtextxy(50,100,"PLAYER 1 is the WINNER");

		 setcolor(BLUE);
		 rectangle(150,200,550,290);
		 setfillstyle(SOLID_FILL,LIGHTBLUE);
		 floodfill(175,250,BLUE);

		 settextstyle(8,HORIZ_DIR,1);
		 setcolor(BROWN);
		 outtextxy(180,230,"Press esc to leave the game");

		 if(kbhit)
		 {
			char ch=getch();
			if(ch==27)
			{
				exit(0);
			}
		 }
	}

	if(player==2)
	{
		 setcolor(LIGHTGREEN);
		 settextstyle(7,HORIZ_DIR,5);
		 outtextxy(50,100,"PLAYER 2 is the WINNER");

		 setcolor(GREEN);
		 rectangle(150,200,550,290);
		 setfillstyle(SOLID_FILL,LIGHTGREEN);
		 floodfill(175,250,GREEN);

		 settextstyle(8,HORIZ_DIR,1);
		 setcolor(BROWN);
		 outtextxy(180,230,"Press esc to leave the game");

		 if(kbhit)
		 {
			char ch=getch();
			if(ch==27)
			{
				exit(0);
			}
		 }
	}

}
/*<----------------------------------------------------------------------->*/