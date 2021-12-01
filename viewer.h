#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>


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
public slots:
    void saveCallback(bool success);
    void loadCallback(bool success);
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
    bool changed;
};
#endif // VIEWER_H
