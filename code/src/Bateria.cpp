#include "Bateria.h"

Bateria::Bateria(const sf::Texture& capaText, const sf::Texture& celulaText):capa(capaText), celula(celulaText)
{
    carga = 5;
    capa.setOrigin(capa.getGlobalBounds().width/2, capa.getGlobalBounds().height/2);
    capa.setRotation(-90);
    capa.setScale(0.5, 0.5);

    celula.setOrigin(celula.getGlobalBounds().width/2, celula.getGlobalBounds().height/2);
    celula.setRotation(-90);
    celula.setScale(0.5, 0.5);
    celula.setPosition(-90,0);
    celula.setColor(sf::Color(141, 200, 50));

}

void Bateria::setCarga(int carga)
{
    this->carga = carga;

    switch(carga)
    {
    case 5:
    {
        celula.setColor(sf::Color(141, 200, 50));
        break;
    }
    case 4:
    {
        celula.setColor(sf::Color(201, 219, 36));
        break;
    }
    case 3:
    {
        celula.setColor(sf::Color(227, 182, 18));
        break;
    }
    case 2:
    {
        celula.setColor(sf::Color(235, 146, 43));
        break;
    }
    case 1:
    {
        celula.setColor(sf::Color(190, 22, 34));
        break;
    }
    default:
        break;

    }
}

void    Bateria::setPosition(float x, float y)
{
    this->capa.setPosition(x, y);
    this->celula.setPosition(x + 45, y);
}

int Bateria::getCarga()
{
    return this->carga;
}

void Bateria::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(capa, states);
    sf::Sprite aux = celula;
    sf::Vector2f pos = aux.getPosition();
    //target.draw(aux);
    for(int i = 0; i < carga; i++)
    {
        aux.setPosition(-20*i + pos.x, pos.y);
        target.draw(aux);
    }
    //celula.move(-i*10, 0);
}

int Bateria::reinicia()
{
    this->setCarga(5);
    return this->carga;
}

