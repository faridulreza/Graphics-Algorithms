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
#include <set>
#include <vector>
#include <queue>

static int slices = 16;
static int stacks = 16;

double wxmin,wymin,wxmax,wymax;

class Line{

    int c1;
    int c2;
    double dx;
    double dy;
    std::pair<double,double> p1;
    std::pair<double,double> p2;

    void update_code(){
        c1 = 0;
        c2 = 0;

        if(p1.second - wymax>0)
            c1 = c1 | 8;

        if(wymin-p1.second>0)
            c1 = c1 | 4;

        if(p1.first-wxmax>0)
            c1 = c1 | 2;

        if(wxmin-p1.first>0)
            c1 = c1|1;


        if(p2.second - wymax>0)
            c2 = c2 | 8;

        if(wymin-p2.second>0)
            c2 = c2 | 4;

        if(p2.first-wxmax>0)
            c2 = c2 | 2;

        if(wxmin-p2.first>0)
            c2 = c2|1;


    }
public:

    Line(double x1, double y1, double x2, double y2){
        p1.first = x1;
        p1.second = y1;

        p2.first = x2;
        p2.second = y2;

        dx= x1-x2;
        dy= y1-y2;

        update_code();
    }

    int AND(){
        return c1&c2;
    }

    bool onezero(){
        return c1==0 || c2==0;
    }

    int p1check(int i){
        return c1 & (1<<i);
    }
    int p2check(int i){
        return c2& (1<<i);
    }

    void updatep1x(double x){

        if(dx)
            p1.second = p1.second + (x-p1.first)*dy/dx;

        p1.first = x;

        update_code();
    }
    void updatep2x(double x){

        if(dx)
            p2.second = p2.second + (x-p2.first)*dy/dx;

        p2.first = x;

        update_code();
    }

    void updatep1y(double y){
        if(dy)
            p1.first = p1.first + (y-p1.second)*dx/dy;
        p1.second = y;

        update_code();
    }

    void updatep2y(double y){
         if(dy)
            p2.first = p2.first + (y-p2.second)*dx/dy;
        p2.second = y;

        update_code();
    }

    void draw(){
        glVertex3f(p1.first,p1.second,0);
        glVertex3f(p2.first,p2.second,0);
    }
};


std::vector<Line> lines;

void cohen_sutherland(){

    while(true){

        //remove the invisible
        for(int i =0;i<lines.size();i++){
            if(lines[i].AND())
            {
                lines.erase(lines.begin()+i);
                i--;
            }
        }

        bool clipped= false;

        for(Line &l:lines){

            for(int i=0;i<=3;i++){
                if(l.p1check(i)){
                    if(i==0)
                        l.updatep1x(wxmin);
                    else if(i==1)
                        l.updatep1x(wxmax);
                    else if(i==2)
                        l.updatep1y(wymin);
                    else
                        l.updatep1y(wymax);
                    clipped = true;
                }
                if(l.p2check(i)){
                    if(i==0)
                        l.updatep2x(wxmin);
                    else if(i==1)
                        l.updatep2x(wxmax);
                    else if(i==2)
                        l.updatep2y(wymin);
                    else
                        l.updatep2y(wymax);

                    clipped = true;
                }
            }
        }


        if(!clipped)
            break;
    }
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

    glColor3f(1,0,1);
    glBegin(GL_LINES);
    glVertex3d(wxmin, wymin,0);
    glVertex3d(wxmax, wymin,0);


    glVertex3d(wxmin, wymin,0);
    glVertex3d(wxmin, wymax,0);

    glVertex3d(wxmax, wymax,0);
    glVertex3d(wxmin, wymax,0);

    glVertex3d(wxmax, wymax,0);
    glVertex3d(wxmax, wymin,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    for(Line &l:lines){
        l.draw();
    }
    glEnd();

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

    //freopen("in.txt","r", stdin);
    double x,y, x1,y1;
    scanf("%lf %lf", &x, &y);

    wxmin = wxmax = x;
    wymin = wymin = y;

    for(int i=0;i<3;i++){
        scanf("%lf %lf", &x, &y);
        wxmin = std::min(wxmin,x);
        wxmax = std::max(wxmax,x);

        wymin = std::min(wymin,y);
        wymax = std::max(wymax,y);
    }

    int n;

    scanf("%d", &n);
    printf("%d\n",n);

    for(int i=0;i<n;i++){

        scanf("%lf %lf %lf %lf", &x,&y,&x1,&y1);
        lines.emplace_back(x,y,x1,y1);
    }

    cohen_sutherland();

    //freopen("out.txt","w+",stdout);
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

