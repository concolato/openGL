#include <stdio.h> // For debugging 
#include <stdlib.h>
#include <math.h> // Calculations to use later, not in this assignment
//Open GL includes
#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
// To Compile
//sudo g++ -L/usr/lib lineGraph.cpp -lglut -lGL -lGLU -o lineGraph

GLsizei winWidth = 600, winHeight = 500;    // Initial display window size.
GLint xRaster = 25, yRaster = 150;          // Initialize raster position. 

GLubyte label [36] = {'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r', 
                      'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n', 
                      'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p', 
                      'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c'}; 
// Actual data values
GLint dataValue [12] = {420, 342, 324, 310, 262, 185, 
                        190, 196, 217, 240, 312, 438};
// Text for data values
GLubyte dataLable [36] = {'4','2','0',  '3','4','2',   '3','2','4',    
                         '3','1','0',   '2','6','2',   '1','8','5',   
                         '1','9','0',   '1','9','6',   '2','1','7',  
                         '2','4','0',   '3','1','2',   '4','3','8' };
GLint month, k;
GLint x = 30; // Initialize x position for chart.

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);    // White display window.
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void lineAxis (void)
{
    int yline [] = {20, 165};           // Position at a relative 0,0 point
    int yline2 [] = {20, 480};

    int xline [] = {20, 165};
    int xline2 [] = {600, 165};

    glColor3f (0.0, 0.0, 0.0);           //  Set y line color to black.
    glBegin (GL_LINES); 
            glVertex2iv(yline);
            glVertex2iv(yline2);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);           //  Set x line color to black.     
    glBegin (GL_LINES); 
            glVertex2iv(xline);
            glVertex2iv(xline2);
    glEnd();
}

void dataLine(void)
{
    //  Plot data as asterisk polymarkers.
    glColor3f (1.0, 0.0, 0.0);          //  Set marker color to red.
    for (k = 0; k < 12; k++) {           
        glRasterPos2i (xRaster + k*50, dataValue [k] - 4);
        glutBitmapCharacter (GLUT_BITMAP_9_BY_15, '*');
    }

        //Enable line styling for dashed data line
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);

           //  Clear display window.
    glColor3f (0.0, 0.0, 1.0);           //  Set line color to blue.
    glBegin (GL_LINE_STRIP);             //  Plot data as a polyline.
        for (k = 0; k < 12; k++){
            glVertex2i (x + k*50, dataValue [k]);
        }
    glEnd ();

    glDisable(GL_LINE_STIPPLE); 
}

void yearlyDataChart(void)
{
    glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
    xRaster = 20;                       //  Display chart labels.
    for (month = 0; month < 12; month++) {
        glRasterPos2i (xRaster, yRaster);

        for (k = 3*month; k < 3*month + 3; k++) 
          glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label [k]);
        
        xRaster += 50;
    }

    // Insert Text for Data
    glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
    xRaster = 20;                       //  Display data labels.
    for (month = 0; month < 12; month++) {
        glRasterPos2i (xRaster +5, dataValue [month] +5);

        for (k = 3*month; k < 3*month + 3; k++) 
          glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, dataLable [k]);
        
        xRaster += 50;
    }
}

void lineGraph (void)
{  
    //glClear (GL_COLOR_BUFFER_BIT); //Why does this hide the red asterisks on Ubuntu 13.01?
    dataLine();
    //Draw x and y axises.
    lineAxis();  
    yearlyDataChart();
    
    glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));

    glClear (GL_COLOR_BUFFER_BIT);   
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Line Chart Data Plot");

    init ( );  

    glutDisplayFunc (lineGraph);
    glutReshapeFunc (winReshapeFcn);

    glutMainLoop ( );
}