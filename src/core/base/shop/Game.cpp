#include "src/core/shop/game.h"
#include "src/core/shop/game_state.h"
#include "src/core/shop/character.h"
#include <cmath>


class BankAccount;

ExolorGame::Game::Game() : running(true), gameName("Default"), canvas(new GameRenderer::TextCanvas(0, 0)),
                           currentState(nullptr), prevState(nullptr) {
    initCharacters();
    registerCommands();
}

ExolorGame::Game::Game(int canvasWidth, int canvasHeight, std::string name) : canvas(
        new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true), gameName(name), currentState(nullptr),
                                                                              prevState(nullptr), character(nullptr) {
    initCharacters();
    registerCommands();
}

// Destructor
ExolorGame::Game::~Game() {

}

void ExolorGame::Game::addCommand(const std::string &command, const std::function<void(Game *)> consumer) {
    //   commandMap[command] = (consumer);
    commandMap.emplace(command, consumer);
}

std::string ExolorGame::Game::getName() {
    return gameName;
}



void ExolorGame::Game::registerCommands() {
    GameRenderer::TextCanvas *canvas = this->getCanvas();


    if (getCharacter() == nullptr) { //Horrendous logic but will do for now
        addCommand("start", [this, canvas](Game *g) {
            if (getCharacter() == nullptr) {
                //     std::cout << "Starting game..." << std::endl;
                canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
                g->setGameState(new CharacterSelectState(g));
                std::cout << "[Game Started]" << std::endl;
            }
        });

    }


}


// Method to process input and trigger associated consumers
void ExolorGame::Game::processInput(const std::string &input) {


    auto it = commandMap.find(input);
    if (it != commandMap.end()) {
        it->second(this);
    } else {
        if (currentState) {
            currentState->handleInput(this, input);
        } else {
            std::cout << "Command not recognized. Try again." << std::endl;
        }
    }
}

void ExolorGame::Game::update(GameRenderer::TextCanvas *canvas) {

    std::string input;
    std::cout << "Enter a command: ";
    std::cin >> input;


    processInput(input);

    if (currentState) {
        currentState->render(canvas);
        currentState->update(this);
    }


}


void ExolorGame::Game::clean() {
}

void ExolorGame::Game::render() {
    canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
    if (currentState) {

        currentState->render(canvas);
        // Render the canvas after updating its content
    }
    canvas->render();
}

const bool ExolorGame::Game::isRunning() {

    return this->running;
}

void ExolorGame::Game::setRunning(bool val) {

    this->running = val;

}

GameRenderer::TextCanvas *ExolorGame::Game::getCanvas() {

    return canvas;
}

void ExolorGame::Game::setGameState(GameMenu *state) {
    prevState = currentState;

    if (!state) {
        return;
    }


    if (currentState != state) {
        currentState = state;
        std::cout << "Switching GameState.. " << state->getName() << std::endl;
        currentState->initCommands(); // Register commands for the new state
        currentState->init(this); // Initialize the new state
    }
}


void ExolorGame::Game::setCharacter(ExolorGame::Character *character) {

    this->character = character;
}

void ExolorGame::Game::addCharacter(ExolorGame::Character *character) {

    characters.push_back(character);


}

void ExolorGame::Game::initCharacters() {
    addCharacter(new Character("Main", 5000, 0));
    addCharacter(new Character("Villain", 6500, 1));
    addCharacter(new Character("Mentor", 50000, 3));
    addCharacter(new Character("Sidekick", 4500, 2));


}

ExolorGame::Character *ExolorGame::Game::getCharacter() {

    return character;
}


ExolorGame::GameMenu *ExolorGame::Game::getGameState() {
    return currentState;
}

ExolorGame::GameMenu *ExolorGame::Game::getPreviousState() {
    return prevState;
}

// Method to start the game
void ExolorGame::Game::start() {
    //   std::cout << "[Game Started]" << std::endl;
    std::cout << "Type 'start' to start the game." << std::endl;
    //  canvas->drawText({ 0, 0 }, "Type 'start' to start the game.");

    //  std::cout << "Type 'exit' to quit the game." << std::endl;
}


// Helper method for handling user input
void ExolorGame::Game::handleInput(const std::string &input) {


}