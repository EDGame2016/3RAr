#ifndef BATERIA_H
#define BATERIA_H

#include <SFML/Graphics.hpp>
#include "NodeCena.h"

class Bateria: public NodeCena
{
public:
            Bateria(const sf::Texture& capa, const sf::Texture& celula);
    void    setCarga(int *carga);
    void    setPosition(float x, float y);

private:
    void    desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const;
    void    atualizaAtual(sf::Time dt);

private:
    int *carga;
    sf::Sprite  capa;
    sf::Sprite  celula;
};

#endif // BATERIA_H
