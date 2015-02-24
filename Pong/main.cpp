//
//  main.cpp
//  Pong
//
//  Created by Roberto Mtz on 2/23/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>

double posIzq=0, posDer=0;//posicion x de raquetas
double xBola=0, yBola=2.8;//posicion pelota
double cambioX=-0.1, cambioY=-0.1;//traslacion pelota

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);//sombreado plano GL_SMOOTH
    gluOrtho2D(-500,500, -500,500);
}


void mySpecialKey(int key, int x, int y){
    switch (key)
    {
        case GLUT_KEY_UP:
            posDer<=2.5 ? posDer+=.1 : posDer-=.1;
            break;
        
        case GLUT_KEY_DOWN:
            posDer>=-2.5 ? posDer-=.1 : posDer+=.1;
            break;
            
        default:
            break;		      // do nothing
    }
    //std::cout<<posDer<<std::endl;
    glutPostRedisplay();
}

void myKey(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
        case 'w':
        case 'W':
            posIzq<=2.5 ? posIzq+=.2 : posIzq-=.2;
            break;
            
        case 's':
        case 'S':
            posIzq>=-2.5 ? posIzq-=.2 : posIzq+=.2;
            break;
            
        default:
            break;		      // do nothing
    }
    glutPostRedisplay();
}

void timer (int v)
{
    if (xBola<-2.8 || xBola>2.8) {
        cambioX=-cambioX;
    }
    
    if (yBola<-2.8 || yBola>2.8) {
        cambioY=-cambioY;
    }
    
    yBola+=cambioY;
    xBola+=cambioX;
    glutPostRedisplay();
    glutTimerFunc(50,timer,1);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 1.0, 1.0);
    
    glPushMatrix();
    glTranslatef(-3,posIzq,0);
    glScaled(.2, 2, .2);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3,posDer ,0);
    glScaled(.2, 2, .2);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(xBola,yBola ,0);
    glutSolidSphere(.14,16,16);
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecialKey);
    glutTimerFunc(100, timer, 1);
    glutMainLoop();
    return 0;
}
