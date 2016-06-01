#include "Foguete.h"
#include <iostream>
#include <math.h>

#define PI 3.14

Foguete::Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2):
    sprite(foguete),
    fogo(),
    launchSound()
{
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    fogo[0].setTexture(fogo1);
    fogo[1].setTexture(fogo2);
    for(int i = 0; i < 2; i++)
    {
        fogo[i].setOrigin(fogo[i].getGlobalBounds().width/2, fogo[i].getGlobalBounds().height/2);
        fogo[i].setPosition(0,sprite.getGlobalBounds().top+sprite.getGlobalBounds().height+5);
    }
    SpriteNode* aux = new SpriteNode(fogo1);
    this->velocidade = 0;
}

sf::FloatRect Foguete::getBoundingRect() const
{
    return this->sprite.getGlobalBounds();
}

void Foguete::setSound(sf::SoundBuffer& buffer)
{
    std::cout<<"aqui";
    launchSound.setBuffer(buffer);

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

void Foguete::colidiuLateral()
{
    setDirecao(-direcao.x, direcao.y);
    this->setRotation(-getRotation());
}

sf::Sprite Foguete::getSprite() const
{
    sf::Sprite aux;
    aux = this->sprite;
    aux.setScale(getScale());
    aux.setPosition(this->getWorldPosition());
    aux.setRotation(this->getRotation());

    return aux;
}

void Foguete::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (velocidade > 100)
    {
        target.draw(fogo[0], states);
    }
}

void Foguete::atualizaAtual(sf::Time dt)
{

    if(velocidade <= 100)
    {
        acelera(5*dt.asSeconds()/2);
        atualizaVelocidade();
    }

    else if (velocidade > 100 && velocidade < 300)
    {
        //if(launchSound.Stopped)
            //launchSound.play();
        acelera(10*dt.asSeconds());
        atualizaVelocidade();
    }
    sf::Vector2f position;
    position.x = velocidade* direcao.x *dt.asSeconds();
    position.y = velocidade* direcao.y *dt.asSeconds();
    this->move(position);
}
