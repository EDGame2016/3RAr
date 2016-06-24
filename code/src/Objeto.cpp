#include "Objeto.h"

#define WIDTH 1280

Objeto::Objeto(Tipo ID, const sf::Texture& textura):
    sprite(textura)
{
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    this->ID = ID;
    /**Ajustar essa parte**/
    this->setDirecao(1,0);
}

sf::Sprite Objeto::getSprite() const
{
    sf::Sprite aux;
    aux = this->sprite;
    aux.setScale(getScale());
    aux.setPosition(this->getWorldPosition());
    aux.setRotation(this->getRotation());

    return aux;
}

Objeto::Tipo Objeto::getTipo()
{
    return this->ID;
}

void Objeto::setColor(int r, int g, int b, int a)
{
    this->sprite.setColor(sf::Color(r,g,b,a));
}

void Objeto::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(sprite, states);
}

void Objeto::atualizaAtual(sf::Time dt)
{
    sf::Vector2f position;
    position.x = getVelocidade() * getDirecao().x * dt.asSeconds();
    position.y = getVelocidade() * getDirecao().y * dt.asSeconds();
    this->move(position);

    if((this->getPosition().x <= 10)||(this->getPosition().x >= WIDTH - 10))
    {
        setDirecao(-getDirecao().x, getDirecao().y);
        this->setRotation(-getRotation());
    }
}
