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
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
int dx=0,dy=0,dz=0;
double dtheta=0;
bool is_task1 = true;

class Matrix{

    vector<vector<double>> mat;

public:
    Matrix(){}
    Matrix(const Matrix& other){
        mat = other.mat;
    }
    Matrix& operator=(const Matrix& other){
        if(this!=&other){
            this->mat = other.mat;
        }
        return *this;
    }

    addRow(const vector<double>& r){
        mat.push_back(r);
    }

    Matrix operator -(const Matrix &other){
            Matrix res(*this);
            for(int i=0;i<mat.size();i++)
                for(int j=0;j<mat[0].size();j++)
                    res.mat[i][j] -= other.mat[j][i];

            return res;
    }


    Matrix operator +(const Matrix &other){
            Matrix res(*this);
            for(int i=0;i<mat.size();i++)
                for(int j=0;j<mat[0].size();j++)
                    res.mat[i][j] += other.mat[j][i];

        return res;
    }


   Matrix operator *(const Matrix &other){
            Matrix res;

            vector<double> row(other[0].size(),0);
            for(int i=0;i<mat.size();i++)
                res.addRow(row);

            for(int i=0;i<mat.size();i++)
                for(int j=0;j<other[0].size();j++)
                    for(int k=0;k<mat[0].size();k++)
                        res.mat[i][j]+=mat[i][k]*other.mat[k][j];

            return res;
    }

    vector<double>& operator[](int i){
        return mat[i];
    }

    void print(){

        puts("---------------------");
        for(auto&x :mat){
            for(auto &c:x){
                printf("%.2f ",c);
            }
            puts("");
        }


        puts("---------------------");
    }
};




void task1(){

    is_task1 =true;
    //Trapezoid
    pair<double,double> p1{4+dx,10+dy};

    pair<double,double> p2{1+dx,7+dy};
    pair<double,double> p3{7+dx,7+dy};




    //translate
    Matrix cords;

    cords.addRow({p1.first,p2.first,p3.first});
    cords.addRow({p1.second,p2.second,p3.second});
    cords.addRow({1,1,1});

    Matrix trans;
    trans.addRow({1,0,-p1.first});
    trans.addRow({0,1,-p1.second});
    trans.addRow({0,0,0});

    Matrix rota;
    rota.addRow({cos(dtheta),-sin(dtheta),0});
    rota.addRow({sin(dtheta),cos(dtheta),0});
    rota.addRow({0,0,1});


    Matrix trans2;
    trans2.addRow({1,0,p1.first});
    trans2.addRow({0,1,p1.second});
    trans2.addRow({0,0,0});




    cords = (trans*cords);
    cords = (rota*cords);
    cords[2]={1,1,1};
    cords = (trans2*cords);

    //cords.print();




    glBegin(GL_TRIANGLES);

    glVertex3f(cords[0][0], cords[1][0], 0.0f);
    glVertex3f(cords[0][1], cords[1][1], 0.0f);
    glVertex3f(cords[0][2], cords[1][2], 0.0f);



    glEnd(); //End quadrilateral coordinates


}

void task2(){
    //Trapezoid

    is_task1 =false;

    pair<double,double> m_cent = {(4+1+7)/3.00, (10+7+7)/3.00};

    pair<double,double> p1{4+dx,10+dy};

    pair<double,double> p2{1+dx,7+dy};
    pair<double,double> p3{7+dx,7+dy};


    pair<double,double> n_cent = {(p1.first+p2.first+p3.first)/3.00, (p1.second+p2.second+p3.second)/3.00};


    double d1 = sqrt(m_cent.first*m_cent.first + m_cent.second*m_cent.second);
    double d2 = sqrt(n_cent.first*n_cent.first + n_cent.second*n_cent.second);

    double sc= d2/d1;

    //translate
    Matrix cords;

    cords.addRow({p1.first,p2.first,p3.first});
    cords.addRow({p1.second,p2.second,p3.second});
    cords.addRow({1,1,1});

    Matrix trans;
    trans.addRow({1,0,-n_cent.first});
    trans.addRow({0,1,-n_cent.second});
    trans.addRow({0,0,0});




    Matrix scale_mat;
    scale_mat.addRow({sc,0,0});
    scale_mat.addRow({0,sc,0});
    scale_mat.addRow({0,0,sc});


    Matrix trans2;
    trans2.addRow({1,0,n_cent.first});
    trans2.addRow({0,1,n_cent.second});
    trans2.addRow({0,0,0});




    cords = (scale_mat*(trans*cords));
    cords[2]={1,1,1};
    cords = (trans2*cords);

    //cords.print();




    glBegin(GL_TRIANGLES);

    glVertex3f(cords[0][0], cords[1][0], 0.0f);
    glVertex3f(cords[0][1], cords[1][1], 0.0f);
    glVertex3f(cords[0][2], cords[1][2], 0.0f);



    glEnd(); //End quadrilateral coordinates



}

void task3(){


    is_task1 =true;

    pair<double,double> m_cent = {(4+1+7)/3.00, (10+7+7)/3.00};

    pair<double,double> p1{4+dx,10+dy};

    pair<double,double> p2{1+dx,7+dy};
    pair<double,double> p3{7+dx,7+dy};


    pair<double,double> n_cent = {(p1.first+p2.first+p3.first)/3.00, (p1.second+p2.second+p3.second)/3.00};


    double d1 = sqrt(m_cent.first*m_cent.first + m_cent.second*m_cent.second);
    double d2 = sqrt(n_cent.first*n_cent.first + n_cent.second*n_cent.second);

    double sc= (dtheta+2*acos(-1))/(2*acos(-1)) ;


    //translate
    Matrix cords;

    cords.addRow({p1.first,p2.first,p3.first});
    cords.addRow({p1.second,p2.second,p3.second});
    cords.addRow({1,1,1});

    Matrix trans;
    trans.addRow({1,0,-n_cent.first});
    trans.addRow({0,1,-n_cent.second});
    trans.addRow({0,0,0});

    Matrix rota;
    rota.addRow({cos(dtheta),-sin(dtheta),0});
    rota.addRow({sin(dtheta),cos(dtheta),0});
    rota.addRow({0,0,1});


    Matrix scale_mat;
    scale_mat.addRow({sc,0,0});
    scale_mat.addRow({0,sc,0});
    scale_mat.addRow({0,0,sc});


    Matrix trans2;
    trans2.addRow({1,0,n_cent.first});
    trans2.addRow({0,1,n_cent.second});
    trans2.addRow({0,0,0});




    cords = rota*(scale_mat*(trans*cords));
    cords[2]={1,1,1};
    cords = (trans2*cords);

    //cords.print();




    glBegin(GL_TRIANGLES);

    glVertex3f(cords[0][0], cords[1][0], 0.0f);
    glVertex3f(cords[0][1], cords[1][1], 0.0f);
    glVertex3f(cords[0][2], cords[1][2], 0.0f);



    glEnd(); //End quadrilateral coordinates


}
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);


  glColor3f (1.0,0, 1.0);

    glBegin(GL_LINES);

        glVertex3f(-80,0,0);
        glVertex3f(80,0,0);

        glVertex3f(0,-80,0);
        glVertex3f(0,80,0);


    glEnd();

    glColor3f (1.0, 1.0, 1.0);


    task2();


    glFlush ();
    glutPostRedisplay();
    glutSwapBuffers();
}

void key(int key,int x,int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(is_task1)
            dtheta+=(acos(-1)/180.00);
            else
                dy++;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:

            if(is_task1)
            dtheta-=(acos(-1)/180.00);
            else
                dy--;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            dx++;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            dx--;
            glutPostRedisplay();
            break;
    }
}

/* Program entry point */

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-80.0, 80, -80, 80, -10.0, 10.0);

}

int main(int argc, char *argv[])
{

 /*   Matrix a;
    a.addRow({1,2});
    a.addRow({2,-1});

    Matrix b(a);

    Matrix c = a*b;


    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
    {

        printf("%f \n",c[i][j]);
    }

*/
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Demo");
    init ();
    glutDisplayFunc(display);
    glutSpecialFunc(key);
    glutMainLoop();
    return 0;
}

