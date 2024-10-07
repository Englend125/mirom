#include "App.h"

//void f() {
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//        if (vec_start.x == -1) {
//            vec_start = Point<double>(m_pozition.x, m_pozition.y);
//            vec_end = Point<double>(-1, -1);
//            lines[0].position = sf::Vector2f(vec_start.x, vec_start.y);
//            lines[1].position = sf::Vector2f(vec_end.x, vec_end.y);
//        } else {
//            vec_end = Point<double>(m_pozition.x, m_pozition.y);
//            lines[0].position = sf::Vector2f(vec_start.x, vec_start.y);
//            lines[1].position = sf::Vector2f(vec_end.x, vec_end.y);
//        }
//    } else {
//        if (vec_end.x != -1) {
//
//        }
//    }
//}

int16_t App::render() {
    Stage stage = input;
    //input
    Label label(100, 70, 20, 0, sf::Color::Transparent, sf::Color::Transparent);
    label.setText("select number of points:");
    std::vector<Button1> buttons(7, Button1(40, 70));
    for (int i = 3; i <= 9; ++i) {
        buttons[i-3].setText('0'+i);
        buttons[i-3].setPos(30+(i-3)*45, 90);
    }
    int angl_num = 0;

    //poinsts
    sf::VertexArray polygon(sf::Lines);
    bool kostil = true;
    int cur_ind = 0;

    //ray
    Point<double> vec_start(-1, -1);
    Point<double> vec_end(-1, -1);
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(0,0);
    line[1].position = sf::Vector2f(100,150);
    line[0].color = sf::Color::Blue;
    line[1].color = sf::Color::Cyan;
    while (window_->isOpen()) {
        sf::Event event;
        sf::Vector2i m_pozition = sf::Mouse::getPosition(*window_);
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_->close();
        }
        window_->clear();

        switch (stage) {
            case input:
                label.draw(*window_);
                for (int i = 3; i <= 9; ++i) {
                    buttons[i-3].draw(*window_);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (buttons[i - 3].Pressed(m_pozition)) {
                            angl_num = i;
                            polygon = sf::VertexArray(sf::Lines, 2*i);
                            label.setText("click on the corners of the room:");
                            kostil = false;
                            stage = points;
                        }
                    }
                }
                break;
            case points:
                label.draw(*window_);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (kostil) {
                        kostil = false;
                        if (cur_ind == 0) {
                            for (int i = 0; i < angl_num*2; ++i) {
                                polygon[i] = sf::Vector2f(m_pozition.x, m_pozition.y);
                            }
                        } else {
                            polygon[cur_ind - 1] = sf::Vector2f(m_pozition.x, m_pozition.y);
                            polygon[cur_ind] = sf::Vector2f(m_pozition.x, m_pozition.y);
                        }
                        cur_ind += 2;
                        if (cur_ind == angl_num*2) {
                            stage = walls;
                        }
                    }
                } else {
                    kostil = true;
                }
                window_->draw(polygon);

                break;
            case walls:
                window_->draw(polygon);

                break;
            case ray:
                if (vec_end.x != -1) {
                    window_->draw(line);
                }
        }


        window_->display();
    }
    return 0;
}