/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.hpp
*/

#ifndef CPP_PLAZZA_GUIMANAGER_HPP
#define CPP_PLAZZA_GUIMANAGER_HPP

#include "Keys.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>

namespace Plazza {
	class GuiManager {
	public:
		GuiManager();
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
		std::unordered_map<sf::Keyboard::Key, Plazza::Keys> _keyMap = {
			{sf::Keyboard::Key::A, Plazza::Keys::A},
			{sf::Keyboard::Key::B, Plazza::Keys::B},
			{sf::Keyboard::Key::C, Plazza::Keys::C},
			{sf::Keyboard::Key::D, Plazza::Keys::D},
			{sf::Keyboard::Key::E, Plazza::Keys::E},
			{sf::Keyboard::Key::F, Plazza::Keys::F},
			{sf::Keyboard::Key::G, Plazza::Keys::G},
			{sf::Keyboard::Key::H, Plazza::Keys::H},
			{sf::Keyboard::Key::I, Plazza::Keys::I},
			{sf::Keyboard::Key::J, Plazza::Keys::J},
			{sf::Keyboard::Key::K, Plazza::Keys::K},
			{sf::Keyboard::Key::L, Plazza::Keys::L},
			{sf::Keyboard::Key::M, Plazza::Keys::M},
			{sf::Keyboard::Key::N, Plazza::Keys::N},
			{sf::Keyboard::Key::O, Plazza::Keys::O},
			{sf::Keyboard::Key::P, Plazza::Keys::P},
			{sf::Keyboard::Key::Q, Plazza::Keys::Q},
			{sf::Keyboard::Key::R, Plazza::Keys::R},
			{sf::Keyboard::Key::S, Plazza::Keys::S},
			{sf::Keyboard::Key::T, Plazza::Keys::T},
			{sf::Keyboard::Key::U, Plazza::Keys::U},
			{sf::Keyboard::Key::V, Plazza::Keys::V},
			{sf::Keyboard::Key::W, Plazza::Keys::W},
			{sf::Keyboard::Key::X, Plazza::Keys::X},
			{sf::Keyboard::Key::Y, Plazza::Keys::Y},
			{sf::Keyboard::Key::Z, Plazza::Keys::Z},
			{sf::Keyboard::Key::Left, Plazza::Keys::LEFT},
			{sf::Keyboard::Key::Right, Plazza::Keys::RIGHT},
			{sf::Keyboard::Key::Up, Plazza::Keys::UP},
			{sf::Keyboard::Key::Down, Plazza::Keys::DOWN},
			{sf::Keyboard::Key::Return, Plazza::Keys::ENTER},
			{sf::Keyboard::Key::Space, Plazza::Keys::SPACE},
			{sf::Keyboard::Key::Delete, Plazza::Keys::DELETE},
			{sf::Keyboard::Key::BackSpace, Plazza::Keys::BACKSPACE},
			{sf::Keyboard::Key::Tab, Plazza::Keys::TAB},
			{sf::Keyboard::Key::Escape, Plazza::Keys::ESC}};

		void setCmd(char i);

		void cmdReady();
	};
};
#endif
