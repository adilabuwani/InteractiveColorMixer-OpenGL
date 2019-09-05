//ADIL ABUWANI
//PROJECT 2
//CLASS: 368
//DATE: 7/29/2019

#include <iostream>
#include <GL/glut.h>
#include <string>
#include <cstring>
using namespace std;

GLint asciiOfZero = 48;
GLint width = 800; 
GLint height = 700;
GLfloat red = 0.0;
GLfloat green = 0.0; 
GLfloat blue = 0.0;
GLfloat lRed, lGreen, lBlue,rRed, rGreen, rBlue;

class SliderBar {
public:
	//x and y for the slidebox
	int x;  //the x and y will change in the future
	int y; //the y will change in the future
	bool specificBarSelected = false; //to indicate specific bar that is selected
	bool hoverBar = false;            //if there is a hover of the mouse
	char slideColor;

	SliderBar(int X, int Y, char color) {
		this->x = X;
		this->y = Y;
		this->slideColor = color;

	}

	void createSliderBar() {
		//specific bar selected, then change to gray 
		if (specificBarSelected==true) {
			glColor3f(0.8, 0.8, 0.8);
		}else if (hoverBar == true) {
			glColor3f(0.2, 0.2, 0.2);
		}else if (slideColor == 'r') {
			glColor3f(1.0, 0.0, 0.0);
		}else if (slideColor == 'g') {
			glColor3f(0.0, 1.0, 0.0);
		}else if (slideColor == 'b') {
			glColor3f(0.0, 0.0, 1.0);
		}else {//do nothing
			return;
		}
		


		// coordinates for the slideBox
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + 30, y);  //balance between
		glVertex2i(x + 30, y + 15);
		glVertex2i(x, y + 15);
		glEnd();
	}


};//end class sliderBar

void displayDigit(float color, int pos) {
	int current = color * 255;                      //convert color to 255 range
	int length = to_string(current).length();
	for (int i = 0; i < length; i++) {
		
		glRasterPos2i(pos, 560);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, to_string(current).at(i));
		pos =pos+ 11;
	}//end for
}
//give initials and create slider bars
int initialX = 85;
int initialY = 264;
SliderBar redSlideBox(initialX, initialY, 'r');
SliderBar greenSlideBox(initialX+100, initialY, 'g');
SliderBar blueSlideBox(initialX + 200, initialY, 'b');

void display() {

	//draw lines first
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(4.0);  //width of the line
	
	glBegin(GL_LINES);
	int xCord = 100;
	int yCord = 272;

	for (int i = 0; i < 3; i++) {
		if (i == 0) {
		glColor3f(1.0, 0.0, 0.0);  // red line
		}
		else if (i == 1) {
			glColor3f(0.0, 1.0, 0.0);  //green line
		}
		else {
			glColor3f(0.0, 0.0, 1.0);  //blue line
		}
		glVertex2i(xCord, yCord);
		glVertex2i(xCord, yCord + 256);

		xCord += 100;
	}//end for
	glEnd();
	//////////////////////////////////////////////////////////////////////////
	//middle square
	glBegin(GL_QUADS);
	glColor3f(red, green, blue);
	glVertex2i(440, 650);
	glVertex2i(660, 650);
	glVertex2i(660, 430);
	glVertex2i(440, 430);

	// rectangle box-by dfault black
	glColor3f(lRed, lGreen, lBlue);
	glVertex2i(400, 350); //top left
	glVertex2i(400, 230); //bottom left

	//by default black
	glColor3f(rRed, rGreen, rBlue);
	glVertex2i(700, 230);
	glVertex2i(700, 350);

	glEnd();

	redSlideBox.createSliderBar();
	greenSlideBox.createSliderBar();
	blueSlideBox.createSliderBar();



	//display letters for each bar
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2i(91, 220);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2i(191, 225);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');

	glColor3f(0.0, 0.0, 1.0);
	glRasterPos2i(291, 225);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');

	glColor3f(1.0, 0.0, 0.0);
	displayDigit(red, 89);

	glColor3f(0.0, 1.0, 0.0);
	displayDigit(green, 189);

	glColor3f(0.0, 0.0, 1.0);
	displayDigit(blue, 289);
	glutSwapBuffers();
}//end display

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'R':
	case 'r':       //r is pressed
		rRed = red;              //amount of color to put
		rGreen = green;
		rBlue = blue;
		break;
	case 'L':
	case 'l':                //l key is pressed
		lRed = red;   //amount of color
		lGreen = green;
		lBlue = blue;
		break;
	}

	//refresh after click
	glutPostRedisplay();

}

//x is in the range of a particular bar
void sliderSelected(int mouseX, int mouseY, SliderBar& selectedBox, float& colorDigit) {
	float getColor = 0.0;
	float convertedY = height - mouseY - 1;
	GLint yBegin = 272;
	GLint yEnd = 528;
	GLint maxDistance = 256;

	GLfloat boxGap = convertedY - selectedBox.y;

	//between the box-its active
	if ((convertedY) >= (selectedBox.y) && (convertedY) < (selectedBox.y + 15) && mouseX > (selectedBox.x) && mouseX < (selectedBox.x + 30)) {
		selectedBox.specificBarSelected = true;
	}else if (convertedY >= yBegin && convertedY <= yEnd && mouseX >= selectedBox.x+5 && mouseX <= selectedBox.x+25) {
		selectedBox.y = convertedY;                   //get the y exact coordinate in the xy plane where the mouse points                         
		getColor = ((float)convertedY - yBegin) / maxDistance;       //get range from 0-1
		selectedBox.specificBarSelected = true;
		colorDigit = getColor;
	}else if (convertedY > yEnd && convertedY<yEnd+10 && mouseX >= selectedBox.x + 5 && mouseX <= selectedBox.x + 25) {                        //greater? set color to 1 (max)
		selectedBox.y = yEnd;                              //max y
		getColor = 1;
		colorDigit = getColor;
	}else if (convertedY < yBegin && convertedY >yBegin-10 && mouseX >= selectedBox.x + 5 && mouseX <= selectedBox.x + 25) {
		selectedBox.y = yBegin;                         //minY 
		getColor = 0;   
		colorDigit = getColor;
		//less? set to min=0
	}

}
// select pixel box from the rectangle 
void updateSlider(int mouseX, int mouseY) {
	GLint yBegin = 272;
	GLint range = 256;
	glutSwapBuffers();
	float rangeInBetween = 300;

	//get in percentage
	float Rprobability = (mouseX-400) / rangeInBetween;
	float Lprobability = 1.0 - Rprobability;

	//amount of red, green and blue
	red = (rRed * Rprobability) + (lRed * Lprobability);
	green = (rGreen * Rprobability) + (lGreen * Lprobability);
	blue = (rBlue * Rprobability) + (lBlue * Lprobability);

	//allocate location of y on rgb
	redSlideBox.y = red * range + yBegin;
	greenSlideBox.y = green * range + yBegin;
	blueSlideBox.y = blue * range + yBegin;

}

void mouse(int button, int state, int mouseX, int mouseY) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		//left mouse button is pressed
		if (state == GLUT_DOWN) {
			if (mouseX > 85 && mouseX <= 115) {  //red slidebox selected
				sliderSelected(mouseX, mouseY, redSlideBox, red);
			}
			else if (mouseX > 184 && mouseX < 214) {  //greenslide box selected
				sliderSelected(mouseX, mouseY, greenSlideBox, green);
			}
			else if (mouseX > 284 && mouseX < 314) {    //blue selected
				sliderSelected(mouseX, mouseY, blueSlideBox, blue);
			}
			else if (mouseX > 400 && mouseX < 700 && (height - mouseY - 1) > 230 && (height - mouseY - 1) < 350) {   //rectangularBox clicked, find the pixel and asign
				updateSlider(mouseX, (height - mouseY - 1));
			}
			else {
				return;
			}
		}
		else { //hold down, change back to false
			redSlideBox.specificBarSelected = false;
			blueSlideBox.specificBarSelected = false;
			greenSlideBox.specificBarSelected = false;
		}
		break;
	}

	glutPostRedisplay();
}//end mouse

//done
float slideBar(int mouseX, int mouseY, SliderBar& currBar) {
	float getColor = 0.0;
	float convertedY = height - mouseY - 1;
	GLint yBegin = 272;
	GLint yEnd = 528; 
	GLint maxDistance = 256;          //max distance

	if (convertedY>=yBegin && convertedY<=yEnd) {
		currBar.y = convertedY;                    //get the y exact coordinate in the xy plane where the mouse points                         
		getColor = ((float)convertedY - yBegin)/maxDistance;       //get range from 0-1
	}else if (convertedY > yEnd) {                        //greater? set color to 1 (max)
		currBar.y = yEnd;                              //max y
		getColor = 1;
	}else if (convertedY < yBegin) {
		currBar.y = yBegin;                         //minY 
		getColor = 0;                                 //less? set to min=0
	}
	return getColor;
}

//motion used when the click is in the range
void motion(int mouseX, int mouseY) {
	if (mouseX > 49 && mouseX < 150 && redSlideBox.specificBarSelected) {  //max range for redBox
		red = slideBar(mouseX, mouseY, redSlideBox);
	}
	else if (mouseX > 150 && mouseX < 250 && greenSlideBox.specificBarSelected) {   //max range for green box
		green = slideBar(mouseX, mouseY, greenSlideBox);
	}
	else if (mouseX > 250 && mouseX < 350 && blueSlideBox.specificBarSelected) {   //max range for blue box
		blue = slideBar(mouseX, mouseY, blueSlideBox);
	}
	else {
		return;
	}
	glutPostRedisplay();
}

void passive(int mouseX, int mouseY) {

	float convertedY = height - mouseY - 1;

	if (mouseX >= 85 && mouseX <= 115 && convertedY >= redSlideBox.y && convertedY <= redSlideBox.y + 15) {  //red slidebox selected
		redSlideBox.hoverBar = true;
	}
	else if (mouseX >= 185 && mouseX <= 215 && convertedY >= greenSlideBox.y && convertedY <= greenSlideBox.y + 15) {  //greenslide box selected
		greenSlideBox.hoverBar = true;
	}
	else if (mouseX >= 285 && mouseX <= 315 && convertedY >= blueSlideBox.y && convertedY <= blueSlideBox.y + 15) {    //blue selected
		blueSlideBox.hoverBar = true;
	}
	else {//set all to false
		redSlideBox.hoverBar = false;
		greenSlideBox.hoverBar = false;
		blueSlideBox.hoverBar = false;
	}
	glutPostRedisplay();

}//end passive
void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 0);
	glutCreateWindow("Sample");
	
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glColor3f(1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutMainLoop();
}//end main