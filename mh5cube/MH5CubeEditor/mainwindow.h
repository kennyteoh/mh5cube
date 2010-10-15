/*
# This file is part of the Qube5-Editor.
#
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009 Christian Strobel
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "cubewidgetgl.h"
#include "cubepreview.h"
#include "cubepreviewdelegate.h"
#include "cubecommunication.h"
#include "dialog.h"
#include "timesdialog.h"


#include <QGridLayout>

namespace Ui
{
    class MainWindowClass;
}


//!  MainWindow
/*!
  This class is the central Window of this Application.
  The User-Interface is created by the QT uic (User Interface Compiler), which parses the file mainwindow.ui.
  The ui-file was created with the QT Designer (http://doc.trolltech.com/4.5/designer-manual.html)
  The ui-file holds all Widgets (QPushButtons, QSliders, Actions, etc) needed to control the Application, and a tableView to display the Figure-Set.

  This class MainWindow provides an interface between the UI and the following classes:
  - CubeCommunication (used for the Serial Communication with the Qube)
  - CubeWidgetGL (used to render a 3D-Model of the Qube)

  The MainWindow holds
   - a QStandardItemModel (model) used by ui->tableView which contains the Data for the whole Figure-Set
   - a QItemSelectionModel (selectionModel) used by ui->tableView
   - an instance of CubeWidgetGL (cubeWidgetGL) used as the central Widget (Editor for one Figure at a time).
   - another instance of CubeWidgetGL (cubeWidgetPreview), which is only used for creating preview Screenshots for the list and is not displayed anywhere
   - an instance of CubeCommunication (cubeCommunication), to interact with the Qube
   - several Widgets, used in the StatusBar

  The Constructor MainWindow::MainWindow() of this class has the following jobs:
    - it creates the Data Model for the ui->tableView
    - it creates a statusBar for the MainWindow and adds the needed Widgets (Buttons, Labels, ProgressBar) to it
    - it connects the UI - SIGNALS concerning File-Management (like Open, Append, Save, SaveAs) to SLOTS in this class
    - it connects the UI - SIGNALS concerning List-Management (like moving, inserting, deleting, cloning Figures) to SLOTS in this class
    - it connects the UI - SIGNALS concerning Figure Editing (like Move, Rotate, Layer-Selection, Random, Perspective, Coordinates, etc) directly to the SLOTS of cubeWidget
    - it connects the SIGNALS of the statusBar-Widgets (Programming, Connect, etc) to the SIGNALS of cubeCommunication

*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    int statesChanged(QBitArray *states);
    int FigureTimesIncrease();
    int FigureTimesDecrease();
    int FigureTimesChange(int increment  = 0, int fixtime  = 0);
    int FigureTimesSet(int newTime);
    int FigurePlay();
    int FigureAdd();
    int FigureInsert();
    int FigureClone();
    int FigureMoveUp();
    int FigureMoveDown();
    int FigureDelete();

    int CopyFigureToCube(QModelIndex,QModelIndex);
    void generateOutput();

    void showFixedEffects();
    void prepareProgramming();
    void failedProgramming();
    void successProgramming();
    void failedOpeningCOMPort(QString COMPortName);
    void successOpeningCOMPort(QString COMPortName);
    void failedFindingCube(QString COMPortName);
    void FillFixedEffectsComboBox();

    void writeSettings();
    void readSettings();
    void defaultSettings();
    void selectAll();

    void FileNew();
    void FileSave();
    void FileSaveAs();
    void FileOpen();
    void FileAppend();

    void About();

    void openFile(); //Not used
    void saveFile(); //Not used

    void openSettingsDialog();
    void openTimesDialog();

    void updateGLSettingsCube(GLSettings);
    void updateGLSettingsCubePreview(GLSettings);

    void TimeOut();


private:
    CubeWidgetGL *cubeWidget;           //!< This object is used as centralWidget (Editor)
    CubeWidgetGL *cubeWidgetPreview;    //!< This object is used for rendering the Preview-Icons, not displayed anywhere
    CubeCommunication *cubeCommunication; //!< This object handles the communication with the Qube

    void CreateModel(void);
    void CreateStatusBar(void);
    void closeEvent(QCloseEvent* event);

    int GetFigureData(int selectedRow, QPixmap &preview, QBitArray &states, QString &description, int &time);
    int SetFigureData(int selectedRow, QPixmap preview, QBitArray states, QString description, int time);

    int CreateEmptyFigure(int Row);
    int CreateFigureFromData(int Row, QPixmap preview, QBitArray states, QString description, int time);

    void saveBinFile(QString fileName);
    void openBinFile(bool appendMode);

    Ui::MainWindowClass *ui;            //!< UserInterface from mainwindow.ui
    QStandardItemModel *model;          //!< holds the Data for ui->tableView
    QItemSelectionModel *selectionModel; //!< used to retrieve the current selections of ui->tableView
    QBitArray *tempStates;              //!< holds temporary States of one figure
    QString currentFileName;            //!< holds the full path of the current file

    //StatusBar Items
    QPushButton *pushButtonLiveMode;    //!< permanentWidget in MainWindow::statusBar()
    QPushButton *pushButtonConnect;     //!< permanentWidget in MainWindow::statusBar()
    QPushButton *pushButtonFixedEffects;//!< permanentWidget in MainWindow::statusBar()
    QPushButton *pushButtonProgram;     //!< permanentWidget in MainWindow::statusBar()
    QWidget *widgetConnection;          //!< permanentWidget in nWindow::statusBar(), used as a Container for labelCOMPort and comboCOMPort
    QLabel *labelCOMPort;               //!< permanentWidget in MainWindow::statusBar()
    QComboBox *comboCOMPort;            //!< permanentWidget in MainWindow::statusBar()
    QWidget *widgetFixedEffects;        //!< permanentWidget in nWindow::statusBar(), used as a Container for Fixed Effects widgets
    QLabel *labelLoop;                  //!< permanentWidget in MainWindow::statusBar()
    QComboBox *comboFixedEffects;       //!< permanentWidget in MainWindow::statusBar()
    QProgressBar *programmProgressBar;  //!< permanentWidget in MainWindow::statusBar()
    QCheckBox *checkBoxLoop;            //!< permanentWidget in MainWindow::statusBar()

    //Play-Mode + Timer
    QProgressBar *playProgressBar;  //!< temporaryWidget in MainWindow::statusBar()
    QTimer* playTimer;
    int figureIndex;

    //Settings for the GL Widgets
    Dialog *settingsDialog;
    TimesDialog *timesDialog;

    GLSettings GLSettingsCube;
    GLSettings GLSettingsCubePreview;

signals:

};

#endif // MAINWINDOW_H
