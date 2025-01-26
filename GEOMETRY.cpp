#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <list>
#include <cmath>


void circle_circle_collision(sf::CircleShape& circle1, sf::CircleShape circle2,float&radius1, float&radius2,float &sx1,float&sx2 ) {

    float x1 = circle1.getPosition().x;
    float y1 = circle1.getPosition().y;
    float x2 = circle2.getPosition().x;
    float y2 = circle2.getPosition().y;
    float dy = y1 - y2;
    float dx = x1 - x2;
    float d = std::sqrt((dx * dx ) + ( dy * dy));

    float collision_min_range = radius1+radius2;
    if (d <= collision_min_range) {
        sx1 = -sx1;
        sx2 = -sx2;
    }



}

class Circle {

public:
    sf::CircleShape name;
    float radius;
    float sx;
    float sy;
    float x, y;
    sf::Text text;
    Circle(sf::CircleShape& name, float& radius, float& x, float& y, float& sx, float&sy, sf::Text& text)  : name(name), radius(radius), x(x),y(y), sx(sx), sy(sy), text(text) {};


    void setTextPosition(sf::Text text) {
        text.setPosition(x+radius, y+radius);
    }



};



class RectangleInfo {

 

public:
    sf::RectangleShape rectangle;
    float sx;
    float sy;
    float width, height;
    RectangleInfo(sf::RectangleShape& rectangle, float &sx, float &sy, float&width, float&height ) : rectangle(rectangle), sx(sx), sy(sy),width(width),height(height) {}

};


void check_circle(sf::CircleShape& circle,float& radius,float& circle_x_speed, float& circle_y_speed,int& WIDTH,int& HEIGHT) {

    if (circle.getPosition().x < 0.01f) {
        circle_x_speed = -circle_x_speed;

    }

    else if (circle.getPosition().x + 2 * radius > WIDTH - 0.01f) {
        circle_x_speed = -circle_x_speed;
    }
    else if (circle.getPosition().y < 0.01f) {
        circle_y_speed = -circle_y_speed;
    }
    else if (circle.getPosition().y + 2 * radius + 0.01f > HEIGHT) {
        circle_y_speed = -circle_y_speed;

    }
    circle.move(circle_x_speed, circle_y_speed);

}

void check_rectangle(sf::RectangleShape& rectangle, float& rectangle_width, float& rectangle_height, float& rectangle_x_speed, float& rectangle_y_speed,int&WIDTH,int&HEIGHT)
{

    if (rectangle.getPosition().x < 0.01f) {
        rectangle_x_speed = -rectangle_x_speed;

    }

    else if (rectangle.getPosition().x +rectangle_width > WIDTH - 0.01f) {
        rectangle_x_speed = -rectangle_x_speed;

    }
    else if (rectangle.getPosition().y < 0.01f) {
        rectangle_y_speed = -rectangle_y_speed;
    }
    else if (rectangle.getPosition().y + rectangle_width + 0.01f > HEIGHT) {
        rectangle_y_speed = -rectangle_y_speed;

    }
    rectangle.move(rectangle_x_speed, rectangle_y_speed);

}
void LoadFromFileRectangle(const std::string& file_name,int& WIDTH, int& HEIGHT, std::list<RectangleInfo>& RECTANGLE_LIST,std::list<Circle>& CIRCLE_LIST)
{
    std::ifstream fin(file_name);
    std::string name,NICKNAME;
    sf::Font font;
    sf::Text text;
    font.loadFromFile("C:/Users/anime/OneDrive/Masaüstü/Genflox.ttf");
    text.setFont(font);
    text.setCharacterSize(30);

    float x, y, sx, sy, r, g, b, width, height;
    float radius;
    while (fin >> name)
    {

        if (name == "Rectangle")
        {
            fin >> NICKNAME>> x >> y >> sx >> sy >> r >> g >> b >> width >> height;
            sf::RectangleShape name(sf::Vector2f(width, height));
            name.setPosition(x, y);
            std::cout << x << std::endl;;
            name.setFillColor(sf::Color(r, g, b));
            RECTANGLE_LIST.push_back(RectangleInfo(name,sx,sy,height,width));
        }

        else if (name == "Circle") {

            fin >> NICKNAME>> x >> y >> sx >> sy >> r >> g >> b>>radius;
            
            sf:: CircleShape name (radius);
            name.setPosition(x, y);
            std::cout << x << std::endl;;

            name.setFillColor(sf::Color (r,g,b));
            text.setString(NICKNAME);
            text.setPosition(x + radius, y + radius);

            CIRCLE_LIST.push_back(Circle(name, radius, x,y ,sx, sy,text));



        }
    }

    fin.close();
}


int main() {
    std::list<RectangleInfo>RECTANGLE_LIST;
    std::list<Circle> CIRCLE_LIST;
    int WIDTH = 1000;
    int HEIGHT = 800;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "my window");
    LoadFromFileRectangle("C:/Users/anime/OneDrive/Masaüstü/shape_file.txt", WIDTH, HEIGHT, RECTANGLE_LIST,CIRCLE_LIST);
    while (window.isOpen())

    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }


        window.clear(sf::Color::Black);



        for (auto& classes : RECTANGLE_LIST) {
            window.draw(classes.rectangle);
            check_rectangle(classes.rectangle, classes.width,classes.height, classes.sx, classes.sy, WIDTH, HEIGHT);

        }

        for (auto& classes : CIRCLE_LIST) {
            window.draw(classes.name);
            check_circle(classes.name, classes.radius, classes.sx, classes.sy, WIDTH, HEIGHT);
            classes.setTextPosition(classes.text);

            for (auto& classe : CIRCLE_LIST) {
                circle_circle_collision(classes.name, classe.name, classes.radius, classe.radius,  classes.sx, classe.sx);
            }
        }


        
        window.display();
    }
    
    return 0;
}



