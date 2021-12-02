#include "filesystem.h"

FileSystem::FileSystem()
{

}

void FileSystem:: setMaze(Maze * target)
{
    maze = target;
}

bool FileSystem::loadMazeFromFile(QString filepath)
{
    QFile loadFile(filepath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open the file.");
        emit loadCallback(false);
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    mazeReader(loadDoc.object(),*maze);
    emit loadCallback(true);
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
    json["height"] = maze->getHeight();
    json["width"] = maze->getWidth();
    QList<int> map(maze->getMap());
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
