/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<math.h>
#include <stdio.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */



void plotDDA(){

const double mult = 1;
double x1 = 2*mult;
double yy1 =6*mult;

double x2 = 6*mult;
double yy2 =13*mult;



double dx = (x2-x1);
double dy = (yy2-yy1);


        glBegin(GL_POINTS); //Begin quadrilateral coordinates
            double delY = .01;
            double mDDA = dy/dx;
            double xi = x1;
            for(double y =yy1;y<=yy2;y+=delY){
                glVertex3f(x1,y,0);
                 printf("(%.3lf %.3lf)\n",x1,y);
                x1 += delY/mDDA;
            }

        glEnd();
}
double BrasenHam(){

    double factor = 1<<5;
    int px1 = 6*factor;
    int py1 = 2*factor;

    int px2 = 13*factor;
    int py2 = 6*factor;

    int BHdy =  py2 - py1;
    int BHdx =  px2 - px1;


    int di = (BHdy<<1) - BHdx;
    glColor3f (1, 1, 1);

    glVertex3f(py1/factor,px1/factor,0);
    printf("(%.3lf %.3lf\n)\n",py1/factor,px1/factor);


    glBegin(GL_POINTS);
    while(px1<=px2){

        if(di>=0){
            di+= (BHdy - BHdx)<<1;
            py1++;
        }
        else{
            di+= BHdy<<1;
        }
        px1++;

        printf("(%.3lf %.3lf)\n",py1/factor,px1/factor);
        glVertex3f(py1/factor,px1/factor,0);
    }

    glEnd();

}


void putEllipsePoint(double x, double y){
    int h = 7, k = 5;
    glVertex3f(y+h,-x+k,0);

}

void plotElipse(){

double scale = 1<<5;
int h = 0, k = 0;

int or_a = 5, or_b = 7;

int a = or_b*scale, b = or_a*scale;

int x=0 , y =b;

int aa = a*a, bb= b*b, aa2= aa*2, bb2 = bb*2;

int fx = 0, fy = aa2*b;
int p = bb-aa*b+0.25*aa;

glBegin(GL_POINTS);

while(fx<fy){
    double px= x/scale;
    double py= y/scale;

    putEllipsePoint(px,py);
    putEllipsePoint(px,-py);
    putEllipsePoint(-px,py);
    putEllipsePoint(-px,-py);
    x++;
    fx +=bb2;

    if(p<0)
        p+=fx+bb;
    else {
        y--;
        fy -=aa2;
        p+= fx+bb-fy;
    }
}

putEllipsePoint(x/scale+h, y/scale+k);


p  = bb*(x+.5)*(x+.5)+aa*(y-1)*(y-1)-aa*bb;
while(y>0){
    y--;
    fy -=aa2;

    if(p>=0)
        p = p -fy+aa;
    else{
        x++;
        fx+= bb2;
        p = p+fx-fy-aa;
    }

    double px= x/scale;
    double py= y/scale;


    putEllipsePoint(px,py);
    putEllipsePoint(px,-py);
    putEllipsePoint(-px,py);
    putEllipsePoint(-px,-py);

}


glEnd();


}






static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0,0);




    //plotDDA();
    //BrasenHam();

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3f(-20.0,0,0);
    glVertex3f(20.0,0,0);

    glVertex3f(0,20.0,0);
    glVertex3f(0,-20.0,0);

    glEnd();


    glColor3f (1.0, .1, .1);
    plotElipse();



    glFlush();
}


static void init(){

     glClearColor (0.0, 0.0, 0.0, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 10.0);

}



int main(int argc, char *argv[])
{
    freopen("out.txt","w+",stdout);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);

    glutCreateWindow("GLUT Shapes");


    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
