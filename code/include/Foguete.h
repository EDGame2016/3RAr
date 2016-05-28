#ifndef FOGUETE_H
#define FOGUETE_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entidade.h"
class Foguete: public Entidade
{
public:
                        Foguete();

private:
    sf::Sprite sprite;
    sf::Vector2f speed;
};

#endif // FOGUETE_H
