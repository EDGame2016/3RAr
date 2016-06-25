#include "Foguete.h"
#include <iostream>
#include <math.h>

#define PI 3.14
#define WIDTH 1280

Foguete::Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2):
    sprite(foguete),
    fogo(),
    partidaSound(),
    tempo(),
    estado(false)
{
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    fogo[0].setTexture(fogo1);
    fogo[1].setTexture(fogo2);
    for(int i = 0; i < 2; i++)
    {
        fogo[i].setOrigin(fogo[i].getGlobalBounds().width/2, fogo[i].getGlobalBounds().height/2);
        fogo[i].setPosition(0,sprite.getGlobalBounds().top+sprite.getGlobalBounds().height+5);
    }

    this->setDirecao(0,-1);

    carga = 5;
    tCarga = 3;
    dano = 5;
    isColliding = false;
    turbo = false;
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

void Foguete::colidiu(Objeto::Tipo objeto)
{
    if(objeto == Objeto::NONE)
    {
        this->isColliding = false;
    }
    else
    {
        if(this->isColliding == false)
        {
            if(objeto == Objeto::NUVEM)
            {

            }
            dano--;
            isColliding = true;
        }

        this->setVelocidade(100);
    }
}

void Foguete::reinicia()
{
    this->setRotation(0);
    setDirecao(0,-1);
    setVelocidade(0);
    setAceleracao(0);
    this->carga = 5;
    setEstado(false);

}

void Foguete::destroi()
{

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

void Foguete::setEstado(bool value)
{
    this->estado = value;
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
    if(this->estado == true)
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
        /**else if(turbo && getVelocidade() < 500)
        {
            acelera(5*dt.asSeconds());
            atualizaVelocidade();
        }**/

        sf::Vector2f position;
        position.x = getVelocidade() * getDirecao().x * dt.asSeconds();
        position.y = getVelocidade() * getDirecao().y * dt.asSeconds();
        this->move(position);

        //Se o jogador tocar as bordas da tela inverte sua direcao
        if((this->getPosition().x <= 10)||(this->getPosition().x >= WIDTH - 10))
        {
            setDirecao(-getDirecao().x, getDirecao().y);
            this->setRotation(-getRotation());
        }
    }
}
