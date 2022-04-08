#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "DCT.h"
#include "Logger.h"
#include "Plotter.h"
#include "misc.h"
#include "Slider.h"
#include "PickableTable.h"

const int WIDTH  = 1000;
const int HEIGHT = 1000;
const sf::Vector2f window_asp = sf::Vector2f((float)WIDTH, (float)HEIGHT);

float function_from_index(int index, float x);

int main()
{

	std::vector<float> val;

    for (float i = 0.0f; i < 4 * DCT::PI; i += .2f)
    {
        val.push_back(
            std::max(
                4.7f * std::pow(std::sin(DCT::PI + i), 16.f), 
                0.5f * std::sqrt(fmod(DCT::PI * i, DCT::PI * DCT::PI) - (fmod(i, DCT::PI) * fmod(i, DCT::PI)))
            )
        );
    }

    std::vector<float> dct =  DCT::dct(val);
    std::vector<float> idct = DCT::idct(dct);

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
        return -1;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Discrete Cosine Transform Viewer", sf::Style::Default, settings);

    sf::Image icon;
    if (!icon.loadFromFile("icon.png"))
        return -1;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setFramerateLimit(60);

    sf::Text fps;

    fps.setFont(font);
    fps.setPosition(WIDTH - 150.0f, 25.0f);
    fps.setCharacterSize(25);
    fps.setFillColor(sf::Color(200, 200, 200));

    sf::Text copyright;

    copyright.setString("Made by\nAndrey Soldatov\nin 2021");
    copyright.setFont(font);
    copyright.setPosition(750, HEIGHT - (25.0f + 25.0f * 3.0f));
    copyright.setCharacterSize(25);
    copyright.setFillColor(sf::Color(100, 100, 100));

    sf::Text text_1;

    text_1.setString("Raw Function:");
    text_1.setFont(font);
    text_1.setPosition(100.0f, 25.0f);
    text_1.setCharacterSize(25);
    text_1.setFillColor(sf::Color(200, 200, 200));

    sf::Text text_2;

    text_2.setString("Discrete Cosine Transform(DCT):");
    text_2.setFont(font);
    text_2.setPosition(100.0f, 350.0f);
    text_2.setCharacterSize(25);
    text_2.setFillColor(sf::Color(200, 200, 200));

    sf::Text text_3;

    text_3.setString("Invert Discrete Cosine Transform(IDCT):");
    text_3.setFont(font);
    text_3.setPosition(100.0f, 675.0f);
    text_3.setCharacterSize(25);
    text_3.setFillColor(sf::Color(200, 200, 200));

    Plotter plot_1 = Plotter(
        val, 
        sf::Vector2f(100.0f, 75.0f), 
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(15, 252, 3),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    Plotter plot_2 = Plotter(
        dct,
        sf::Vector2f(100.0f, 400.0f),
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(255, 41, 66),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    Plotter plot_3 = Plotter(
        idct,
        sf::Vector2f(100.0f, 725.0f),
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(41, 219, 255),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    sf::Text error_percentage;

    error_percentage.setFont(font);
    error_percentage.setPosition(750, 300);
    error_percentage.setCharacterSize(25);
    error_percentage.setFillColor(sf::Color(200, 200, 200));

    sf::Text compression_percentage;

    compression_percentage.setFont(font);
    compression_percentage.setPosition(750, 150);
    compression_percentage.setCharacterSize(25);
    compression_percentage.setFillColor(sf::Color(200, 200, 200));

    Slider compression_slider = Slider(sf::Vector2f(750, 250), 200.f, sf::Color(200, 200, 200), sf::Color(100, 100, 100), window_asp);

    sf::Text speed_text;

    speed_text.setFont(font);
    speed_text.setPosition(750, 400);
    speed_text.setCharacterSize(25);
    speed_text.setFillColor(sf::Color(200, 200, 200));
    speed_text.setString("Rate of change:");

    Slider speed_slider = Slider(sf::Vector2f(750, 475), 200.f, sf::Color(200, 200, 200), sf::Color(100, 100, 100), window_asp);

    PickableTable table = PickableTable(
        sf::Vector2f(750, 550),
        200.0f,
        50.0f,
        {"sin(x)", "saw tooth", "square wave", "comp. func.", "triangle", "linear"},
        font);

    float a = DCT::PI * 2.0f;

    sf::Clock cl;
    size_t count = 0;

    sf::Color lsd;

    while (window.isOpen())
    {
        float fps_num = 1.0f / cl.getElapsedTime().asSeconds();
        cl.restart();

        count++;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                switch (event.key.code) 
                {
                case sf::Keyboard::Q:
                    plot_1.flip_col();
                    plot_2.flip_col();
                    plot_3.flip_col();
                    break;
                case sf::Keyboard::W:
                    plot_1.flip_cir();
                    plot_2.flip_cir();
                    plot_3.flip_cir();
                    break;
                case sf::Keyboard::E:
                    plot_1.flip_lin();
                    plot_2.flip_lin();
                    plot_3.flip_lin();
                    break;
                }
            }
        }

        val.clear();
        for (float i = 0.0f + a; i < 4 * DCT::PI + a; i += .2f)
        {
            val.push_back(
                function_from_index(table.get_current_index(), i)
            );
        }

        speed_slider.process_input(window);
        a += speed_slider.get_value() / 50.0f;

        table.process_input(window);

        dct = DCT::dct(val);

        compression_slider.process_input(window);

        DCT::compress(dct, compression_slider.get_value());

        idct = DCT::idct(dct);

        float error = 0.f;

        for (size_t i = 0; i < val.size(); i++)
        {
            if (val[i] != 0) 
            {
                error += fabs((idct[i] - val[i]) / val[i]) * 100.f;
            }
        }

        error /= val.size();

        compression_percentage.setString("Compression:\n" + to_string_with_precision(compression_slider.get_value() * 100.f) + "%");

        if (count == 20)
        {
            fps.setString("fps:\n" + to_string_with_precision(fps_num));
            error_percentage.setString("Error:\n" + to_string_with_precision(error) + "%");
            count = 0;
        }

        plot_1.reset_values(val);
        plot_2.reset_values(dct);
        plot_3.reset_values(idct);

        window.clear(sf::Color(40, 40, 40));

        plot_1.draw(window);
        plot_2.draw(window);
        plot_3.draw(window);

        compression_slider.draw(window);
        speed_slider.draw(window);


        window.draw(copyright);

        window.draw(text_1);
        window.draw(text_2);
        window.draw(text_3);

        window.draw(fps);
        window.draw(error_percentage);
        window.draw(compression_percentage);
        window.draw(speed_text);

        table.draw(window);

        window.display();
    }

	return 0;
}

float function_from_index(int index, float x) {
    switch (index)
    {
    case 0:
        return std::sin(x);
    case 1:
        return std::fmod(x, 3.0f);
    case 2:
        return std::sin(x) > 0 ? 1 : 0;
    case 3:
        return std::max(4.7f * std::pow(std::sin(DCT::PI + x), 16.f),
            0.5f * std::sqrt(fmod(DCT::PI * x, DCT::PI * DCT::PI) - (fmod(x, DCT::PI) * fmod(x, DCT::PI))));
    case 4:
        return std::asin(std::sin(x * 2.0f));
    default:
        return x;
    }
}