#include "filesystem.h"

FileSystem::FileSystem()
{

}

bool FileSystem::loadMazeFromFile(QString filepath)
{
    QFile loadFile(filepath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open the file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    //mazeReader(loadDoc.object(),*maze);
    return true;
}

bool FileSystem::saveMazeToFile(QString filename)
{
    QFile saveFile(filename);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open the file in a writing way");
        return false;
    }

    QJsonObject mazeObject;
    mazeWriter(mazeObject);
    QJsonDocument saveDoc(mazeObject);
    saveFile.write(saveDoc.toJson());
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
