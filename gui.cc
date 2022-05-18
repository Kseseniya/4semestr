#include "gui.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
namespace {
sf::Color toSf(Color clr) {
	switch (clr) {
		default:
		case BLACK:
			return sf::Color::Black;
		case RED:
			return sf::Color::Red;
		case GREEN:
			return sf::Color::Green;
		case YELLOW:
			return sf::Color::Yellow;
		case BLUE:
			return sf::Color::Blue;
		case MAGENTA:
			return sf::Color::Magenta;
		case CYAN:
			return sf::Color::Cyan;
		case WHITE:
			return sf::Color::White;
	}
}

Color fromSf(sf::Color clr) {
	if (clr == sf::Color::Red)
		return RED;
	if (clr == sf::Color::Green)
		return GREEN;
	if (clr == sf::Color::Yellow)
		return YELLOW;
	if (clr == sf::Color::Blue)
		return BLUE;
	if (clr == sf::Color::Magenta)
		return MAGENTA;
	if (clr == sf::Color::Cyan)
		return CYAN;
	if (clr == sf::Color::White)
		return WHITE;
	return BLACK;
}

int fromSf(sf::Keyboard::Key code) {
	return code + 'A';
}
}

void Gui::draw() {
}

void Gui::stop() {
	window_.close();
}

void Gui::runloop() {
	while (window_.isOpen()) {
		sf::Event event;
		while (window_.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					for (auto &&sub : callkey_)
						sub(fromSf(event.key.code));
					break;
				case sf::Event::Resized:
					window_.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					break;
				case sf::Event::Closed:
					stop();
					break;
				default:
					break;
			}
		}
		for (auto &&sub : calltimer_)
			sub();
		window_.display();
	}
}

Gui::Gui() : window_(sf::VideoMode(800, 600), "Snake" ) {
	window_.setFramerateLimit(20);
}

void Gui::drawEmpty(Coord rab) {
	auto box{sf::RectangleShape{sf::Vector2f(cell_sz, cell_sz)}};
	box.setFillColor(sf::Color::Black);
	box.setPosition(cell_sz * rab.x, cell_sz * rab.y);
	window_.draw(box);
}

void Gui::drawRab(Coord rab) {
	auto circle{sf::CircleShape{float(cell_sz) / 2}};
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(cell_sz * rab.x, cell_sz * rab.y);
	window_.draw(circle);
}

void Gui::drawSnake(Coord head, Color clr) {
	auto circle{sf::CircleShape{float(cell_sz) / 2}};
	circle.setFillColor(toSf(clr));
	circle.setPosition(cell_sz * head.x, cell_sz * head.y);
	window_.draw(circle);
}

void Gui::drawSnake(Coord head, Coord tail, Color clr) {
	drawSnake(head, clr);
	drawEmpty(tail);
}

void Gui::drawSnake(std::list<Coord> body, Color clr) {
	for (auto crd : body)
		drawSnake(crd, clr);
}

Coord Gui::getSize() const {
	auto sz = window_.getSize();
	return Coord{static_cast<int>(sz.x/cell_sz),static_cast<int>(sz.y/cell_sz)};
}