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

int dx[]={-1,0,1};
int dy[]={-1,0,1};
/* GLUT callback Handlers */





std::set< std::pair<int,int> > points;

void fill(int x, int y){

    auto it = points.find({x,y});

    if(it!=points.end()){
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
        glVertex3f(x,y,0);
        glEnd();

        points.erase(it);

    }
    else return;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
    {
        int nx = x+dx[i];
        int ny = y + dy[j];

        if(x== nx && y==ny)
            continue;

        fill(nx,ny);

    }
}



void floodFill(){

glColor3f(1,1,1);
glBegin(GL_POINTS);
for(int i=1; i<=5; i++)
for(int j=1; j<=10; j++){
     glVertex3f(i,i+j,0);
     points.insert({i,i+j});
}
glEnd();

fill(2,3);
}


struct Edge{

    double ymin;
    double ymax;
    double x;
    double inverse_m;

};

bool operator<(const Edge &a, const Edge &b){
    return a.ymin < b.ymin;
}

std::vector< std::pair<int,int>> polygon=
    {{0, 0}, {-4, 2}, {-2, 6}, {1, 3}, {4, 4}, {6, 2}, {6, 0}};

std::multiset<Edge> edges;


void scanLine(){

    int ymin=100;
    int ymax=-100;

    for(auto & v:polygon)
    {
        ymin = std::min(v.second,ymin);
        ymax = std::max(v.second,ymax);
    }

    glColor3f(1,1,0);
    glBegin(GL_LINES);
    for(int i=0;i<polygon.size();i++){

        int j = (i+1)%polygon.size();

        glVertex3f(polygon[i].first,polygon[i].second,0);
        glVertex3f(polygon[j].first,polygon[j].second,0);

    }

    glEnd();


    for(int i=0;i<polygon.size();i++){

        int j = (i+1)%polygon.size();

        int x=polygon[i].first;
        int y=polygon[i].second;

        int x1=polygon[j].first;
        int y1=polygon[j].second;

        Edge e;

        e.ymin = std::min(y,y1);
        e.ymax = std::max(y,y1);

        double ddx = x1-x;
        int ddy = y1-y;



        if(ddy){
            e.inverse_m = ddx/ddy;

            if(e.ymin == y)
                e.x = x;
            else
                e.x = x1;

            edges.insert(e);
            printf("Edge: %f %f %f %f\n",e.ymin,e.ymax,e.x,e.inverse_m);
        }

    }



    //scanline
    double delx=1;
    double dely=01;

    for(double nowy = ymin;nowy<=ymax; nowy+=dely){

        std::vector<Edge> tmpList;

        glColor3f(1,0,0);
        glBegin(GL_LINES);

        puts("ssd");
        for(auto it = edges.begin();it!=edges.end();){

            if(it->ymin==nowy){

                double inter_sect_x= it->x;
                double inter_sect_y = it->ymin;

                puts("sd");
                glVertex3f(inter_sect_x,inter_sect_y,0);

                Edge  e = *it;

                e.ymin+=dely;
                e.x += e.inverse_m;

                auto tmp = it;

                it++;
                edges.erase(tmp);



                if(e.ymin!=e.ymax)
                    tmpList.push_back(e);

            }
            else it++;
        }
        glEnd();

        for(auto x: tmpList)
            edges.insert(x);
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


    floodFill();
    //scanLine();






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
