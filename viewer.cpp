#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);

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

void Viewer::loadCallback(bool success){
    if(success)
            changed = false;
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

void Viewer::on_actionNew_triggered()
{
    if(changed){
            QMessageBox msgBox;
            msgBox.setText("The maze has not been modified");
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
}


void Viewer::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                   this,
                   tr("Open File"),
                   "C://",
                   "Maze Project (*.mep);;"
                );
    //Filesystem
    //emit
}


void Viewer::on_actionSave_triggered()
{
    QString fileDir = QFileDialog::getSaveFileName(
                    this,
                    tr("Choose Directory"),
                    "C://",
                    "Maze Project (*.mep);;"
                    );
        changed = false;
        //Filesystem
        //emit
}


void Viewer::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Instruction", "Instruction");
}


void Viewer::on_actionResize_triggered()
{
    //emit resize
}


void Viewer::on_startButton_clicked()
{
    if(gameStarted){
        emit gameStop();
    }else{
        emit gameStart();
    }
}

void Viewer::mousePressEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton){//if mouse left button clicked
        QPoint screenPos = event -> pos();
        blockPos = QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y())/(blockSize+blockOffset));
        emit useToolOn(blockPos);//get mouse position as start point
    }else if(event->button() == Qt::RightButton){
        movePivot = event->pos();
    }
}

void Viewer::mouseMoveEvent(QMouseEvent * event){
    if(event->buttons()&Qt::LeftButton){//if mouse left button clicked and move at same time
        QPoint screenPos = event -> pos();
        if(blockPos != QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y())/(blockSize+blockOffset))){
            blockPos = QPoint((screenPos.x()-drawingPivot.x())/(blockSize+blockOffset), (screenPos.y()-drawingPivot.y())/(blockSize+blockOffset));
            emit useToolOn(blockPos);
        }
    }else{
        drawingPivot += event->pos() - movePivot;
        movePivot = event->pos();
        repaint();
    }
}

void Viewer::wheelEvent(QWheelEvent * event){
    //scale function
    blockSize += event->angleDelta().y()/120;
    if(blockSize<15){
        blockOffset = 0;
    }else{
        blockOffset = 1;
    }
    repaint();
}


void Viewer::paintEvent(QPaintEvent *){
    QPixmap scene(ui->editorScene->width(), ui->editorScene->height());
    scene.fill(QColor("transparent"));
    QPainter painter(&scene);
    int pos = blockSize+blockOffset;
    for(int i = 0; i < maze->getWidth(); i++){
        for(int j = 0; j < maze->getHeight(); j++){
            QColor c;
            if(maze->getObject(i, j) == maze->wall){
                c = wallColor;
            }else if(maze->getObject(i, j) == maze->coin){
                c = coinColor;
            }else if(maze->getObject(i, j) == maze->start){
                c = startColor;
            }else if(maze->getObject(i, j) == maze->space){
                c = spaceColor;
            }
            painter.fillRect(i * pos + drawingPivot.x(), j * pos + drawingPivot.y(), blockSize, blockSize, c);
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

}


void Viewer::on_DoButton_clicked()
{
    addItemToActionList("Do");
    emit addDo();
}


void Viewer::on_UntilButton_clicked()
{
    addItemToActionList("Until Hit");
    emit addUntilHit();
}


void Viewer::on_RightButton_clicked()
{
    addItemToActionList("Right");
    emit addRight();
}


void Viewer::on_LeftButton_clicked()
{
    addItemToActionList("Left");
    emit addLeft();
}


void Viewer::on_ForwardButton_clicked()
{
    addItemToActionList("Forward");
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

