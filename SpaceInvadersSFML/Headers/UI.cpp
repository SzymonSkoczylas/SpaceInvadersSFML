#include "UI.h"



UI::MyText::MyText()
{
	this->font.loadFromFile("Fonts/PTSansNarrow-Bold.ttf");
}

void UI::MyText::SetText(const std::string& sentence, int size, sf::Color color, int xpos, int ypos)
{
	this->content = sentence;
	this->text.setFont(this->font);
	this->text.setString(sentence);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setPosition(xpos,ypos);
}

void UI::MyText::UpdateText()
{
	this->text.setString(this->content);
}

void UI::MyText::Underline()
{
	this->text.setStyle(sf::Text::Underlined);
}

void UI::MyText::Default()
{
	this->text.setStyle(sf::Text::Regular);
}
