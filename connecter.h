#ifndef CONNECTER_H
#define CONNECTER_H

#include <QObject>
#include "bot.h"
#include "boteditor.h"
#include "filesystem.h"
#include "gamemode.h"
#include "gamemodeRender.h"
#include "maze.h"
#include "mazeeditor.h"
#include "viewer.h"

class Connecter : public QObject
{
    Q_OBJECT
public:
    Connecter();
    void show();
private:
    Maze editorMaze;
    Maze gamemodeMaze;
    Bot bot;
    BotEditor botEditor;
    FileSystem fileSystem;
    GameMode gameMode;
    GameModeRender gameModeRender;
    MazeEditor mazeEditor;
    Viewer viewer;

    void connect_Viewer_BotEditor();
    void connect_Viewer_FileSystem();
    void connect_Viewer_GameMode();
    void connect_Viewer_GameModeRender();
    void connect_Viewer_MazeEditor();

    void connect_BotEditor_BotEditorRender();
    void connect_GameMode_GameModeRender();

    void connect_FileSystem_GameMode();

    void setMaze();
    void setBot();
};

#endif // CONNECTER_H
