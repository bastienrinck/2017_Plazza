/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

namespace Plazza {
	class GuiManager {
	public:
		GuiManager();
		~GuiManager();
		void openRenderer();
		void closeRenderer();
		void refreshWindow();
		void setButtonWindow();
		bool isOpen() const;
		bool guiLoop();
		bool pollEvents();
	private:
		sf::RenderWindow _window;
		sf::Text _text;
		sf::Font _font;
		sf::Sprite _sprite;
		sf::Texture _texture;
		sf::Texture _textureImg;
	};
};