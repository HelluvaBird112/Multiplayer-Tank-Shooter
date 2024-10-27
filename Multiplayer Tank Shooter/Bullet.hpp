

#include <SFML/Graphics.hpp>
#include "Enum.hpp"
class Bullet {
public:
    Bullet(float startX, float startY, Direction dir);
    void update();
    void draw(sf::RenderTarget& target);
    bool isOutside();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    Direction direction;
};

