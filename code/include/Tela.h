#ifndef TELA_H
#define TELA_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Button.h"

class Tela
{
public:
                Tela(sf::RenderWindow& window);
    void        atualiza(sf::Time dt);
    void        setCamada(int altura);
    bool        processaEventos();
    void        desenha();

private:
    void                loadTexturas();
    void                constroiCena();

private:

    sf::RenderWindow&   tela;
    NodeCena            cenaTree;

    std::array<sf::Texture, 8>  texturas;

    SpriteNode*     icone;
    SpriteNode*     info;
    Button*         continuar;
};

#endif // TELA_H
