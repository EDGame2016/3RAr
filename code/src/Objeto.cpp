#include "Objeto.h"
#include "iostream"

Objeto::Objeto(Tipo ID, const sf::Texture& textura):
    sprite(textura)
{
    //sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    this->ID = ID;
    /**Ajustar essa parte**/
    this->setVelocidade(10);
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
}
