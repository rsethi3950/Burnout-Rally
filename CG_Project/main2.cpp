#include<GL/glut.h>
#include<iostream>
#include<fstream>
#include<math.h>
#include<mmsystem.h>
using namespace std;

//game speed
int FPS = 50;
//GAME TRACK
int start = 0;
int gv = 0;		//gameover
int level = 0;

//TRACK SCORE
int score = 0;

//FORM MOVE TRACK
int scoreUpdater = 0;


//FOR CAR LEFT / RIGHT
int lrIndex =0;
int lrIndextemp=22;
float yBoat=0,des_pos=45.0;

//CARS COMING
int car1 = 0;
int lrIndex1 = 0;
int car2 = 0;
int lrIndex2 =0;
int car3 = 0;
int lrIndex3 = 0;

//FOR DISPLAY TEXT
GLvoid *font1 =GLUT_BITMAP_TIMES_ROMAN_24;
GLvoid *font2 =GLUT_BITMAP_HELVETICA_18;
GLvoid *font3 =GLUT_BITMAP_9_BY_15;

bool starState=true;
int blinkTime = 60;
int highScore, finalScore;

char s[30];

void readFromFile() {
	ifstream file_handle;
	file_handle.open("HighScoreFile.txt",ios::in);
	file_handle>>highScore;
	file_handle.close();
}

void writeIntoFile(int final) {					
	ofstream file_handle;
	file_handle.open("HighScoreFile.txt",ios::out);
	file_handle<<final;
	file_handle.close();
}

void initialiseHighScoreFile(){
   	ifstream ifile;
   	ifile.open("HighScoreFile.txt");
   	if(ifile) {
    	ifile.close();
  	} else {
    	writeIntoFile(10);
   	}	
}


void renderBitmapString(float x, float y, void *font, const char *string){
	const char *c;
	glRasterPos2f(x, y);  //pointer
	for (c=string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
}

void tree(int x, int y){
	int newx = x;
	int newy = y;
	//TREE LEFT
		//BOTTOM
		
		glColor3f(0.871, 0.722, 0.529);
		glBegin(GL_TRIANGLES);
		glVertex2f(newx+11,newy+55);
		glVertex2f(newx+12,newy+55-10);
		glVertex2f(newx+10,newy+55-10);
		glEnd();
		//up
		glColor3f(0.133,0.545,0.133);
		glBegin(GL_TRIANGLES);
		glVertex2f(newx+11,newy+55+3);
		glVertex2f(newx+12+3,newy+55-3);
		glVertex2f(newx+10-3,newy+55-3);
		glEnd();
}


void startGame(){
	//ROAD
	//glColor3f(0.412,0.412,0.412);
	glColor3f(0.47,0.70,0.93);
	glBegin(GL_POLYGON);
	glVertex2f(20,0);
	glVertex2f(20,100);
	glColor3f(0.21,0.36,0.49);
	glVertex2f(80,100);
	glVertex2f(80,0);
	glEnd();
	
	//ROAD BORDER AT LEFT
	glColor3f(1.000,1.000,1.000);
	glBegin(GL_POLYGON);
	glVertex2f(20,0);
	glVertex2f(20,100);
	glVertex2f(23,100);
	glVertex2f(23,0);
	glEnd();
	
	//ROAD BORDER AT RIGHT
	glColor3f(1.000,1.000,1.000);
	glBegin(GL_POLYGON);
	glVertex2f(77,0);
	glVertex2f(77,100);
	glVertex2f(80,100);
	glVertex2f(80,0);
	glEnd();
	
	scoreUpdater--;
	if(scoreUpdater<-20){
		scoreUpdater=20;
		score+=1;
	}
	
	//SCORE BOARD
	glColor3f(0.000,0.000,0.000);
	glBegin(GL_POLYGON);
	glVertex2f(80,97);
	glVertex2f(100,97);
	glVertex2f(100,98-8);
	glVertex2f(80,98-8);
	glEnd();
	
	//PRINT SCORE
	char buffer [50];
	finalScore = score;
	if(highScore<finalScore)
		writeIntoFile(finalScore);
	
	sprintf (buffer, "SCORE: %d", score);
	glColor3f(1.000,1.000,1.000);
	renderBitmapString(80.5,95,(void *)font3,buffer);
	
	//SPEED PRINT
	char buffer1 [50];
	sprintf (buffer1, "SPEED: %d", FPS);
	glColor3f(1.000,1.000,1.000);
	renderBitmapString(80.5,95-2,(void *)font3,buffer1);
	
	//level PRINT and increase speed with level
	if(score % 10 == 0){
		int last = score/10;
		if(last!=level){
			level = score/10;
			FPS = FPS+2;
		}
	}	
	char level_buffer [50];
	sprintf (level_buffer, "LEVEL: %d", level);
	glColor3f(1.000,1.000,1.000);
	renderBitmapString(80.5,95-4,(void *)font3,level_buffer);
	
		//BOAT BODY
		glColor3f(0.54,0.84,0.82);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex+25,1);
		glVertex2f(lrIndex+25,10);
		glVertex2f(lrIndex+28,12);
		glVertex2f(lrIndex+31,10);
		glVertex2f(lrIndex+31,1);
		glEnd();

		glColor3f(00,0.25,0.25);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex+26,5);
		glVertex2f(lrIndex+26,2.5);	
		glVertex2f(lrIndex+30,2.5);
		glVertex2f(lrIndex+30,5);
		glEnd();
		
		glColor3f(0,0.25,0.25);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex+26,6);
		glVertex2f(lrIndex+26,9);
		glVertex2f(lrIndex+28,10.5);
		glVertex2f(lrIndex+30,9);
		glVertex2f(lrIndex+30,6);
		glEnd();
		
		
		//OPPOSITE CAR1
		glColor3f(0.19, 0.40, 0.33);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex1+26,car1+100);
		glVertex2f(lrIndex1+26,car1+100-7);
		glVertex2f(lrIndex1+28,car1+100-9);
		glVertex2f(lrIndex1+30,car1+100-7);		
		glVertex2f(lrIndex1+30,car1+100);
		glEnd();
		glColor3f(0.60, 0.78, 0.056);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex1+27,car1+100-01);
		glVertex2f(lrIndex1+27,car1+100-7);
		glVertex2f(lrIndex1+28,car1+100-9+1);
		glVertex2f(lrIndex1+29,car1+100-7);		
		glVertex2f(lrIndex1+29,car1+100-1);
		glEnd();
		car1--;
		if(car1<-100){
			car1=0;
			lrIndex1=lrIndex;
		}
		//KILL CHECK CAR1
		if((abs(lrIndex-lrIndex1)<6)&&(car1+100<10)){
			start=0;
			gv=1;	
		}
	
		//OPPOSITE CAR2
		glColor3f(1,0.86,0.35);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex2+26,car2+100);
		glVertex2f(lrIndex2+26,car2+100-7);
		glVertex2f(lrIndex2+28,car2+100-9);
		glVertex2f(lrIndex2+30,car2+100-7);		
		glVertex2f(lrIndex2+30,car2+100);
		glEnd();
		glColor3f(0.78, 0.64, 0.09);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex2+27,car2+100-01);
		glVertex2f(lrIndex2+27,car2+100-7);
		glVertex2f(lrIndex2+28,car2+100-9+1);
		glVertex2f(lrIndex2+29,car2+100-7);		
		glVertex2f(lrIndex2+29,car2+100-1);
		glEnd();
		car2--;
		if(car2<-100){
			car2=0;
			lrIndex2=lrIndex;
		}
		//KILL CHECK CAR2
		if((abs(lrIndex-lrIndex2)<6)&&(car2+100<10)){
			start=0;
			gv=1;		
		}

		//OPPOSITE CAR3
		glColor3f(0.88,0.55,0.42);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex3+26,car3+100);
		glVertex2f(lrIndex3+26,car3+100-7);
		glVertex2f(lrIndex3+28,car3+100-9);
		glVertex2f(lrIndex3+30,car3+100-7);		
		glVertex2f(lrIndex3+30,car3+100);
		glEnd();
		glColor3f(0.76, 0.38, 0.25);
		glBegin(GL_POLYGON);
		glVertex2f(lrIndex3+27,car3+100-01);
		glVertex2f(lrIndex3+27,car3+100-7);
		glVertex2f(lrIndex3+28,car3+100-9+1);
		glVertex2f(lrIndex3+29,car3+100-7);		
		glVertex2f(lrIndex3+29,car3+100-1);
		glEnd();
		car3--;
		if(car3<-100){
			car3=0;
			lrIndex3=lrIndex;
		}
		//KILL CHECK CAR3
		if((abs(lrIndex-lrIndex3)<6)&&(car3+100<10)){
			start=0;
			gv=1;		
		}		
	
				
}

void firstDesign(){
	
//	Road background
	glColor3f(0.94, 0.85, 0.59);
	glBegin(GL_POLYGON);
	glVertex2f(0,55);
	glVertex2f(100,55);
	glColor3f(0.83, 0.62, 0.52);
	glVertex2f(100,50-50);
	glVertex2f(0,50-50);
	glEnd();
	
	//water
	glColor3f(0.21,0.36,0.49);
	glBegin(GL_TRIANGLES);
	glVertex2f(32-2+21,55);
	glVertex2f(32+58,50-50);
	glColor3f(0.47,0.70,0.93);
	glVertex2f(32-22,50-50);
	glEnd();
	
	//boat
	glColor3f(0.54,0.84,0.82);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndextemp+25,1+yBoat);
	glVertex2f(lrIndextemp+25,10+yBoat);
	glVertex2f(lrIndextemp+28,12+yBoat);
	glVertex2f(lrIndextemp+31,10+yBoat);
	glVertex2f(lrIndextemp+31,1+yBoat);
	glEnd();

	glColor3f(00,0.25,0.25);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndextemp+26,5+yBoat);
	glVertex2f(lrIndextemp+26,2.5+yBoat);	
	glVertex2f(lrIndextemp+30,2.5+yBoat);
	glVertex2f(lrIndextemp+30,5+yBoat);
	glEnd();
	
	glColor3f(0,0.25,0.25);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndextemp+26,6+yBoat);
	glVertex2f(lrIndextemp+26,9+yBoat);
	glVertex2f(lrIndextemp+28,10.5+yBoat);
	glVertex2f(lrIndextemp+30,9+yBoat);
	glVertex2f(lrIndextemp+30,6+yBoat);
	glEnd();
	
	glColor3f(0.0,0.0,0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(lrIndextemp+28,7+yBoat);
	glVertex2f(lrIndextemp+34,4+yBoat);
	glVertex2f(lrIndextemp+28,7+yBoat);
	glVertex2f(lrIndextemp+22,4+yBoat);
	glEnd();
	glLineWidth(1.0);
//	Road Sky
	glColor3f(0.39, 0.29, 0.45);
	glBegin(GL_POLYGON);
	glVertex2f(100,100);
	glVertex2f(0,100);
	glColor3f(0.64, 0.35, 0.44);
	glVertex2f(0,55);
	glVertex2f(100,55);
	glEnd();
	
	if(starState){
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5);
		glBegin(GL_POINTS);
	//	x-axis=0-100, y-axis=55-100
		glVertex2f(50,85);
		glVertex2f(10,90);
		glVertex2f(30,70);
		glVertex2f(90,80);
		glEnd();
	}
	else{
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(60,95);
		glVertex2f(20,90);
		glVertex2f(50,70);
		glVertex2f(70,80);
		glVertex2f(5,60);
		glVertex2f(90,90);
		glEnd();
	}
//	Hill 1
	glColor3f(0.4, 0.21, 0.06);
	glBegin(GL_TRIANGLES);
	glVertex2f(20,55+10);
	glVertex2f(20+7,55);
	glVertex2f(0,55);
	glEnd();
	
	//	Hill 2
	glColor3f(0.14, 0.09, 0.04);
	glBegin(GL_TRIANGLES);
	glVertex2f(20+15,55+12);
	glVertex2f(20+20+10,55);
	glVertex2f(0+10,55);
	glEnd();
	
	//	Hill 3
	glColor3f(0.4, 0.21, 0.06);
	glBegin(GL_TRIANGLES);
	glVertex2f(87,55+10);
	glVertex2f(100,55);
	glVertex2f(60,55);
	glEnd();
	
	//	Hill 4
	glColor3f(0.14, 0.09, 0.04);
	glBegin(GL_TRIANGLES);
	glVertex2f(70,70);
	glVertex2f(90,55);
	glVertex2f(50,55);
	glEnd();
	
//	Tree Left
	//	Bottom
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_TRIANGLES);
	glVertex2f(11,55);
	glVertex2f(12,55-10);
	glVertex2f(10,55-10);
	glEnd();
	
	//	Up
	glColor3f(0.133, 0.545, 0.133);
	glBegin(GL_TRIANGLES);
	glVertex2f(11,55+3);
	glVertex2f(12+3,55-3);
	glVertex2f(10-3,55-3);
	glEnd();
	
	tree(5,-15);
	tree(9,5);
	tree(85,9);
	tree(75,-5);
	
//	Menu Place Holder
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(32-4-1,50+5+10+1);
	glVertex2f(32+46+1,50+5+10+1);
	glVertex2f(32+46+1,50-15+10-1);
	glVertex2f(32-4-1,50-15+10-1);
	glEnd();
	
	glColor3f(0.0, 0.52, 0.52);
	glBegin(GL_POLYGON);
	glVertex2f(32-4,50+5+10);
	glVertex2f(32+46,50+5+10);
	glVertex2f(32+46,50-15+10);
	glVertex2f(32-4,50-15+10);
	glEnd();

	
//	text info on first page
	if (gv==1){
		glColor3f(1.0, 1.0, 1.0);
		renderBitmapString(48,60+10,(void *)font1, "GAME OVER");
		glColor3f(1.0, 1.0, 1.0);
		char buffer2 [50],buffer3 [50];
		sprintf (buffer2, "Score : %d", score);
		renderBitmapString(50,40,(void *)font1, buffer2);
		readFromFile();
		sprintf (buffer3, "Maximum Score : %d", highScore);
		renderBitmapString(46,35,(void *)font1, buffer3);
	}
	
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(45,75,(void *)font1, "BURNOUT RALLY");
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(45-des_pos,10,(void *)font1, "DESIGNED BY");
	
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(43+des_pos,5,(void *)font1, "RIYA AND VANSHIKA");
	
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(30,50+10,(void *)font2, "Press SPACE to start");
	renderBitmapString(30,50-3+10,(void *)font2, "Press ESC to exit");
	
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(30,50-6+10,(void *)font3, "Press UP to increase speed");
	renderBitmapString(30,50-8+10,(void *)font3, "Press DOWN to decrease speed");
	renderBitmapString(30,50-10+10,(void *)font3, "Press RIGHT to turn right");
	renderBitmapString(30,50-12+10,(void *)font3, "Press LEFT to turn left");
	
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(30-5,50-40,(void *)font3, " ");
	renderBitmapString(30-5,50-43,(void *)font3, " ");
	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(start==1){
		glClearColor(0.94, 0.85, 0.59, 1.0);
		startGame();
	}
	else{
		firstDesign();
	}
	glFlush();
	glutSwapBuffers();
}

void spe_key(int key, int x, int y){
	switch(key){
		case GLUT_KEY_DOWN:
			if(FPS>(50+(level*2)))
			FPS=FPS-2;
			break;
			
		case GLUT_KEY_UP:
			FPS=FPS+2; 
			break;
			
		case GLUT_KEY_LEFT:
			if (lrIndex>=0){
				lrIndex= lrIndex- (FPS/10);
				if(lrIndex<0) lrIndex=-1;
			}
			break;
		
		case GLUT_KEY_RIGHT:
			if (lrIndex<=44){
				lrIndex= lrIndex+ (FPS/10);
				if(lrIndex>44) lrIndex=45;
			}
			break;
		default:
			break;
	}
}

void processKeys(unsigned char key, int x, int y){
	switch(key){
		case ' ':
			if (start==0){
				start=1;
				gv=0;
				FPS=50;
				scoreUpdater=0;
				lrIndex=0;
				car1=0;
				lrIndex1=0;
				car2=35;
				lrIndex2=0;
				car3=70;
				lrIndex3=0;
				score=0;
				level=0;
			}
			break;
			
		case 27:
			exit(0);
		break;
		default:
			break;
	}
}

void timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0);
	blinkTime--;
	if(blinkTime<0){
		blinkTime = 60;
		starState = !starState;
	}
	yBoat+=0.4;
	if(yBoat>70){
		yBoat = 0;
	}
	des_pos -= 0.3;
	if(des_pos<=0){
		des_pos = 0;
	}
	
}


int main(int argc, char** argv){
	initialiseHighScoreFile();
	readFromFile();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 650);
	glutInitWindowPosition(200,20);
	glutCreateWindow("Save The Boat");
	glutDisplayFunc(display);	
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(processKeys);
	
	// Music
	PlaySound(TEXT("strings3.wav"), NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);  
	
	glOrtho(0,100,0,100,-1,1);
	glClearColor(0.18,0.31, 0.31, 1);
	
	glutTimerFunc(1000, timer, 0);
	glutMainLoop();
	return 0;
}



