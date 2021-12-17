#include "viewer.h"
#include "ui_viewer.h"
#include <QTabWidget>

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);
    menubarHeight = ui->menubar->height();
    ui->winLabel->setPixmap(QPixmap(":/icon/res/win.png").scaled(ui->winLabel->width(),ui->winLabel->height(), Qt::KeepAspectRatio));
    ui->winLabel->setVisible(false);

}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::setMaze(Maze * m){
    maze = m;
}

void Viewer::saveCallback(bool success){
    if(success)
            changed = false;
}

void Viewer::loadToEditorCallback(bool success){
    if(success)
        changed = false;
}

void Viewer::loadToGamemodeCallback(bool success){
    if(success){

    }

}

void Viewer::updateScene(const QPixmap& scene){
    int w = ui->gameScene->width();
    int h = ui->gameScene->height();
    ui->gameScene->setPixmap(scene.scaled(w,h,Qt::KeepAspectRatio));
    repaint();
}

void Viewer::compiled(bool success){
    if(success){
        ui->startButton->setDisabled(true);
    }else{
        ui->startButton->setDisabled(false);
    }
}

void Viewer::winEvent(){

}

void Viewer::winDisplay(bool show){
    ui->winLabel->setVisible(show);
}


void Viewer::on_actionNew_triggered()
{
    if(changed){
            QMessageBox msgBox;
            msgBox.setText("The maze has been modified");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Save:
                  on_actionSave_triggered();
                  break;
              case QMessageBox::Discard:

                  break;
              case QMessageBox::Cancel:
                  return;
              default:
                  // should never be reached
                return;
            }

    }
    changed = false;
    emit reset();
}

void Viewer::on_actionSave_triggered()
{
    if(maze->hasSolution())
    {
        QString fileDir = QFileDialog::getSaveFileName(
                        this,
                        tr("Choose Directory"),
                        "C://",
                        "Maze Project (*.mep);;"
                        );
        changed = false;
        emit saveMazeToFile(fileDir);
    }
    else
    {
        QMessageBox msgBox;
        changed = false;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The maze has no solution. Before saving the maze, please be sure there exists at least one solution.");
        msgBox.exec();
    }

}

void Viewer::on_actionLoad_to_Editor_triggered(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Maze Project (*.mep);;"

                );
    changed = false;
    emit loadMazeToEditor(filename);
}

void Viewer::on_actionLoad_to_Game_triggered(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Maze Project (*.mep);;"

                );
    qDebug()<<filename;
    emit loadMazeToGamemode(filename);
}

void Viewer::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Instruction", "This game has two modes.\n1.Maze Editor is used for the users to draw the custom maze and save the maze in their machine.\n2.Game mode is used for the users to load the maze and add a list of commands to tell the robot to move following commands. If the robot collects all the gold, it will win the game. Among them, the most difficult to understand is do and until. When the player chooses do, it means the robot starts to operate, but when chooses until, the robot stops operating, so do and until should be the same number, otherwise an error will be reported.");
}


void Viewer::mousePressEvent(QMouseEvent * event){
    // in the maze editor tab
    if(currentTabIndex == 0)
    {
        if(event->button() == Qt::LeftButton){//if mouse left button clicked
            QPoint screenPos = event -> pos();
            blockPos = QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y()-menubarHeight)/(blockSize+blockOffset));
            emit useToolOn(blockPos);//get mouse position as start point
        }else if(event->button() == Qt::RightButton){
            movePivot = event->pos();
        }
    }
    // in the game windows tab
    if(currentTabIndex == 1)
    {

    }
}

void Viewer::mouseMoveEvent(QMouseEvent * event){
    // in the maze editor tab
    if(currentTabIndex == 0)
    {
        if(event->buttons()&Qt::LeftButton){//if mouse left button clicked and move at same time
            QPoint screenPos = event -> pos();
            if(blockPos != QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y()-menubarHeight)/(blockSize+blockOffset))){
                blockPos = QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y()-menubarHeight)/(blockSize+blockOffset));
                emit useToolOn(blockPos);
            }
        }else{
            drawingPivot += event->pos() - movePivot;
            movePivot = event->pos();
            repaint();
        }
    }
    // in the game windows tab
    if(currentTabIndex == 1)
    {

    }
}

void Viewer::wheelEvent(QWheelEvent * event){
    // in the maze editor tab
    if(currentTabIndex == 0)
    {
        //scale function
        blockSize += event->angleDelta().y()/120;
        if(blockSize<15){
            blockOffset = 0;
        }else{
            blockOffset = 1;
        }
        repaint();
    }
}


void Viewer::paintEvent(QPaintEvent *){
    QPixmap scene(ui->editorScene->width(), ui->editorScene->height());
    scene.fill(QColor("transparent"));
    QPainter painter(&scene);
    int pos = blockSize+blockOffset;
    QPixmap pixmap;
    for(int i = 0; i < maze->getWidth(); i++){
        for(int j = 0; j < maze->getHeight(); j++){
            if(maze->getObject(i, j) == maze->wall){
                pixmap = *wallPix;
            }else if(maze->getObject(i, j) == maze->coin){
                pixmap = *coinPix;
            }else if(maze->getObject(i, j) == maze->start){
                pixmap = *robotPix;
            }else if(maze->getObject(i, j) == maze->space){
                pixmap.fill(spaceColor);
                pixmap = *blockPix;
            }
            painter.drawPixmap(i * pos + drawingPivot.x(), j * pos + drawingPivot.y(), blockSize, blockSize, pixmap);
        }
    }
    ui->editorScene->setPixmap(scene);
}

void Viewer::on_coinButton_clicked()
{
    emit switchToolTo(tool_coin);
}


void Viewer::on_wallButton_clicked()
{
    emit switchToolTo(tool_wall);
}


void Viewer::on_spaceButton_clicked()
{
    emit switchToolTo(tool_space);
}


void Viewer::on_startPointButton_clicked()
{
    emit switchToolTo(tool_start);
}


void Viewer::on_tabWidget_tabBarClicked(int index)
{
    currentTabIndex = index;
}


void Viewer::on_DoButton_clicked()
{
    addItemToActionList("Do {");
    emit addDo();
}


void Viewer::on_UntilButton_clicked()
{
    addItemToActionList("Until Hit }");
    emit addUntilHit();
}


void Viewer::on_RightButton_clicked()
{
    addItemToActionListWithIcon(QIcon(*rightArrowPix),"Right");
    emit addRight();
}


void Viewer::on_LeftButton_clicked()
{
    addItemToActionListWithIcon(QIcon(*leftArrowPix),"Left");
    emit addLeft();
}


void Viewer::on_ForwardButton_clicked()
{
    addItemToActionListWithIcon(QIcon(*forwardArrowPix), "Forward");
    emit addForward();
}

void Viewer::addItemToActionList(QString name){
    QListWidgetItem *item = new QListWidgetItem;
    item->setData(0, name);
    item->setData(1, actionList.size());
    ui->actionList->addItem(item);
    ui->actionList->setCurrentItem(item);
    actionList.append(item);
}

void Viewer::addItemToActionListWithIcon(QIcon pic, QString name){
    QListWidgetItem *item = new QListWidgetItem;
    item->setData(0, name);
    item->setData(1, actionList.size());
    item->setIcon(pic);
    ui->actionList->addItem(item);
    ui->actionList->setCurrentItem(item);
    actionList.append(item);
}

void Viewer::on_deleteButton_clicked()
{
    if(actionList.size() == 0){
        return;
    }
    int id = ui->actionList->currentItem()->data(1).toInt();
    for(int i = id; i < actionList.size() - 1; i++){
        actionList[i] = actionList[i + 1];
    }
    actionList.pop_back();
    emit deleteAction(id);
    delete ui->actionList->currentItem();
}


void Viewer::on_cleanButton_clicked()
{
    actionList = QList<QListWidgetItem *>();
    ui->actionList->clear();
    emit clearActions();
}


void Viewer::on_startButton_clicked(bool gameStarted)
{
    if(checked && gameStarted == false){
        ui->startButton->setText("Stop");
        ui->startButton->setStyleSheet("background-color :red");
        gameStarted = true;
        checked = false;
        emit gameStart();
    }
    else{
        ui->startButton->setText("Start");
         ui->startButton->setStyleSheet("background-color :green");
        checked = true;
        gameStarted = false;
        winDisplay(false);
        emit gameStop();
    }
}


void Viewer::on_Level1Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level1.mep");
}


void Viewer::on_Level2Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level2.mep");
}


void Viewer::on_Level3Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level3.mep");
}


void Viewer::on_Level4Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level4.mep");
}


void Viewer::on_Level5Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level5.mep");
}


void Viewer::on_Level6Button_clicked()
{
    emit loadMazeToGamemode(":/ExampleLevels/levels/Level6.mep");
}

void Viewer::updateEditor(){
    changed = true;
}
