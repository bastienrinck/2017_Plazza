/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.hpp
*/

#pragma once

#include "Keys.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include "ForkPool.hpp"
#include <SFML/Graphics.hpp>

namespace Plazza {
	class GuiManager {
	public:
		GuiManager(std::string arg);
		~GuiManager();
		void openRenderer();
		void closeRenderer();
		void refreshWindow();
		void getMousePressed(sf::Vector2f click);
		void setButtonWindow();
		bool isOpen() const;
		bool guiLoop();
		bool pollEvents();
		void drawText(std::basic_string<char> text, sf::Vector2f pos);
		void drawLine();
		void setCmd(char i);
		//void cmdReady(Plazza pl);
	private:
		std::string _info = "";
		std::map<std::string, sf::FloatRect> _vector;
		sf::RenderWindow _window;
		sf::Text _text;
		sf::Font _font;
		sf::Sprite _sprite;
		sf::Texture _texture;
		sf::Texture _textureImg;
		std::string _file;
		bool _isCmdReady = false;
		std::unordered_map<sf::Keyboard::Key, Keys> _keyMap = {
			{sf::Keyboard::Key::A, Keys::A},
			{sf::Keyboard::Key::B, Keys::B},
			{sf::Keyboard::Key::C, Keys::C},
			{sf::Keyboard::Key::D, Keys::D},
			{sf::Keyboard::Key::E, Keys::E},
			{sf::Keyboard::Key::F, Keys::F},
			{sf::Keyboard::Key::G, Keys::G},
			{sf::Keyboard::Key::H, Keys::H},
			{sf::Keyboard::Key::I, Keys::I},
			{sf::Keyboard::Key::J, Keys::J},
			{sf::Keyboard::Key::K, Keys::K},
			{sf::Keyboard::Key::L, Keys::L},
			{sf::Keyboard::Key::M, Keys::M},
			{sf::Keyboard::Key::N, Keys::N},
			{sf::Keyboard::Key::O, Keys::O},
			{sf::Keyboard::Key::P, Keys::P},
			{sf::Keyboard::Key::Q, Keys::Q},
			{sf::Keyboard::Key::R, Keys::R},
			{sf::Keyboard::Key::S, Keys::S},
			{sf::Keyboard::Key::T, Keys::T},
			{sf::Keyboard::Key::U, Keys::U},
			{sf::Keyboard::Key::V, Keys::V},
			{sf::Keyboard::Key::W, Keys::W},
			{sf::Keyboard::Key::X, Keys::X},
			{sf::Keyboard::Key::Y, Keys::Y},
			{sf::Keyboard::Key::Z, Keys::Z},
			{sf::Keyboard::Key::Left, Keys::LEFT},
			{sf::Keyboard::Key::Right, Keys::RIGHT},
			{sf::Keyboard::Key::Up, Keys::UP},
			{sf::Keyboard::Key::Down, Keys::DOWN},
			{sf::Keyboard::Key::Return, Keys::ENTER},
			{sf::Keyboard::Key::Space, Keys::SPACE},
			{sf::Keyboard::Key::Delete, Keys::DELETE},
			{sf::Keyboard::Key::BackSpace, Keys::BACKSPACE},
			{sf::Keyboard::Key::Tab, Keys::TAB},
			{sf::Keyboard::Key::Escape, Keys::ESC}};
		std::string _arg;
	};
};