//
//  main.cpp
//  assignment4
//
//  Created by Mavilla Jyothi on 5/06/19.
//  Copyright © 2019 Mavilla Jyothi. All rights reserved.
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include<vector>
#include <functional>
#include<Math.h>
#include <GLUT/glut.h>
#include <openGL/glu.h>
#include <openGL/gl.h>

using namespace std;
bool b = true;
string filename;
float ax, ay, az, bx, by, bz, cx, cy, cz;
int on_mouseDown = 0;
int changeMode = 0;
int pX = 0, pY = 0;
float mX, mY, mZ;
float m1, m2, m3;
int mode = -1;

float cosine1 = 0.0;
float cosine2 = 0.0;
float cosine = 0.0;

struct Vertex {
    float x;
    float y;
    float z;
    Vertex cross(const Vertex& right)
    {
        Vertex res;
        res.x = y*right.z - z*right.y;
        res.y = z*right.x - x*right.z;
        res.z = x*right.y - y*right.x;
        return res;
    }
    const Vertex operator - (const Vertex& right) const
    {
        Vertex res;
        res.x = x - right.x;
        res.y = y - right.y;
        res.z = z - right.z;
        return res;
    }
    const Vertex operator + (const Vertex& right) const
    {
        Vertex res;
        res.x = x + right.x;
        res.y = y + right.y;
        res.z = z + right.z;
        return res;
    }
    const Vertex operator * (const float right) const
    {
        Vertex res;
        res.x = x*right;
        res.y = y*right;
        res.z = z*right;
        return res;
    }
    float dotProduct(const Vertex& right) const
    {
        float r;
        r = x*right.x + y*right.y + z*right.z;
        
        return r;
    }
};
struct Triangle {
    int v1;
    int v2;
    int v3;
};
struct Material {
    float elem[4][4];
    float value[4];
    const Material operator *(const Material& right) const
    {
        Material result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.elem[i][j] = elem[i][0] * right.elem[0][j] + elem[i][1] * right.elem[1][j] + elem[i][2] * right.elem[2][j] + elem[i][3] * right.elem[3][j];
            }
        }
        return result;
    }
    const Vertex operator *(const Vertex& v) const
    {
        Vertex result;
        Material r;
        for (int i = 0; i < 4; i++)
        {
            r.value[i] = elem[i][0] * v.x + elem[i][1] * v.y + elem[i][2] * v.z + elem[i][3];
        }
        for (int i = 0; i < 3; i++)
        {
            r.value[i] = r.value[i] / r.value[3];
        }
        result.x = r.value[0];
        result.y = r.value[1];
        result.z = r.value[2];
        return result;
    }
};

vector<Vertex> vertexList1, vertexList2;
vector<Triangle> traingleList1, traingleList2;
Vertex Cr, Ca, Cp, Cl;
Vertex l6;
Vertex illuminate;
Vertex n6;
Vertex N1, N2;
Vertex V;
Vertex C;
Vertex R;
Vertex Center;
void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-40, 40, -40 * .48 / .64, 40 * .48 / .64, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
    
    if (b)
    {
        for (int i = 0; i < traingleList1.size(); i++)
        {
            glColor3f(0.9, 0.9, 0.9);
            glBegin(GL_LINE_LOOP);
            glVertex3f(vertexList1[traingleList1[i].v1 - 1].x*70, vertexList1[traingleList1[i].v1 - 1].y*70, vertexList1[traingleList1[i].v1 - 1].z*70); //point 1
            glVertex3f(vertexList1[traingleList1[i].v2 - 1].x*70, vertexList1[traingleList1[i].v2 - 1].y*70, vertexList1[traingleList1[i].v2 - 1].z*70); //point 2
            glVertex3f(vertexList1[traingleList1[i].v3 - 1].x*70, vertexList1[traingleList1[i].v3 - 1].y*70, vertexList1[traingleList1[i].v3 - 1].z*70); //point 3
            glEnd();
        }
    }
    else if (mode == 0){
        for (int i = 0; i < traingleList2.size(); i++)
        {
            glColor3f(Cr.x, Cr.y, Cr.z);
            glBegin(GL_TRIANGLES);
            glVertex3f(vertexList2[traingleList2[i].v1 - 1].x*70, vertexList2[traingleList2[i].v1 - 1].y*70, vertexList2[traingleList2[i].v1 - 1].z*70);
            glVertex3f(vertexList2[traingleList2[i].v2 - 1].x*70, vertexList2[traingleList2[i].v2 - 1].y*70, vertexList2[traingleList2[i].v2 - 1].z*70);
            glVertex3f(vertexList2[traingleList2[i].v3 - 1].x*70, vertexList2[traingleList2[i].v3 - 1].y*70, vertexList2[traingleList2[i].v3 - 1].z*70);
            glEnd();
        }
        for (int i = 0; i < traingleList2.size(); i++)
        {
            glColor3f(0.9, 0.9, 0.9);
            glBegin(GL_LINE_LOOP);
            glVertex3f(vertexList2[traingleList2[i].v1 - 1].x*70, vertexList2[traingleList2[i].v1 - 1].y*70, vertexList2[traingleList2[i].v1 - 1].z*70);
            glVertex3f(vertexList2[traingleList2[i].v2 - 1].x*70, vertexList2[traingleList2[i].v2 - 1].y*70, vertexList2[traingleList2[i].v2 - 1].z*70);
            glVertex3f(vertexList2[traingleList2[i].v3 - 1].x*70, vertexList2[traingleList2[i].v3 - 1].y*70, vertexList2[traingleList2[i].v3 - 1].z*70);
            glEnd();
        }
    }
    else if (mode == 1){
        for (int i = 0; i < traingleList2.size(); i++)
        {
            N1 = vertexList2[traingleList2[i].v2 - 1] - vertexList2[traingleList2[i].v1 - 1];
            N2 = vertexList2[traingleList2[i].v3 - 1] - vertexList2[traingleList2[i].v1 - 1];
            
            float ra = sqrt(N1.x*N1.x + N1.y*N1.y + N1.z*N1.z);
            N1.x = N1.x / ra;
            N1.y = N1.y / ra;
            N1.z = N1.z / ra;
            
            float rb = sqrt(N2.x*N2.x + N2.y*N2.y + N2.z*N2.z);
            N2.x = N2.x / rb;
            N2.y = N2.y / rb;
            N2.z = N2.z / rb;
            n6 = N2.cross(N1);
            
            float rc = sqrt(n6.x*n6.x + n6.y*n6.y + n6.z*n6.z);
            n6.x = n6.x / rc;
            n6.y = n6.y / rc;
            n6.z = n6.z / rc;
            
            Center = vertexList2[traingleList2[i].v2 - 1] + vertexList2[traingleList2[i].v1 - 1] + vertexList2[traingleList2[i].v3 - 1];
            Center.x = Center.x / 3.0;
            Center.y = Center.y / 3.0;
            Center.z = Center.z / 3.0;
            illuminate = Center - l6;
            C = Cr;
            float rd = sqrt(illuminate.x*illuminate.x + illuminate.y*illuminate.y + illuminate.z*illuminate.z);
            illuminate.x = illuminate.x / rd;
            illuminate.y = illuminate.y / rd;
            illuminate.z = illuminate.z / rd;
            
            if (illuminate.dotProduct(n6) > 0)
                cosine = illuminate.dotProduct(n6);
            C.x = Cr.x*Ca.x + Cl.x*Cr.x*cosine;
            C.y = Cr.y*Ca.y + Cl.y*Cr.y*cosine;
            C.z = Cr.z*Ca.z + Cl.z*Cr.z*cosine;
            glColor3f(C.x, C.y, C.z);
            
            glBegin(GL_TRIANGLES);
            glVertex3f(vertexList2[traingleList2[i].v1 - 1].x*70, vertexList2[traingleList2[i].v1 - 1].y*70, vertexList2[traingleList2[i].v1 - 1].z*100);
            glVertex3f(vertexList2[traingleList2[i].v2 - 1].x*70, vertexList2[traingleList2[i].v2 - 1].y*70, vertexList2[traingleList2[i].v2 - 1].z*100);
            glVertex3f(vertexList2[traingleList2[i].v3 - 1].x*70, vertexList2[traingleList2[i].v3 - 1].y*70, vertexList2[traingleList2[i].v3 - 1].z*100);
            glEnd();
        }
    }
    else if (mode == 2){
        for (int i = 0; i < traingleList2.size(); i++)
        {
            V.x = 0;
            V.y = 0;
            V.z = 4;
            N1 = vertexList2[traingleList2[i].v2 - 1] - vertexList2[traingleList2[i].v1 - 1];
            N2 = vertexList2[traingleList2[i].v3 - 1] - vertexList2[traingleList2[i].v1 - 1];
            float r1 = sqrt(N1.x*N1.x + N1.y*N1.y + N1.z*N1.z);
            N1.x = N1.x / r1;
            N1.y = N1.y / r1;
            N1.z = N1.z / r1;
            float r2 = sqrt(N2.x*N2.x + N2.y*N2.y + N2.z*N2.z);
            N2.x = N2.x / r2;
            N2.y = N2.y / r2;
            N2.z = N2.z / r2;
            n6 = N1.cross(N2);
            float r3 = sqrt(n6.x*n6.x + n6.y*n6.y + n6.z*n6.z);
            n6.x = n6.x / r3;
            n6.y = n6.y / r3;
            n6.z = n6.z / r3;
            
            Center = vertexList2[traingleList2[i].v2 - 1] + vertexList2[traingleList2[i].v1 - 1] + vertexList2[traingleList2[i].v3 - 1];
            Center.x = Center.x / 3.0;
            Center.y = Center.y / 3.0;
            Center.z = Center.z / 3.0;
            illuminate = l6 - Center;
            float rl = sqrt(illuminate.x*illuminate.x + illuminate.y*illuminate.y + illuminate.z*illuminate.z);
            illuminate.x = illuminate.x / rl;
            illuminate.y = illuminate.y / rl;
            illuminate.z = illuminate.z / rl;
            C = Cr;
            cosine = n6.dotProduct(illuminate);
            R = n6*cosine * 2 - illuminate;
            if (illuminate.dotProduct(n6) > 0)
                cosine1 = illuminate.dotProduct(n6);
            if (V.dotProduct(R) > 0)
                cosine2 = V.dotProduct(R);
            cosine2 = pow(cosine2, 0.5);
            C.x = Cr.x*Ca.x + Cl.x*Cr.x*cosine1 + Cl.x*Cp.x*cosine2;
            C.y = Cr.y*Ca.y + Cl.y*Cr.y*cosine1 + Cl.y*Cp.y*cosine2;
            C.z = Cr.z*Ca.z + Cl.z*Cr.z*cosine1 + Cl.z*Cp.z*cosine2;
            glColor3f(C.x, C.y, C.z);
            glBegin(GL_TRIANGLES);
            glVertex3f(vertexList2[traingleList2[i].v1 - 1].x*100, vertexList2[traingleList2[i].v1 - 1].y*100, vertexList2[traingleList2[i].v1 - 1].z*100);
            glVertex3f(vertexList2[traingleList2[i].v2 - 1].x*100, vertexList2[traingleList2[i].v2 - 1].y*100, vertexList2[traingleList2[i].v2 - 1].z*100);
            glVertex3f(vertexList2[traingleList2[i].v3 - 1].x*100, vertexList2[traingleList2[i].v3 - 1].y*100, vertexList2[traingleList2[i].v3 - 1].z*100);
            glEnd();
        }
    }
    glFlush();
    glutSwapBuffers();
}
void onMouse(int button, int state, int x, int y)
{
    GLint specialKey = glutGetModifiers();
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                on_mouseDown = 1;
                pX = x;
                pY = y;
                if (specialKey == GLUT_ACTIVE_SHIFT)
                {
                    changeMode = 1;
                }
                else if (specialKey == GLUT_ACTIVE_CTRL)
                {
                    changeMode = 2;
                    mX = 0;
                    mY = 0;
                    mZ = 0;
                    m1 = 0;
                    m2 = 0;
                    m3 = 0;
                    for (int i = 0; i < vertexList1.size(); i++)
                    {
                        mX += vertexList1[i].x;
                        mY += vertexList1[i].y;
                        mZ += vertexList1[i].z;
                    }
                    mX = mX / vertexList1.size();
                    mY = mY / vertexList1.size();
                    mZ = mZ / vertexList1.size();
                    for (int i = 0; i < vertexList2.size(); i++)
                    {
                        m1 += vertexList2[i].x;
                        m2 += vertexList2[i].y;
                        m3 += vertexList2[i].z;
                    }
                    m1 = m1 / vertexList2.size();
                    m2 = m2 / vertexList2.size();
                    m3 = m3 / vertexList2.size();
                }
                else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                {
                    mX = 0;
                    mY = 0;
                    mZ = 0;
                    m1 = 0;
                    m2 = 0;
                    m3 = 0;
                    for (int i = 0; i < vertexList1.size(); i++)
                    {
                        mX += vertexList1[i].x;
                        mY += vertexList1[i].y;
                        mZ += vertexList1[i].z;
                    }
                    mX = mX / vertexList1.size();
                    mY = mY / vertexList1.size();
                    mZ = mZ / vertexList1.size();
                    for (int i = 0; i < vertexList2.size(); i++)
                    {
                        m1 += vertexList2[i].x;
                        m2 += vertexList2[i].y;
                        m3 += vertexList2[i].z;
                    }
                    m1 = m1 / vertexList2.size();
                    m2 = m2 / vertexList2.size();
                    m3 = m3 / vertexList2.size();
                }
                else
                {
                    changeMode = 0;
                }
            }
            else if (state == GLUT_UP)
            {
                on_mouseDown = 0;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                break;
        default:
            break;
    }
}
void onMouseMotion(int x, int y)
{
    if (on_mouseDown == 1)
    {
        if (changeMode == 0)
        {
            Material Rx, Ry;
            Material RXRY;
            float theta;
            theta = (x - pX) / 100.f;
            float thetay = (y - pY) / 100.f;
            float elemy[4][4] = { { cos(theta), 0, sin(theta), 0 }, { 0, 1, 0, 0 }, { -sin(theta), 0, cos(theta), 0 }, { 0, 0, 0, 1 } };
            float elemx[4][4] = { { 1, 0, 0, 0 }, { 0, cos(thetay), -sin(thetay), 0 }, { 0, sin(thetay), cos(thetay), 0 }, { 0, 0, 0, 1 } };
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    Rx.elem[i][j] = elemy[i][j];
                    Ry.elem[i][j] = elemx[i][j];
                }
            }
            RXRY = Rx*Ry;
            if (b)
            {
                for (int i = 0; i < vertexList1.size(); i++)
                {
                    vertexList1[i] = RXRY*vertexList1[i];
                }
            }
            else
            {
                for (int i = 0; i < vertexList2.size(); i++)
                {
                    vertexList2[i] = RXRY*vertexList2[i];
                }
            }
            
        }
        else if (changeMode == 1)
        {
            Material Tx;
            float pos1, pos2;
            pos1 = 1.0*(x - pX) / 400.f;
            pos2 = 1.0*(y - pY) / 400.f;
            float trans1[4][4] = { { 1, 0, 0, pos1 }, { 0, 1, 0, -pos2 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    Tx.elem[i][j] = trans1[i][j];
                    
                }
            }
            if (b)
            {
                for (int i = 0; i < vertexList1.size(); i++)
                {
                    vertexList1[i] = Tx*vertexList1[i];
                }
            }
            else
            {
                for (int i = 0; i < vertexList2.size(); i++)
                {
                    vertexList2[i] = Tx*vertexList2[i];
                }
            }
        }
        else
        {
            Material T1, T2;
            Material Ry, Rx;
            Material P;
            float theta;
            theta = (x - pX) / 100.f;
            float thetax = (y - pY) / 100.f;
            float elemy[4][4] = { { cos(theta), 0, sin(theta), 0 }, { 0, 1, 0, 0 }, { -sin(theta), 0, cos(theta), 0 }, { 0, 0, 0, 1 } };
            float elemx[4][4] = { { 1, 0, 0, 0 }, { 0, cos(thetax), -sin(thetax), 0 }, { 0, sin(thetax), cos(thetax), 0 }, { 0, 0, 0, 1 } };
            float trans1[4][4] = { { 1, 0, 0, mX }, { 0, 1, 0, mY }, { 0, 0, 1, mZ }, { 0, 0, 0, 1 } };
            float trans2[4][4] = { { 1, 0, 0, -mX }, { 0, 1, 0, -mY }, { 0, 0, 1, -mZ }, { 0, 0, 0, 1 } };
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    T1.elem[i][j] = trans1[i][j];
                    T2.elem[i][j] = trans2[i][j];
                    Ry.elem[i][j] = elemy[i][j];
                    Rx.elem[i][j] = elemx[i][j];
                }
            }
            P = T1*(Rx*Ry)*T2;
            if (b)
            {
                for (int i = 0; i < vertexList1.size(); i++)
                {
                    vertexList1[i] = P*vertexList1[i];
                }
                
            }
            else
            {
                T1.elem[0][3] = m1;
                T1.elem[1][3] = m2;
                T1.elem[2][3] = m3;
                T2.elem[0][3] = -m1;
                T2.elem[1][3] = -m2;
                T2.elem[2][3] = -m3;
                P = T1*(Rx*Ry)*T2;
                for (int i = 0; i < vertexList2.size(); i++)
                {
                    vertexList2[i] = P*vertexList2[i];
                }
            }
        }
        pX = x;
        pY = y;
    }
    glutPostRedisplay();
}
void onKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(1);
            break;
        case 'm':
            b = !b;
            glutPostRedisplay();
            break;
        case'M':
            b = !b;
            glutPostRedisplay();
            break;
        case '0':
            mode = 0;
            b = false;
            glutPostRedisplay();
            break;
        case '1':
            mode = 1;
            b = false;
            glutPostRedisplay();
            break;
        case '2':
            mode = 2;
            b = false;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 800);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("3D Bunny");
    glViewport(0, 0, 800, 800);
    mX = 0.0;
    mY = 0.0;
    mZ = 0.0;
    m1 = 0.0;
    m2 = 0.0;
    m3 = 0.0;
    Cr.x = 0.72;
    Cr.y = 0.72;
    Cr.z = 0.72;
    Ca.x = 0.7;
    Ca.y = 0.7;
    Ca.z = 0.2;
    Cl.x = 0.7;
    Cl.y = 0.7;
    Cl.z = 0.7;
    Cp.x = 0.21;
    Cp.y = 0.7;
    Cp.z = 0.2;
    filename = "bunny_high.obj.txt";
    ifstream file;
    file.open(filename);
    char c;
    float f1, f2, f3;
    while (!file.eof())
    {
        file >> c >> f1 >> f2 >> f3;
        if (c == 'v')
        {
            Vertex vertex;
            vertex.x = f1;
            vertex.y = f2;
            vertex.z = f3;
            mX += f1;
            mY += f2;
            mZ += f3;
            m1 += f1;
            m2 += f2;
            m3 += f3;
            vertexList1.push_back(vertex);
            vertexList2.push_back(vertex);
        }
        else if (c == 'f')
        {
            Triangle triangle;
            triangle.v1 = f1;
            triangle.v2 = f2;
            triangle.v3 = f3;
            traingleList1.push_back(triangle);
            traingleList2.push_back(triangle);
        }
        else
        {
            exit(-1);
        }
    }
    mX = mX / vertexList1.size();
    mY = mY / vertexList1.size();
    mZ = mZ / vertexList1.size();
    m1 = m1 / vertexList2.size();
    m2 = m2 / vertexList2.size();
    m3 = m3 / vertexList2.size();
    l6.x = 0;    l6.y = 0;    l6.z = 5;
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-40, 40, -40 * .48 / .64, 40 * .48 / .64, -100, 100);
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
    
    glutDisplayFunc(onDisplay);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMouseMotion);
    glutKeyboardFunc(onKeyboard);
    
    glutMainLoop();
    return 0;
}
