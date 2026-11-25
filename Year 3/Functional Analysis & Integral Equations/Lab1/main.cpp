#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

double g(double x)
{
    return 3.0 * x + std::sin(x) + std::sqrt(1.0 + x * x);
}

double f(double x, double lambda)
{
    return x - lambda * g(x);
}

int calculate_apriori_iterations(double x0, double x1, double eps, double alpha)
{
    double diff = std::abs(x0 - x1);

    if (diff == 0)
    {
        return 0;
    }

    double val = eps * (1.0 - alpha) / diff;

    return std::floor(std::log(val) / std::log(alpha)) + 1;
}

std::string format_number(double value, int precision = 3)
{
    if (std::abs(value) < 1e-9)
    {
        value = 0.0;
    }

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;

    std::string result = ss.str();

    if (result.find('.') != std::string::npos)
    {
        while (!result.empty() && result.back() == '0')
        {
            result.pop_back();
        }

        if (!result.empty() && result.back() == '.')
        {
            result.pop_back();
        }
    }

    if (result == "-0")
    {
        result = "0";
    }

    return result;
}

void plot_graph(double x_min, double x_max)
{
    const unsigned int WINDOW_WIDTH = 1100;
    const unsigned int WINDOW_HEIGHT = 800;
    const float MARGIN = 80.f;

    const double dx = 0.05;
    const double dy = 0.05;

    double y_min = 1e9;
    double y_max = -1e9;

    const int POINT_COUNT = 2000;

    std::vector<sf::Vector2f> points;

    for (int i = 0; i <= POINT_COUNT; ++i)
    {
        double x = x_min + (x_max - x_min) * i / POINT_COUNT;
        double y = g(x);

        y_min = std::min(y_min, y);
        y_max = std::max(y_max, y);

        points.push_back(sf::Vector2f((float)x, (float)y));
    }

    y_min = std::floor(y_min / dy) * dy - dy;
    y_max = std::ceil(y_max / dy) * dy + dy;

    double x_span = x_max - x_min;
    double y_span = y_max - y_min;

    double pixels_per_unit = std::min(
        (WINDOW_WIDTH - 2 * MARGIN) / x_span,
        (WINDOW_HEIGHT - 2 * MARGIN) / y_span
    );

    double plot_width = x_span * pixels_per_unit;
    double plot_height = y_span * pixels_per_unit;

    double offset_x = MARGIN + (WINDOW_WIDTH - 2 * MARGIN - plot_width) / 2.0;
    double offset_y = MARGIN + (WINDOW_HEIGHT - 2 * MARGIN - plot_height) / 2.0;

    auto to_pixel = [&](double x, double y) -> sf::Vector2f
        {
            float px = (float)(offset_x + (x - x_min) * pixels_per_unit);
            float py = (float)(offset_y + (y_max - y) * pixels_per_unit);

            return sf::Vector2f(px, py);
        };

    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Graph of g(x)"
    );

    window.setFramerateLimit(60);

    sf::Font font;
    bool font_loaded = false;

    const char* font_paths[] =
    {
        "arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf"
    };

    for (const char* path : font_paths)
    {
        if (font.loadFromFile(path))
        {
            font_loaded = true;
            break;
        }
    }

    if (!font_loaded)
    {
        std::cerr
            << "Failed to load font. Axis labels will not be displayed.\n"
            << "Place arial.ttf next to the executable or specify another .ttf font path.\n";
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        std::vector<sf::Vertex> grid;

        int k = 0;

        for (double x = x_min; x <= x_max + 1e-9; x += dx, ++k)
        {
            sf::Vector2f p1 = to_pixel(x, y_min);
            sf::Vector2f p2 = to_pixel(x, y_max);

            sf::Color color = (k % 2 == 0)
                ? sf::Color(185, 185, 185)
                : sf::Color(225, 225, 225);

            grid.push_back(sf::Vertex(p1, color));
            grid.push_back(sf::Vertex(p2, color));
        }

        k = 0;

        for (double y = y_min; y <= y_max + 1e-9; y += dy, ++k)
        {
            sf::Vector2f p1 = to_pixel(x_min, y);
            sf::Vector2f p2 = to_pixel(x_max, y);

            sf::Color color = (k % 2 == 0)
                ? sf::Color(185, 185, 185)
                : sf::Color(225, 225, 225);

            grid.push_back(sf::Vertex(p1, color));
            grid.push_back(sf::Vertex(p2, color));
        }

        window.draw(grid.data(), grid.size(), sf::Lines);

        sf::Vertex x_axis[] =
        {
            sf::Vertex(to_pixel(x_min, 0.0), sf::Color::Black),
            sf::Vertex(to_pixel(x_max, 0.0), sf::Color::Black)
        };

        sf::Vertex y_axis[] =
        {
            sf::Vertex(to_pixel(0.0, y_min), sf::Color::Black),
            sf::Vertex(to_pixel(0.0, y_max), sf::Color::Black)
        };

        window.draw(x_axis, 2, sf::Lines);
        window.draw(y_axis, 2, sf::Lines);

        sf::VertexArray curve(sf::LineStrip, points.size());

        for (std::size_t i = 0; i < points.size(); ++i)
        {
            curve[i] = sf::Vertex(
                to_pixel(points[i].x, points[i].y),
                sf::Color(30, 100, 220)
            );
        }

        window.draw(curve);

        const double x_root = -0.2590;

        sf::CircleShape root_marker(5.f);
        root_marker.setFillColor(sf::Color::Red);
        root_marker.setOrigin(5.f, 5.f);
        root_marker.setPosition(to_pixel(x_root, g(x_root)));

        window.draw(root_marker);

        if (font_loaded)
        {
            k = 0;

            for (double x = x_min; x <= x_max + 1e-9; x += dx, ++k)
            {
                if (k % 4 == 0)
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(format_number(x, 2));
                    text.setCharacterSize(12);
                    text.setFillColor(sf::Color::Black);

                    sf::FloatRect bounds = text.getLocalBounds();
                    sf::Vector2f position = to_pixel(x, y_min);

                    text.setPosition(
                        position.x - bounds.width / 2.f,
                        position.y + 4.f
                    );

                    window.draw(text);
                }
            }

            k = 0;

            for (double y = y_min; y <= y_max + 1e-9; y += dy, ++k)
            {
                if (k % 2 == 0)
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(format_number(y, 2));
                    text.setCharacterSize(12);
                    text.setFillColor(sf::Color::Black);

                    sf::FloatRect bounds = text.getLocalBounds();
                    sf::Vector2f position = to_pixel(x_min, y);

                    text.setPosition(
                        position.x - bounds.width - 6.f,
                        position.y - bounds.height / 2.f
                    );

                    window.draw(text);
                }
            }

            sf::Text x_label;
            x_label.setFont(font);
            x_label.setString("x");
            x_label.setCharacterSize(22);
            x_label.setStyle(sf::Text::Bold);
            x_label.setFillColor(sf::Color::Black);
            x_label.setPosition(
                to_pixel(x_max, 0.0) + sf::Vector2f(10.f, -10.f)
            );

            window.draw(x_label);

            sf::Text y_label;
            y_label.setFont(font);
            y_label.setString("g(x)");
            y_label.setCharacterSize(22);
            y_label.setStyle(sf::Text::Bold);
            y_label.setFillColor(sf::Color::Black);
            y_label.setPosition(
                to_pixel(0.0, y_max) + sf::Vector2f(8.f, -30.f)
            );

            window.draw(y_label);

            sf::Text title;
            title.setFont(font);
            title.setString(
                "g(x) = 3x + sin(x) + sqrt(1 + x^2),  grid dx = dy = 0.05"
            );
            title.setCharacterSize(16);
            title.setFillColor(sf::Color(30, 100, 220));
            title.setPosition(MARGIN, 10.f);

            window.draw(title);
        }

        window.display();
    }
}

int main()
{
    double eps = 1e-4;

    double k1 = 2.833;
    double k2 = 4.0;

    double lambda = 2.0 / (k1 + k2);
    double alpha = (k2 - k1) / (k2 + k1);

    double x0 = -0.5;
    double x1 = f(x0, lambda);

    int apriori_iterations = calculate_apriori_iterations(
        x0,
        x1,
        eps,
        alpha
    );

    std::cout
        << "A priori iteration estimate: "
        << apriori_iterations << std::endl;

    int iterations = 0;

    double x_current = x0;
    double x_next = x1;

    do
    {
        iterations++;

        x_current = x_next;
        x_next = f(x_current, lambda);

    } while (
        alpha / (1.0 - alpha) * std::abs(x_next - x_current) > eps
        );

    std::cout
        << "Actual number of iterations: "
        << iterations << std::endl;

    std::cout << std::fixed << std::setprecision(6);

    std::cout
        << "Approximate solution: "
        << x_next << std::endl;

    std::cout
        << "Verification (g(x)): "
        << g(x_next) << std::endl;

    plot_graph(-1.0, 0.0);

    return 0;
}
