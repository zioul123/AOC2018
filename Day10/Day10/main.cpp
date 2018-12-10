/**
 * TO USE:
 * Go to the folder where the built artefacts are, and pipe the input using ./Day10 < b.txt.
 * The text file must be cleaned up using the Cleaner.java class first.
 */
#include <cmath>
#include <iostream>
#include <vector>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;

int points[356][2];
int velocities[356][2];
int c;
bool changedSinceLastDisplay = false;
/*
 * Constants
 */
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
int factor = 1;

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-50000, 50000, -50000, 50000, -50000, 50000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 }

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
    
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

    /*
     * Draw things
     */
    glBegin(GL_POINTS);
    for (int i = 0; i < 356; i++) {
        glVertex2f((float)points[i][0], (float) points[i][1]);
    }
    glEnd();
    
    if (changedSinceLastDisplay) {
        changedSinceLastDisplay = false;
        cout << c << endl;
    }
    
	glPopMatrix();
	glFlush ();
}

void idle()
{
	glutPostRedisplay();	//after updating, draw the screen again
}

// Handle rendering while a edit point is being dragged
int mX;
void mouseDrag(int x, int y)
{
    changedSinceLastDisplay = true;
    int delta = x-mX;
    c += delta;
    for (int i = 0; i < 356; i++) {
        points[i][0] += delta * velocities[i][0];
        points[i][1] += delta * velocities[i][1];
    }
}

// Zoom by one near the end
void zoomByOne(bool unZoom) {
    changedSinceLastDisplay = true;
    
    if (unZoom) {
    c++;
    for (int i = 0; i < 356; i++) {
        
        points[i][0] += velocities[i][0];
        points[i][1] += velocities[i][1];
    }}
    else{
    c--;
        for (int i = 0; i < 356; i++) {
        points[i][0] -= velocities[i][0];
        points[i][1] -= velocities[i][1];
    }}
}

void mouse(int button, int state, int x, int y)
{
    /*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
    /*state: GLUT_UP or GLUT_DOWN */
    enum
    {
        MOUSE_LEFT_BUTTON = 0,
        MOUSE_MIDDLE_BUTTON = 1,
        MOUSE_RIGHT_BUTTON = 2,
        MOUSE_SCROLL_UP = 3,
        MOUSE_SCROLL_DOWN = 4
    };
    
    if((button == MOUSE_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        mX = x;
    }
 
    if((button == MOUSE_LEFT_BUTTON) && (state == GLUT_UP))
    {
        mX = 0;
    }
    glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
        case 'z':
            zoomByOne(true);
            break;
        case 'Z':
            zoomByOne(false);
            break;
        case 'f':
            factor += 1;
            break;
        case 'F':
            factor -= 1;
            break;
		case 'q':
			k+=factor;
			glutPostRedisplay();
		    break;
		case 'Q':
			if(k>0.1)
				k-=factor;
			glutPostRedisplay();
		    break;
		case 'X':
			tx-=factor;
			glutPostRedisplay();
		    break;
		case 'x':
			tx+=factor;
			glutPostRedisplay();
		    break;
		case 'y':
			ty-=factor;
			glutPostRedisplay();
		    break;
		case 'Y':
			ty+=factor;
			glutPostRedisplay();
		    break;
		case 27:
			exit(0);
		break;
		default:
		break;
	}
}

// Getting input points
void getInput() {
    int x,y;
    for (int i = 0; i < 356; i++) {
        scanf("%d, %d", &x, &y);
        points[i][0] = x;
        points[i][1] = y;
    }
    for (int i = 0; i < 356; i++) {
        scanf("%d, %d", &x, &y);
        velocities[i][0] = x;
        velocities[i][1] = y;
    }
}

int main(int argc, char **argv)
{
	cout<<"Day 10!\n\n";
    cout <<"Drag mouse: Move by mouse moved amount\n";
    cout <<"Z/z: move by one\n";
    cout <<"F/f: decrease/increase scale factor\n";
    cout <<"X/x: shift everything along x axis\n";
    cout <<"Y/y: shift everything along y axis\n";
    cout <<"Q/q: zoom in or out\n";
	cout <<"ESC: Quit\n";

    getInput();
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	glutMouseFunc(mouse);
    glutMotionFunc(mouseDrag);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
