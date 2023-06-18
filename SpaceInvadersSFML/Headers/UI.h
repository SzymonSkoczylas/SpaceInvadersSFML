#ifndef UI_H
#define UI_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

namespace UI {
	static std::string font_path;
	static void setFont(const std::string& path) {font_path = path;}

	class MyText {
	private:
		sf::Text text;
		sf::Font font;
		std::string content;
	public:
		MyText();
		void SetText(const std::string& sentence, int size, sf::Color color, int xpos, int ypos);
		void UpdateText();
		void Underline();
		void Default();
		sf::Text getText() { return this->text; }
		std::string getContent(){ return this->content; }
		void setContent(const std::string& input) { this->content = input; }
	};

};


#endif 