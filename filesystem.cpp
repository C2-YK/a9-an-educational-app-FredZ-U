#include "filesystem.h"
#include <QDebug>

FileSystem::FileSystem()
{

}

void FileSystem:: setEditorMaze(Maze * target)
{
    editorMaze = target;
}

void FileSystem::setGamemodeMaze(Maze * target){
    gamemodeMaze = target;
}

bool FileSystem::loadMazeToEditor(QString filepath)
{
    QFile loadFile(filepath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open the file.");
        emit loadToEditorCallback(false);
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    mazeReader(loadDoc.object(),*editorMaze);
    emit loadToEditorCallback(true);
    return true;
}

bool FileSystem::loadMazeToGamemode(QString filepath){
    QFile loadFile(filepath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open the file.");
        emit loadToEditorCallback(false);
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    mazeReader(loadDoc.object(),*gamemodeMaze);
    qDebug()<<"load success";
    emit refreshGamemode();
    emit loadToEditorCallback(true);
    return true;
}

bool FileSystem::saveMazeToFile(QString filename)
{
    QFile saveFile(filename);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open the file in a writing way");
        emit saveCallback(false);
        return false;
    }

    QJsonObject mazeObject;
    mazeWriter(mazeObject);
    QJsonDocument saveDoc(mazeObject);
    saveFile.write(saveDoc.toJson());
    emit saveCallback(true);
    return true;
}

void FileSystem:: mazeWriter(QJsonObject &json)
{
    json["height"] = editorMaze->getHeight();
    json["width"] = editorMaze->getWidth();
    QList<int> map(editorMaze->getMap());
    QString mapInfo;
    foreach(int info,map)
    {
        mapInfo.append(QString::number(info));
        mapInfo.append(" ");
    }
    json["info"] = mapInfo;
}

void FileSystem:: mazeReader(const QJsonObject &json, Maze& maze)
{
    int height = json["height"].toInt();
    int width = json["width"].toInt();
    QString s = json["info"].toString();
    QStringList infoList = s.split(QRegularExpression("\\W+"),Qt::SkipEmptyParts);
    QList<int> map;
    foreach(QString mapInfo,infoList)
    {
        map.append(mapInfo.toInt());
    }
    maze = Maze(height,width,map);
}
