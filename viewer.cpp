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

void Viewer::addItemToactionList(){

}


void Viewer::paintEvent(QPaintEvent *){
    QPainter painter(ui->tab);
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
}
