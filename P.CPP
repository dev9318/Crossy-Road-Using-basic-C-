#include<graphics.h>
#include<process.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
int z=8;
int j=0,a=100,b=400;
int posarr[2]={0,0},x,y,cl;
union REGS in,out;
void rules();
int score=0;
int callmouse()
	  {
		 in.x.ax=1;
		 int86(51,&in,&out);
		 return 1;
	  }
////////////////////////////////////////////////////////////////////////////////
	 void restrictmouseptr(int x1,int y1,int x2,int y2)
	  {
		 in.x.ax=7;
		 in.x.cx=x1;
		 in.x.dx=x2;
		 int86(51,&in,&out);
		 in.x.ax=8;
		 in.x.cx=y1;
		 in.x.dx=y2;
		 int86(51,&in,&out);
	  }
////////////////////////////////////////////////////////////////////////////////
	  void mouseposi(int x[],int &xpos,int &ypos,int &click)
	   {
		  in.x.ax=3;
		  int86(51,&in,&out);
		  click=out.x.bx;
		  xpos=out.x.cx;
		  ypos=out.x.dx;
		  if(!click)j=1;
		  if(click&&j==1)
		  {
		  x[0]=xpos;
		  x[1]=ypos;
		  }
	  }
////////////////////////////////////////////////////////////////////////////////
	   int mousehide()
	   {
		  in.x.ax=2;
		  int86(51,&in,&out);
		  return 1;
	   }
////////////////////////////////////////////////////////////////////////////////
	  void setposi(int &xpos,int &ypos)
	  {
		 in.x.ax=4;
		 in.x.cx=xpos;
		 in.x.dx=ypos;
		 int86(51,&in,&out);
	  }
void intro()
	  {
		 settextstyle(1,HORIZ_DIR,5);
		 outtextxy(getmaxx()/2-getmaxx()/8-50,getmaxy()/2-getmaxy()/8,"CROSSY ROAD");
		 settextstyle(1,HORIZ_DIR,3);
		 outtextxy(getmaxx()/2-getmaxx()/8+25,getmaxy()/2,"LOADING...");
		 rectangle(getmaxx()/2-getmaxx()/8,getmaxy()/2+getmaxy()/8,getmaxx()/2-getmaxx()/8+175,getmaxy()/2+getmaxy()/8+35);
		 for(int fg=getmaxx()/2-getmaxx()/8+10;fg<getmaxx()/2-getmaxx()/8+164;fg++)
		     { bar(fg,getmaxy()/2+getmaxy()/8+5,fg+1,getmaxy()/2+getmaxy()/8+30);
		       delay(20);
	  }          }

int mainmenu()
	  {	 int k=0;
		 clrscr();
		 int g=DETECT,m;
		 initgraph(&g,&m,"C:\\TurboC3\\BGI");
		 intro();
		 cleardevice();
		 setcolor(WHITE);
		 settextstyle(4,HORIZ_DIR,6);
		 rectangle(10,10,620,450);
		 rectangle(15,15,615,445);
		 restrictmouseptr(15,15,615,445);
		 setposi(a,b);
		 callmouse();
		 do
		 {
			settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
			mouseposi(posarr,x,y,cl);
			gotoxy(1,2);
			setcolor(WHITE);
			rectangle(150,150,475,200);
			rectangle(155,155,470,195);
			setcolor(RED);
			outtextxy(270,150,"PLAY");
			setcolor(WHITE);
			rectangle(150,250,475,300);
			rectangle(155,255,470,295);
			setcolor(RED);
			outtextxy(260,255,"RULES");
			setcolor(WHITE);
			rectangle(150,355,475,400);
			rectangle(155,360,470,395);
			setcolor(RED);
			outtextxy(270,355,"QUIT");

			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]>=350&&posarr[1]<=400)
			  exit(0);
			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]<=300&&posarr[1]>=250)
			{
			  rules();
			 cleardevice();
			}

			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]>=150&&posarr[1]<=200)
			{
			cleardevice();
			mousehide();
			return 1;
			}


		 }while(k==0);
	  }
////////////////////////////////////////////////////////////////////////////////
	   void rules()
	 {       mousehide();
		 cleardevice();
		 settextstyle(4,HORIZ_DIR,6);
		 setcolor(CYAN);
		 outtextxy(230,20,"RULES");
		 rectangle(10,10,620,450);
		 rectangle(15,15,615,445);
		 restrictmouseptr(15,15,615,445);
		 settextstyle(0,HORIZ_DIR,4);
		 outtextxy(577,25,"X");
		 settextstyle(0,HORIZ_DIR,1);
		 rectangle(615,15,565,60);
		 rectangle(610,20,570,55);
		 outtextxy(50,130,"1. Your objective is to dodge the blocks.");
		 outtextxy(50,140,"2. Use wasd to move.");
		 outtextxy(50,150,"3. Use p to pause.");
		 outtextxy(50,160,"4. Use q to quit.");
		 outtextxy(50,170,"4. You have to move the circle from the starting to the left ");
		 outtextxy(50,180,"of the screen.");
		 int m=0;
		 setposi(a,b);
		 callmouse();
		 while(m==0)
		 {
		 mouseposi(posarr,x,y,cl);
			gotoxy(1,2);
		 if(posarr[0]>=550&&posarr[0]<=615&&posarr[1]<=60&&posarr[1]>=15)
		 {cleardevice();
		  mainmenu();
		  m=1;  }

		  }
		   }


void ch(int &j,int &i)
	 {  if(j>getmaxy())
		   j=0;
		if(j<0)
		   j=getmaxy();
		if(i>getmaxx())
		   i=getmaxx();

		if(i<0)
		   {i=getmaxx();
			score+=50;
			if(z!=0)
			  z--;
		   }
	  }
void move(char r,int &j,int &i)
	 {  if(r== 'w')
		  j -=20;
		if(r=='s')
		  j +=20;
		if(r== 'a')
		  i -=20;
		if(r=='d')
		  i +=20;
		ch(j,i);
	 }
int col(int poso[2],int pos[4][4])
  { for(int i=0;i<4;i++)
	   if(poso[0]+20>= pos[i][0]&&poso[1]+20>= pos[i][1]&&poso[0]-20<= pos[i][2]&&poso[1]-20 <= pos[i][3])
			 return 0;
	   return 1;
  }
void display(int pos[2])
	 {
	   circle(pos[0],pos[1],20);
	 }
void display1(int pos[3][4])
	 { setfillstyle(1,random(14));
	   bar(pos[0][0], pos[0][1], pos[0][2],pos[0][3]);
	 }
void display2(int pos[3][4])
	 { setfillstyle(1,random(14));
	   bar(pos[1][0], pos[1][1], pos[1][2],pos[1][3]);
	 }
void display3(int pos[3][4])
	 { setfillstyle(1,random(14));
	   bar(pos[2][0], pos[2][1], pos[2][2],pos[2][3]);
	 }
void display4(int pos[4][4])
	 { setfillstyle(1,random(14));
	   bar(pos[3][0], pos[3][1], pos[3][2],pos[3][3]);
	 }
void pos_ch(int pos[3][4])
	 { int s=1;
	   for(int i=0;i<4;i++)
		 {s=s*-1;
		 for(int j=1;j<4;j=j+2)
		   pos[i][j]-=1;
		 }
		 delay(z);
	   cleardevice();
	 }
void re(int pos[4][4],int midx,int midy)
	  {for(int i=0;i<4;i++)
		 if(pos[i][3]<0)
			{ pos[i][1]=midy*2;
			  pos[i][3]=midy*2+50;
			  if(pos[i][0]>midx)
			   {pos[i][0]=midx+random(midx-50);
				pos[i][2]=pos[i][0]+50;
			   }
			  else
			   {pos[i][0]=midx-random(midx+1);
				pos[i][2]=pos[i][0]+50;
			   }
			}

	  }


void main()
 {
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics and local
	  variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error
	   occurred */
   {
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1); /* terminate with an error
				  code */
   }
	int zz=mainmenu();
	int midx = getmaxx()/ 2;
	int midy = getmaxy()/ 2;
	int poso[2];
	int pos[4][4]={midx-midx/3,midy,midx-midx/3+50,midy+50,midx+midx/4,midy-midy/3,midx+midx/4+50,midy-midy/3+50,midx+midx/2,midy+midy/3,midx+midx/2+50,midy+midy/3+50,midx-3*midx/4,midy+midy/10,midx-3*midx/4+50,midy+midy/10+50};
	int i=midx*2,j=midy;
	char m;
	randomize();
	while(1)
	  { while(!kbhit())
		{j=j;
		 i=i;
		 poso[1]=j;
		 poso[0]=i;
		 setcolor(WHITE);
		 line(midx,0,midx,midy*2);
		 pos_ch(pos);
		 display1(pos);
		 display2(pos);
		 display3(pos);
		 display4(pos);
		 display(poso);
		 re(pos,midx,midy);
		 if(!col(poso,pos))
			goto e;
	   }
		m=getch();
	   move(m,j,i);
	   if(m=='q')
		 goto e;
	   if(m=='p')
		 system("pause");
	   if(!col(poso,pos))
		 goto e;
	  }
   e: settextstyle(4, HORIZ_DIR, 10);
	  outtextxy(midx-midx/2,midy-midy/2,"you die!");
	  getch();
	  cleardevice();
	  char string[25];
	  itoa(score, string, 10);
	  settextstyle(4,HORIZ_DIR,7);
	  outtextxy(midx-midx/2,midy-midy/2,"score :");
	  outtextxy(midx+50,midy-midy/2,string);
	  getch();
}