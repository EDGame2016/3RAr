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
    NodeCena            telaCamadas;
    NodeCena            telaFinal;

    std::array<sf::Texture, 8>  texturas;

    SpriteNode*     icone;
    SpriteNode*     info;
    Button*         continuar;
    Button*         continuarFinal;
    bool            estado;
};

#endif // TELA_H
