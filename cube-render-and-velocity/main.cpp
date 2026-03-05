#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Vec2 {
    float x, y;
};

struct Vector2 {
    Vec2 points[5];

    Vector2() = default;

    Vector2(Vec2 _a1, Vec2 _a2, Vec2 _b2, Vec2 _b1)
        : points{_a1, _a2, _b2, _b1, _a1} {}
};

struct StructRectangle {
    Vector2 pos;
    Vec2 velocity;
    float rotation;
    float rotationvelocity;
    Vec2 center;
};

StructRectangle Rectangle(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2, float v1, float v2, float r1, float rv) {

    StructRectangle rect;
    rect.pos = Vector2({a1,a2}, {b1,b2}, {c1,c2}, {d1,d2});
    rect.velocity = {0, 200};
    rect.rotation = r1;
    rect.rotationvelocity = rv;

    return rect;
}

struct Colors {
    sf::Color colors[5];

    Colors(sf::Color c1, sf::Color c2, sf::Color c3, sf::Color c4, sf::Color c5)
        : colors{c1, c2, c3, c4, c5} {}
};
const Colors COLORS(sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue, sf::Color::Cyan);

const Vector2 BoundingBox({0,0}, {1920,0}, {1920, 1080}, {0, 1080});

std::vector<StructRectangle> objectVector;

bool TimeP = false;

void CreateRectangle(int x, int y) {
    StructRectangle rect = Rectangle(
        x,y,      //a
        x+50,y,     //b
        x+50,y+50,    //c
        x,y+50,     //d
        0,-10,      //v
        90,          //r
        0.01          //rv
    );
    objectVector.push_back(rect);
    std::cout << objectVector.size() << '\n';
};

void Tick(float dt) {
    for (StructRectangle& rect : objectVector) {
        //rect.velocity.x *= 1;
        rect.velocity.y += 2;

        //std::cout << rect.velocity.y << '\n';

        //rect.rotation += rect.rotationvelocity;

        for (int i = 0; i < 5; i++) {
            rect.pos.points[i].x += rect.velocity.x * dt;
            rect.pos.points[i].y += rect.velocity.y * dt;
        }

        if (TimeP) {
            rect.rotation += rect.rotationvelocity;
            if (rect.rotation > 1) {
                TimeP = false;
            }
        } else {
            rect.rotation -= rect.rotationvelocity;
            if (rect.rotation < -1) {
                TimeP = true;
            }
        }

        rect.center.x = 0;
        rect.center.y = 0;
        for (int i = 0; i < 4; i++) {
            rect.center.x += rect.pos.points[i].x / 4;
            rect.center.y += rect.pos.points[i].y / 4;
        }
        // std::cout << "CENTER.X: " << rect.center.x << ' ';
        // std::cout << "CENTER.Y: " << rect.center.y << '\n';
        for (int i = 0; i < 5; i++) {
            rect.rotation += rect.rotationvelocity;

            for (int i = 0; i < 5; i++) {
            float dx = rect.pos.points[i].x - rect.center.x;
            float dy = rect.pos.points[i].y - rect.center.y;

            rect.pos.points[i].x = dx * cos(rect.rotationvelocity) - dy * sin(rect.rotationvelocity) + rect.center.x;
            rect.pos.points[i].y = dx * sin(rect.rotationvelocity) + dy * cos(rect.rotationvelocity) + rect.center.y;
            }

            //float dxn = dx * cos(rect.rotation) - dy * sin(rect.rotation);
            //float dyn = dy * sin(rect.rotation) - dy * cos(rect.rotation);

            //rect.pos.points[i].x = dxn;
            //rect.pos.points[i].y = dyn;



            //std::cout << cos(rect.rotation) << '\n';
        }

        float lp = rect.pos.points[0].y;
        for (int i = 0; i < 4; i++) {
            if (rect.pos.points[i].y < lp) {
                continue;
            }
            lp = rect.pos.points[i].y;
        }

        if (lp > 1000) {
            rect.velocity.y = -300;
            float comp = lp - 1000;
            for (int i = 0; i < 5; i++) {
                rect.pos.points[i].y -= comp;
            }
        }

        //std::cout << rect.velocity.y << '\n';
    }
};

int main()
{
    sf::Clock clock;

    CreateRectangle(200, 200);

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Bluemoon");
    window.setPosition({0, 0});

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                const auto* mouseEvent =
                    event->getIf<sf::Event::MouseButtonPressed>();

                if (mouseEvent &&
                    mouseEvent->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition();
                    CreateRectangle(pos.x, pos.y);
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        float dt = clock.restart().asSeconds();
        Tick(dt);

        window.clear(sf::Color::Black);

        sf::VertexArray cube(sf::PrimitiveType::LineStrip, 5);

        for (StructRectangle& rect : objectVector) {
            for (int i = 0; i < 5; i++) {
                cube[i].position = sf::Vector2f(rect.pos.points[i].x, rect.pos.points[i].y);
                cube[i].color = COLORS.colors[i];
            }
            window.draw(cube);
        }

        //sf::VertexArray debug(sf::PrimitiveType::Points, 1);
        //debug[0].position = sf::Vector2f(500, 500 + (rect.rotation * 100));
        //debug[0].color = sf::Color::Red;


        // sf::VertexArray triangle(sf::PrimitiveType::LineStrip, 5);

        // triangle[0].position = sf::Vector2f(100.f, 100.f);


        // triangle[0].color = sf::Color::Red;

        //window.draw(debug);

        window.display();
    }
}