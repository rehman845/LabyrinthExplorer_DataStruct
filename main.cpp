#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
using namespace std;
using namespace sf;

int main() {
    Music music;
    if (!music.openFromFile("Gorgeous.ogg"))
        return -1; // error
    music.play();
    system("pause");

    RenderWindow window1(VideoMode(WINDOW_WIDTH, 600), "ENCHANTED LABYRINTH EXPLORER");
    Menu m;
    m.display_menu(window1);
}