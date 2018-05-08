/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Bastien Gaming
*/

#ifndef sfml_HPP
#define sfml_HPP

#include <string>
#include <list>
#include <unordered_map>
#include "IGraphicLib.hpp"

namespace Arcade {
	class Sfml : public Arcade::IGraphicLib {
	public:
		Sfml();
		~Sfml() override;

	public:
		std::string getName() const final;

		bool isOpen() const final;
		void closeRenderer() final;
		void openRenderer(std::string const &title) final;
		void clearWindow() final;
		void refreshWindow() final;
		void drawPixelBox(PixelBox const &) final;
		void drawText(TextBox const &) final;
		bool pollEvents() final;
		Keys getLastEvent() final;
		void clearEvents() final;
		Vect<size_t> getScreenSize() const final;
		size_t getMaxY() const final;
		size_t getMaxX() const final;

	private:
		std::string _name = "SFML";
		std::list<Arcade::Keys> _events;
		sf::Text _text;
		sf::Font _font;
		sf::Sprite _sprite;
		sf::Texture _texture;
		sf::RenderWindow _window;
		std::unordered_map<sf::Keyboard::Key, Arcade::Keys> _keyMap = {
			{sf::Keyboard::Key::A, Arcade::Keys::A},
			{sf::Keyboard::Key::B, Arcade::Keys::B},
			{sf::Keyboard::Key::C, Arcade::Keys::C},
			{sf::Keyboard::Key::D, Arcade::Keys::D},
			{sf::Keyboard::Key::E, Arcade::Keys::E},
			{sf::Keyboard::Key::F, Arcade::Keys::F},
			{sf::Keyboard::Key::G, Arcade::Keys::G},
			{sf::Keyboard::Key::H, Arcade::Keys::H},
			{sf::Keyboard::Key::I, Arcade::Keys::I},
			{sf::Keyboard::Key::J, Arcade::Keys::J},
			{sf::Keyboard::Key::K, Arcade::Keys::K},
			{sf::Keyboard::Key::L, Arcade::Keys::L},
			{sf::Keyboard::Key::M, Arcade::Keys::M},
			{sf::Keyboard::Key::N, Arcade::Keys::N},
			{sf::Keyboard::Key::O, Arcade::Keys::O},
			{sf::Keyboard::Key::P, Arcade::Keys::P},
			{sf::Keyboard::Key::Q, Arcade::Keys::Q},
			{sf::Keyboard::Key::R, Arcade::Keys::R},
			{sf::Keyboard::Key::S, Arcade::Keys::S},
			{sf::Keyboard::Key::T, Arcade::Keys::T},
			{sf::Keyboard::Key::U, Arcade::Keys::U},
			{sf::Keyboard::Key::V, Arcade::Keys::V},
			{sf::Keyboard::Key::W, Arcade::Keys::W},
			{sf::Keyboard::Key::X, Arcade::Keys::X},
			{sf::Keyboard::Key::Y, Arcade::Keys::Y},
			{sf::Keyboard::Key::Z, Arcade::Keys::Z},
			{sf::Keyboard::Key::Left, Arcade::Keys::LEFT},
			{sf::Keyboard::Key::Right, Arcade::Keys::RIGHT},
			{sf::Keyboard::Key::Up, Arcade::Keys::UP},
			{sf::Keyboard::Key::Down, Arcade::Keys::DOWN},
			{sf::Keyboard::Key::Return, Arcade::Keys::ENTER},
			{sf::Keyboard::Key::Space, Arcade::Keys::SPACE},
			{sf::Keyboard::Key::Delete, Arcade::Keys::DELETE},
			{sf::Keyboard::Key::BackSpace, Arcade::Keys::BACKSPACE},
			{sf::Keyboard::Key::Tab, Arcade::Keys::TAB},
			{sf::Keyboard::Key::Escape, Arcade::Keys::ESC}};
	};
}
#endif
