#include "App.h"

bool App::render() {
    int kostil = 0;
    Point<double> vec_start(-1, -1);
    Point<double> vec_end(-1, -1);
    sf::VertexArray lines(sf::Lines, 2);
    lines[0].position = sf::Vector2f(0,0);
    lines[1].position = sf::Vector2f(100,150);
    lines[0].color = sf::Color::Magenta;
    lines[1].color = sf::Color::Yellow;
    while (window_->isOpen()) {
        sf::Event event;
        sf::Vector2i m_pozition = sf::Mouse::getPosition(*window_);
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (kostil == 0) {
                kostil = 0;
                if (vec_start.x == -1) {
                    vec_start = Point<double>(m_pozition.x, m_pozition.y);
                    vec_end = Point<double>(-1, -1);
                    lines[0] = sf::Vector2f(vec_start.x, vec_start.y);
                    lines[1] = sf::Vector2f(vec_end.x, vec_end.y);
                } else {
                    vec_end = Point<double>(m_pozition.x, m_pozition.y);
                    lines[0] = sf::Vector2f(vec_start.x, vec_start.y);
                    lines[1] = sf::Vector2f(vec_end.x, vec_end.y);
                }
            } else {
                --kostil;
            }
        } else {
            kostil = 0;
        }
        window_->clear();
        if (vec_end.x != -1) {
            window_->draw(lines);
        }
        window_->display();
    }
    return true;
}