#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QListWidgetItem>
#include <QMouseEvent>

#include "maze.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();
    void paintEvent(QPaintEvent *);
    void setMaze(Maze*);
public slots:
    void saveCallback(bool success);
    void loadCallback(bool success);
    void updateScene(const QPixmap& scene);
signals:
    void resize(int height, int width);
    void switchToolTo(int toolIndex);
    void useToolOn(QPoint position);
    void saveSprite(QString filename);
    void loadJason(QString filepath);

private slots:


    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void on_actionResize_triggered();

    void on_startButton_clicked();

private:
    Ui::Viewer *ui;
    Maze* maze;
    bool changed;
    QPoint drawingPivot = QPoint(160,80);
    QPoint movePivot;
    QPoint blockPos;
    QList<QListWidgetItem *> actionList;
    int blockSize = 20;
    int blockOffset = 1;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void addItemToactionList();

    const QColor wallColor = QColor(0, 0, 0, 255);
    const QColor coinColor = QColor(255, 255, 0, 255);
    const QColor spaceColor = QColor(255, 255, 255, 255);
    const QColor startColor = QColor(0, 255, 255, 255);
    const QColor playerColor = QColor(0, 0, 255, 255);
};
#endif // VIEWER_H
