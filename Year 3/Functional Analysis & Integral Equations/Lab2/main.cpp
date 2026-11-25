#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <SFML/Graphics.hpp>

double exact_solution(double t, double lambda)
{
    return (36.0 * lambda / (12.0 - 7.0 * lambda)) * t * t + 2.0;
}

double K(double t, double s)
{
    return t * t * (1.0 + s);
}

double simpson_integral(
    const std::vector<double>& x_prev,
    const std::vector<double>& s_grid,
    double t,
    double h)
{
    int n = static_cast<int>(s_grid.size());
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double value = K(t, s_grid[i]) * x_prev[i];

        if (i == 0 || i == n - 1)
        {
            sum += value;
        }
        else if (i % 2 != 0)
        {
            sum += 4.0 * value;
        }
        else
        {
            sum += 2.0 * value;
        }
    }

    return sum * h / 3.0;
}

std::string format_number(double value)
{
    if (std::abs(value) < 1e-9)
    {
        return "0";
    }

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;

    std::string result = stream.str();

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

    return result;
}

std::vector<double> solve_integral_equation(
    int space_type,
    double lambda,
    double eps,
    const std::vector<double>& grid,
    double h)
{
    int m = static_cast<int>(grid.size()) - 1;

    std::vector<double> x0(m + 1, 2.0);
    std::vector<double> x1(m + 1, 2.0);
    std::vector<double> x_current(m + 1, 2.0);

    for (int i = 0; i <= m; ++i)
    {
        x1[i] = lambda * simpson_integral(x0, grid, grid[i], h) + 2.0;
    }

    double alpha;
    std::string space_name;
    double norm_diff = 0.0;

    if (space_type == 0)
    {
        alpha = 2.0 * std::abs(lambda);
        space_name = "C[0,1]";

        for (int i = 0; i <= m; ++i)
        {
            double diff = std::abs(x1[i] - x0[i]);

            if (diff > norm_diff)
            {
                norm_diff = diff;
            }
        }
    }
    else
    {
        alpha = std::abs(lambda) * std::sqrt(7.0 / 15.0);
        space_name = "L2[0,1]";

        double sum_sq = 0.0;

        for (int i = 0; i <= m; ++i)
        {
            sum_sq += (x1[i] - x0[i]) * (x1[i] - x0[i]) * h;
        }

        norm_diff = std::sqrt(sum_sq);
    }

    int apriori_iterations =
        static_cast<int>(
            std::floor(
                std::log(eps * (1.0 - alpha) / norm_diff) /
                std::log(alpha)
            )
            ) + 1;

    int iterations = 0;
    double error = 0.0;

    while (true)
    {
        iterations++;

        double max_diff = 0.0;
        double sum_sq_diff = 0.0;

        for (int i = 0; i <= m; ++i)
        {
            x_current[i] =
                lambda * simpson_integral(x1, grid, grid[i], h) + 2.0;

            double diff = std::abs(x_current[i] - x1[i]);

            if (diff > max_diff)
            {
                max_diff = diff;
            }

            sum_sq_diff += diff * diff * h;
        }

        if (space_type == 0)
        {
            error = (alpha / (1.0 - alpha)) * max_diff;
        }
        else
        {
            error = (alpha / (1.0 - alpha)) * std::sqrt(sum_sq_diff);
        }

        if (error <= eps)
        {
            break;
        }

        x1 = x_current;

        if (iterations > 10000)
        {
            break;
        }
    }

    std::cout << "--- Space: " << space_name << " ---\n";
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Contraction coefficient (alpha): " << alpha << "\n";
    std::cout << "A priori iteration count: " << apriori_iterations << "\n";
    std::cout << "Actual iteration count: " << iterations << "\n";
    std::cout << "A posteriori error estimate: " << error << "\n\n";

    return x_current;
}

void draw_solution_plot(
    const std::vector<double>& grid,
    const std::vector<double>& x_approx,
    double lambda)
{
    const unsigned int W = 1000;
    const unsigned int H = 700;
    const float margin = 70.f;

    double x_min_plot = 0.0;
    double x_max_plot = 1.0;
    double y_min_plot = 1.5;
    double y_max_plot = 4.0;

    double x_span = x_max_plot - x_min_plot;
    double y_span = y_max_plot - y_min_plot;

    double px_per_unit = std::min(
        (W - 2 * margin) / x_span,
        (H - 2 * margin) / y_span
    );

    double offset_x =
        margin + (W - 2 * margin - x_span * px_per_unit) / 2.0;

    double offset_y =
        margin + (H - 2 * margin - y_span * px_per_unit) / 2.0;

    auto to_pixel = [&](double x, double y) -> sf::Vector2f
        {
            float px = static_cast<float>(
                offset_x + (x - x_min_plot) * px_per_unit
                );

            float py = static_cast<float>(
                offset_y + (y_max_plot - y) * px_per_unit
                );

            return sf::Vector2f(px, py);
        };

    sf::RenderWindow window(
        sf::VideoMode(W, H),
        "Variant 1.16: Solutions (lambda = 0.4)"
    );

    window.setFramerateLimit(60);

    sf::Font font;

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    int m = static_cast<int>(grid.size()) - 1;
    float thickness = 3.0f;

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

        std::vector<sf::Vertex> grid_lines;

        for (double x = 0.0; x <= 1.001; x += 0.05)
        {
            grid_lines.push_back(
                sf::Vertex(to_pixel(x, y_min_plot), sf::Color(235, 235, 235))
            );

            grid_lines.push_back(
                sf::Vertex(to_pixel(x, y_max_plot), sf::Color(235, 235, 235))
            );
        }

        for (double y = 1.5; y <= 4.001; y += 0.05)
        {
            grid_lines.push_back(
                sf::Vertex(to_pixel(x_min_plot, y), sf::Color(235, 235, 235))
            );

            grid_lines.push_back(
                sf::Vertex(to_pixel(x_max_plot, y), sf::Color(235, 235, 235))
            );
        }

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_min_plot, y_min_plot), sf::Color::Black)
        );

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_max_plot, y_min_plot), sf::Color::Black)
        );

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_min_plot, y_min_plot), sf::Color::Black)
        );

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_min_plot, y_max_plot), sf::Color::Black)
        );

        window.draw(grid_lines.data(), grid_lines.size(), sf::Lines);

        sf::VertexArray approx_curve(
            sf::TriangleStrip,
            (m + 1) * 2
        );

        sf::VertexArray exact_curve(
            sf::TriangleStrip,
            (m + 1) * 2
        );

        for (int i = 0; i <= m; ++i)
        {
            sf::Vector2f p_approx = to_pixel(grid[i], x_approx[i]);

            sf::Vector2f p_exact = to_pixel(
                grid[i],
                exact_solution(grid[i], lambda)
            );

            approx_curve[i * 2] = sf::Vertex(
                sf::Vector2f(
                    p_approx.x,
                    p_approx.y - thickness / 2
                ),
                sf::Color::Blue
            );

            approx_curve[i * 2 + 1] = sf::Vertex(
                sf::Vector2f(
                    p_approx.x,
                    p_approx.y + thickness / 2
                ),
                sf::Color::Blue
            );

            exact_curve[i * 2] = sf::Vertex(
                sf::Vector2f(
                    p_exact.x,
                    p_exact.y - thickness / 2
                ),
                sf::Color(0, 180, 0)
            );

            exact_curve[i * 2 + 1] = sf::Vertex(
                sf::Vector2f(
                    p_exact.x,
                    p_exact.y + thickness / 2
                ),
                sf::Color(0, 180, 0)
            );
        }

        window.draw(approx_curve);
        window.draw(exact_curve);

        if (font.getInfo().family != "")
        {
            for (double x = 0.0; x <= 1.001; x += 0.2)
            {
                sf::Text text(format_number(x), font, 14);
                text.setFillColor(sf::Color::Black);

                sf::FloatRect bounds = text.getLocalBounds();
                sf::Vector2f position = to_pixel(x, y_min_plot);

                text.setPosition(
                    position.x - bounds.width / 2.f,
                    position.y + 5.f
                );

                window.draw(text);
            }

            for (double y = 1.6; y <= 4.001; y += 0.2)
            {
                sf::Text text(format_number(y), font, 14);
                text.setFillColor(sf::Color::Black);

                sf::FloatRect bounds = text.getLocalBounds();
                sf::Vector2f position = to_pixel(x_min_plot, y);

                text.setPosition(
                    position.x - bounds.width - 6.f,
                    position.y - bounds.height / 2.f
                );

                window.draw(text);
            }

            sf::Text legend(
                "Green: exact, Blue: approximate",
                font,
                16
            );

            legend.setFillColor(sf::Color::Black);
            legend.setPosition(margin, 10);

            window.draw(legend);
        }

        window.display();
    }
}

void draw_error_plot(
    const std::vector<double>& grid,
    const std::vector<double>& x_approx,
    double lambda)
{
    const unsigned int W = 1000;
    const unsigned int H = 700;
    const float margin = 70.f;

    double x_min_plot = 0.0;
    double x_max_plot = 1.0;

    double max_error = 0.0;
    int m = static_cast<int>(grid.size()) - 1;

    for (int i = 0; i <= m; ++i)
    {
        double error = std::abs(
            x_approx[i] - exact_solution(grid[i], lambda)
        );

        if (error > max_error)
        {
            max_error = error;
        }
    }

    max_error = std::ceil(max_error * 1000.0) / 1000.0;

    if (max_error < 1e-5)
    {
        max_error = 1e-5;
    }

    double y_min_plot = 0.0;
    double y_max_plot = max_error;

    double y_span = y_max_plot - y_min_plot;
    double x_span = x_max_plot - x_min_plot;

    double px_per_unit_x = (W - 2 * margin) / x_span;
    double px_per_unit_y = (H - 2 * margin) / y_span;

    auto to_pixel = [&](double x, double y) -> sf::Vector2f
        {
            float px = static_cast<float>(
                margin + (x - x_min_plot) * px_per_unit_x
                );

            float py = static_cast<float>(
                H - margin - (y - y_min_plot) * px_per_unit_y
                );

            return sf::Vector2f(px, py);
        };

    sf::RenderWindow window(
        sf::VideoMode(W, H),
        "Error: |approximate - exact| (lambda = 0.4)"
    );

    window.setFramerateLimit(60);

    sf::Font font;

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
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

        std::vector<sf::Vertex> grid_lines;

        for (double x = 0.0; x <= 1.001; x += 0.1)
        {
            grid_lines.push_back(
                sf::Vertex(to_pixel(x, y_min_plot), sf::Color(235, 235, 235))
            );

            grid_lines.push_back(
                sf::Vertex(to_pixel(x, y_max_plot), sf::Color(235, 235, 235))
            );
        }

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_min_plot, 0), sf::Color::Black)
        );

        grid_lines.push_back(
            sf::Vertex(to_pixel(x_max_plot, 0), sf::Color::Black)
        );

        window.draw(grid_lines.data(), grid_lines.size(), sf::Lines);

        sf::VertexArray error_curve(sf::LineStrip, m + 1);

        for (int i = 0; i <= m; ++i)
        {
            double error = std::abs(
                x_approx[i] - exact_solution(grid[i], lambda)
            );

            error_curve[i] = sf::Vertex(
                to_pixel(grid[i], error),
                sf::Color::Red
            );
        }

        window.draw(error_curve);

        if (font.getInfo().family != "")
        {
            for (double x = 0.0; x <= 1.001; x += 0.2)
            {
                sf::Text text(format_number(x), font, 14);
                text.setFillColor(sf::Color::Black);

                sf::FloatRect bounds = text.getLocalBounds();
                sf::Vector2f position = to_pixel(x, 0.0);

                text.setPosition(
                    position.x - bounds.width / 2.f,
                    position.y + 5.f
                );

                window.draw(text);
            }

            std::ostringstream stream;
            stream << std::scientific << std::setprecision(1) << max_error;

            sf::Text error_label(stream.str(), font, 14);
            error_label.setFillColor(sf::Color::Black);
            error_label.setPosition(margin - 50.f, margin);

            window.draw(error_label);

            sf::Text title(
                "Error |x_approx(t) - x_exact(t)|",
                font,
                18
            );

            title.setFillColor(sf::Color::Red);
            title.setPosition(margin + 100, 10);

            window.draw(title);
        }

        window.display();
    }
}

int main()
{
    double lambda = 0.4;
    double eps = 1e-3;

    double a = 0.0;
    double b = 1.0;
    double h = 0.05;

    int m = static_cast<int>((b - a) / h);

    std::vector<double> grid(m + 1);

    for (int i = 0; i <= m; ++i)
    {
        grid[i] = a + i * h;
    }

    std::vector<double> x_approx =
        solve_integral_equation(0, lambda, eps, grid, h);

    solve_integral_equation(1, lambda, eps, grid, h);

    double max_diff = 0.0;

    for (int i = 0; i <= m; ++i)
    {
        double diff = std::abs(
            x_approx[i] - exact_solution(grid[i], lambda)
        );

        if (diff > max_diff)
        {
            max_diff = diff;
        }
    }

    std::cout << "Maximum difference between exact and approximate solutions: "
        << max_diff << "\n";

    draw_solution_plot(grid, x_approx, lambda);
    draw_error_plot(grid, x_approx, lambda);

    return 0;
}
