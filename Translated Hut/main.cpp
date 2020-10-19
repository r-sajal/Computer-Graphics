#include<graphics.h>
#include<bits/stdc++.h>
using namespace std;

// Variables for coloring scaled image
// maxi1--> max value of x1
// mini1--> max value of y1
// maxi2--> max value of x2
// mini2--> max value of y2
int maxi1=-1,mini1=10000,maxi2=-1,mini2=10000;

// boundary fill algorithm fill everyting inside the boundary
// x= any x-axis coordinate inside polygon
// y= any y-axis coordinate inside polygon
void boundaryfill(int x, int y, int fill_color,int boundary_color) 
{ 
	// getpixel --> takes one pixel at position and compare color with boundary
	// if color is same as boundary then it is end of polygon
	// else replace its color with fill_color
    if(getpixel(x, y) != boundary_color && 
       getpixel(x, y) != fill_color) 
    { 
    	// put fill_color to the pixel at location (x,y)
        putpixel(x, y, fill_color); 
        // to reach all points in all four direction
        // we recursively call the function updating values
        boundaryfill(x + 1, y, fill_color, boundary_color); 
        boundaryfill(x, y + 1, fill_color, boundary_color); 
        boundaryfill(x - 1, y, fill_color, boundary_color); 
        boundaryfill(x, y - 1, fill_color, boundary_color); 
    } 
} 

// General line drawing function
// from points X0,Y0 to X1,Y1
void DDA(int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps for points
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
        putpixel (X,Y,WHITE);  // put pixel at (X,Y) with color white
        X += Xinc;           // increment in x at each step with previously calculated value 
        Y += Yinc;           // increment in y at each step 

    } 
}

// To translate and scale the coordinate and line
// T1 = change for x
// T2 = change for y
// sx = scale x
// sy = scale y

void translateline ( int x1,int y1,int x2,int y2, int t1,int t2,float sx,float sy) 
{     
    // updating translated coordinates 
    x1 = x1 + t1; 
    y1 = y1 + t2; 
    x2 = x2 + t1; 
    y2 = y2 + t2; 
  
    // updating scaling x and scaling y value
    x1=x1*sx;
    y1=y1*sy;
    x2=x2*sx;
    y2=y2*sy;
    // Calculating mini and max value for using them in coloring the polygon formed
	maxi1 = max(maxi1,x1);
	maxi2= max(maxi2,y1);
	// extracting mini value
	if(mini2>y2){
		mini1=x2;
		mini2=y2;
	}
	// Drawing the new transformed line using DDA algorithm
    DDA(x1, y1, x2, y2); 
} 

 
int main()
{
 
// Initializing drivers and mode for graph drawing
int gdriver=DETECT,gmode;
// initializing window with width , height
initwindow(800, 800);
initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");

// DDA algorithm drawing line from (x0,y0) --> (x1,y1)
DDA(116,110,310,110);
DDA(116,110,116,250);
DDA(116,250,310,250);
DDA(310,110,310,250);

DDA(116,110,213,10);   
DDA(310,110,213,10);
DDA(150,250,150,150);   
DDA(200,250,200,150);
DDA(150,150,200,150);

// Filling Color in the above formed shape 
// using points under the boundary
// x,y,fillin_color,boundary_color
boundaryfill(308,248,3,WHITE);
boundaryfill(213,12,8,WHITE);



// taking t1,t2 --> translating the hut 
int t1=200,t2=200;
// sx,sy --> rescaling x-axis and y-axi
float sx=1.5,sy=1.5;
// Translate line uses same coordinates as above 
// And also takes t1,t2 --> for transformation 
// And sx,sy --> for scaling
translateline(116,110,310,110,t1,t2,sx,sy);
translateline(116,110,116,250,t1,t2,sx,sy);
translateline(116,250,310,250,t1,t2,sx,sy);
translateline(310,110,310,250,t1,t2,sx,sy);

translateline(116,110,213,10,t1,t2,sx,sy);   
translateline(310,110,213,10,t1,t2,sx,sy);
translateline(150,250,150,150,t1,t2,sx,sy);   
translateline(200,250,200,150,t1,t2,sx,sy);
translateline(150,150,200,150,t1,t2,sx,sy);

// uses maxi, mini combination to find coordinates of above triangle and rectangle
// boundary fill fills the color
boundaryfill(maxi1-2,maxi2-1,3,WHITE);
boundaryfill(mini1,mini2+2,8,WHITE);


// 3 --> cyan
// 8 --> dark grey

// to stop screen 
getch(); 
return 0;
}
 
