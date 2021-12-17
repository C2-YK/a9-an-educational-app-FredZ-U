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

    connect_FileSystem_GameMode();
    connect_GameMode_GameModeRender();
    gameMode.initGame();
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
    //save and load
    QObject::connect(&viewer, &Viewer::loadMazeToEditor, &fileSystem, &FileSystem::loadMazeToEditor);
    QObject::connect(&viewer, &Viewer::loadMazeToGamemode, &fileSystem, &FileSystem::loadMazeToGamemode);
    QObject::connect(&viewer, &Viewer::saveMazeToFile, &fileSystem, &FileSystem::saveMazeToFile);
    //callback
    QObject::connect(&fileSystem, &FileSystem::saveCallback, &viewer, &Viewer::saveCallback);
    QObject::connect(&fileSystem, &FileSystem::loadToEditorCallback, &viewer, &Viewer::loadToEditorCallback);
    QObject::connect(&fileSystem, &FileSystem::loadToGamemodeCallback, &viewer, &Viewer::loadToGamemodeCallback);

}
void Connecter::connect_Viewer_GameMode(){
    QObject::connect(&viewer, &Viewer::gameStart, &gameMode, &GameMode::start);
    QObject::connect(&viewer, &Viewer::gameStop, &gameMode, &GameMode::stop);
    QObject::connect(&gameMode, &GameMode::winEvent, &viewer, &Viewer::winEvent);
    QObject::connect(&gameMode, &GameMode::winDisplay, &viewer, &Viewer::winDisplay);
}
void Connecter::connect_Viewer_GameModeRender(){
    QObject::connect(&gameModeRender, &GameModeRender::updateScene, &viewer, &Viewer::updateScene);
}
void Connecter::connect_Viewer_MazeEditor(){
    QObject::connect(&viewer, &Viewer::switchToolTo, &mazeEditor, &MazeEditor::switchTool);
    QObject::connect(&viewer, &Viewer::useToolOn, &mazeEditor, &MazeEditor::useToolOn);
    QObject::connect(&viewer, &Viewer::reset, &mazeEditor, &MazeEditor::reset);
    QObject::connect(&mazeEditor,&MazeEditor::success,&viewer,&Viewer::changedCallBack);
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

void Connecter::connect_FileSystem_GameMode(){
    QObject::connect(&fileSystem, &FileSystem::refreshGamemode, &gameMode, &GameMode::initGame);
}

void Connecter::setMaze(){
    fileSystem.setEditorMaze(&editorMaze);
    fileSystem.setGamemodeMaze(&gamemodeMaze);
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
