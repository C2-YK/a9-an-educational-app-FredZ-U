#include "connecter.h"

Connecter::Connecter()
{
    setMaze();
    setBot();
    connect_Viewer_BotEditor();
    connect_Viewer_FileSystem();
    connect_Viewer_GameMode();
    connect_Viewer_GameModeRender();
    connect_Viewer_MazeEditor();

    connect_GameMode_GameModeRender();
}

void Connecter::connect_Viewer_BotEditor(){

}
void Connecter::connect_Viewer_FileSystem(){

}
void Connecter::connect_Viewer_GameMode(){

}
void Connecter::connect_Viewer_GameModeRender(){

}
void Connecter::connect_Viewer_MazeEditor(){

}

void Connecter::connect_GameMode_GameModeRender(){
    QObject::connect(&gameMode, &GameMode::updatePlayerPosition, &gameModeRender, &GameModeRender::setPlayerPosition);
    QObject::connect(&gameMode, &GameMode::setToSpace, &gameModeRender, &GameModeRender::setToSpace);
    QObject::connect(&gameMode, &GameMode::setPlayerSize, &gameModeRender, &GameModeRender::setPlayerSize);
    QObject::connect(&gameMode, &GameMode::setMazeData, &gameModeRender, &GameModeRender::setMazeData);
    QObject::connect(&gameMode, &GameMode::winEvent, &gameModeRender, &GameModeRender::stopRender);
    QObject::connect(&gameMode, &GameMode::stopEvent, &gameModeRender, &GameModeRender::stopRender);
    QObject::connect(&gameMode, &GameMode::startEvent, &gameModeRender, &GameModeRender::startRender);
}

void Connecter::setMaze(){
    fileSystem.setEditorMaze(&editorMaze);
    gameMode.setMaze(&gamemodeMaze);
    mazeEditor.setMaze(&editorMaze);

}
void Connecter::setBot(){
    botEditor.setBot(&bot);
    gameMode.setBot(&bot);

}

void Connecter::show(){
    viewer.show();
}
