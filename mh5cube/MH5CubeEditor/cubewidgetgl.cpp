/*
# This file is part of the Qube5-Editor.
#
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009-2010 Christian Strobel
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui>
#include <QtOpenGL>
#include <unistd.h>
#include <sys/time.h>

#include "cubewidgetgl.h"

CubeWidgetGL::CubeWidgetGL(QWidget *parent)
    : QGLWidget(parent)
{
    xRot = 10;
    yRot = 0;
    zRot = 0;

    zoom = 8;

    selectMode = false;
    setMode = TOGGLE;

    SLevel = 1;
    SRow = 1;
    SCol = 1;

    SLevelEnabled = false;
    SRowEnabled = false;
    SColEnabled = false;

    coordActive = false;
    currentPerspective = PERSPECTIV;
    nightModeActive = false;

    quadric = gluNewQuadric();

    //Pointer has to be initialized by Parent (here it's done in the MainWindow Constructor). Otherwise Runtime Error!
    //states = new QBitArray(NUM_ITEMS+1);

    defaultGLSettings();
}

CubeWidgetGL::~CubeWidgetGL() {
    makeCurrent();
    glDeleteLists((GLuint)LIST_LED_ON, 6);
}

void CubeWidgetGL::defaultGLSettings() {

    myGLSettings.ColorBGDay = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    myGLSettings.ColorBGNight = QColor(0,0,0);
    myGLSettings.ColorLEDOn  = QColor(180, 0, 0);
    myGLSettings.ColorLEDOff = QColor(200,200,200);

    setGLSettings(myGLSettings);
}

GLSettings CubeWidgetGL::getGLSettings() {
    return myGLSettings;
}

void CubeWidgetGL::setGLSettings(GLSettings newSettings) {
    myGLSettings = newSettings;
    this->createListLEDOn();
    this->createListLEDOff();    
    this->updateBackground();
    this->update();
}



QSize CubeWidgetGL::minimumSizeHint() const
{
    return QSize(340, 500);
}

QSize CubeWidgetGL::sizeHint() const
{
    return QSize(500, 500);
}



/* --------- Rotating -------------------- */

void CubeWidgetGL::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}

void CubeWidgetGL::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void CubeWidgetGL::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void CubeWidgetGL::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void CubeWidgetGL::setZoom(int nzoom)
{
    bool changed = false;

    if (nzoom > zoom) {
        if(zoom < 15) {
            zoom = nzoom;
            changed = true;
        }
    }
    if (nzoom < zoom) {
        if(zoom > 0) {
            zoom = nzoom;
            changed = true;
        }        
    }

    //Update only if zoom has changed
    if(changed) {
        if(currentPerspective==ORTHO) { //Render Perspective in ORTHO-Mode
            //Render new Perspective
            this->makeCurrent();
            glError();
            glMatrixMode(GL_PROJECTION);
            glError();
            glLoadIdentity();
            glError();
            this->RenderPerspective();
            glError();
            glMatrixMode(GL_MODELVIEW);
            glError();
        }
        emit zoomChanged(nzoom);
        updateGL();
    }

}


void CubeWidgetGL::resetRotation() {
    xRot = 10;
    yRot = 0;
    zRot = 0;
    zoom = 8;
    this->updateCube();
}


/* Update Selection Layers */

void CubeWidgetGL::setSLevel(int level) {
    SLevel = level;
    createListLevel();
    updateCube();
}

void CubeWidgetGL::setSRow(int row) {
    SRow = row;
    createListRow();
    updateCube();
}

void CubeWidgetGL::setSCol(int col){
    SCol = col;
    createListColumn();
    updateCube();
}


void CubeWidgetGL::setSLevelEnabled(bool state) {
    SLevelEnabled = state;
    updateCube();
}

void CubeWidgetGL::setSRowEnabled(bool state) {
    SRowEnabled = state;
    updateCube();
}

void CubeWidgetGL::setSColEnabled(bool state) {
    SColEnabled = state;
    updateCube();
}

/* Move states Actions */
void CubeWidgetGL::moveXPlus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int level = 0; level < (DIMENSION); level++) {
        for(int i = 1; i <= DIMENSION*DIMENSION; i++) {
            int id = (level*DIMENSION*DIMENSION)+i;
            if( i <= DIMENSION*DIMENSION-DIMENSION) { //20
                newStates.setBit(id, states->testBit(id+DIMENSION));
            }
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::moveXMinus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int level = 0; level < (DIMENSION); level++) {
        for(int i = 1; i <= DIMENSION*DIMENSION; i++) {
            int id = (level*DIMENSION*DIMENSION)+i;
            if( i > DIMENSION) { //5
                newStates.setBit(id, states->testBit(id-DIMENSION));
            }
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::moveYPlus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int i = 1; i <= (NUM_ITEMS); i++) {
        if(i < NUM_ITEMS+1 - DIMENSION*DIMENSION) {
            newStates.setBit(i, states->testBit(i+DIMENSION*DIMENSION));
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::moveYMinus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int i = 1; i <= (NUM_ITEMS); i++) {
        if(i > DIMENSION*DIMENSION) {
            newStates.setBit(i, states->testBit(i-DIMENSION*DIMENSION));
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::moveZPlus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int i = 1; i <= (NUM_ITEMS); i++) {
        if((i%DIMENSION)) {
            newStates.setBit(i, states->testBit(i+1));
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::moveZMinus() {
    QBitArray newStates(NUM_ITEMS+1);
    for(int i = 1; i <= (NUM_ITEMS); i++) {
        if((i-1)%DIMENSION) {
            newStates.setBit(i, states->testBit(i-1));
        }
    }
    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

/* Rotate States */
void CubeWidgetGL::rotateYPlus() {
    qDebug()<<"RotateYPlus";


    QBitArray newStates(NUM_ITEMS+1);

    /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {

        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        int id = level*25+1;
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++, id++) {
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

        turn2DMatrix(data, 1, true);
        turn2DMatrix(data, 2, true);

        /* Load Matrix into BitArray newStates*/
        id = level*25+1;
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++, id++) {
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);

}


void CubeWidgetGL::rotateYMinus() {
    qDebug()<<"RotateYMinus";


    QBitArray newStates(NUM_ITEMS+1);

    /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {

        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        int id = level*25+1;
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++, id++) {
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

        turn2DMatrix(data, 1, false);
        turn2DMatrix(data, 2, false);

        /* Load Matrix into BitArray newStates*/
        id = level*25+1;
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++, id++) {
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::rotateXPlus() {
    qDebug()<<"RotateXPlus";

    QBitArray newStates(NUM_ITEMS+1);

    /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {

        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
               int id = x*DIMENSION*DIMENSION+(y+1)+level*DIMENSION;
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

        turn2DMatrix(data, 1, true);
        turn2DMatrix(data, 2, true);

        /* Load Matrix into BitArray newStates*/
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
                int id = x*DIMENSION*DIMENSION+(y+1)+level*DIMENSION;
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);

}

void CubeWidgetGL::rotateXMinus() {
    qDebug()<<"RotateXminus";

    QBitArray newStates(NUM_ITEMS+1);

    /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {

        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
               int id = x*DIMENSION*DIMENSION+(y+1)+level*DIMENSION;
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

        turn2DMatrix(data, 1, false);
        turn2DMatrix(data, 2, false);

        /* Load Matrix into BitArray newStates*/
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
                int id = x*DIMENSION*DIMENSION+(y+1)+level*DIMENSION;
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);

}

void CubeWidgetGL::rotateZPlus() {
    qDebug()<<"RotateXminus";

    QBitArray newStates(NUM_ITEMS+1);

    /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {
        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        for(int y = 0; y < DIMENSION; y++) {
            for(int x = 0; x < DIMENSION; x++) {
                int id = y*25 + 1 + x * 5 + level;
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

            turn2DMatrix(data, 1, true);
            turn2DMatrix(data, 2, true);

        /* Load Matrix into BitArray newStates*/
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
                int id = y*25 + 1 + x * 5 + level;
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);

}

void CubeWidgetGL::rotateZMinus() {
    qDebug()<<"RotateZminus";

    QBitArray newStates(NUM_ITEMS+1);

     /* Load states (BitArray) into 2d-matrix */
    for(int level = 0; level < DIMENSION; level++) {
        bool data[DIMENSION][DIMENSION]; //2d Matrix for 1 Level

        for(int y = 0; y < DIMENSION; y++) {
            for(int x = 0; x < DIMENSION; x++) {
               int id = y*25 + 1 + x * 5 + level;
                data[y][x] = states->testBit(id);
                qDebug()<<"ID to Rotate:"<<id;
            }
        }

            turn2DMatrix(data, 1, false);
            turn2DMatrix(data, 2, false);

        /* Load Matrix into BitArray newStates*/
        for(int y = 0; y < (DIMENSION); y++) {
            for(int x = 0; x < DIMENSION; x++) {
                int id = y*25 + 1 + x * 5 + level;
                newStates.setBit(id, data[y][x]);
            }
        }
    }

    *states = newStates;
    updateCube();
    emit statesChanged(this->states);

}


//! Turns a 2D-Matrix (counter-)clockwise

void CubeWidgetGL::turn2DMatrix(bool data[DIMENSION][DIMENSION], int radius, bool clockwise) {

    int center = (DIMENSION-1)/2;
    int pos = 0; //Position in linear Array
    bool linear[(DIMENSION-1)*4]; //Maximale benötigte Größe: Dimension * 4 Kanten - 4 Ecken

    int y;
    int x = (center-radius);

    for(y=(center-radius); y<(center+radius); y++, pos++) {
        linear[pos] = data[y][x];
    }
    for(; x<(center+radius); x++, pos++) {
        linear[pos] = data[y][x];
    }
    for(; y>(center-radius); y--, pos++) {
        linear[pos] = data[y][x];
    }
    for(; x>(center-radius); x--, pos++) {
        linear[pos] = data[y][x];
    }

    int highestLinearIndex = 7;
    if(radius == 2)
        highestLinearIndex = 15;

    bool temp;
    bool temp1;

    if(clockwise==false) { //CounterClockwise
        /* shift array um 1 nach links */

        if(radius==1) {
            temp = linear[0];
            for(pos = 0; pos < highestLinearIndex; pos++) {
                linear[pos] = linear[pos+1];
            }
            linear[pos] = temp;
        }
        else
        {
            /*Shift Array um  2 nach links*/
            temp = linear[0];
            temp1 = linear[1];
            for(pos = 0; pos < highestLinearIndex-1; pos++) {
                linear[pos] = linear[pos+2];
            }
            linear[pos] = temp;
            linear[pos+1] = temp1;
        }
    }
    else { //Clockwise
        if(radius==1) {
            /* shift array um 1 nach rechts */
            temp = linear[highestLinearIndex];
            for(pos = highestLinearIndex; pos > 0; pos--) {
                linear[pos] = linear[pos-1];
            }
            linear[0] = temp;
        }
        else
        {
            /* shift array um 2 nach rechts */
            temp = linear[highestLinearIndex];
            temp1 = linear[highestLinearIndex-1];
            for(pos = highestLinearIndex; pos > 0; pos--) {
                linear[pos] = linear[pos-2];
            }
            linear[1] = temp;
            linear[0] = temp1;
        }

    }

    pos = 0;
    for(y=(center-radius); y<(center+radius); y++, pos++) {
        data[y][x] = linear[pos];
    }
    for(; x<(center+radius); x++, pos++) {
        data[y][x] = linear[pos];
    }
    for(; y>(center-radius); y--, pos++) {
        data[y][x] = linear[pos];
    }
    for(; x>(center-radius); x--, pos++) {
        data[y][x] = linear[pos];
    }

    /* Ende Turn*/

}


/*----------- OPEN-GL Specific -------------- */

void CubeWidgetGL::initializeGL()
{
    this->updateBackground();
    glError();

    float LightPosX = 0;
    float LightPosY = 10;
    float LightPosZ = 100;


    GLfloat light_diffuse[]     = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[]	= {LightPosX, LightPosY, LightPosZ, 1.0};
    GLfloat light_ambient[]     = {1.0, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

//LIGHT_1
//    float Light1PosX = -150;
//    float Light1PosY = 150;
//    float Light1PosZ = 150;
//
//    GLfloat light1_diffuse[]     = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light1_position[]	= {Light1PosX, Light1PosY, Light1PosZ, 1.0};
//    GLfloat light1_ambient[]     = {1.0, 1.0f, 1.0f, 1.0f };
//
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);




    //added
    GLfloat LModelAmbient[4] = {0.2F, 0.2F, 0.2F, 1.0F}; //Umgebungslicht
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &LModelAmbient[0]);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //ende added

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);

    glShadeModel(GL_SMOOTH);//GL_FLAT
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_NORMALIZE);



    // glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glError();


    createListLEDOn();
    glError();
    createListLEDOff();
    glError();
    createListBox();
    glError();
    createListCoord();
    glError();
    createListCube();
    glError();
    createListLevel();
    glError();
    createListRow();
    glError();
    createListColumn();
    glError();
    createListBoard();
    glError();
    createListLightPosition(LightPosX,LightPosY,LightPosZ);
    glError();
    createListConnector();
    glError();



}

void CubeWidgetGL::paintGL()
{
    this->makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear old Scene to prevent from Overdrawing
    glError();

    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    if(this->currentPerspective == ORTHO) {
        //glRotatef(zoom*3.0,0,0,0);
    }
    else {
        glTranslated(0.0, 0.0, zoom*-1.0);
    }



    //glTranslated(0.0, 0.4, -2.5);

    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glFinish();






    if(this->coordActive) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_COLOR_MATERIAL);
        glCallList((GLuint)LIST_COORD);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glPushMatrix();
        //Create Labels for Coordinate System
        QFont font( "Arial", 12, QFont::Bold);

        qglColor ( QColor(255,0,0)) ;
        this->renderText(1.5, 0.0, 0.0, QString("x"), font);
        qglColor ( QColor(0,255,0)) ;
        this->renderText(0.0, 1.5, 0.0, QString("y"), font);
        qglColor ( QColor(0,0,255)) ;
        this->renderText(0.0, 0.0, 1.5, QString("z"), font);
        glPopMatrix();

    }

    glCallList((GLuint)LIST_CUBE);



    if(!selectMode) {
        if(SLevelEnabled) glCallList((GLuint)LIST_LEVEL);
        if(SColEnabled) glCallList((GLuint)LIST_COLUMN);
        if(SRowEnabled) glCallList((GLuint)LIST_ROW);
        glCallList((GLuint)LIST_BOARD);
        glCallList((GLuint)LIST_LIGHT_POSITION);
        glCallList((GLuint)LIST_CONNECTOR);

    }


    glFinish();


}

void CubeWidgetGL::resizeGL(int width, int height)
{
    int side = qMax(width, height);

    //qDebug("WidgetHeight = %d", height);
    //qDebug("WidgetWidth = %d", width);

    glViewport((GLint)(width - side) / 2, (GLint)((height - side) / 2), (GLsizei)side, (GLsizei)side);
    glError();

    glMatrixMode(GL_PROJECTION);
    glError();
    glLoadIdentity();
    glError();

    this->RenderPerspective();
    glError();

    glMatrixMode(GL_MODELVIEW);
    glError();

}

void CubeWidgetGL::toggleCoordinates(bool show) {
    if(show) {
        this->coordActive = true;
    }
    else {
        this->coordActive = false;
    }
    this->updateCube();
}

void CubeWidgetGL::togglePerspective(bool ortho) {
    if(ortho) {
        this->currentPerspective = ORTHO;
        qDebug()<<"Perspective is now: ORTHOGONAL";
    }
    else {
        this->currentPerspective = PERSPECTIV;
        qDebug()<<"Perspective is now: PERSPECTIV";
    }

    //Render new Perspective
    this->makeCurrent();
    glError();
    glMatrixMode(GL_PROJECTION);
    glError();
    glLoadIdentity();
    glError();
    this->RenderPerspective();
    glError();
    glMatrixMode(GL_MODELVIEW);
    glError();

    this->updateCube();
}

void CubeWidgetGL::toggleNightMode(bool state) {
    this->makeCurrent();

    qDebug()<<"NightMode"<<state;
    if(nightModeActive) {
        nightModeActive = false;
    }
    else {
        nightModeActive = true;        
    }

    this->createListLEDOff();
    this->createListLEDOn();
    this->updateBackground();
    this->updateCube();

}



void CubeWidgetGL::RenderPerspective() {

   if(this->currentPerspective == ORTHO) {
       float atz = zoom / 8.0;
       qDebug()<<"-2*atz:" << -2* atz;
        glOrtho(-2*atz, +2*atz, -2*atz, +2*atz, -15, 15.0);

    }
   else {
        gluPerspective(30.0,1,1.0,30.0);
        //gluPerspective(30.0,1,0.1,30.0); //alt
    }

}


/* -------- Mouse Event Handling --------- */
void CubeWidgetGL::mousePressEvent(QMouseEvent *event)
{
    setMode = TOGGLE;
    this->updateCube();
    lastPos = event->pos();
    this->gl_select(lastPos.x(), (this->height())-lastPos.y()); //da höhe abgezogen werden muss (y koordinate umdrehen von fensterpos zu opengl koordinaten)
}

void CubeWidgetGL::wheelEvent(QWheelEvent *event) {

     int numDegrees = event->delta() / 8;
     int numSteps = numDegrees / 15;

     setZoom(zoom+numSteps);

     qDebug()<<"Steps:"<<numSteps;
     qDebug()<<"Zoom: "<<zoom;

}

void CubeWidgetGL::mouseMoveEvent(QMouseEvent *event)
{

    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();


    if (event->buttons() & Qt::LeftButton && !(event->modifiers()) ) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton && !(event->modifiers()) ) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    else if (event->buttons() & Qt::LeftButton && event->modifiers() & Qt::ShiftModifier) {
        setMode = MULTISET;
        this->updateCube();
        lastPos = event->pos();
        this->gl_select(lastPos.x(), (this->height())-lastPos.y());
    }
    else if (event->buttons() & Qt::RightButton && event->modifiers() & Qt::ShiftModifier) {
        setMode = MULTIUNSET;
        this->updateCube();
        lastPos = event->pos();
        this->gl_select(lastPos.x(), (this->height())-lastPos.y());
    }

    lastPos = event->pos();

}

/* ------- Cube Drawing Specific ----------- */

void CubeWidgetGL::updateCube(){
    this->makeCurrent();
    this->createListCube();

    //Render new Perspective
    this->makeCurrent();
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    this->RenderPerspective();
    glMatrixMode(GL_MODELVIEW);

    updateGL();
    glError();
}

void CubeWidgetGL::updateBackground(){
    this->makeCurrent();
    if(nightModeActive) {
        qglClearColor(myGLSettings.ColorBGNight);
    }
    else {
        qglClearColor(myGLSettings.ColorBGDay);
    }
}


//! Creates a sphere with id, at position : level, col, row
void CubeWidgetGL::smallSphere(int id, int level, int col, int row) {
    int size = DIMENSION;
    GLdouble space = (2.0 / (size-1));
    //GLdouble a = (space / 3) / 2;

    GLdouble x = 1.0 - col*space;
    GLdouble y = 1.0 - level*space;
    GLdouble z = 1.0 - row*space;

    

    glPushMatrix();

        glLoadName(id); /* Overwrite the first name in the buffer */
        glError();
        glTranslatef(x, y, z); /* Translate to the Right Position */

        if(states->testBit(id)==1)
        {
            glCallList((GLuint)LIST_LED_ON);
        }
        else
        {
            glCallList((GLuint)LIST_LED_OFF);
        }

    glPopMatrix();


}

void CubeWidgetGL::createListLEDOn() {
    int size = DIMENSION;
    GLdouble space = (3.0 / (size-1));
    GLdouble a = (space / 3) / 2;

    QColor tempColor = myGLSettings.ColorLEDOn;

    glNewList((GLuint)LIST_LED_ON, GL_COMPILE);
        /*MaterialColor*/
        GLfloat matAmbient[] = {0.0,0.0,0.0};
        GLfloat matDiffuse[4] = {tempColor.red()/255.0,
                                tempColor.green()/255.0,
                                tempColor.blue()/255.0, 1.0};
        GLfloat matSpecular[] = {0.0,0.0,0.0};
        float matShininess = 30;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        gluSphere(quadric, a, 16, 16);
    glEndList();
}

void CubeWidgetGL::createListLEDOff() {
    int size = DIMENSION;
    GLdouble space = (2.0 / (size-1));
    GLdouble a = (space / 3) / 2;


    QColor tempColor = myGLSettings.ColorLEDOff;

    if(this->nightModeActive) {
        tempColor = tempColor.darker(300);
        a/=2;
    }

    glNewList((GLuint)LIST_LED_OFF, GL_COMPILE);
        /*MaterialColor*/
        GLfloat matAmbient[] = {0.0,0.0,0.0};    
        GLfloat matDiffuse[4] = {tempColor.red()/255.0,
                                tempColor.green()/255.0,
                                tempColor.blue()/255.0, 1.0};
        GLfloat matSpecular[] = {0.0,0.0,0.0};
        float matShininess = 20;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        gluSphere(quadric, a, 16, 16);
    glEndList();
}

void CubeWidgetGL::createListBox() {
    glNewList((GLuint) LIST_BOX, GL_COMPILE);
    glPushMatrix();
        glBegin(GL_QUAD_STRIP);
            glNormal3d(0.0, 0.0, -1.0);
            glVertex3d(-1,-1,-1); //HLU
            glVertex3d(-1, 1,-1); //HLO
            glVertex3d( 1,-1,-1); //HRU
            glVertex3d( 1, 1,-1); //HRO

            glNormal3d(1.0, 0.0, 0.0);
            glVertex3d( 1,-1, 1); //VRU
            glVertex3d( 1, 1, 1); //VRO

            glNormal3d(0.0, 0.0, 1.0);
            glVertex3d( -1,-1, 1); //VLU
            glVertex3d( -1, 1, 1); //VLO

            glNormal3d(-1.0, 0.0, 0.0);
            glVertex3d( -1,-1,-1); //HLU
            glVertex3d( -1, 1,-1); //HLO

        glEnd();

        glBegin(GL_QUADS);
            glNormal3d(0.0, 1.0, 0.0);
            glVertex3d(1, 1, 1); //VRO
            glVertex3d(1, 1,-1); //HRO
            glVertex3d(-1,1,-1); //HLO
            glVertex3d(-1,1,1);  //VLO
        glEnd();

        glBegin(GL_QUADS);
            glNormal3d(0.0, -1.0, 0.0);
            glVertex3d(1, -1, 1); //VRU
            glVertex3d(1, -1,-1); //HRU
            glVertex3d(-1,-1,-1); //HLU
            glVertex3d(-1,-1,1);  //VLU
        glEnd();


    glPopMatrix();
    glEndList();
}

//void CubeWidgetGL::createListBox() {
//    glNewList((GLuint) LIST_BOX, GL_COMPILE);
//    glPushMatrix();
//        glBegin(GL_QUADS);
//            glNormal3d(0.0, 1.0, 0.0);
//            glVertex3d(1, 1, 1); //VRO
//            glVertex3d(1, 1,-1); //HRO
//            glVertex3d(-1,1,-1); //HLO
//            glVertex3d(-1,1,1);  //VLO
//        glEnd();
//
//        glBegin(GL_QUADS);
//            glNormal3d(0.0, -1.0, 0.0);
//            glVertex3d(1, -1, 1); //VRU
//            glVertex3d(1, -1,-1); //HRU
//            glVertex3d(-1,-1,-1); //HLU
//            glVertex3d(-1,-1,1);  //VLU
//        glEnd();
//
//
//    glPopMatrix();
//    glEndList();
//}



void CubeWidgetGL::createListCoord() {
    glNewList(LIST_COORD, GL_COMPILE);

        glBegin(GL_LINES);

            //glLoadName(0);
            // x: red
            glColor3f(1.0,0.0,0.0);
            glVertex3f(0.,0.,0.);
            glVertex3f(1.5,0.,0.);

            // y: green
            glColor3f(0.0,1.0,0.0);
            glVertex3f(0.,0.,0.);
            glVertex3f(0.,1.5,0.);

            // z: blue
            glColor3f(0.0,0.0,1.0);
            glVertex3f(0.,0.,0.);
            glVertex3f(0.,0.,1.5);

        glEnd();        
    glEndList();
}

void CubeWidgetGL::createListCube() {
    this->makeCurrent();
    glDeleteLists((GLuint) LIST_CUBE, 1); //Delete old List
    glNewList((GLuint) LIST_CUBE, GL_COMPILE);

        int i = 1;
        int size = DIMENSION;

        for(int levels = 0; levels < size; levels++) {

            for(int cols = 0; cols < size; cols++) {
                for(int rows = 0; rows < size; rows++) {
                    this->smallSphere(i, levels, cols, rows);
                    i++;
                }
            }
        }

    glEndList();
}

void CubeWidgetGL::createListLevel() {
    glNewList((GLuint) LIST_LEVEL, GL_COMPILE);

    int size = DIMENSION;
    GLdouble space = (2.0 / (size-1));

    GLdouble y = 1.0 - (SLevel-1)*space;

    glPushMatrix();
        //glLoadName(127); /* Overwrite the first name in the buffer */
        /*MaterialColor*/
        GLfloat matAmbient[] =  {0.0, 0.5, 0.0, 0.2F};
        GLfloat matDiffuse[] =  {0.0, 1.0, 0.0, 0.6F };
        GLfloat matSpecular[] = {0.0, 0.0, 0.0, 1.0F};
        float matShininess = 10.0;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(0.0, y ,0.0);
        glScalef(1.21,0.15,1.21);

        glCallList((GLuint) LIST_BOX);
    glPopMatrix();
    glEndList();
}

void CubeWidgetGL::createListRow() {
    glNewList((GLuint) LIST_ROW, GL_COMPILE);

    int size = DIMENSION;
    GLdouble space = (2.0 / (size-1));

    GLdouble z = 1.0 - (SRow-1)*space;


    glPushMatrix();
        //glLoadName(127); /* Overwrite the first name in the buffer */
        
         /*MaterialColor*/
        GLfloat matAmbient[] =  {0.0, 0.0, 0.1, 0.2F};
        GLfloat matDiffuse[] =  {0.0, 0.0, 1.0, 0.6F };
        GLfloat matSpecular[] = {0.0, 0.0, 0.0, 1.0F};
        float matShininess = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(0.0, 0.0 ,z);
        glScalef(1.22,1.22,0.15);

        glCallList((GLuint) LIST_BOX);
    glPopMatrix();
    glEndList();
}

void CubeWidgetGL::createListColumn() {
    glNewList((GLuint) LIST_COLUMN, GL_COMPILE);

    int size = DIMENSION;
    GLdouble space = (2.0 / (size-1));

    GLdouble x = 1.0 - (SCol-1)*space;

    glPushMatrix();
        //glLoadName(127); /* Overwrite the first name in the buffer */

        /*MaterialColor*/
        GLfloat matAmbient[] =  {0.8, 0.0, 0.0, 0.4F};
        GLfloat matDiffuse[] =  {1.0, 0.0, 0.0, 0.6F };
        GLfloat matSpecular[] = {0.0, 0.0, 0.0, 1.0F};
        float matShininess = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(x, 0.0 ,0.0);
        glScalef(0.15,1.2,1.2);


        glCallList((GLuint) LIST_BOX);
    glPopMatrix();
    glEndList();
}

void CubeWidgetGL::createListBoard() {
    glNewList((GLuint) LIST_BOARD, GL_COMPILE);

    glPushMatrix();
         /*MaterialColor*/
        GLfloat matAmbient[] =  {0.1, 0.1, 0.1, 1.0F};
        GLfloat matDiffuse[] =  {0.1, 0.1, 0.1, 1.0F };
        GLfloat matSpecular[] = {0.2, 0.2, 0.2, 1.0F};
        float matShininess = 5.0;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(0.0, -1.3 ,0.0);
        glScalef(1.2,0.02,1.2);
        glCallList((GLuint) LIST_BOX);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, -1.7 ,0.0);
        glScalef(1.2,0.02,1.2);
        glCallList((GLuint) LIST_BOX);

    glPopMatrix();
    glEndList();
}

void CubeWidgetGL::createListConnector() {
    glNewList((GLuint) LIST_CONNECTOR, GL_COMPILE);

    glPushMatrix();
         /*MaterialColor*/
        GLfloat matAmbient[] =  {0.4, 0.4, 0.4, 1.0F};
        GLfloat matDiffuse[] =  {0.2, 0.2, 0.2, 1.0F };
        GLfloat matSpecular[] = {0.5, 0.5, 0.5, 1.0F};
        float matShininess = 5.0;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(0.0, -1.5 ,1.1);

        //glTranslatef(-16*4.0 + 1.0 ,0,0);
        float space = 4.5;
        float size = 0.015;
        for(int i = 0; i < 30; i++) {
            
            glPushMatrix();
            glScalef(size,0.2,size);
            glTranslatef(-15*space + i*space + space/2, 0.0 ,0.0);
            //
            glCallList((GLuint) LIST_BOX);
            glPopMatrix();
        }

//        glPopMatrix();
//        glPushMatrix();
//        glTranslatef(0.0, -1.7 ,0.0);
//        glScalef(1.2,0.02,1.2);
//        glCallList((GLuint) LIST_BOX);

    glPopMatrix();
    glEndList();
}

void CubeWidgetGL::createListLightPosition(float x, float y, float z) {
    int size = DIMENSION;
    GLdouble space = (3.0 / (size-1));
    GLdouble a = (space / 3) / 2;

    float colR, colG, colB;
    colR=0.8f;
    colG=0.8f;
    colB=0.0f;

    glNewList((GLuint)LIST_LIGHT_POSITION, GL_COMPILE);
    glPushMatrix();

        /*MaterialColor*/
        GLfloat matAmbient[] = {0.0,0.0,0.0};
        GLfloat matDiffuse[] = { colR,colG, colB, 1.0 };
        GLfloat matSpecular[] = {colR*0.8,colR*0.8,colR*0.8};
        float matShininess = 30;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininess);

        glTranslatef(x,y,z);
        gluSphere(quadric, a, 16, 16);

    glPopMatrix();
    glEndList();
}


//! Checks if Mouse-Click has selected objects.
/*!
    More information: http://gpwiki.org/index.php/OpenGL:Tutorials:Picking
*/
void CubeWidgetGL::gl_select(int x, int y)
 {
   qDebug()<<"gl_select"<<x << " " << y;

   startPicking(x, y);

   this->selectMode = true;
    this->makeCurrent();
    this->createListCube();
    glDraw();
    glFlush();
   this->selectMode = false;

   stopPicking();

 }



void CubeWidgetGL::startPicking(int cursorX, int cursorY) {

        GLint viewport[4];

        glSelectBuffer(512,selectBuf);
        glRenderMode(GL_SELECT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        glGetIntegerv(GL_VIEWPORT,viewport);
        gluPickMatrix(cursorX,cursorY, 1.0,1.0,viewport);

        this->RenderPerspective();

        glMatrixMode(GL_MODELVIEW);
        glInitNames();
        glPushName(0);
}

void CubeWidgetGL::stopPicking() {

        int hits;

        // restoring the original projection matrix
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glFlush();

        // returning to normal rendering mode
        hits = glRenderMode(GL_RENDER);

        // if there are hits process them
        if (hits != 0)
                processHits2(hits,selectBuf);
}





//! Retrieves picked objects and toggles their states
/* von http://www.lighthouse3d.com/opengl/picking/index.php?openglway3 */
void CubeWidgetGL::processHits2 (GLint hits, GLuint buffer[])
{
   unsigned int i, j, select;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   qDebug("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {
      names = *ptr;
          ptr++;
          if (*ptr < minZ) {
                  numberOfNames = names;
                  minZ = *ptr;
                  ptrNames = ptr+2;
          }

          ptr += names+2;
        }
  qDebug ("The closest hit names are ");
  ptr = ptrNames;

  for (j = 0; j < numberOfNames; j++,ptr++) {
     qDebug("%d ", *ptr);
     select = *ptr;
  }


  qDebug("\n");
    switch (setMode) {

        case TOGGLE:
            if(states->testBit(select))
                states->setBit(select, false);
            else
                states->setBit(select, true);
        break;

        case MULTISET:
            states->setBit(select, true);
        break;

        case MULTIUNSET:
            states->setBit(select, false);
        break;

    }

    updateCube();
    emit statesChanged(this->states);
}






/* ------ Setting States -------------- */

void CubeWidgetGL::setAll(){
    states->fill(true);
    updateCube();
    emit statesChanged(this->states);
}
void CubeWidgetGL::unsetAll(){
   states->fill(false);
    updateCube();
    emit statesChanged(this->states);
}
void CubeWidgetGL::setRandom(){


    //Initialize with time of day microsecond
    timeval tv;
    gettimeofday(&tv, 0);

    // use BOTH microsecond precision AND pid as seed
    long int n = tv.tv_usec * getpid();
    srand(n);

    for(int i = 1; i <= (NUM_ITEMS); i++) {
        /* Zufallswert zuweisen zw 0 und 1 */
        states->setBit(i, (bool)(rand() % 2));
        }
    updateCube();
    emit statesChanged(this->states);
}

void CubeWidgetGL::setInvert(){
    for(int i = 1; i <= (NUM_ITEMS); i++) {
          if(states->testBit(i)) states->setBit(i, false);
          else states->setBit(i, true);
        }
    updateCube();
    emit statesChanged(this->states);
}

//! Slot for selection-set-Button in MainWindow
void CubeWidgetGL::setCurrentLayersTrue() {
    this->setCurrentLayers(true);
    emit statesChanged(this->states);
}

//! Slot for selection unset-Button in MainWindow
void CubeWidgetGL::setCurrentLayersFalse() {
    this->setCurrentLayers(false);
    emit statesChanged(this->states);
}

//! Sets the selected Layers to state (true or false)
void CubeWidgetGL::setCurrentLayers(bool state) {

    for(int i = 1; i <= (NUM_ITEMS); i++) {
        if(SLevelEnabled) {
            if( i <= (SLevel * DIMENSION*DIMENSION) && (i > ((SLevel-1)*DIMENSION*DIMENSION))) {
                states->setBit(i, state);
            }
        }
        if(SColEnabled) {
            int addVal = ((SCol-1) * (DIMENSION));
            for(int j = 0; j < DIMENSION; j++) {
                if( i <= addVal+DIMENSION*DIMENSION*j+DIMENSION && i >= addVal+DIMENSION*DIMENSION*j+1)
                states->setBit(i, state);
            }
        }
        if(SRowEnabled) {
            int erg = (i % DIMENSION);
            if(erg == SRow || erg == (SRow - DIMENSION))
                states->setBit(i, state);
        }
    }
    updateCube();

}

//! Output of the current states (only in Debug-Mode)
void CubeWidgetGL::showDebug(){
        for(int i = 0; i <= (NUM_ITEMS); i++) {
            if(this->states->testBit(i))
                qDebug("%s", "1");
            else
                qDebug("%s", "0");
        }
}

//! Creates a preview-pixmap from the Widget */
QPixmap CubeWidgetGL::renderIntoPixmap()
{
    QSize size = QSize(100,100);
    if (size.isValid()) {
        QPixmap pixmap = this->renderPixmap(size.width(), size.height());
        return pixmap;
    }
    return 0;
}

//! Fills states with newStates
void CubeWidgetGL::setStates(QBitArray *newStates) {
    newStates->detach();
    this->states = newStates;
    this->updateCube();
}



