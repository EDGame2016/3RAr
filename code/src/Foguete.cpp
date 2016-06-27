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

    for(int i = 0; i < 7; i++)
        aprimoramento[i] = false;

    this->setDirecao(0,-1);

    carga = 5;
    tCarga = 3;
    dano = 5;
    shield = 100;
    isColliding = false;
    turbo = false;
    ignoraNuvem = false;
    camadaOzonio = false;
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
        if(objeto != Objeto::SKILLNONE)
        {
            if(this->isColliding == false)
            {
                if(objeto == Objeto::NUVEM)
                {
                    if(!ignoraNuvem)
                    {
                        dano--;
                        this->setVelocidade(this->shield);
                    }
                }
                else if(objeto == Objeto::OZONIO)
                {
                    if(!camadaOzonio)
                    {
                        dano = dano -2;
                    }
                }
                else if(objeto == Objeto::COMETA || objeto == Objeto::SATELITE || objeto == Objeto::BALAO)
                {
                    dano--;
                    this->setVelocidade(this->shield);
                }
                isColliding = true;
            }

        }
        if(objeto == Objeto::SKILLCO2)
        {
            aprimoramento[SkillsNode::CO2] = true;
        }
        if(objeto == Objeto::SKILLSHIELD)
        {
            aprimoramento[SkillsNode::SHIELD] = true;

        }
        if(objeto == Objeto::SKILLSPEED)
        {
            aprimoramento[SkillsNode::SPEED] = true;
        }
        if(objeto == Objeto::SKILLGAS)
        {
            aprimoramento[SkillsNode::GAS] = true;
        }
        if(objeto == Objeto::SKILLSPRAY)
        {
            aprimoramento[SkillsNode::SPRAY] = true;
        }
        if(objeto == Objeto::SKILLCOMETA)
        {
            aprimoramento[SkillsNode::COMETA] = true;
        }
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
        else if(turbo && getVelocidade() < 500)
        {
            acelera(5*dt.asSeconds());
            atualizaVelocidade();
        }

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
