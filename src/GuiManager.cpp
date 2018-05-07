/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.cpp
*/

#include <unistd.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GuiManager.hpp"

Plazza::GuiManager::GuiManager()
{
	_texture.create(1920, 1080);
	_sprite.setTexture(_texture);
	_font.loadFromFile("fonts/font.ttf");
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
	sprite.setScale(sf::Vector2f(0.09f, 0.09f));
	_vector["Email Address"] = sprite.getGlobalBounds();
	this->drawText(std::string("Email Adress"), {40, 20});
	_window.draw(sprite);
	sprite.setPosition(10, 50);
	sprite.setScale(sf::Vector2f(0.09f, 0.09f));
	_vector["Phone Number"] = sprite.getGlobalBounds();
	this->drawText(std::string("Phone Number"), {40, 50});
	_window.draw(sprite);
	sprite.setPosition(10, 80);
	sprite.setScale(sf::Vector2f(0.09f, 0.09f));
	_vector["Ip Address"] = sprite.getGlobalBounds();
	this->drawText(std::string("Ip Address"), {40, 80});
	_window.draw(sprite);
	if (!_info.empty())
		this->drawText("Info choisi : " + _info, {10, 110});
	this->drawText(std::string("Looking for " + _info + " on file: " + _file), {0, 200});
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
		switch (event.type) {
			case sf::Event::Closed :
				_window.close();
				break;
			case sf::Event::MouseButtonPressed :
				this->getMousePressed(sf::Vector2f(sf::Mouse::getPosition(_window)));
				break;
			case sf::Event::TextEntered :
				setCmd(static_cast<char>(event.text.unicode));
				break;
			case sf::Event::Resized:break;
			case sf::Event::LostFocus:break;
			case sf::Event::GainedFocus:break;
			case sf::Event::KeyPressed:break;
			case sf::Event::KeyReleased:break;
			case sf::Event::MouseWheelMoved:break;
			case sf::Event::MouseWheelScrolled:break;
			case sf::Event::MouseButtonReleased:break;
			case sf::Event::MouseMoved:break;
			case sf::Event::MouseEntered:break;
			case sf::Event::MouseLeft:break;
			case sf::Event::JoystickButtonPressed:break;
			case sf::Event::JoystickButtonReleased:break;
			case sf::Event::JoystickMoved:break;
			case sf::Event::JoystickConnected:break;
			case sf::Event::JoystickDisconnected:break;
			case sf::Event::TouchBegan:break;
			case sf::Event::TouchMoved:break;
			case sf::Event::TouchEnded:break;
			case sf::Event::SensorChanged:break;
			case sf::Event::Count:break;
		}
	}
	return ret;
}

void Plazza::GuiManager::drawLine()
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(0, 150)),
		sf::Vertex(sf::Vector2f(250, 150))
	};
	_window.draw(line, 2, sf::Lines);
	sf::Vertex linetmp[] = {
		sf::Vertex(sf::Vector2f(250, 0)),
		sf::Vertex(sf::Vector2f(250, 150))
	};
	_window.draw(linetmp, 2, sf::Lines);
}

bool Plazza::GuiManager::guiLoop()
{
	this->openRenderer();
	this->openRenderer();
	while (this->isOpen()) {
		_window.clear();
		this->pollEvents();
		this->setButtonWindow();
		this->drawLine();
		_window.display();
		if (_isCmdReady) {
			this->drawText(std::string("Find " + _info + " on file: " + _file), {200, 200});
			_file.clear();
			_info.clear();
			_isCmdReady = false;
		}
	}
	closeRenderer();
	return true;
}

void Plazza::GuiManager::getMousePressed(sf::Vector2f click)
{
	for (auto x : _vector) {
		if (x.second.contains(click.x, click.y))
			_info = x.first;
	}
}

void Plazza::GuiManager::drawText(std::basic_string<char> string, sf::Vector2f pos)
{
	_text.setFont(_font);
	_text.setString(string);
	_text.setCharacterSize(18);
	_text.setColor(sf::Color::White);
	_text.setPosition(pos.x, pos.y);
	_window.draw(_text);
}

void Plazza::GuiManager::setCmd(char c)
{
	if (c != 0) {
		if (c == '\r' || c == '\n')
			_isCmdReady = true;
		else
			_file += c;
	}
}

void Plazza::GuiManager::cmdReady()
{
	std::cout << std::string("Find " + _info + " on file: " + _file) << std::endl;
	usleep(5000);
	this->drawText(std::string("Find " + _info + " on file: " + _file), {60, 60});
	_file.clear();
	_info.clear();
}
