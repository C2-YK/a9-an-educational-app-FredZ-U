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

void Viewer::saveCallback(bool success){
    if(success)
            changed = false;
}

void Viewer::loadCallback(bool success){
    if(success)
            changed = false;
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


void Viewer::paintEvent(QPaintEvent *){

}
