#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDebug>

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
    void loadToEditorCallback(bool success);
    void loadToGamemodeCallback(bool success);//to do
    void updateScene(const QPixmap& scene);
    void compiled(bool success);
    void winEvent();
signals:
    void resize(int height, int width);
    void switchToolTo(int toolIndex);
    void useToolOn(QPoint position);
    void saveMazeToFile(QString filename);
    void loadMazeToEditor(QString filepath);
    void loadMazeToGamemode(QString filepath);//todo
    void addDo();
    void addUntilHit();
    void addRight();
    void addLeft();
    void addForward();
    void deleteAction(int index);
    void clearActions();
    void gameStart();
    void gameStop();

private slots:


    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void on_actionResize_triggered();

    void on_startButton_clicked();

    void on_coinButton_clicked();

    void on_wallButton_clicked();

    void on_spaceButton_clicked();

    void on_startPointButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_DoButton_clicked();

    void on_UntilButton_clicked();

    void on_RightButton_clicked();

    void on_LeftButton_clicked();

    void on_ForwardButton_clicked();

    void on_deleteButton_clicked();

    void on_cleanButton_clicked();

private:
    Ui::Viewer *ui;
    Maze* maze;
    bool changed;
    bool gameStarted = false;
    QPoint drawingPivot = QPoint(160,80);
    QPoint movePivot;
    QPoint blockPos;
    QList<QListWidgetItem *> actionList;
    int blockSize = 20;
    int blockOffset = 1;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void addItemToActionList(QString name);

    int tool_space = 0;
    int tool_wall = 1;
    int tool_coin = 2;
    int tool_start = 3;
    // in the maze editor tab, index = 0;
    // in the game windows tab, index = 1.
    int currentTabIndex = 0;

    const QColor wallColor = QColor(0, 0, 0, 255);
    const QColor coinColor = QColor(255, 255, 0, 255);
    const QColor spaceColor = QColor(255, 255, 255, 255);
    const QColor startColor = QColor(0, 255, 255, 255);
    const QColor playerColor = QColor(0, 0, 255, 255);

    const QImage *wallImg = new QImage(":/icon/res/wall.png");
    const QImage *coinImg = new QImage(":/icon/res/coin.png");
    const QImage *Pic = new QImage(":/icon/res/wall.png");
    const QImage *robotImg = new QImage(":/icon/res/wall.png");

    const QPixmap *wallPix = new QPixmap(":/icon/res/wall.png");
    const QPixmap *coinPix = new QPixmap(":/icon/res/coin.png");
    const QPixmap *Pix = new QPixmap(":/icon/res/wall.png");
    const QPixmap *robotPix = new QPixmap(":/icon/res/robot.png");

    int menubarHeight;
};
#endif // VIEWER_H
