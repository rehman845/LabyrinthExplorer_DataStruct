#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <random>
//#include "menu.h"
#include "Food.h"
#include "AVL.h"
using namespace std;
using namespace sf;

// Maze parameters
const int Mazewidth = 60;
const int MAZE_HEIGHT = 40;
const int Cellsize = 10;

// Window parameters
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

// Cell status
enum class CellStatus { VISITED, UNVISITED };

// Direction offsets for neighboring cells
const vector<pair<int, int>> DIRS = {
    {0, -1}, // Up
    {0, 1},  // Down
    {-1, 0}, // Left
    {1, 0}   // Right
};


class Inventory {
public:
    Food* food;
    Inventory(Food* fd):food(fd) {}
    bool operator==(Inventory i) {
        if (!food && !i.food) return true;
        if(food && i.food)
            return this->food->FoodScore == i.food->FoodScore;
        
        return false;
    }
    bool operator<(Inventory i) {
        //if (!food && !i.food) return true;
        if (food && i.food)
            return this->food->FoodScore < i.food->FoodScore;

        return false;
    }
};

template<typename T>
void InOrderTraversal(Node<T>* ptr, RenderWindow& window) {
    if (!ptr) return;
    InOrderTraversal(ptr->left,window);
    window.draw(ptr->data->food->spr);
    InOrderTraversal(ptr->right,window);
}


class Maze {
public:
    Texture playerTexture;
    Sprite playerSprite;
    int Score = 0;
    AVL<Inventory*> inv;

    Maze() {
        // Initialize maze grid
        grid.resize(MAZE_HEIGHT, vector<CellStatus>(Mazewidth, CellStatus::UNVISITED));

        // Generate maze
        generateMaze();
        for (int i = 0; i < numOfFoods; i++) {
            bool flag = true;
            foods[i] = new Food;
            int x = rand() % Mazewidth;
            int y = rand() % MAZE_HEIGHT;
            foods[i]->setPosition((WINDOW_WIDTH - Mazewidth * Cellsize) / 2 + x * Cellsize, (WINDOW_HEIGHT - MAZE_HEIGHT * Cellsize) / 2 + y * Cellsize);;
            for (int j = 0; j < i; j++) {
                if (foods[j]->spr.getPosition().x == foods[i]->spr.getPosition().x && foods[j]->spr.getPosition().y == foods[i]->spr.getPosition().y) {
                    i--;
                    flag = false;
                    //delete foods[i];
                    break;
                }
            }
            if (!flag) continue;
            for (int y = 0; y < MAZE_HEIGHT; ++y) {
                for (int x = 0; x < Mazewidth; ++x) {
                    if (grid[y][x] == CellStatus::UNVISITED) {
                        RectangleShape wall(Vector2f(Cellsize, Cellsize));
                        int xPos = (WINDOW_WIDTH - Mazewidth * Cellsize) / 2 + x * Cellsize;
                        int yPos =(WINDOW_HEIGHT - MAZE_HEIGHT * Cellsize) / 2 + y * Cellsize;
                        while (foods[i]->spr.getPosition().x == xPos && foods[i]->spr.getPosition().y == yPos) {
                            foods[i]->spr.move(Cellsize,0);
                        }
                    }
                }
            }
            foods[i]->FoodScore = rand() % 50;
        }


        // Set random player position
        setRandomPlayerPosition();
        playerTexture.loadFromFile("img/PNG/PLAYER/player_image.png");
        playerSprite.setTexture(playerTexture);
        playerSprite.setScale(0.7f, 0.4f);
    }

    void StartMaze(RenderWindow& window) {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                else if (event.type == Event::KeyPressed) {
                    movePlayer(event.key.code);
                }
            }
            draw(window);
        }
    }
    
    void draw(RenderWindow& window) {
        window.clear(Color::Black);

        RectangleShape background(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        background.setPosition(0, 0);
        background.setFillColor(Color::White);
        window.draw(background);

        // Draw maze walls
        for (int y = 0; y < MAZE_HEIGHT; ++y) {
            for (int x = 0; x < Mazewidth; ++x) {
                if (grid[y][x] == CellStatus::UNVISITED) {
                    RectangleShape wall(Vector2f(Cellsize, Cellsize));
                    wall.setPosition((WINDOW_WIDTH - Mazewidth * Cellsize) / 2 + x * Cellsize, (WINDOW_HEIGHT - MAZE_HEIGHT * Cellsize) / 2 + y * Cellsize);
                    wall.setFillColor(Color::Black);
                    window.draw(wall);
                }
            }
        }

        // Draw player sprite
        playerSprite.setPosition((WINDOW_WIDTH - Mazewidth * Cellsize) / 2 + playerPosition.x * Cellsize, (WINDOW_HEIGHT - MAZE_HEIGHT * Cellsize) / 2 + playerPosition.y * Cellsize);
        window.draw(playerSprite);

        Font font;
        font.loadFromFile("Fonts/Chunk Five Print.otf");
        Text inventoryText("INVENTORY: ", font, 20);
        inventoryText.setFillColor(Color::Black);
        inventoryText.setPosition(140, 40);
        window.draw(inventoryText);

        // Draw PROGRESS text
        string Prog = "PROGRESS: " + to_string(Score);
        Text progressText(Prog, font, 20);
        progressText.setFillColor(Color::Black);
        progressText.setPosition(600, 40);
        window.draw(progressText);

        for (int i = 0; i < numOfFoods; i++) {
            if(foods[i])
                foods[i]->draw(window);
        }
        InOrderTraversal(inv.root, window);

        if (Score >= 100)
        {
            //Menu p("");
            //p.game_end();
            //window.close();
        }
        window.display();
    }

    int Prevposx = 280, Prevposy = 50;
    void PlayerFoodCollision() {
        for (int i = 0; i < numOfFoods; i++) {
            if (foods[i]) {
                if (foods[i]->spr.getPosition().x == (WINDOW_WIDTH - Mazewidth * Cellsize) / 2 + playerPosition.x * Cellsize && foods[i]->spr.getPosition().y == (WINDOW_HEIGHT - MAZE_HEIGHT * Cellsize) / 2 + playerPosition.y * Cellsize) {
                    Score += foods[i]->FoodScore;
                    foods[i]->spr.setPosition(Prevposx,Prevposy);
                    Prevposx+=10;
                    inv.insert(new Inventory(foods[i]));

                    foods[i] = NULL;
                    cout << "score = " << Score << endl;
                }
            }
        }

    }
    void movePlayer(Keyboard::Key key) {
        int dx = 0, dy = 0;
        switch (key) {
        case Keyboard::Up:
            dy = -1;
            break;
        case Keyboard::Down:
            dy = 1;
            break;
        case Keyboard::Left:
            dx = -1;
            break;
        case Keyboard::Right:
            dx = 1;
            break;
        default:
            break;
        }

        int newX = playerPosition.x + dx;
        int newY = playerPosition.y + dy;

        if (newX >= 0 && newX < Mazewidth && newY >= 0 && newY < MAZE_HEIGHT && grid[newY][newX] == CellStatus::VISITED) {
            playerPosition.x = newX;
            playerPosition.y = newY;
        }
        PlayerFoodCollision();
    }

    vector<vector<CellStatus>> grid;
    Vector2i playerPosition;
    int numOfFoods = 20;
    Food** foods = new Food * [numOfFoods];
    
    void generateMaze() {
        stack<pair<int, int>> stack;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, DIRS.size() - 1);

        int startX = 0;
        int startY = 0;

        stack.push({ startX, startY });
        grid[startY][startX] = CellStatus::VISITED;

        while (!stack.empty()) {
            int x = stack.top().first;
            int y = stack.top().second;
            bool found = false;

            vector<int> directions = { 0, 1, 2, 3 };
            shuffle(directions.begin(), directions.end(), gen);

            for (int i = 0; i < directions.size(); ++i) {
                int dirIndex = directions[i];
                int dx = DIRS[dirIndex].first;
                int dy = DIRS[dirIndex].second;
                int nx = x + dx * 2;
                int ny = y + dy * 2;

                if (nx >= 0 && nx < Mazewidth && ny >= 0 && ny < MAZE_HEIGHT &&
                    grid[ny][nx] == CellStatus::UNVISITED) {
                    grid[y + dy][x + dx] = CellStatus::VISITED;
                    grid[ny][nx] = CellStatus::VISITED;
                    stack.push({ nx, ny });
                    found = true;
                    break;
                }
            }

            if (!found) {
                stack.pop();
            }
        }
    }

    void setRandomPlayerPosition() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> disX(0, Mazewidth - 1);
        uniform_int_distribution<> disY(0, MAZE_HEIGHT - 1);

        playerPosition.x = disX(gen);
        playerPosition.y = disY(gen);
        while (grid[playerPosition.x][playerPosition.y] == CellStatus::UNVISITED) {
            playerPosition.x++;
        }
    }
};