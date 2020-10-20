#include<iostream>
#include<graphics.h>
using namespace std;
#define WHITE 7 	// defining white as 7
int onetime=1;      // integer to be used only once

// This Function is for printing the pixels on screen
// x = point on x-axis
// y = point on y-axis
// xc = center's x comp
// yc = centers y-comp

void drawCircle(int x, int y, int xc, int yc,int ot)
{
	// hiding pixels except the first circle
	if(ot){	
		putpixel(x+xc, -y+yc,7);		
		putpixel(y+xc, x+yc, 7);
		putpixel(-y+xc, x+yc, 7);
		
	}
	// using geometry of circle i.e. four octant property
	// where these points lie on circle (x,y) , (x,-y) , (-x,y),(-x,-y) , (y,x)
	// (-y,x)........
	putpixel(x+xc,y+yc,WHITE);
	putpixel(-x+xc,y+yc,WHITE);
	putpixel(-x+xc, -y+yc, WHITE);
	putpixel(y+xc, -x+yc, WHITE);
	putpixel(-y+xc, -x+yc, WHITE);
}
// function for creating circle
void caller(int xc,int yc,int r){
	 // decision parameter : (xk-0.5)^2 + (yk+1)^2 - r^2 simplifies to 1-r
	int pk = 1 - r;
	int x = 0;
	int y = r;
	int ot=0;
	// initial point to be plotted - (x,y) : (0,r) 
	
	// after 1st circle no complete circle
	if(onetime){
		ot=1;
		onetime=0;
	}
	// developing a loop to generate points for first octant
	while(x < y)
	{
		drawCircle(x,y,xc,yc,ot);
		// starting x from 0 means any next pixel will be at least 1 distance pixel
		++x;
		// if pk<0 mid point inside the circle
		if(pk < 0)
		{
			pk = pk + (2*x) + 1; //nest point - (xk+1,yk)
		}
		else // point outside the perimeter
		{
			--y;
			pk = pk + (2*x) + 1 - (2*y); // next point : (xk+1,yk-1)
		}
	}
}

int main()
{
	// Auto detect screen
	int gd = DETECT, gm;
	int r, xc, yc, pk, x, y;
	// initialise graph
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	cout<<"Enter the center \n";
	cin>>xc>>yc;
	cout<<"Enter the radius \n";
	cin>>r;
	
	// flags to decide the trajectory
	int p = 0,flag=0;
	
	// looping to create 20 circles 
	for(int i = 0 ; i < 20;i++){
		
		caller(xc,yc,r);
		// always adding +30 to center to move it to right
		xc+=30;
		
		// changing flags to change direction of slant trajectry
		if(p==-1 && flag==1){
			flag=0;
		}
		if(p>=4)flag=1;
		
		// p circles for a \ slant  and then again p for / slant
		if(p<4 && flag==0){
			yc+=30;	
			p+=1;
		}
		else{
			p-=1;
			yc-=30; 
		}
	}
	
	// Hold the screen
	getch();
	
}


