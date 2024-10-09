#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <random>
using namespace std;
using namespace sf;

class Food {
public:
	Texture tex;
	Sprite spr;
	int FoodScore;
	Food() {
		tex.loadFromFile("img/PNG/INVENTORY/healthPotion.png");
		spr.setTexture(tex);
		spr.setScale(0.5, 0.5);
		FoodScore = 0;
	}
	void setPosition(float x, float y) {
		spr.setPosition(x, y);
	}
	void draw(RenderWindow& window) {
		window.draw(spr);
	}
};