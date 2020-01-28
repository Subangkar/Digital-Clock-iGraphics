#include "iGraphics.h"

int currentX , currentY , isPermittedToDrawDelimiter=1; // co-ordinates to draw current digit is maintained globally & increamented inside functions

struct Color
{
	int r;
	int g;
	int b;
} DigitColor; // maintains current digit drawing colors & changes with mouse left & right click

struct Time
{
	int hour;
	int min;
	int sec;
}Now;

// updates The global "struct Time Now" with the current Time
void getCurrentTime()
{
	time_t ctime;
	tm *current;
	time ( &ctime );
	current = localtime ( &ctime );

	Now.hour = current->tm_hour;
	Now.min = current->tm_min;
	Now.sec = current->tm_sec;
}

void detimiterStatus()
{
	isPermittedToDrawDelimiter = !isPermittedToDrawDelimiter;
}


#define DIGIT_START_X 70
#define DIGIT_START_Y 100

#define SEGMENT_RECT_HEIGHT 90
#define SEGMENT_RECT_WIDTH 10

#define TRIANGLE_HEIGHT 15 // Arrow's length

#define SEGMENT_PEAK_TO_PEAK_DIFFERENCE (SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT) // total length of a polygon = 1 rectangle + 2 triangles
#define DIGIT_TO_DIGIT_DIFFERENCE 25
#define DELEMITER_DIFFERENCE DIGIT_TO_DIGIT_DIFFERENCE

#define BLINKING_TIME_DIFFERENCE 500 // The Time Difference after which the delimiter circles will appear in the screen

// Draws a vertical   ( |^| ) polygon having 6 vertices starts with assuming (X,Y)=peak point of lower arrow and rect = (dx * dy)
void VerticalSegment(int X,int Y,int dx,int dy)
{
	int triangleHeight = TRIANGLE_HEIGHT;
	double  x[6]={X , X-dx/2 , X-dx/2 , X , X+dx/2 , X+dx/2},
			y[6]={Y , Y+triangleHeight , Y+dy+triangleHeight , Y+dy+2*triangleHeight , Y+dy+triangleHeight , Y+triangleHeight};

	iFilledPolygon(x,y,6);
}

// Draws a horizontal ( <_> ) polygon having 6 vertices starts with assuming (X,Y)=peak point of left arrow and rect = (dx * dy)
void HorizontalSegment(int X,int Y,int dx,int dy)
{
	int triangleHeight = TRIANGLE_HEIGHT;
	double  x[6]={X , X+triangleHeight , X+dx+triangleHeight , X+dx+2*triangleHeight , X+dx+triangleHeight , X+triangleHeight},
			y[6]={Y , Y+dy/2 , Y+dy/2 , Y , Y-dy/2 , Y-dy/2};

	iFilledPolygon(x,y,6);
}



// draws delimiter circles @ first vertical segment's mid point & second vertical segments midpoint but doesn't shift current drawing X pos
void DrawDelimiter(int x=0,int y=0)
{
	iFilledCircle(x , y+TRIANGLE_HEIGHT*3+SEGMENT_RECT_HEIGHT+SEGMENT_RECT_HEIGHT/2 ,7); /// upper one
	iFilledCircle(x , y+TRIANGLE_HEIGHT+SEGMENT_RECT_HEIGHT/2                       ,7); /// lower one

	//    currentX += DIGIT_TO_DIGIT_DIFFERENCE;
}

// draws a digit's segments starting from (x,y) = peak point of arrow of bottom-leftmost segment
void DrawDigit(int x,int y,int digit)
{
	if(digit==0 || digit==2 || digit==6 || digit==8)
		VerticalSegment(x , y,SEGMENT_RECT_WIDTH , SEGMENT_RECT_HEIGHT);
	if(digit==0 || digit==4 || digit==5 || digit==6 || digit==8 || digit==9)
		VerticalSegment(x , y+SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT , SEGMENT_RECT_WIDTH , SEGMENT_RECT_HEIGHT);


	if(digit==0 || digit==2 || digit==3 || digit==5 || digit==6 || digit==7 || digit==8 || digit==9)
		HorizontalSegment(x , y+2*SEGMENT_RECT_HEIGHT+4*TRIANGLE_HEIGHT , SEGMENT_RECT_HEIGHT,SEGMENT_RECT_WIDTH );
	if(digit==2 || digit==3 || digit==4 || digit==5 || digit==6 || digit==8 || digit==9)
		HorizontalSegment(x , y+SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT , SEGMENT_RECT_HEIGHT  , SEGMENT_RECT_WIDTH);
	if(digit==0 || digit==2 || digit==3 || digit==5 || digit==6 || digit==8 || digit==9)
		HorizontalSegment(x , y , SEGMENT_RECT_HEIGHT   , SEGMENT_RECT_WIDTH);


	if(digit==0 || digit==1 || digit==3 || digit==4 || digit==5 || digit==6 || digit==7 || digit==8 || digit==9)
		VerticalSegment(x+SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT , y , SEGMENT_RECT_WIDTH , SEGMENT_RECT_HEIGHT);
	if(digit==0 || digit==1 || digit==2 || digit==3 || digit==4 || digit==7 || digit==8 || digit==9)
		VerticalSegment(x+SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT , y+SEGMENT_RECT_HEIGHT+2*TRIANGLE_HEIGHT , SEGMENT_RECT_WIDTH , SEGMENT_RECT_HEIGHT);

}


// Splits a number into two digits and pass them to DrawDigit & after drawing shift current drawing X pos
void DrawNum(int num)
{
	int firstDigit = num/10;
	int secondDigit = num%10;


	DrawDigit(currentX,currentY,firstDigit);
	currentX += SEGMENT_PEAK_TO_PEAK_DIFFERENCE + DIGIT_TO_DIGIT_DIFFERENCE;

	DrawDigit(currentX,currentY,secondDigit);
	currentX += SEGMENT_PEAK_TO_PEAK_DIFFERENCE + DIGIT_TO_DIGIT_DIFFERENCE;
}


// takes current time values from getCurrentTime & calls DrawNum() with them & also calls DrawDelimiter() with condition
void DrawTimeLine()
{
	getCurrentTime();// "Now" got updated with current time at here

	if(Now.min==00 && Now.sec==00) iSetColor(248,50,7);

	DrawNum(Now.hour);

	if(isPermittedToDrawDelimiter || !Now.sec) DrawDelimiter(currentX,currentY);// "isPermittedToDrawDelimiter" is toggled globally by iSetTimer()
	currentX += DELEMITER_DIFFERENCE; // moves the current drawing X pos always as DrawDelimiter() does not change currentX

	if(Now.sec==00) iSetColor(200,37,7);

	DrawNum(Now.min);

	if(isPermittedToDrawDelimiter || !Now.sec) DrawDelimiter(currentX,currentY);
	currentX += DELEMITER_DIFFERENCE;

	DrawNum(Now.sec);

	iSetColor(75,150,120);
	if(Now.hour<12) iText(1072,385,"AM",GLUT_BITMAP_HELVETICA_18);
	else iText(1072,385,"PM",GLUT_BITMAP_HELVETICA_18);
}


void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		printf("x=%d  y=%d\n",mx,my);
//		DigitColor.r=50,DigitColor.g=140,DigitColor.b=255;
		DigitColor.r=rand()%256,DigitColor.g=rand()%256,DigitColor.b=rand()%256;
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		DigitColor.r=255,DigitColor.g=128,DigitColor.b=0;
	}
}



void iDraw() {

	iClear();

	iSetColor(DigitColor.r, DigitColor.g, DigitColor.b);

	currentX=DIGIT_START_X,currentY=DIGIT_START_Y;

	DrawTimeLine();

	iSetColor(40, 120, 230);

	iText(960,5,"Press 'Q' To EXIT");
//	iText(240,25,"DIGITAL Clock :: Submitted by   #1505015",GLUT_BITMAP_TIMES_ROMAN_24);
}



int main() {


	//    iSetColor(255,0,0);

	DigitColor.r=255,DigitColor.g=128,DigitColor.b=0;

	iSetTimer(BLINKING_TIME_DIFFERENCE,detimiterStatus);

	iInitialize(1100, 400, "Digital Clock");


	return 0;
}
















/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}



/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'q') {
		exit(0);
	}
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

