#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT.h>

#define ROT(x, y, costheta, sintheta) x*costheta - y*sintheta, x*sintheta + y*costheta
GLfloat rotatedegree=0;

//Code written by Dr. Jeong - Professor of Computer Science at the University of the District of Columbia (UDC)
class CVector{
public:
	CVector(){x=y=z=0;};
	CVector(float x, float y, float z){this->x=x;this->y=y;this->z=z;};
	CVector operator+(const CVector& rhs){
		double r_x, r_y, r_z;
		r_x = this->x + rhs.x;
		r_y = this->y + rhs.y;
		r_z = this->z + rhs.z;
		return CVector(r_x, r_y, r_z);
	};
	CVector operator=(const CVector& rhs)
	{
		x = rhs.x; y=rhs.y; z=rhs.z;
		return *this;
	};
	CVector CrossProduct(CVector rhs) {
	  return CVector( y * rhs.z - z * rhs.y,
                 z * rhs.x - x * rhs.z,
                 x * rhs.y - y * rhs.x);
	};
	CVector operator*(float constant){
		return CVector(x*constant, y*constant, z*constant);
	};

	CVector vector_scale(float constant, CVector v) {
	  return CVector(constant*v.x, constant*v.y, constant*v.z);
	}

	float Size() {
	  return sqrt(x*x + y*y + z*z);
	};

	CVector Norm(){
	  return *this*(1/this->Size());
	}
	float DotProduct(CVector rhs) {
		return (x*rhs.x + y*rhs.y + z*rhs.z);
	};

public:
	float x, y, z;
};


class CQuaternion{
public:
	CQuaternion(){s=x=y=z=0;};
	CQuaternion(float s, float x, float y, float z){this->s=s;this->x=x;this->y=y;this->z=z;};
	CQuaternion operator*(const CQuaternion& rhs){
		double r_s, r_x, r_y, r_z;
		r_s = this->s*rhs.s - this->x*rhs.x - this->y*rhs.y - this->z*rhs.z;
		r_x = this->s*rhs.x + this->x*rhs.s + this->y*rhs.z - this->z*rhs.y;
		r_y = this->s*rhs.y - this->x*rhs.z + this->y*rhs.s + this->z*rhs.x;
		r_z = this->s*rhs.z + this->x*rhs.y - this->y*rhs.x + this->z*rhs.s;
		return CQuaternion(r_s, r_x, r_y, r_z);
	};
	CQuaternion Conjugate(){
	 return CQuaternion(s, -x, -y, -z);
	};

public:
	float s, x, y, z;
};


CQuaternion CreateQuaternionWithThetha(CVector axis, float angle) {
  return CQuaternion(cos(angle/2.0),
                      axis.x*sin(angle/2.0),
                      axis.y*sin(angle/2.0),
                      axis.z*sin(angle/2.0));
}

CVector QuaternionRotation(CQuaternion q, CVector v) {
  CQuaternion vq;
  
  vq = CQuaternion(0, v.x, v.y, v.z);
  vq = q * vq;
  vq = vq * q.Conjugate();
  return CVector(vq.x, vq.y, vq.z);
}

void QuaternionRotationMatrix(CQuaternion q, GLfloat * m) {
  CVector x,   y,   z;
  CVector x_t, y_t, z_t;
  
  x = CVector(1, 0, 0);
  y = CVector(0, 1, 0);
  z = CVector(0, 0, 1);
  
  x_t = QuaternionRotation(q, x);
  y_t = QuaternionRotation(q, y);
  z_t = QuaternionRotation(q, z);

  m[ 0] = x_t.x;
  m[ 1] = x_t.y;
  m[ 2] = x_t.z;
  m[ 3] = 0;
  m[ 4] = x.DotProduct(y_t);
  m[ 5] = y.DotProduct(y_t);
  m[ 6] = z.DotProduct(y_t);
  m[ 7] = 0;
  
  m[ 8] = x.DotProduct(z_t);
  m[ 9] = y.DotProduct(z_t);
  m[10] = z.DotProduct(z_t);
  m[11] = 0;

  m[12] = 0;
  m[13] = 0;
  m[14] = 0;
  m[15] = 1;
}

CVector downwards = CVector(0, 0, 1);
CVector ball_position = CVector(0, 0, 0);
CQuaternion ball_orientation = CQuaternion(0,1, 0, 0);
//End Dr. Jeong Code

//Begin Claude C Code
void display() {
  GLfloat rotation[16];
  float d;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glLoadIdentity();
  glTranslatef(0, 0, -20);
  
  //creating spheres with quaternion implemented
  glPushMatrix(); 
  glScalef(2,2,2);
  QuaternionRotationMatrix(ball_orientation, rotation);
  glMultMatrixf(rotation);
  glColor3f(1, 0, 0);
  glutSolidSphere(2,15,15);   // red sphere
	glPopMatrix();

	glPushMatrix(); 
  glRotatef (rotatedegree, 0,1,0);
  glScalef(.6,.6,.6);
  glTranslatef(7,0,7);

  glMultMatrixf(rotation);
  glColor3f(0, 0, 1);

	glutSolidSphere(1,15,15);		 //blue sphere
	glPopMatrix();
  glutSwapBuffers();
}

//For continuous rotation
void timer(int ignored) {
	rotatedegree+=5;

	if(rotatedegree>360)    //360 rotation
		rotatedegree-=360;

	glutPostRedisplay();
	glutTimerFunc(40,timer,0);  // (msec , function callback, int value to pass to the timer)
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Quaternion Rotation");
  
  ///////////////////////////
  glViewport(0, 0, 640, 480);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 640.0/480.0, 5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  
  glClearColor(0, 0, 0, 1);
  ///////////////////////////
  
  glutDisplayFunc(display);
  glutTimerFunc (40, timer,0);  
  glutMainLoop();
  
  return EXIT_SUCCESS;
}
//End Claude C
