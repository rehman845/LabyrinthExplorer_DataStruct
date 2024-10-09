#include <iostream>
#include<SFML/audio.hpp>
#include<SFML/graphics.hpp>
#include "menu.h"
using namespace std;
using namespace sf;
const char title[] = "";


Menu::Menu()
{

    //constructors body
   // back.loadFromFile("./img/backgroundnew.jpg");
    // background.setTexture(back.Texture);
    /*op[0].loadFromFile("img/PNG/UI/buttonBlue.png");
    op[1].loadFromFile("img/PNG/UI/buttonGreen.png");
    op[2].loadFromFile("img/PNG/UI/buttonRed.png");
    op[3].loadFromFile("img/PNG/UI/buttonYellow.png");
    op[4].loadFromFile("img/PNG/UI/buttonRed.png");*/
    for (int i = 0, j = 120, k = 5; i < 5; i++, j += 90)
    {
        // options[i].setTexture(op[i].Texture);
        options[i].setPosition(310, j + i * k); //Placing items on menu
        options[i].setScale(1.2, 1.2); //size adjustment
    }
    font.loadFromFile("Fonts/Oswald-Regular.ttf");
    // font.loadFromFile("Fonts/SEASRN__.ttf");
    for (int i = 0; i < 5; i++)
    {
        option_text[i].setFont(font);
        option_text[i].setCharacterSize(30);
        option_text[i].setScale(1.3, 1);
        option_text[i].setFillColor(Color::Black);
        option_text[i].setStyle(Text::Bold);
        option_text[i].setPosition(options[i].getPosition());
        option_text[i].move(0, 5);
    }
    selected = 1;
    option_text[1].setFillColor(Color::Red);
    option_text[0].setString("       RESUME");
    option_text[1].setString("     NEW GAME");
    option_text[2].setString("  INSTRUCTIONS");
    option_text[3].setString("    HIGH SCORE");
    option_text[4].setString("          EXIT");
}
//
//Menu::Menu(string over)
//{
//    over = "";
//}

void Menu::show_instructions(RenderWindow& window)
{
    Texture local_back;
    Sprite backg;
    local_back.loadFromFile("img/instructions.jpg");
    backg.setTexture(local_back);
    Texture arr[2];
    Sprite arrows[2];
    arr[0].loadFromFile("img/PNG/UI/arrow keys.png");
    arrows[0].setTexture(arr[0]);
    arrows[0].move(0, 400);
    arrows[0].setScale(0.5, 0.5);

    Text instruct[5];
    for (int i = 0; i < 5; i++)
    {
        instruct[i].setFont(font);
        instruct[i].setCharacterSize(35);
        instruct[i].setFillColor(Color::Black);
        instruct[i].setStyle(Text::Bold);
    }
    instruct[0].move(300, 500);
    instruct[0].setString("USE ARROW KEYS TO");
    instruct[1].move(330, 550);
    instruct[1].setString("MOVE THE PAYER.");
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
            {

                return;

            }
            else if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                {

                    return;

                }
            }
        }

        // instruct.setString(instructions);
        window.clear(Color::Black); //clears the screen
        window.setMouseCursorVisible(0);
        window.draw(backg);  // setting background
        for (int i = 0; i < 2; i++)
            window.draw(arrows[i]);
        for (int i = 0; i < 5; i++)
            window.draw(instruct[i]);
        window.display();
    }
}

char* Menu::get_name()
{
    Texture backgrd, tex;
    Text enter;
    enter.setFont(font);
    enter.setCharacterSize(30);
    enter.setFillColor(Color::Red);
    enter.setStyle(Text::Bold);
    enter.setString("Enter Name:");
    enter.setPosition(150, 150);
    backgrd.loadFromFile("img/background2.jpg");
    Sprite spr;
    spr.setTexture(backgrd);
    tex.loadFromFile("img/PNG/UI/buttonBlue.png");
    Sprite input;
    input.setTexture(tex);
    input.setPosition(150, 200);
    input.setScale(1.25, 1.5);
    spr.setScale(1.75, 2);
    Text name_input;
    name_input.setFont(font);
    name_input.setCharacterSize(30);
    name_input.setFillColor(Color::Black);
    name_input.setStyle(Text::Bold);
    name_input.setPosition(input.getPosition());
    name_input.move(10, 7);
    srand(time(0));
    Clock clock;
    float timer = 0.0;
    RenderWindow window(VideoMode(600, 500), title);
    char* the_name = new char[13];
    for (int i = 0; i < 13; i++)
        the_name[i] = '\0';
    int i = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        //std::cout << timer << std::endl;
        clock.restart();
        timer += time;
        name_input.setString(the_name);
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::KeyPressed)
            {
                if (i < 12)
                {
                    if (e.key.code == Keyboard::A) the_name[i++] = 'A';
                    else if (e.key.code == Keyboard::B) the_name[i++] = 'B';
                    else if (e.key.code == Keyboard::C) the_name[i++] = 'C';
                    else if (e.key.code == Keyboard::D) the_name[i++] = 'D';
                    else if (e.key.code == Keyboard::E) the_name[i++] = 'E';
                    else if (e.key.code == Keyboard::F) the_name[i++] = 'F';
                    else if (e.key.code == Keyboard::G) the_name[i++] = 'G';
                    else if (e.key.code == Keyboard::H) the_name[i++] = 'H';
                    else if (e.key.code == Keyboard::I) the_name[i++] = 'I';
                    else if (e.key.code == Keyboard::J) the_name[i++] = 'J';
                    else if (e.key.code == Keyboard::K) the_name[i++] = 'K';
                    else if (e.key.code == Keyboard::L) the_name[i++] = 'L';
                    else if (e.key.code == Keyboard::M) the_name[i++] = 'M';
                    else if (e.key.code == Keyboard::N) the_name[i++] = 'N';
                    else if (e.key.code == Keyboard::O) the_name[i++] = 'O';
                    else if (e.key.code == Keyboard::P) the_name[i++] = 'P';
                    else if (e.key.code == Keyboard::Q) the_name[i++] = 'Q';
                    else if (e.key.code == Keyboard::R) the_name[i++] = 'R';
                    else if (e.key.code == Keyboard::S) the_name[i++] = 'S';
                    else if (e.key.code == Keyboard::T) the_name[i++] = 'T';
                    else if (e.key.code == Keyboard::U) the_name[i++] = 'U';
                    else if (e.key.code == Keyboard::V) the_name[i++] = 'V';
                    else if (e.key.code == Keyboard::W) the_name[i++] = 'W';
                    else if (e.key.code == Keyboard::X) the_name[i++] = 'X';
                    else if (e.key.code == Keyboard::Y) the_name[i++] = 'Y';
                    else if (e.key.code == Keyboard::Z) the_name[i++] = 'Z';
                    else if (e.key.code == Keyboard::Space) the_name[i++] = ' ';
                }
                if (e.key.code == Keyboard::BackSpace && i > 0) the_name[--i] = '\0';
                if (e.key.code == Keyboard::Enter)
                {
                    window.close();
                    return the_name;
                }
            }
        }
        window.clear(Color::Black); //clears the screen
        window.setMouseCursorVisible(0);
        window.draw(spr);  // setting background
        window.draw(input);
        window.draw(enter);
        window.draw(name_input);
        window.display();
    }
    return NULL;
}

string Menu::score_to_string(int score)
{
    int size = 0;
    int temp = score;
    while (temp != 0)
    {
        temp /= 10;
        size++;
    }
    char* answer = new char[size + 1];
    answer[size] = '\0';
    for (int i = size - 1; i >= 0; i--)
    {
        answer[i] = (score % 10) + '0';
        score /= 10;
    }
    return answer;
}

void Menu::show_highscore(RenderWindow& window)
{
    Texture boxx;
    Sprite box;
    boxx.loadFromFile("img/PNG/UI/white.png");
    box.setTexture(boxx);
    box.setPosition(250, 20);
    box.setScale(1, 1.5);
    // font.loadFromFile("Fonts/Oswald-Regular.ttf");
    Texture medal_tex[3];
    Sprite medals[3];
    for (int i = 0; i < 3; i++)
    {
        medal_tex[i].loadFromFile("img/PNG/UI/medals.png");
        medals[i].setTexture(medal_tex[i]);
        medals[i].setTextureRect(IntRect(34 * i, 0, 34.33, 43));
    }
    medals[0].setPosition(280, 175);
    medals[1].setPosition(280, 220);
    medals[2].setPosition(280, 270);
    // RenderWindow window(VideoMode(350, 655), title);
  //  Text highnames[high.size], highscores[high.size];
    Text heading;
    Font f;
    f.loadFromFile("Fonts/Pacifico.ttf");
    heading.setFont(f);
    heading.setCharacterSize(35);
    heading.move(5, 15);
    heading.setFillColor(Color::Blue);
    heading.setStyle(Text::Bold);
    heading.setString("HIGHSCORES");
    heading.setPosition(290, 100);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
            {
                // window.close();
                // display_menu();
                return;
            }
            else if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                {
                    // window.close();
                    // display_menu();
                    return;
                }
            }
        }
        window.clear(Color::Black); //clears the screen
        window.setMouseCursorVisible(0);
        window.draw(background);  // setting background
        window.draw(box);
        window.draw(heading);
        for (int i = 0; i < 3; i++)
            window.draw(medals[i]);
        window.display();
    }
}

void Menu::game_over() {
    Texture t;
    t.loadFromFile("img/PNG/UI/game_over.png");
    Sprite spr;
    spr.setTexture(t);
    spr.setPosition(290, 100);
    spr.setScale(2, 2);
    RenderWindow window(VideoMode(900, 600), title);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
        window.clear(Color::Black); //clears the screen
        window.setMouseCursorVisible(0);
        window.draw(background);  // setting background
        window.draw(spr);
        window.display();
    }
}

int Menu::display_menu(RenderWindow& window) {
    // add functionality of all the menu options here
    Texture boxx;
    Sprite box;
    boxx.loadFromFile("img/PNG/UI/box.png");
    box.setTexture(boxx);
    box.setPosition(250, 20);
    box.setScale(1, 1.5);
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game  
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Down)
                {
                    option_text[selected].setFillColor(Color::Black);
                    selected++;
                    if (selected > 4)
                        selected = 0;
                    option_text[selected].setFillColor(Color::Red);
                }
                else if (e.key.code == Keyboard::Up)
                {
                    option_text[selected].setFillColor(Color::Black);
                    selected--;
                    if (selected < 0)
                        selected = 4;
                    option_text[selected].setFillColor(Color::Red);
                }
                else if (e.key.code == Keyboard::Enter)
                {
                    if (selected == 0 || selected == 4)
                    {
                        window.close();
                        return selected;
                    }
                    else if (selected == 1) {
                        m.StartMaze(window);
                    }
                    else if (selected == 2)
                    {
                        show_instructions(window);
                    }
                    else if (selected == 3)
                    {
                        show_highscore(window);
                    }
                }
            }
        }

        window.clear(Color::Black); //clears the screen
        window.setMouseCursorVisible(0);
        window.draw(background);  // setting background
        window.draw(box);
        for (int i = 0; i < 5; i++)
        {
            window.draw(options[i]);
            window.draw(option_text[i]);
        }
        window.display();

    }


   

    return 4;
    //if Start game option is chosen 
         //g.start_game();
}


//void Menu::game_end()
//{
//    game_over();
//}