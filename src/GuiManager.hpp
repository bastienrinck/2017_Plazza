/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** GuiManager.hpp
*/

#ifndef CPP_PLAZZA_GUIMANAGER_HPP
#define CPP_PLAZZA_GUIMANAGER_HPP

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
	private:
		sf::RenderWindow _window;
		sf::Text _text;
		sf::Font _font;
		sf::Sprite _sprite;
		sf::Texture _texture;
		sf::Texture _textureImg;

		bool guiLoop();

		bool pollEvents();
	};
};
#endif /* !CPP_PLAZZA_GUIMANAGER_HPP */
