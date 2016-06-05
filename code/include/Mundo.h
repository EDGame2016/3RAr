#ifndef MUNDO_H
#define MUNDO_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Foguete.h"

class Mundo
{
public:
    enum Evento
    {
        NONE,
        PAUSA
    };

public:
    Mundo(sf::RenderWindow& window);
    void								atualiza(sf::Time dt);
    void								desenha();
    Evento                              processaEventos();
    void                                playerInput(sf::Keyboard::Key key, bool isPressed);

private:
    void								loadTexturas();
    void								constroiCena();


public:

    enum Layer
    {
        Background,
        Middle,
        Top,
        LayerCount
    };

    enum BackgroundTexturas
    {
        Grama,
        Troposfera,
        Estratosfera,
        Mesosfera,
        Termosfera,
        Exosfera,
        T1,
        T2,
        T3,
        T4,
        BackTexturasCount
    };

    enum ObjetosTexturas
    {
        Nave,
        Fogo1,
        Fogo2,
        ObjetosTexturasCount
    };

 public:   enum Estados
    {
        PAUSADO,
        JOGANDO,
        INICIO
    };


private:

    sf::RenderWindow&					tela;
    sf::View							mundoView;

    NodeCena							cenaTree;
    std::array<NodeCena*, LayerCount>	layersCena;

    std::array<sf::Texture, BackTexturasCount> background;
    std::array<sf::Texture, ObjetosTexturasCount> objetoText;

    sf::FloatRect						mundoBounds;
    sf::Vector2f						viewCenter;
    float								scrollSpeed;

    Foguete* player;
    Estados estado;

};

#endif // MUNDO_H
