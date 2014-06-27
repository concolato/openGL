#include <stdio.h> // For debugging 
#include <math.h> // Calculations to use later, not in this assignment
//Open GL includes
#include <GL/glut.h>
#include <GL/gl.h>
//By Claude Concolato - 10-2013

typedef struct {
    int width;
    int height;
    char* title;

    float field_of_view_angle;
    float z_near;
    float z_far;
} 

glutWindow; 
glutWindow win;

int rotatedegree;
float translatex;
float translatey;
 
 
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear screen and depth buffer
    glLoadIdentity();
    glTranslatef(translatex,translatey,-3.0f);
    glRotatef(rotatedegree,0.0f,0.0f,1.0f);// Rotate The Triangle

    glBegin(GL_TRIANGLES); // Triangle vertices and colors
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( -0.0f, 1.0f, 0.0f);                                          
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f, -0.5f, 0.0f);                                           
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f, -0.5f, 0.0f);                    
                    
    glEnd();                               

    glutSwapBuffers();
}
 
void keyboardfunc(unsigned char key, int x, int y){
    switch (key){
        case '+':
                rotatedegree+=5;
                printf("rotation +5 degree\n");
        break;
        case '-':
                rotatedegree-=5;
                printf("rotation -5 degree\n");
        break;
    }

    glutPostRedisplay(); // refresh
 
}

void specialfunc(int key, int x, int y){
    switch (key){
        case 100:
                translatex-=0.1;
                printf("left arrow pressed\n");
        break;
        case 101:
                translatey+=0.1;
                printf("up arrow pressed\n");
        break;
        case 102:
                translatex+=0.1;
                printf("right arrow pressed\n");
        break;
        case 103:
                translatey-=0.1;
                printf("down arrow pressed\n");
        break;
    }
 
    glutPostRedisplay(); // refresh
}

void init (){
    glMatrixMode(GL_PROJECTION);                                                                                                // select projection matrix
    glViewport(0, 0, win.width, win.height); // set the viewport
    glMatrixMode(GL_PROJECTION);                                                                                                // set matrix mode
    glLoadIdentity();                                                                                                                   // reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far); // set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);                                                                                                 // specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
}
 
int main(int argc, char **argv){
    // set window size, geometry
    win.width = 640;
    win.height = 480;
    win.title = "Assignment 1";
    win.field_of_view_angle = 45;
    win.z_near = 1.0f;
    win.z_far = 500.0f;

    // initialize and run program
    glutInit(&argc, argv);                                      // GLUT initialization
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // display mode
    glutInitWindowSize(win.width,win.height);                   // set window size
    glutCreateWindow(win.title);                                // create window
    glutDisplayFunc(display);                                   // register display function
    init();
    glutDisplayFunc (display);// Send graphics to display window.
    glutSpecialFunc(specialfunc);// Special Key pressed
    glutKeyboardFunc(keyboardfunc);// Other key pressed
    glutMainLoop();  // run GLUT mainloop
    return 0;
}
