#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maze.h"

using namespace std;

using namespace sf;


class Menu {
public:

    // Fonts and Text
    int selected;
    Font font;
    Text option_text[5];
    Texture back;
    Sprite background;
    Texture op[5];
    Sprite options[5];
    Maze m;


    //HighScores high;
    Menu();
  //  Menu(string);
    void show_instructions(RenderWindow& window);
    char* get_name();
    string score_to_string(int score);
    void show_highscore(RenderWindow& window);
    void game_over();
    int display_menu(RenderWindow& window1);
    //void game_end();
    virtual ~Menu() {}
};


