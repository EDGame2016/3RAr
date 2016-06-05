#ifndef MENU_H
#define MENU_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Button.h"

class Menu
{

public:

    enum Evento
    {
        NONE,
        JOGAR,
        SAIR
    };

public:

                        Menu(sf::RenderWindow& window);

    void                atualiza(sf::Time dt);
    Evento              processaEventos();
    void                desenha();
    void                playMusic();
    void                stopMusic();

private:

    void                loadTexturas();
    void                constroiCena();

private:

    enum Layer
    {
        Background,
        Top,
        LayerCount
    };

    enum Textura
    {
        Estrelas,
        Logo,
        Elementos,
        Titulo,
        JogarD,
        JogarS,
        SairD,
        SairS,
        TexturaCount
    };


private:

    sf::RenderWindow& tela;
    NodeCena cenaTree;
    SpriteNode* logoSprite;
    sf::Music musica;

    std::array<NodeCena*, LayerCount> layersCena;
    std::array<sf::Texture, TexturaCount> texturas;

    Button* jogar;
    Button* sair;

};

#endif // MENU_H
