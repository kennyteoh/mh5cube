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

#include "mainwindow.h"
#include <QBitArray>
#include <QDataStream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    tempStates = new QBitArray(NUM_ITEMS+1); //Allocate Memory for temporary Figure

    // cubeWidget is used for displaying / editing data of one Figure
    cubeWidget = new CubeWidgetGL(this);
    cubeWidget->setStates(tempStates);
    this->setCentralWidget(cubeWidget);
    this->setWindowTitle(QString(WINDOW_TITLE));

    // cubeWidgetPreview is used only for creating Preview-Screenshots, not displayed anywhere
    cubeWidgetPreview = new CubeWidgetGL(this);
    cubeWidgetPreview->setStates(tempStates);
    cubeWidgetPreview->setGeometry(50,50,150,150);
    //cubeWidgetPreview->hide(); //Preview is adopted by Settings-Dialog


    GLSettingsCube.DefaultColorBGDay = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    GLSettingsCube.DefaultColorBGNight = QColor(0,0,0);
    GLSettingsCube.DefaultColorLEDOn  = QColor(0, 0, 180);
    GLSettingsCube.DefaultColorLEDOff = QColor(200,200,200);

    GLSettingsCube.ColorBGDay   = GLSettingsCube.DefaultColorBGDay;
    GLSettingsCube.ColorBGNight = GLSettingsCube.DefaultColorBGNight;
    GLSettingsCube.ColorLEDOn = GLSettingsCube.DefaultColorLEDOn;
    GLSettingsCube.ColorLEDOff = GLSettingsCube.DefaultColorLEDOff;

    GLSettingsCubePreview = GLSettingsCube; //Same Settings for Preview

    cubeWidget->setGLSettings(GLSettingsCube);
    cubeWidgetPreview->setGLSettings(GLSettingsCubePreview);
    

    CreateModel(); //Create The Data Model and Connect it with the ui->tableView

    //----------------------------------------------------------------------------------------------------------------

    CreateStatusBar(); //Create StatusBar and add some Widgets to it
    cubeCommunication = new CubeCommunication(this, this->comboCOMPort);

    //Connect actions for widgets created in CreateStatusBar()
    connect(this->pushButtonConnect, SIGNAL(toggled(bool)), this->cubeCommunication, SLOT(ConnectionToggle(bool)));
    connect(this->pushButtonLiveMode, SIGNAL(toggled(bool)), this->cubeCommunication, SLOT(LiveModeToggle(bool)));
    connect(this->pushButtonFixedEffects, SIGNAL(clicked()), this, SLOT(showFixedEffects()));
    connect(this->pushButtonProgram, SIGNAL(clicked()), this, SLOT(prepareProgramming()));

    //Connect Error-Handling / Status for cubeCommunication
    connect(cubeCommunication, SIGNAL(programmingSuccessful()), this, SLOT(successProgramming()));
    connect(cubeCommunication, SIGNAL(programmingFailed()), this, SLOT(failedProgramming()));
    connect(cubeCommunication, SIGNAL(programmingPercentage(int)), this->programmProgressBar, SLOT(setValue(int)));
    connect(cubeCommunication, SIGNAL(findingCubeFailed(QString)), this, SLOT(failedFindingCube(QString)));
    connect(cubeCommunication, SIGNAL(openingCOMPortFailed(QString)), this, SLOT(failedOpeningCOMPort(QString)));
    connect(cubeCommunication, SIGNAL(openingCOMPortSuccessful(QString)), this, SLOT(successOpeningCOMPort(QString)));

    //-----------------------------------------------------------------------------------------------------------------

    //Update the displayed data, if the current selection in the ui->tableView (Figure List) has changed
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(CopyFigureToCube(QModelIndex,QModelIndex)));

    //Update states in the Figure-List (model), when states were changed in the cubeWidget
    connect(this->cubeWidget, SIGNAL(statesChanged(QBitArray*)), this, SLOT(statesChanged(QBitArray*)));

    //Update states in the cubePreviewWidget, when states were changed in the cubeWidgetGL
    connect(this->cubeWidget, SIGNAL(statesChanged(QBitArray*)), this->cubeWidgetPreview, SLOT(setStates(QBitArray*)));

    //Update LiveModeStates when states were changed in the cubeWidgetGL
    connect(this->cubeWidget, SIGNAL(statesChanged(QBitArray*)), this->cubeCommunication, SLOT(updateLiveModeStates(QBitArray*)));




    //-----------------------------------------------------------------------------------------------------------------

    // Connect Actions for File - Menu
    connect(this->ui->actionNew, SIGNAL(triggered()), this, SLOT(FileNew()));
    connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(FileOpen()));
    connect(this->ui->actionAppend, SIGNAL(triggered()), this, SLOT(FileAppend()));
    connect(this->ui->actionSave, SIGNAL(triggered()), this, SLOT(FileSave()));
    connect(this->ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(FileSaveAs()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // Connect Actions for Edit - Menu
    connect(this->ui->actionSelect_All, SIGNAL(triggered()), this, SLOT(selectAll()));

    //Connect Actions for View - Menu
    connect(ui->actionPerspective, SIGNAL(toggled(bool)), this->cubeWidget, SLOT(togglePerspective(bool)));
    connect(ui->actionPerspective, SIGNAL(toggled(bool)), this->cubeWidgetPreview, SLOT(togglePerspective(bool)));
    connect(ui->actionCoordinates, SIGNAL(toggled(bool)), this->cubeWidget, SLOT(toggleCoordinates(bool)));
    connect(ui->actionLayout_Save, SIGNAL(triggered()), this, SLOT(writeSettings()));
    connect(ui->actionLayout_Load, SIGNAL(triggered()), this, SLOT(readSettings()));
    connect(ui->actionLayout_Default, SIGNAL(triggered()), this, SLOT(defaultSettings()));

    connect(ui->actionNightMode, SIGNAL(toggled(bool)), this->cubeWidget, SLOT(toggleNightMode(bool)));
    connect(ui->actionReset_Rotation, SIGNAL(triggered()), this->cubeWidget, SLOT(resetRotation()));
    connect(ui->actionReset_Rotation, SIGNAL(triggered()), this->cubeWidgetPreview, SLOT(resetRotation()));

    //Connect Actions for Help - Menu
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(About()));

    //Connect Buttons for List Management
    connect(ui->pushButtonFigPlay, SIGNAL(clicked()), this, SLOT(FigurePlay()));
    connect(ui->pushButtonFigAdd, SIGNAL(clicked()), this, SLOT(FigureAdd()));
    connect(ui->pushButtonFigClone, SIGNAL(clicked()), this, SLOT(FigureClone()));
    connect(ui->pushButtonFigInsert, SIGNAL(clicked()), this, SLOT(FigureInsert()));
    connect(ui->pushButtonFigDelete, SIGNAL(clicked()), this, SLOT(FigureDelete()));
    connect(ui->pushButtonFigMoveUp, SIGNAL(clicked()), this, SLOT(FigureMoveUp()));
    connect(ui->pushButtonFigMoveDown, SIGNAL(clicked()), this, SLOT(FigureMoveDown()));

    //Connect Selection Sliders
    connect(ui->horizontalSliderSelectionLevel, SIGNAL(valueChanged(int)), this->cubeWidget, SLOT(setSLevel(int)));
    connect(ui->horizontalSliderSelectionColumn, SIGNAL(valueChanged(int)), this->cubeWidget, SLOT(setSCol(int)));
    connect(ui->horizontalSliderSelectionRow, SIGNAL(valueChanged(int)), this->cubeWidget, SLOT(setSRow(int)));

    //Connect Selection CheckBoxes
    connect(ui->checkBoxSelectionLevel, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setSLevelEnabled(bool)));
    connect(ui->checkBoxSelectionColumn, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setSColEnabled(bool)));
    connect(ui->checkBoxSelectionRow, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setSRowEnabled(bool)));

    //Connect Selection Buttons
    connect(ui->pushButtonSelectionSet, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setCurrentLayersTrue()));
    connect(ui->pushButtonSelectionUnset, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setCurrentLayersFalse()));

    //Connect EditStates Buttons
    connect(ui->pushButtonStatesSetAll, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setAll()));
    connect(ui->pushButtonStatesUnsetAll, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(unsetAll()));
    connect(ui->pushButtonStatesRandom, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setRandom()));
    connect(ui->pushButtonStatesInvert, SIGNAL(clicked(bool)), this->cubeWidget, SLOT(setInvert()));

    connect(ui->pushButtonMoveXPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveXPlus()));
    connect(ui->pushButtonMoveXMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveXMinus()));
    connect(ui->pushButtonMoveYPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveYPlus()));
    connect(ui->pushButtonMoveYMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveYMinus()));
    connect(ui->pushButtonMoveZPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveZPlus()));
    connect(ui->pushButtonMoveZMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(moveZMinus()));

    connect(ui->pushButtonRotateXPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateXPlus()));
    connect(ui->pushButtonRotateXMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateXMinus()));
    connect(ui->pushButtonRotateYPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateYPlus()));
    connect(ui->pushButtonRotateYMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateYMinus()));
    connect(ui->pushButtonRotateZPlus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateZPlus()));
    connect(ui->pushButtonRotateZMinus, SIGNAL(clicked()), this->cubeWidget, SLOT(rotateZMinus()));


    settingsDialog = new Dialog(this, this->cubeWidgetPreview, this->cubeWidget);
    timesDialog = new TimesDialog(this);

    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    connect(ui->pushButtonFigTimes, SIGNAL(clicked()), this, SLOT(openTimesDialog()));

    connect(this->timesDialog, SIGNAL(increaseTime()), this, SLOT(FigureTimesIncrease()));
    connect(this->timesDialog, SIGNAL(decreaseTime()), this, SLOT(FigureTimesDecrease()));
    connect(this->timesDialog, SIGNAL(setTimes(int)), this, SLOT(FigureTimesSet(int)));

    //Update changed Settings From Dialog to MainWindow
    connect(settingsDialog, SIGNAL(settingsChangedCube(GLSettings)), this, SLOT(updateGLSettingsCube(GLSettings)));
    connect(settingsDialog, SIGNAL(settingsChangedCubePreview(GLSettings)), this, SLOT(updateGLSettingsCubePreview(GLSettings)));


    //---------------- Play Button
    playTimer = new QTimer(this);
    playProgressBar = new QProgressBar;

    connect(this->playTimer, SIGNAL(timeout()), this, SLOT(TimeOut()));
    playTimer->setInterval(226); //Standardzeit für 10
    this->figureIndex = 0;

    //Developer Output

    connect(this->ui->actionDeveloperOutput, SIGNAL(triggered()), this, SLOT(generateOutput()));

    this->readSettings();
    this->updateGLSettingsCube(GLSettingsCube);
    this->updateGLSettingsCubePreview(GLSettingsCubePreview);

}

void MainWindow::closeEvent(QCloseEvent* event) {

    this->writeSettings();

    event->accept();
}


//! Creates the Data Model, connects it to the tableView and adds the first figure
/*!
   The Columns of the Data Model are:
    - 0: QBitArray states
    - 1: QPixmap preview
    - 2: QString description
    - 3: int time
*/
void MainWindow::CreateModel() {

    /* Create and Associate the Data Model with the tableView */
    /* Columns are: 0:Data | 1:Preview | 2: Desc | 3: Time */
    model = new QStandardItemModel(1,4);
    model->removeRows(0, 1, QModelIndex()); //Delete first automatically created Item

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new CubePreviewDelegate); //Use a special delegate for displaying data

    /* Create and Associate the Selection Model with the tableView */
    selectionModel = new QItemSelectionModel(model);
    selectionModel = ui->tableView->selectionModel();

    /* Create Header Labels for the tableView */
    QStringList labels;
    labels << tr("Data") << tr("Preview") << tr("Desc") << tr("Time");
    model->setHorizontalHeaderLabels(labels);

    //Set displaying options for tableView
    ui->tableView->setColumnHidden (0, true); //Don't display the Data Column
    ui->tableView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed); //Preview fix
    ui->tableView->horizontalHeader()->resizeSection(1, 100);
    ui->tableView->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setResizeMode(3, QHeaderView::ResizeToContents);

    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //Create First Figure
    FigureAdd();

    this->cubeWidget->states = tempStates;
}

//! Sets up a StatusBar for the MainWindow and adds some permanent Widgets to it
void MainWindow::CreateStatusBar() {
    programmProgressBar = new QProgressBar;

    pushButtonConnect = new QPushButton;
    pushButtonConnect->setText(tr("Connect"));
    pushButtonConnect->setCheckable(true);
    pushButtonLiveMode = new QPushButton;
    pushButtonLiveMode->setText(tr("Live-Mode"));
    pushButtonLiveMode->setCheckable(true);
    pushButtonProgram = new QPushButton;
    pushButtonProgram->setText(tr("Program!"));

    widgetConnection = new QWidget;
    QHBoxLayout *widgetConnectionLayout = new QHBoxLayout();
    labelCOMPort = new QLabel(tr("Com-Port:"));
    comboCOMPort = new QComboBox;
    widgetConnectionLayout->addWidget(labelCOMPort);
    widgetConnectionLayout->addWidget(comboCOMPort);
    widgetConnection->setLayout(widgetConnectionLayout);

    widgetFixedEffects = new QWidget;
    QHBoxLayout *widgetFixedEffectsLayout = new QHBoxLayout();
    labelLoop = new QLabel(tr("loop"));
    pushButtonFixedEffects = new QPushButton;
    pushButtonFixedEffects->setText(tr("Show Fixed Effect(s)"));
    checkBoxLoop = new QCheckBox;
    checkBoxLoop->setCheckable(true);
    checkBoxLoop->setChecked(true);
    comboFixedEffects = new QComboBox;
    this->FillFixedEffectsComboBox();
    widgetFixedEffectsLayout->addWidget(pushButtonFixedEffects);
    widgetFixedEffectsLayout->addWidget(comboFixedEffects);
    widgetFixedEffectsLayout->addWidget(checkBoxLoop);
    widgetFixedEffectsLayout->addWidget(labelLoop);
    widgetFixedEffects->setLayout(widgetFixedEffectsLayout);

    this->statusBar();
    this->statusBar()->showMessage(tr("Initialisation successful"));

    this->statusBar()->addPermanentWidget(widgetConnection);
    this->statusBar()->addPermanentWidget(pushButtonConnect);
    this->statusBar()->addPermanentWidget(pushButtonLiveMode);
    this->statusBar()->addPermanentWidget(widgetFixedEffects);
    this->statusBar()->addPermanentWidget(programmProgressBar);
    this->statusBar()->addPermanentWidget(pushButtonProgram);

}

/*
\todo: Implement ability to restore default Settings
*/
void MainWindow::defaultSettings() {
    //this->restoreState();
}

void MainWindow::FillFixedEffectsComboBox() {
    comboFixedEffects->clear();
    QStringList FixedEffects;

    FixedEffects << " 0 - Show All";
    FixedEffects << " 1 - Lights all the layers one by one";
    FixedEffects << " 2 - Pixel bouncing randomly around";
    FixedEffects << " 3 - Randomly fill/empty the cube";
    FixedEffects << " 4 - Send pixels randomly back and forth the Z axis";
    FixedEffects << " 5 - Spinning spiral";
    FixedEffects << " 6 - A coordinate bounces randomly around the cube";
    FixedEffects << " 7 - Random raindrops";
    FixedEffects << " 8 - A snake randomly bounce around the cub";
    FixedEffects << " 9 - Spinning plane";
    FixedEffects << "10 - Increasingly set/unset x number of random pixels";
    FixedEffects << "11 - Set/unset all pixels in a random order";
    FixedEffects << "12 - Bounce a plane up and down all the directions";
    FixedEffects << "13 - Fade in and out at low framerate";
    FixedEffects << "14 - Send all pixels down/up the Z axis";
    comboFixedEffects->insertItems(0, FixedEffects);

}

//! Saves the current Window-Layout
/*!
Uses QSettings (http://doc.trolltech.com/4.5/qsettings.html)
\sa readSettings()
*/
void MainWindow::writeSettings() {
    QSettings settings("Qube-Solutions", "Qube5");

    settings.beginGroup("mainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();

    settings.beginGroup("colors");
    settings.setValue("ColorLEDOn", this->GLSettingsCube.ColorLEDOn);
    settings.setValue("ColorLEDOff", this->GLSettingsCube.ColorLEDOff);
    settings.setValue("ColorBGDay", this->GLSettingsCube.ColorBGDay);
    settings.setValue("ColorBGNight", this->GLSettingsCube.ColorBGNight);
    settings.endGroup();
}

//! Reads the current Window-Layout and restores it
/*!
Uses QSettings (http://doc.trolltech.com/4.5/qsettings.html)
\sa writeSettings()
*/
void MainWindow::readSettings() {
    QSettings settings("Qube-Solutions", "Qube5");

    settings.beginGroup("mainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();

    settings.beginGroup("colors");
    this->GLSettingsCube.ColorLEDOn     = settings.value("ColorLEDOn", GLSettingsCube.DefaultColorLEDOn).value<QColor>();
    this->GLSettingsCube.ColorLEDOff    = settings.value("ColorLEDOff", GLSettingsCube.DefaultColorLEDOff).value<QColor>();
    this->GLSettingsCube.ColorBGDay     = settings.value("ColorBGDay", GLSettingsCube.DefaultColorBGDay).value<QColor>();
    this->GLSettingsCube.ColorBGNight   = settings.value("ColorBGNight", GLSettingsCube.DefaultColorBGNight).value<QColor>();
    settings.endGroup();

    this->updateGLSettingsCube(GLSettingsCube);
    this->updateGLSettingsCubePreview(GLSettingsCube);

}

//! Updates the states in the Model after CubeWidgetGL has changed states
/*!
\retval int success
*/
int MainWindow::statesChanged(QBitArray *states) {
    //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();

    if(indexes.count() > 1) {
        QMessageBox::warning(this, tr("Could not update figure"), tr("The selection contains more than one figure."), QMessageBox::Ok);
        return 0;
    }
    if(indexes.count() < 1) {
        QMessageBox::warning(this, tr("Could not update figure"), tr("The selection contains no figure."), QMessageBox::Ok);
        return 0;
    }

    if(!(indexes.isEmpty())) {
        QModelIndex Lindex = indexes.last();
        QModelIndex dataIndex = model->index(Lindex.row(), 0, QModelIndex()); //Set index to current row, column 0 (Data column)
        model->setData(dataIndex, QVariant(*states)); //Save *states as QVariant into the model

        dataIndex = model->index(Lindex.row(), 1, QModelIndex()); //Set index to current row, column 0 (Data column)
        QPixmap preview = this->cubeWidgetPreview->renderIntoPixmap(); //Create Preview
        glFinish();
        model->setData(dataIndex, qVariantFromValue(CubePreview(preview))); //Save Preview QPixmap into model
        return 1;
    }
    return 0;
}


//! Creates an empty Figure at a given Row
/*!
  Creates a new Item in the Model
  and the Data for it (Preview, states, description, time)
\param[in] row The row into which the new Figure will be inserted
\retval int The row into which the Figure was inserted
\sa CreateFigureFromData()
*/
int MainWindow::CreateEmptyFigure(int Row) {

    QStandardItem *newItem = new QStandardItem;

    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
    model->insertRow(Row, newItem);

    //Data (QBitArray)
    QBitArray states = QBitArray(NUM_ITEMS+1);

    //Create preview with empty states
    QPixmap preview(100,100);
    this->cubeWidgetPreview->setStates(&states);
    preview = this->cubeWidgetPreview->renderIntoPixmap();
    this->cubeWidgetPreview->setStates(tempStates);

    QString description(tr("Figure %1").arg(Row+1));
    int time = (int)DEFAULT_TIME;

    SetFigureData(Row, preview, states, description, time);

    this->ui->tableView->resizeRowToContents(Row); //Get Size-Hint of Delegate and fit Row for it
    this->ui->tableView->setRowHeight(Row,100);


    return Row;
}

//! Get Data from a Figure-Entry at a certain row
/*!
  Gets the Data of selectedRow and returns it on reference.
  \param[in] int selectedRow - Data of this row is returned
  \param[in,out] QPixmap &preview- Reference to the Pixmap of selectedRow
  \param[in,out] QBitArray &states - Reference to the states of selectedRow
  \param[in,out] QString &description - Reference to the description of selectedRow
  \param[in,out] int &time - Reference to the time of selectedRow
  \retval int - always 1
  \sa SetFigureData()
*/
int MainWindow::GetFigureData(int selectedRow, QPixmap &preview, QBitArray &states, QString &description, int &time) {

    CubePreview* tempPreview = new CubePreview(); //Needed to retrieve Preview

    QModelIndex index;
    //Data
    index = model->index(selectedRow, 0, QModelIndex());
    if (qVariantCanConvert<QBitArray>(index.data())) {
        states = qVariantValue<QBitArray>(index.data());
    }

    //Preview
    index = model->index(selectedRow, 1, QModelIndex());
    if (qVariantCanConvert<CubePreview>(index.data())) {
        *tempPreview = qVariantValue<CubePreview>(index.data());
    }
    tempPreview->getPreviewPicture(preview); //Load preview-Argument with the previewPicture  of tempPreview
    delete(tempPreview); //Pixmap has been retrieved, tempPreview not needed any longer

    //Description
    index = model->index(selectedRow, 2, QModelIndex());
    description = qVariantValue<QString>(index.data());

    //Time
    index = model->index(selectedRow, 3, QModelIndex());
    time = qVariantValue<int>(index.data());

    return 1;
}


//! Set the Data for a Figure-Entry in the Model at a certain row */
/*!
  \param[in] int selectedRow - Data is saved into the model at this row
  \param[in] QPixmap preview - Pixmap for the preview
  \param[in] QBitArray states - Data
  \param[in] QString description - Description
  \param[in] int time - Time
  \retval int - always 1
  \sa GetFigureData()
*/
int MainWindow::SetFigureData(int selectedRow, QPixmap preview, QBitArray states, QString description, int time) {

    QModelIndex index;
    index = model->index(selectedRow, 0, QModelIndex());

    //Data (QBitArray)
    model->setData(index, QVariant(states));

    //Preview
    index = model->index(selectedRow, 1, QModelIndex());
    model->setData(index, qVariantFromValue(CubePreview(preview)));

    //Decription
    index = model->index(selectedRow, 2, QModelIndex());
    model->setData(index, QVariant(description));

    //Time
    index = model->index(selectedRow, 3, QModelIndex());
    model->setData(index, QVariant((int)time));

    return 1;
}




//! Creates a Figure at the given Row and fills it with given Data
/*!
  \sa FigureClone()
  \sa setFigureData()
  \sa CreateEmtyFigure()
*/
int MainWindow::CreateFigureFromData(int Row, QPixmap preview, QBitArray states, QString description, int time) {

    if(model->rowCount() >= (int)MAX_ALLOWED_FIGURES) {
        this->statusBar()->showMessage(tr("Number of Figures is limited to %1").arg((int)MAX_ALLOWED_FIGURES));
        return 0;
    }

    QStandardItem *newItem = new QStandardItem;

    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
    model->insertRow(Row, newItem);

    SetFigureData(Row, preview, states, description, time); //Save Data to Figure

    this->ui->tableView->resizeRowToContents(Row); //Get Size-Hint of Delegate and fit Row for it
    this->ui->tableView->setRowHeight(Row,100);

    return Row;
}

int MainWindow::FigurePlay() {

    if(!playTimer->isActive()) {
        qDebug()<<"FigurePlayStart";
        this->statusBar()->addWidget(playProgressBar);
        this->statusBar()->showMessage("");
        playProgressBar->setValue(0);
        playProgressBar->setRange(0,100);
        //playProgressBar->showNormal();
        playProgressBar->setVisible (true);
        this->playTimer->start();

        this->ui->pushButtonFigPlay->setChecked(true);
    }
    else {
        this->statusBar()->showMessage("Playing stopped", 1000);
        this->statusBar()->removeWidget(playProgressBar);
        this->playTimer->stop();
        selectionModel->select(model->index(this->figureIndex-1,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        this->figureIndex = 0;
        this->ui->pushButtonFigPlay->setChecked(false);
    }


    return 1;
}

int MainWindow::FigureTimesIncrease() {
    qDebug()<<"FigureTimesIncrease";

    this->FigureTimesChange(+1);

    return 1;
}

int MainWindow::FigureTimesDecrease() {
    qDebug()<<"FigureTimesDecrease";

    this->FigureTimesChange(-1);

    return 1;
}


//! Changes the Times of all Figures by increment or sets a fixtime for all figures
/*!
  \sa FigureTimesDecrease()
  \sa FigureTimesIncrease()
  \sa FigureTimesSet()
*/
int MainWindow::FigureTimesChange(int increment, int fixtime) {
    qDebug()<<"FigureTimesChange by "<< increment;

    QProgressBar *tempProgress = new QProgressBar;
    tempProgress->setRange(0,100);
    statusBar()->addWidget(tempProgress);
    tempProgress->show();

    int i = 0;
    for(i = 0; i < this->model->rowCount(); i++) {

        qDebug()<<"ChangeTime of Figure" << i;


        QPixmap preview(100,100);
        QString description;
        int time;
        GetFigureData(i, preview, *tempStates, description, time);

        if(increment != 0) { //If increment is given, increase time
            time = time + increment;
            if(time < 1)
                time = 1;
            if (time > 20)
                time = 20;
        }
        else time = fixtime; //or use fix fime for all figures


        SetFigureData(i, preview, *tempStates, description, time);

        int percentage = (int)((((float)i + 1.0) / this->model->rowCount()) * 100);
        tempProgress->setValue(percentage);

     }

    statusBar()->removeWidget(tempProgress);
    statusBar()->showMessage(tr("Time has been changed for %1 Figures").arg(i));

    return 1;

}

int MainWindow::FigureTimesSet(int newTime) {
    qDebug()<<"Change Times to "<<newTime;
    this->FigureTimesChange(0, newTime);
    return 1;
}



//! Add an empty Figure after the last selected item
/*
  \retval int success
  \sa CreateEmptyFigure()
*/
int MainWindow::FigureAdd() {
    qDebug("FigureAdd");

    if(model->rowCount() >= (int)MAX_ALLOWED_FIGURES) {
        this->statusBar()->showMessage(tr("Number of figures is limited to %1").arg((int)MAX_ALLOWED_FIGURES));
        return 0;
    }

    int newRow = model->rowCount();
    CreateEmptyFigure(newRow);
    selectionModel->select(model->index(newRow,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    this->statusBar()->showMessage(tr("Added figure at row %1 ").arg(model->rowCount()));
    return 1;
}

//! Insert an empty figure after the current selection
/*
  \retval int success
*/
int MainWindow::FigureInsert() {
    qDebug("FigureInsert");

    if(model->rowCount() >= (int)MAX_ALLOWED_FIGURES) {
        this->statusBar()->showMessage(tr("Number of figures is limited to %1").arg((int)MAX_ALLOWED_FIGURES));
        return 0;
    }

    //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();

    if(indexes.count() < 1) {
        QMessageBox::warning(this, tr("Could not insert figure"), tr("No figure is selected."), QMessageBox::Ok);
        return 0;
    }

    if(indexes.count() > 1) {
        QMessageBox::warning(this, tr("Could not insert figure"), tr("The selection contains more than one figure."), QMessageBox::Ok);
        return 0;
    }

    QModelIndex index = indexes.last();

    int newRow = CreateEmptyFigure(index.row()+1);
    
    qDebug() << "Inserted new Figure in Row " << newRow;

    selectionModel->select(model->index(newRow,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

    this->statusBar()->showMessage(tr("Inserted Figure at row %1 ").arg(newRow+1));

    return 1;
}


//! Clone the selected figure, insert them after the selected item
/*!
  \todo Extend the function to handle multiple selections
  \retval int success
*/
int MainWindow::FigureClone() {
    qDebug("FigureClone");

    if(model->rowCount() >= (int)MAX_ALLOWED_FIGURES) {
        this->statusBar()->showMessage(tr("Number of figures is limited to %1").arg((int)MAX_ALLOWED_FIGURES));
        return 0;
    }

    //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();

    if(indexes.count() < 1) {
        QMessageBox::warning(this, tr("Could not clone figure"), tr("No figure is selected."), QMessageBox::Ok);
        return 0;
    }

    if(indexes.count() > 1) {
        QMessageBox::warning(this, tr("Could not clone figure"), tr("The selection contains more than one figure."), QMessageBox::Ok);
        return 0;
    }

    QModelIndex index = indexes.last();
    int selectedRow = index.row();

    QPixmap preview(100,100);
    QBitArray states;
    QString description;
    int time;
    GetFigureData(selectedRow, preview, states, description, time);

    int newRow = CreateFigureFromData(selectedRow+1, preview, states, description, time);

    selectionModel->select(model->index(newRow,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    this->statusBar()->showMessage(tr("Cloned Figure at row %1 ").arg(newRow+1));

    return 1;
}

//! Moves the selected figure up by one index
/*!
  \todo Extend the function to handle multiple selections
  \retval int success
*/
int MainWindow::FigureMoveUp() {
    qDebug("FigureMoveUp");

    //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();

    if(indexes.count() > 1) {
        QMessageBox::warning(this, tr("Could not move Figure"), tr("The Selection contains more than one Figures."), QMessageBox::Ok);
        return 0;
    }

    if(indexes.count() < 1) {
        QMessageBox::warning(this, tr("Could not move figure"), tr("No figure is selected."), QMessageBox::Ok);
        return 0;
    }



    QModelIndex index = indexes.last();
    int selectedRow = index.row();

    if(selectedRow == 0)
        return 0;

    /* Get Data from the current Figure */
    QPixmap preview;
    QBitArray states;
    QString description;
    int time;
    GetFigureData(selectedRow, preview, states, description, time);


    /* Get Data from the Figure above the current Figure */
    QPixmap previewTemp;
    QBitArray statesTemp;
    QString descriptionTemp;
    int timeTemp;
    GetFigureData(selectedRow-1, previewTemp, statesTemp, descriptionTemp, timeTemp);


    /* Swap their Data */
    SetFigureData(selectedRow-1, preview, states, description, time);
    SetFigureData(selectedRow, previewTemp, statesTemp, descriptionTemp, timeTemp);

    /*Select Moved Figure */
    selectionModel->select(model->index(selectedRow-1,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

    this->statusBar()->showMessage(tr("Moved Figure to row %1 ").arg(selectedRow));

    return 1;
}

//! Moves the selected figure down by one index
/*!
  \todo Extend the function to handle multiple selections
  \retval int success
*/
int MainWindow::FigureMoveDown() {
    qDebug("FigureMoveDown");

     //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();

    if(indexes.count() > 1) {
        QMessageBox::warning(this, tr("Could not move Figure"), tr("The Selection contains more than one Figures."), QMessageBox::Ok);
        return 0;
    }

    if(indexes.count() < 1) {
        QMessageBox::warning(this, tr("Could not move figure"), tr("No figure is selected."), QMessageBox::Ok);
        return 0;
    }

    QModelIndex index = indexes.last();
    int selectedRow = index.row();

    if(selectedRow >= model->rowCount()-1)
        return 0;

    /* Get Data from the current Figure */
    QPixmap preview;
    QBitArray states;
    QString description;
    int time;
    GetFigureData(selectedRow, preview, states, description, time);

    /* Get Data from the Figure below the current Figure */
    QPixmap previewTemp;
    QBitArray statesTemp;
    QString descriptionTemp;
    int timeTemp;
    GetFigureData(selectedRow+1, previewTemp, statesTemp, descriptionTemp, timeTemp);

    /* Swap their Data */
    SetFigureData(selectedRow+1, preview, states, description, time);
    SetFigureData(selectedRow, previewTemp, statesTemp, descriptionTemp, timeTemp);

    /*Select Moved Figure */
    selectionModel->select(model->index(selectedRow+1,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    this->statusBar()->showMessage(tr("Moved Figure to row %1 ").arg(selectedRow+2));

    return 1;
}

//! Deletes the selected figures
/*!
  Sorts the selected indexes by row-value (descending order) first (Problems with updating occur otherwise)
  Deletes the selected indexes
  \todo Better handling for multiple selections is required
  \retval int success
*/
int MainWindow::FigureDelete() {
    qDebug("FigureDelete");

    //Get selected rows
    QModelIndexList indexes = selectionModel->selectedRows();


    selectionModel->blockSignals(true);
    ui->tableView->blockSignals(true);

    QModelIndex index;
/*
    QPersistentModelIndex pIndex(index);

    pIndex = indexes.at(1);
    this->model->removeRow(1, pIndex);
  */
    qDebug() << "Indexes: " << indexes;
    qDebug() << "Indexes.Count: "<<indexes.count();

    //Sort Unordered Indexes by Row-value (Descending Order)
    int count = indexes.count(); //Number of Selected Rows
    int totalCount = model->rowCount();

    for(int j = 0; j < count; j++) {
        int tempBiggestRow = 0;
        for(int i = j; i < count; i++)
        {
            QModelIndex tempIndex;
            tempIndex = indexes.at(i);
            int currentRow = tempIndex.row();
            qDebug() << "Row: " << currentRow;
            if( currentRow > tempBiggestRow ) {
                tempBiggestRow = currentRow; //New Biggest Row-Value
                indexes.move(i, j); //Move Biggest Value to the Top of the List
            }
        }
    }

    //Delete Rows, beginning with the last selected Row
    int deletedRows = 0;
    foreach(index, indexes)
    {
        int row = index.row();
        qDebug() << "SortedRow: " << row;
        if(deletedRows < totalCount-1) {
            qDebug() <<"Success " << row <<":" << model->removeRow(row);
            deletedRows++;
        }

    }
    ui->tableView->blockSignals(false);
    selectionModel->blockSignals(false);
        
    return 1;
}

//! Copy the current selected Data to the CubeWidget for displaying and editing
/*!
  Gets the current selection of tableView, converts the states-data from the model to QBitArray and update the states of cubeWidgetGL and cubeWidgetPreview
    \retval int - always 1
*/
int MainWindow::CopyFigureToCube(QModelIndex current, QModelIndex previous) {

    qDebug("CopyFigureToCube");
    //qDebug() << "Current ModelIndex:" << current;
    //qDebug() << previous;
    qDebug() << model->data(current);

    int selectedRow = current.row();
    QModelIndex index = model->index(selectedRow, 0, QModelIndex()); //Set Index to selected Row, Column 0 (states-Data)

    //Convert Data back from QVariant to QBitArray
    if (qVariantCanConvert<QBitArray>(index.data())) {
        *tempStates = qVariantValue<QBitArray>(index.data());
        tempStates->detach();
        this->cubeWidget->setStates(tempStates);
        glFinish();
        this->cubeWidgetPreview->setStates(tempStates);
        this->cubeCommunication->updateLiveModeStates(tempStates);
    }
    return 1;
}

//! Show one of the fixed effects already programmed into the cube
/*!
  Show one of the fixed effects or all fixed effects which are already programmed into the cube
 */
void MainWindow::showFixedEffects() {
    qDebug("Showing one of the fixed effects");

    if(!this->cubeCommunication->isConnected()) {
        QMessageBox::critical(this, tr("Connection Problem"), tr("Please connect to the cube first."));
        return;
    }

    //Check value of loop checkbox
    bool looped = false;
    if (checkBoxLoop->isChecked()) {
        looped = true;
    }

    //Check value of combobox
    int fixedEffect = comboFixedEffects->currentIndex();

    qDebug() << "Current selected effect: " << fixedEffect << " - looped is " << looped;

    cubeCommunication->ShowFixedEffects(fixedEffect, looped);

//    QMessageBox::critical(this, tr("Show Fixed Effect"), tr("Sorry, Not yet implemented!"));
}


//! Prepare Data from the Model, checks if the device is connected, initiates programming
/*!
  Retrieves the Data from the Model into a QByteArray, which is sent to CubeCommunication::startProgramming if the Device is connected.
  The QByteArray consists of a Header which contains the Start-Character '*' for Programming Mode and the number of Rows (2 Bytes) to come .

  For each Figure, a 28-Byte long QByteArray is appended, which contains:
    - the start-character '*'
    - 25 Bytes, containing the Data of the Figure,
    - the end-character '~'

    Header (once)   :   *<numRowsLowByte><numRowsHighByte> (3 Bytes in total)

    For each figure :   *<25DataBytes><time>~ (28 Bytes per Figure)

*/
void MainWindow::prepareProgramming()
{
    qDebug("prepareProgramming");

    if(!this->cubeCommunication->isConnected()) {
        QMessageBox::critical(this, tr("Connection Problem"), tr("Please connect first"));
        return;
    }

    if(cubeCommunication->isLiveMode()) {
        QMessageBox::critical(this, tr("Live Mode is active"), tr("Qube can not be programmed while LiveMode is active. Please Leave LiveMode first."));
        return;
    }

    int numRows = model->rowCount();

    QByteArray BytesTotal;
    QByteArray bytesFigure(28, 'y');

    BytesTotal.append("*");
    BytesTotal.append((char)numRows);
    BytesTotal.append((char)(numRows>>8));

    for(int figure = 0; figure < numRows; figure++)
    {
        //Daten der aktuellen Figur figure selektieren
        QModelIndex index = model->index(figure, 0, QModelIndex());

        //QBit-Array erzeugen
        if (qVariantCanConvert<QBitArray>(index.data())) {
            qDebug()<< "Figur "<<figure<<":";
            QBitArray states = qVariantValue<QBitArray>(index.data());

            /*-Debug ausgabe-*/
            QString title = "";
            for(int i = 0;  i < (NUM_ITEMS+1); i++){
                if(states.testBit(i) == true)
                    title.append("1");
                else
                    title.append("0");
            }
            qDebug() << title;

            /* byteFigure füllen */

            bytesFigure[0] = '*';   //Startzeichen Figur

            int i = 0; //index 0 wird übersprungen da immer Leer

            for(int b = 1; b < 26; b++) {
                char Insertion = 0;
                Insertion += (int)states.at(++i)<<4;
                Insertion += (int)states.at(++i)<<3;
                Insertion += (int)states.at(++i)<<2;
                Insertion += (int)states.at(++i)<<1;
                Insertion += (int)states.at(++i);
                bytesFigure[b]=Insertion;
            }

            //Zeit der aktuellen Figur figure selektieren
            QModelIndex index = model->index(figure, 3, QModelIndex());
            int time = qVariantValue<int>(index.data());

            bytesFigure[26] = time; //Zeit
            bytesFigure[27] = '~'; //Abschlusszeichen Figur
            BytesTotal.append(bytesFigure);

        }

    }
    qDebug() << "Datei:" << BytesTotal;

    if(cubeCommunication->isConnected() && !cubeCommunication->isLiveMode()) {
        cubeCommunication->startProgramming(BytesTotal, numRows);
        this->pushButtonProgram->setEnabled(false);
    }

}

//! Called after successful programming
/*!
\sa CubeCommunication::programmingSuccessful()
*/
void MainWindow::successProgramming()
{
    this->statusBar()->showMessage(tr("Programming successful"));
    QMessageBox::information(this, tr("Programming finished"), tr("Successfully finished"));
    this->pushButtonProgram->setEnabled(true);
    this->programmProgressBar->setValue(0);
}

//! Called after programming has failed
/*!
\sa CubeCommunication::programmingFailed()
*/
void MainWindow::failedProgramming()
{
    this->statusBar()->showMessage(tr("Programming failed"));
    QMessageBox::critical(this, tr("Programming failed"), tr("Programming failed, please Reset Qube and try again"));
    this->pushButtonProgram->setEnabled(true);
    this->programmProgressBar->setValue(0);
}

//! Called after finding Qube has failed
/*!
\sa CubeCommunication::findingCubeFailed()
*/
void MainWindow::failedFindingCube(QString COMPortName)
{
    this->statusBar()->showMessage(tr("Could not find Qube at %1").arg(COMPortName));
    QMessageBox::critical(this, tr("Could not find Cube"), tr("Could not detect a Qube Solutions Qube5 at COMPort %1.\n Please check connections and power supply").arg(COMPortName));
}

//! Called after opening Com Port was successful
/*!
\sa CubeCommunication::openingCOMPortSuccessful()
*/
void MainWindow::successOpeningCOMPort(QString COMPortName)
{
    this->statusBar()->showMessage(tr("Opening %1 successful").arg(COMPortName));
}

//! Called after opening Com Port failed
/*!
\sa CubeCommunication::openingCOMPortFailed()
*/
void MainWindow::failedOpeningCOMPort(QString COMPortName)
{
    this->statusBar()->showMessage(tr("Could not open %1").arg(COMPortName));
    QMessageBox::critical(this, tr("Could not open COMPort"), tr("Could not open COMPort %1.\n Device might be used by another program").arg(COMPortName));
}

void MainWindow::generateOutput() {
    qDebug("GenerateOutput to File");

    int numRows = this->model->rowCount();    //@TODO: q_uint16_t verwenden

    qDebug() << "Größe Numrows(int)" << sizeof(numRows);

    QByteArray BytesTotal(0);         //Enthält alle Figuren
    QByteArray bytesFigure(27, '0');  //Enthält Daten einer Figur im Cube5-Format

    for(int figure = 0; figure < numRows; figure++)
    {


        //Daten der aktuellen Figur figure selektieren
        QModelIndex index = this->model->index(figure, 0, QModelIndex());


        //QBit-Array erzeugen
        if (qVariantCanConvert<QBitArray>(index.data())) {
            qDebug()<< "Figur "<<figure<<":";
            QBitArray states = qVariantValue<QBitArray>(index.data());

//            /*-Debug ausgabe-*/
//            QString title = "";
//            for(int i = 0;  i < (NUM_ITEMS+1); i++){
//                if(states.testBit(i) == true)
//                    title.append("1");
//                else
//                    title.append("0");
//            }
//            qDebug() << title;

            /* byteFigure füllen */

            bytesFigure[0] = '*';   //Startzeichen Figur

            int i = 0; //index 0 wird übersprungen da immer Leer

            for(int b = 1; b < 26; b++) {
                char Insertion = 0;
                Insertion += (int)states.at(++i)<<4;
                Insertion += (int)states.at(++i)<<3;
                Insertion += (int)states.at(++i)<<2;
                Insertion += (int)states.at(++i)<<1;
                Insertion += (int)states.at(++i);
                bytesFigure[b]=Insertion;
           }

            //Zeit der aktuellen Figur figure selektieren
//            QModelIndex index = this->model->index(figure, 3, QModelIndex());
//            int time = qVariantValue<int>(index.data());

            //bytesFigure[26] = time; //Zeit
            bytesFigure[26] = '~'; //Abschlusszeichen Figur




            for (int i = 0; i < bytesFigure.count(); i++) {
                QString test;
                test = QString("0x%1,").arg(bytesFigure.at(i), 2, 16, QChar('0'));
                BytesTotal.append(test);
                }

            BytesTotal.chop(1);

            BytesTotal.append("\n");
        }
    }



    QString filename = "DeveloperOutput.txt";

    QFile file( filename );
    if ( file.open( QIODevice::WriteOnly))
    {
        QDataStream stream( &file );
        //stream << BytesTotal;
        stream.writeRawData(BytesTotal, BytesTotal.count());
    }
    else
    {
        qDebug() << "Could not create file <" << filename << ">";
    }

}


void MainWindow::openFile() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "All Files (*.*)");
    if(!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open( QIODevice::ReadOnly | QIODevice::Text)) {
        this->statusBar()->showMessage(file.readAll());
        this->setWindowTitle(fileName);
        }

    }
}




void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if(fileName.isEmpty())
        return;
    if(QFile::exists(fileName)) {
        //File exists already, make Backup Copy
        QString bakName = fileName;
        bakName.append("~bak");
        QFile::copy(fileName, bakName);
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Save Error"), tr("Could not open File %1 for writing: %2 ").arg(fileName).arg(file.errorString()));
        return;
    }

    file.write("Test");
    statusBar()->showMessage(tr("Saving successful"));
    this->setWindowTitle(QString(WINDOW_TITLE) + " - "+ fileName);
}

//! Saves figures to currentFileName
/*!
  All figures from the Model are saved into currentFileName, using the saveBinFile() Method.
  If currentFileName is empty, the FileSaveAs() Method is called to select a Filename first.
  \sa FileSaveAs()
  \sa saveBinFile()
*/
void MainWindow::FileSave() {
    qDebug()<<"FileSave()";
    if(currentFileName.isEmpty()) {
        FileSaveAs(); //First select a Filename
    }
    else {
        saveBinFile(currentFileName);
    }
}

//! Saves figures to a File, creates a backup if file exists
/*!
  Displays a Save-Dialog to select a fileName. If the file already exists, a backup with the extension "~bak" is created.
  All figures from the Model are saved into fileName, using the saveBinFile() Method.
\sa FileSave()
\sa saveBinFile()
*/
void MainWindow::FileSaveAs() {
    qDebug()<<"FileSaveAs()";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Bin File"), QString() ,tr("Qube-Data-Files (*.qdf)"));
    if(fileName.isEmpty())
        return;
    if(QFile::exists(fileName)) {
        //File exists already, make Backup Copy
        QString bakName = fileName;
        bakName.append("~bak");
        QFile::copy(fileName, bakName);
    }
    saveBinFile(fileName);
}

//! Saves Binary Data to fileName
/*!
**  Exports all Data from the Model to a binary File.
**
**    Format:
**      MAGICNUMBER<<VERSION<<numRows
**      for every figure: out << preview << states << description << time
**
\param[in] fileName - QString where to save the Data
\sa openBinFile()
*/
void MainWindow::saveBinFile(QString fileName) {

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Save Error"), tr("Could not open File %1 for writing: %2 ").arg(fileName).arg(file.errorString()));
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);

    //If file empty, put magic number at the beginning
    if(file.size()==0) {
        out<<(quint32)MAGICNUMBER;
        out<<(quint32)VERSION;
    }


    /* Export Model */
    int numRows = model->rowCount();
    out << numRows;

    QProgressBar *tempProgress = new QProgressBar;
    this->statusBar()->addWidget(tempProgress);

    for(int figure = 0; figure < numRows; figure++)
    {
        QPixmap preview(100,100);
        QBitArray states;
        QString description;
        int time;
        GetFigureData(figure, preview, states, description, time);
        out << preview << states << description << time;

        int percentage = (int)((((float)figure + 1.0) / numRows) * 100);
        tempProgress->setValue(percentage);
    }
    /* -- ende EXPORT */

    delete(tempProgress);
    this->statusBar()->showMessage(tr("%1 Figures saved to File %2").arg(numRows).arg(fileName.section('/',-1)));
    this->currentFileName = fileName;
    this->setWindowTitle(QString(WINDOW_TITLE) + " - "+ fileName);
}

//! Creates a new File
void MainWindow::FileNew() {
    /* Delete Old Data */
    model->removeRows(0,this->model->rowCount());

    this->FigureAdd();
    this->currentFileName = "";
    this->setWindowTitle(QString(WINDOW_TITLE).append(" - <new>"));

}



//! Opens a data-file
/*! Uses openBinFile(false) method
\sa openBinFile()
\sa FileOpen()
*/
void MainWindow::FileOpen() {
    openBinFile(false);
}

//! Appends a data-file to the end of the list
/*! Uses openBinFile(true) method
\sa openBinFile()
\sa FileOpen()
*/
void MainWindow::FileAppend() {
    openBinFile(true);
}

//! Reads Binary Data from fileName and fills the tableView with it
/*!
  Imports Binary data from fileName to the Model
    Format:
      MAGICNUMBER<<VERSION<<numRows
      for every figure: out << preview << states << description << time
    The Method also checks if the MAGICNUMBER and VERSION of the loaded file are compatible with this Software Version
\param[in] appendMode true - the figures from the file are appended to the end of the list
                      false - the list is cleared and filled with the loaded figures
\sa saveBinFile()
*/
void MainWindow::openBinFile(bool appendMode) {
    QString fileName;

    if(appendMode)
        fileName = QFileDialog::getOpenFileName(this, tr("Append File"), "", tr("Qube-Data-Files (*.qdf)"));
    else
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Qube-Data-Files (*.qdf)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open( QIODevice::ReadOnly)) {

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);

            quint32 magic, version;
            in >> magic;
            if((quint32)MAGICNUMBER != magic) {
                qDebug()<<"LoadError, wrong MAGICnumber";
                this->statusBar()->showMessage(tr("Error, wrong file format"));
                return;
            }

            in >> version;
            if((quint32)VERSION != version) {
                qDebug()<<"LoadError, wrong version number";
                this->statusBar()->showMessage(tr("Error, wrong file format"));
                return;
            }

            /* Import Model */
            int numRows;
            in >> numRows;

            int totalCount = model->rowCount()-1 + numRows;
            if(totalCount > (int)MAX_ALLOWED_FIGURES) {
                QMessageBox msgBox;
                msgBox.setWindowTitle(tr("Too many Figures in File"));
                msgBox.setInformativeText( tr("The file %1 contains too many Figures. A maximum of %2 Figures is allowed. The Rest (%3 Figures) will be clipped. Do you want to continue?").arg(fileName.section('/',-1)).arg((int)MAX_ALLOWED_FIGURES).arg((int)totalCount-MAX_ALLOWED_FIGURES+1));
                msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
                msgBox.setDefaultButton(QMessageBox::Yes);
                msgBox.setIcon(QMessageBox::Warning);
                int ret = msgBox.exec();

                if(ret == QMessageBox::No) {
                    this->statusBar()->showMessage(tr("Canceled opening File"));
                    return;
                }
            }

            int offset = 0; //Offset for Insertion
            /*Open*/
            if(appendMode==false) {
                /* Delete Old Data */
                model->removeRows(0,this->model->rowCount());
            }
            /*Append*/
            else {
                offset = this->model->rowCount();
            }

            qDebug() << numRows;

            QProgressBar *tempProgress = new QProgressBar;
            this->statusBar()->addWidget(tempProgress);

            for(int figure = 0; figure < numRows; figure++)
            {
                QPixmap preview(100,100);
                QBitArray states;
                QString description;
                int time;

                in >> preview >> states >> description >> time;
                CreateFigureFromData(figure+offset, preview, states, description, time);

                int percentage = (int)((((float)figure + 1.0) / numRows) * 100 );
                tempProgress->setValue(percentage);
            }
            /* end Import */

            delete(tempProgress);

            //If it was opened, not appended, update fileNames
            if(appendMode == false) {
                this->statusBar()->showMessage(tr("%1 Figures loaded from File %2").arg(numRows).arg(fileName.section('/',-1)));
                this->setWindowTitle(QString(WINDOW_TITLE) + " - "+ fileName);
                this->currentFileName = fileName;
                qDebug()<<"CurrentFile"<<this->currentFileName;
            }
            else {
                this->statusBar()->showMessage(tr("%1 Figures appended from File %2").arg(numRows).arg(fileName.section('/',-1)));
            }
        }
    }
}

//! Selects all Figures in the List
void MainWindow::selectAll() {
    qDebug()<<"Select All";
     QModelIndex parent = QModelIndex();
     QModelIndex topLeft = model->index(0, 0, parent);
     QModelIndex bottomRight = model->index(model->rowCount(parent)-1, model->columnCount(parent)-1, parent);

     QItemSelection selection(topLeft, bottomRight);
     selectionModel->select(selection, QItemSelectionModel::Select);
}

// Öffne Settings dialog und übergebe aktuelle Settings der Cubes
void MainWindow::openSettingsDialog() {
    settingsDialog->getGLSettingsCube(this->GLSettingsCube);
    settingsDialog->getGLSettingsCubePreview(this->GLSettingsCube);
    settingsDialog->exec();
}

// Öffne Times Dialog
void MainWindow::openTimesDialog() {
    timesDialog->exec();
}


//Aktualisiere geänderte Settings und gebe es an Cube weiter
void MainWindow::updateGLSettingsCube(GLSettings newSettings) {
    this->GLSettingsCube = newSettings;
    emit cubeWidget->setGLSettings(newSettings);
}

//Aktualisiere geänderte Settings und gebe es an CubePreview weiter
void MainWindow::updateGLSettingsCubePreview(GLSettings newSettings) {
    this->GLSettingsCubePreview = newSettings;
    emit cubeWidgetPreview->setGLSettings(newSettings);

}




void MainWindow::About() {
    QMessageBox::information(this, tr("About ").append(WINDOW_TITLE),
                             tr("Qube5-Editor allows you to create figures and animations for the LED-Qube5.\n" \
                                "For more information about the LED-Qube5 and this program, \nsee <http://www.qube-solutions.de>\n\n"\
                                "This software has been developed for the company \n"\
                                "'Qube Solutions UG (haftungsbeschränkt)'\n"\
                                "Copyright (C) 2009-2010 Christian Strobel\n"\
                                "\n"\
                                "This program is free software: you can redistribute it and/or modify\n"\
                                "it under the terms of the GNU General Public License as published by\n"\
                                "the Free Software Foundation, either version 3 of the License, or\n"\
                                "(at your option) any later version.\n"\
                                "\n"\
                                "This program is distributed in the hope that it will be useful,\n"\
                                "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
                                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
                                "GNU General Public License for more details.\n"\
                                "\n"\
                                "You should have received a copy of the GNU General Public License\n"\
                                "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"\
                                ));

}

void MainWindow::TimeOut() {

     if(figureIndex < this->model->rowCount()) {

        qDebug()<<"PlayFigur" << figureIndex;


        QPixmap preview(100,100);
        QString description;
        int time;

        GetFigureData(figureIndex, preview, *tempStates, description, time);

        tempStates->detach();
        this->cubeWidget->setStates(tempStates);
        glFinish();
        this->cubeWidget->updateCube();


        selectionModel->select(model->index(figureIndex,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

        int percentage = (int)((((float)figureIndex + 1.0) / this->model->rowCount()) * 100);
        this->playProgressBar->setValue(percentage);

        if(time <= 10) {
            playTimer->setInterval((int)(time*22.5));
        } else {
            playTimer->setInterval((int)(time*90.2));
        }

        figureIndex++;
     }
     else {

         this->statusBar()->removeWidget(playProgressBar);
         playTimer->stop();
         selectionModel->select(model->index(this->figureIndex-1,0, QModelIndex()), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
         figureIndex = 0;
         this->ui->pushButtonFigPlay->setChecked(false);
         this->statusBar()->showMessage(tr("Playing finished"),1000);
     }

}

MainWindow::~MainWindow()
{
   delete ui;
}
