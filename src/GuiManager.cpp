/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.cpp
*/

#include <SFML/Graphics.hpp>
#include "GuiManager.hpp"

Plazza::GuiManager::GuiManager()
{
	_window.setFramerateLimit(30);
	_texture.create(1920, 1080);
	_sprite.setTexture(_texture);
	_font.loadFromFile("resources/fonts/font.ttf");
	_textureImg.loadFromFile("img/blue-circle.png");
}

Plazza::GuiManager::~GuiManager()
= default;

void Plazza::GuiManager::openRenderer()
{
	_window.create(sf::VideoMode(1280, 720), "Plazza");
}

void Plazza::GuiManager::closeRenderer()
{
	_window.close();
}

void Plazza::GuiManager::refreshWindow()
{
	_window.display();
}

void Plazza::GuiManager::setButtonWindow()
{
	sf::Sprite sprite(_textureImg);
	sprite.setPosition(10, 20);
	_window.draw(sprite);
}

bool Plazza::GuiManager::isOpen() const
{
	return _window.isOpen();
}

bool Plazza::GuiManager::pollEvents()
{
	auto event = sf::Event();
	bool ret = false;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_window.close();
		}
	}
	return ret;
}

bool Plazza::GuiManager::guiLoop()
{
	this->openRenderer();
	while (this->isOpen()) {
		_window.clear();
		this->pollEvents();
		this->setButtonWindow();
		_window.display();
	}
	closeRenderer();
}