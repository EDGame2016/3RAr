#include "Foguete.h"
#include <iostream>
#include <math.h>

#define PI 3.14

Foguete::Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2):
    sprite(foguete),
    fogo(),
    partidaSound(),
    tempo()
{
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    fogo[0].setTexture(fogo1);
    fogo[1].setTexture(fogo2);
    for(int i = 0; i < 2; i++)
    {
        fogo[i].setOrigin(fogo[i].getGlobalBounds().width/2, fogo[i].getGlobalBounds().height/2);
        fogo[i].setPosition(0,sprite.getGlobalBounds().top+sprite.getGlobalBounds().height+5);
    }
    //SpriteNode* aux = new SpriteNode(fogo1);

    carga = 5;
    tCarga = 3;
    turbo=false;
    tempo = sf::Time::Zero;
}

void Foguete::setSound(sf::SoundBuffer& buffer)
{
    partidaSound.setBuffer(buffer);
}

void Foguete::moveEsq()
{
    this->rotate(-5);
    setDirecao(sin(this->getRotation()*PI/180.f), -cos(this->getRotation()*PI/180.f));
}

void Foguete::moveDir()
{
    this->rotate(5);
    setDirecao(sin(this->getRotation()*PI/180.f),-cos(this->getRotation()*PI/180.f));
}

void Foguete::colidiuLateral()
{
    setDirecao(-getDirecao().x, getDirecao().y);
    this->setRotation(-getRotation());
}

sf::FloatRect Foguete::getBoundingRect() const
{
    return this->sprite.getGlobalBounds();
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

int Foguete::getCarga() const
{
    return carga;
}

void Foguete::reinicia(int carga)
{
    this->setRotation(0);
    setDirecao(0,-1);
    setVelocidade(0);
    setAceleracao(0);
    this->carga = carga;

}


void Foguete::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (getVelocidade() > 100)
    {
        target.draw(fogo[0], states);
    }
}

void Foguete::atualizaAtual(sf::Time dt)
{
    tempo += dt;
    if(tempo.asSeconds()>tCarga)
    {
        carga--;
        tempo = sf::Time::Zero;
    }

    if(getVelocidade() <= 100)
    {
        acelera(5*dt.asSeconds()/2);
        atualizaVelocidade();
    }

    else if (getVelocidade() > 100 && getVelocidade() < 300)
    {
        acelera(10*dt.asSeconds());
        atualizaVelocidade();
    }
    else if(turbo && getVelocidade() < 500)
    {
        acelera(5*dt.asSeconds());
        atualizaVelocidade();
    }
    sf::Vector2f position;
    position.x = getVelocidade()* getDirecao().x *dt.asSeconds();
    position.y = getVelocidade()* getDirecao().y *dt.asSeconds();
    this->move(position);
}
