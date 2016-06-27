#include "Bateria.h"

Bateria::Bateria(const sf::Texture& capaText, const sf::Texture& celulaText, int ID):
    capa(capaText),
    celula(celulaText)
{
    this->ID = ID;
    carga = nullptr;
    if(ID == 0)
    {
        capa.setOrigin(capa.getGlobalBounds().width/2, capa.getGlobalBounds().height/2);
        capa.setRotation(-90);
        capa.setScale(0.35, 0.35);
        celula.setOrigin(celula.getGlobalBounds().width/2, celula.getGlobalBounds().height/2);
        celula.setRotation(-90);
        celula.setScale(0.35, 0.35);
        celula.setColor(sf::Color(141, 200, 50));
    }
    else
    {
        celula.setOrigin(celula.getGlobalBounds().width/2, celula.getGlobalBounds().height/2);
        celula.setScale(0.15, 0.15);
        //celula.setColor(sf::Color(141, 200, 50));
    }
}

void Bateria::setCarga(int *carga)
{
    this->carga = carga;
}

void Bateria::setPosition(float x, float y)
{
    if(ID == 0)
    {
        this->capa.setPosition(x, y);
        this->celula.setPosition(x + 30, y);
    }
    else
    {
        this->celula.setPosition(x,y);
    }
}

void Bateria::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(ID == 0)
        target.draw(capa, states);
    sf::Sprite aux = celula;
    sf::Vector2f pos = aux.getPosition();
    if(carga != nullptr)
    {
        for(int i = 0; i < *carga; i++)
        {
            if (ID == 0)
                aux.setPosition(-13.5*i + pos.x, pos.y);
            else
                aux.setPosition(-25*i + pos.x, pos.y);
            target.draw(aux);
        }
    }
}

void Bateria::atualizaAtual(sf::Time dt)
{
    if(ID == 0)
    {
        if(carga!=nullptr)
    {
        switch(*carga)
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
    }


}

