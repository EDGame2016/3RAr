#ifndef OBJETO_H
#define OBJETO_H

#include <SFML/Graphics.hpp>

#include "Entidade.h"
class Objeto: public Entidade
{
public:
    enum Tipo
    {
        NUVEM,
        BALAO,
        COMETA,
        SATELITE
    };

public:
    Objeto(Tipo ID,const sf::Texture& textura);
    sf::Sprite  getSprite() const;

private:
    void    desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
    void    atualizaAtual(sf::Time dt);

private:
    Tipo ID;
    sf::Sprite sprite;
};

#endif // OBJETO_H
