#include "Foguete.h"
#include <iostream>
#include <math.h>

#define PI 3.14

Foguete::Foguete(const sf::Texture& foguete):
    sprite(foguete)
{

    this->setOriginCenter();
    this->velocidade = 200;
}

sf::FloatRect Foguete::getBoundingRect() const
{
    return sprite.getGlobalBounds();
}

void Foguete::moveEsq()
{
    this->rotate(-5);
    direcao.x = sin(this->getRotation()*PI/180.f);
    direcao.y = -cos(this->getRotation()*PI/180.f);
}

void Foguete::moveDir()
{
    this->rotate(5);
    direcao.x = sin(this->getRotation()*PI/180.f);
    direcao.y = -cos(this->getRotation()*PI/180.f);
}

void Foguete::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Foguete::atualizaAtual(sf::Time dt)
{
    sf::Vector2f position;
    position.x = velocidade* direcao.x *dt.asSeconds();
    position.y = velocidade* direcao.y *dt.asSeconds();
    this->move(position);
}
