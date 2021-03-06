//
//  main.cpp
//  Pong
//
//  Created by Roberto Mtz on 2/23/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <sstream>

double posIzq=0, posDer=0;//posicion x de raquetas
double xBola=0, yBola=2.8;//posicion pelota
double cambioX=-0.15, cambioY=-0.13;//traslacion pelota
double golesDer=0, golesIzq=0;

bool pausa=true;
bool inicio=false;

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
            if (!pausa) {
                posDer<=2.5 ? posDer+=.2 : posDer-=.2;
            }
            break;
        
        case GLUT_KEY_DOWN:
            if (!pausa) {
                posDer>=-2.5 ? posDer-=.2 : posDer+=.2;
            }
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
            if (!pausa) {
                posIzq<=2.5 ? posIzq+=.2 : posIzq-=.2;
            }
            break;
            
        case 's':
        case 'S':
            if (!pausa) {
                posIzq>=-2.5 ? posIzq-=.2 : posIzq+=.2;
            }
            break;
            
        case 'p':
        case 'P':
            if(inicio){
                pausa=!pausa;
            }
            break;
            
        case 'i':
        case 'I':
            if(!inicio){
                pausa=false;
            }
            inicio=true;
            break;
            
        case 'r':
        case 'R':
            inicio=false;
            pausa=true;
            posIzq=posDer=xBola=golesDer=golesIzq=0,yBola=2.8;//reinicia valores
            break;
            
        case 27:
            exit(-1);
            //terminate the program
            break;
            
        default:
            break;		      // do nothing
    }
    glutPostRedisplay();
}


void drawText(float x, float y, std::string text, void* font) {
    //glMatrixMode(GL_MODELVIEW);
    glRasterPos3f(x, y, 0);
    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        //glPushMatrix();
        //glScaled(1, 12.5, 0);
        char c = *i;
        //glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        glutBitmapCharacter(font, c);
        //glPopMatrix();
    }
}



std::string toString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}



void timer (int v)
{
    if (!pausa) {
        
        
        if ((posIzq+.3>yBola) && (posIzq-.3<yBola) && (xBola<-2.8)) {
            cambioX=-cambioX;
            xBola=-2.8;
        }
        
        if ((posDer+.3>yBola) && (posDer-.3<yBola) && (xBola>2.8)) {
            cambioX=-cambioX;
            xBola=2.8;
        }
        
        if (xBola<-3.3 || xBola>3.3) {
            if (xBola>3.3){
                golesDer++;
                yBola=2.8;
                xBola=0;
                //posIzq=posDer=0;
            }
            if (xBola<-3.3){
                golesIzq++;
                yBola=2.8;
                xBola=0;
                //posIzq=posDer=0;
            }
            cambioX=-cambioX;
        }
        
        if (yBola<-2.8 || yBola>2.8) {
            cambioY=-cambioY;
        }
        
        yBola+=cambioY;
        xBola+=cambioX;
        
        glutPostRedisplay();
    }
    glutTimerFunc(50,timer,1);
}

void onMenu(int opcion) {
    switch(opcion) {
        case 1:
            inicio=true;
            pausa=false;
            break;
        case 2:
            inicio=false;
            pausa=true;
            posIzq=posDer=xBola=golesDer=golesIzq=0,yBola=2.8;//reinicia valores
            break;
        case 3:
            if(inicio){
                pausa=!pausa;
            }
            break;
        case 4: // Blanco 3
            exit(-1);
            //terminate the program
            break;
        case 5:
            break;
    }
    glutPostRedisplay();
}


void creacionMenu(void) {
    int menuPrincipal, autores;
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddMenuEntry("Iniciar", 1);
    glutAddMenuEntry("Reiniciar", 2);
    glutAddMenuEntry("Pausa", 3);
    glutAddMenuEntry("Salir", 4);
    glutAddMenuEntry("Roberto Mtz", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 1.0, 1.0);
    
    
    drawText(1.25, 2,toString(golesIzq), GLUT_BITMAP_9_BY_15);
    drawText(-1.25, 2,toString(golesDer), GLUT_BITMAP_9_BY_15);
    
    drawText(-2.75, -2.75,"Roberto Mtz A01190757", GLUT_BITMAP_9_BY_15);
    
    glPushMatrix();
    glTranslatef(-3,posIzq,0);
    glScaled(.2, 2, .2);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.9,0 ,0);
    glScaled(.02, 12, .02);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.9,0 ,0);
    glScaled(.02, 12, .02);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.01,0 ,0);
    glScaled(.02, 12, .02);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(xBola,yBola ,0);
    glutSolidSphere(.14,16,16);
    glPopMatrix();
    
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
    creacionMenu( );
    glutMainLoop();
    return 0;
}
