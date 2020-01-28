#include "iGraphics.h"

//int x = 300, y = 300, r = 20;


int currentX=120,currentY=120;


void getTime(int t[3])
{
    time_t ctime;
    tm *current;
    time ( &ctime );
    current = localtime ( &ctime );

    t[0]=current->tm_hour;
    t[1]=current->tm_min;
    t[2]=current->tm_sec;
}

#define height 80
#define width 10
#define triangleHeight_VERTICAL (sqrt(3)/2)*width
#define triangleHeight_HORIZONTAL (sqrt(3)/2)*height
//#define startX 120
//#define startY 120
#define digitDiff (height+2*width+10)
#define digitShiftX (height+2*width+10)
#define digitShiftY
#define arrowLength 3
#define delemeterDiff 20

void VerticalSegment(int X,int Y,int h,int w)
{
    double  x[6]={X , X , X+w/2 , X+w , X+w , X+w/2},
            y[6]={Y , Y+h , Y+h+(sqrt(3)/2)*w , Y+h , Y , Y-(sqrt(3)/2)*w};

    iFilledPolygon(x,y,6);
}


void HorizontalSegment(int X,int Y,int h,int w)
{
    double  x[6]={X , X+w , X+w+(sqrt(3)/2)*h , X+w , X , X-(sqrt(3)/2)*h},
            y[6]={Y ,Y , Y-h/2 , Y-h , Y-h , Y-h/2};

    iFilledPolygon(x,y,6);
}


void DrawDelimiter(int startX,int startY=0)
{
    iFilledCircle(startX+delemeterDiff/4 , startY+height/2        ,7);
    iFilledCircle(startX+delemeterDiff/4 , startY+height+height/2 ,7);

    currentX += delemeterDiff;
}

void DrawDigit(int startX,int startY,int digit)
{
	if(digit==0 || digit==2 || digit==6 || digit==8)
        iFilledRectangle(startX , startY,width , height);
	if(digit==0 || digit==4 || digit==5 || digit==6 || digit==8 || digit==9)
        iFilledRectangle(startX , startY+height+width+1 , width , height);


	if(digit==0 || digit==2 || digit==3 || digit==5 || digit==6 || digit==7 || digit==8 || digit==9)
        iFilledRectangle(startX+width , startY+2*height+width+1 , height,width );
	if(digit==2 || digit==3 || digit==4 || digit==5 || digit==6 || digit==8 || digit==9)
        iFilledRectangle(startX+width , startY+height , height  , width);
	if(digit==0 || digit==2 || digit==3 || digit==5 || digit==6 || digit==8 || digit==9)
        iFilledRectangle(startX+width , startY-width , height   , width);


	if(digit==0 || digit==1 || digit==3 || digit==4 || digit==5 || digit==6 || digit==7 || digit==8 || digit==9)
        iFilledRectangle(startX+width+height , startY , width , height);
	if(digit==0 || digit==1 || digit==2 || digit==3 || digit==4 || digit==7 || digit==8 || digit==9)
        iFilledRectangle(startX+width+height , startY+height+width+1 , width , height);

}


void DrawNum(int num)
{
    int firstDigit = num/10;
    int secondDigit = num%10;

    DrawDigit(currentX,currentY,firstDigit);
    currentX += digitShiftX;
    DrawDigit(currentX,currentY,secondDigit);
    currentX += digitShiftX;
}


void DrawTimeLine(int time[3])
{
    int hour=0,minitue=0,second=0;

    hour = time[0];
    minitue = time[1];
    second = time[2];

    DrawNum(hour);
    DrawDelimiter(currentX,currentY);
    DrawNum(minitue);
    DrawDelimiter(currentX,currentY);
    DrawNum(second);

}

void iDraw() {
	iClear();
	iSetColor(20, 200, 200);

    currentX=120,currentY=120;

//    int time[3]={};
//    getTime(time);

//    DrawTimeLine(time);

    VerticalSegment(currentX,currentY,height,width);
    VerticalSegment(currentX,currentY+height+2*triangleHeight_VERTICAL,height,width);
    HorizontalSegment(currentX+width+triangleHeight_VERTICAL,currentY,width,height);

	iSetColor(20, 200, 0);
}


int main() {
	//place your own initialization codes here.
	iInitialize(900, 400, "Digital Clock");
	return 0;
}















#pragma region unused

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//		//place your codes here
//		//	printf("x = %d, y= %d\n",mx,my);
//		x += 10;
//		y += 10;
//	}
//	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//		//place your codes here
//		x -= 10;
//		y -= 10;
//	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}

#pragma endregion unused

