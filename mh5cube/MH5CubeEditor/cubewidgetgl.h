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

#ifndef CUBEWIDGETGL_H
#define CUBEWIDGETGL_H

#define LIST_LED_ON    1   //Single LED On
#define LIST_LED_OFF   2   //Single LED Off
#define LIST_BOX    3   //Box 1x1x1
#define LIST_CUBE   4   //Complete Cube
#define LIST_BOARD  5   //Board under Cube
#define LIST_COORD  6   //Coord-System
#define LIST_LEVEL  7 //Level-Selection-Box
#define LIST_ROW    8 //Row-Selection-Box
#define LIST_COLUMN 9 //Column-Selection-Box
#define LIST_LIGHT_POSITION 10 //SHOW LIGHT SOURCE POSITIoN
#define LIST_CONNECTOR 11




#include <QGLWidget>
#include <QBitArray>
#include "core.h"

//! This class renders a 3D Model of the Qube5 in OpenGL and acts as an Editor for a single Figure
class CubeWidgetGL : public QGLWidget
{
    Q_OBJECT

public:
    CubeWidgetGL(QWidget *parent = 0);
    ~CubeWidgetGL();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    QPixmap renderIntoPixmap();

    QBitArray *states; //!< Holds the current states of one Figure

    GLSettings getGLSettings();

public slots:
    void setStates(QBitArray *newStates); //!< updates the states and displays them
    void setXRotation(int angle);    //!< sets the X-Rotation for the View
    void setYRotation(int angle);    //!< sets the X-Rotation for the View
    void setZRotation(int angle);    //!< sets the X-Rotation for the View
    void setZoom(int zoom);

    void resetRotation(); //!< Resets the view to the initial value
    void updateCube(); //!< Updates the displayed cube
    void updateBackground(); //!< Updates the Backgroundcolor according to nightModeActive-Flag

    void setAll();   //!< Set all items of the figure
    void unsetAll(); //!< Unset all items of the figure
    void setRandom(); //!< Fills the figure with Random states(50/50)
    void setInvert(); //!< Invert the current figure
    void setCurrentLayersTrue(); //!< Sets the selected Items according to selection Layers
    void setCurrentLayersFalse(); //!< Unsets the selected Items according to selection Layers

    void setSLevel(int level);  //!< Slot for the Level-Slider to select a Layer
    void setSCol(int col);      //!< Slot for the Column-Slider to select a Layer
    void setSRow(int row);      //!< Slot for the Row-Slider to select a Layer

    void moveXPlus();   //!< Moves the figure-states in X+ Direction
    void moveXMinus();  //!< Moves the figure-states in X- Direction
    void moveYPlus();   //!< Moves the figure-states in Y+ Direction
    void moveYMinus();  //!< Moves the figure-states in Y- Direction
    void moveZPlus();   //!< Moves the figure-states in Z+ Direction
    void moveZMinus();  //!< Moves the figure-states in Z- Direction

    void rotateXPlus(); //!< Rotate the figure-states arround the x-axis (+)
    void rotateXMinus();//!< Rotate the figure-states arround the x-axis (-)
    void rotateYPlus(); //!< Rotate the figure-states arround the y-axis (+)
    void rotateYMinus();//!< Rotate the figure-states arround the y-axis (-)
    void rotateZPlus(); //!< Rotate the figure-states arround the z-axis (+)
    void rotateZMinus();//!< Rotate the figure-states arround the z-axis (-)

    void setSLevelEnabled(bool state);  //!< slot for Level-Checkbox
    void setSRowEnabled(bool  state);   //!< slot for Row-Checkbox
    void setSColEnabled(bool  state);   //!< slot for Column-Checkbox

    void showDebug();
    void togglePerspective(bool ortho); //!< Toggles the perspective between False: Perspective, True: Orthogonal
    void toggleCoordinates(bool show);  //!< Display/Hide Coordinate-System
    void toggleNightMode(bool state); //!< Toggles the NightMode. False: Off, True: On

    void defaultGLSettings();
    void setGLSettings(GLSettings);

signals:
    void statesChanged(QBitArray *states);  //!< Emitted, when states have changed by user interaction
    void xRotationChanged(int angle);   //!< Emitted, when xRotation has Changed (not used currently)
    void yRotationChanged(int angle);   //!< Emitted, when yRotation has Changed (not used currently)
    void zRotationChanged(int angle);   //!< Emitted, when zRotation has Changed (not used currently)
    void zoomChanged(int zoom);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void createListLEDOn();
    void createListLEDOff();
    void createListCube();
    void createListBox();
    void createListBoard();
    void createListCoord();
    void createListLevel();
    void createListRow();
    void createListColumn();
    void createListLightPosition(float x, float y, float z);
    void createListConnector();


    //GLuint makeObject();    //!< Creates the object list for the cube

    void normalizeAngle(int *angle);
    void smallSphere(int id, int level, int row, int col);

    void RenderPerspective();
    void gl_select(int x, int y); //um ein GL-Objekt zu selektieren
    void processHits2 (GLint hits, GLuint buffer[]);

    void startPicking(int cursorX, int cursorY);
    void stopPicking();
    GLuint selectBuf[512];


    int xRot;   //!< holds the current x-Rotation
    int yRot;   //!< holds the current y-Rotation
    int zRot;   //!< holds the current z-Rotation
    int zoom;

    int SLevel; //!< holds the currently selected Level (1..SIZE), if 0, level is not displayed
    int SRow;   //!< holds the currently selected Row (1..SIZE)
    int SCol;   //!< holds the currently selected Column (1..SIZE)

    bool SLevelEnabled; //!< Stores if the Selection Layer is enabled
    bool SRowEnabled;   //!< Stores if the Selection Layer is enabled
    bool SColEnabled;   //!< Stores if the Selection Layer is enabled
    bool selectMode;

    void turn2DMatrix(bool data[DIMENSION][DIMENSION], int radius, bool clockwise);

    bool coordActive; //!< Stores if the Coordinate-System is being displayed
    enum Perspective {ORTHO, PERSPECTIV};
    Perspective currentPerspective; //!< Stores which perspective is being used
    bool nightModeActive;

    enum SetMode {TOGGLE, MULTISET, MULTIUNSET};
    SetMode setMode;




    void setCurrentLayers(bool state);
    GLUquadricObj* quadric; //!< Needed for generating a sphere-object in OpenGL

    QPoint lastPos; //!< Holds the last mouse-position

    GLSettings myGLSettings;



    //QColor BackgroundColorDay; //!< Background-Color for this widget
    //QColor BackgroundColorNight; //!< Background-Color for this widget
};

#endif // CUBEWIDGETGL_H
