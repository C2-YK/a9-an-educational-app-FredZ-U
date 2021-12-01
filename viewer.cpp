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

}

void Viewer::loadCallback(bool success){

}

void Viewer::on_actionNew_triggered()
{

}


void Viewer::on_actionOpen_triggered()
{

}


void Viewer::on_actionSave_triggered()
{
    QString fileDir = QFileDialog::getSaveFileName(
                    this,
                    tr("Choose Directory"),
                    "C://",
                    "Maze Editor Project (*.mep);;"
                    );
        changed = false;
}


void Viewer::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Instruction", "Instruction here");
}


void Viewer::on_actionResize_triggered()
{

}


void Viewer::on_startButton_clicked()
{

}


void Viewer::paintEvent(QPaintEvent *){

}
