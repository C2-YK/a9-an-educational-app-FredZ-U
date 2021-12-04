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
    QObject::connect(&viewer, &Viewer::addDo, &botEditor, &BotEditor::addDo);
    QObject::connect(&viewer, &Viewer::addUntilHit, &botEditor, &BotEditor::addUntilHit);
    QObject::connect(&viewer, &Viewer::addRight, &botEditor, &BotEditor::addRight);
    QObject::connect(&viewer, &Viewer::addLeft, &botEditor, &BotEditor::addLeft);
    QObject::connect(&viewer, &Viewer::addForward, &botEditor, &BotEditor::addForward);

    QObject::connect(&viewer, &Viewer::clearActions, &botEditor, &BotEditor::clearActions);
    QObject::connect(&viewer, &Viewer::deleteAction, &botEditor, &BotEditor::deleteAction);

    QObject::connect(&botEditor, &BotEditor::compiled, &viewer, &Viewer::compiled);
}
void Connecter::connect_Viewer_FileSystem(){

}
void Connecter::connect_Viewer_GameMode(){
    QObject::connect(&viewer, &Viewer::gameStart, &gameMode, &GameMode::start);
    QObject::connect(&viewer, &Viewer::gameStop, &gameMode, &GameMode::stop);
    QObject::connect(&gameMode, &GameMode::winEvent, &viewer, &Viewer::winEvent);
}
void Connecter::connect_Viewer_GameModeRender(){

}
void Connecter::connect_Viewer_MazeEditor(){
    QObject::connect(&viewer, &Viewer::switchToolTo, &mazeEditor, &MazeEditor::switchTool);
    QObject::connect(&viewer, &Viewer::useToolOn, &mazeEditor, &MazeEditor::useToolOn);
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
    viewer.setMaze(&editorMaze);
}
void Connecter::setBot(){
    botEditor.setBot(&bot);
    gameMode.setBot(&bot);

}

void Connecter::show(){
    viewer.show();
}
