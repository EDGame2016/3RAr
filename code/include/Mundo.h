#ifndef MUNDO_H
#define MUNDO_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include "Collision.h"
#include "toString.h"

#include "Skills.h"
#include "NodeCena.h"
#include "SpriteNode.h"
#include "Foguete.h"

class Mundo
{
public:
    enum Evento
    {
        NONE,
        BACK
    };

    enum Estados
    {
        PAUSADO,
        JOGANDO,
        INICIO
    };

public:
    Mundo(sf::RenderWindow& window);
    void								atualiza(sf::Time dt);
    void								desenha();
    Evento                              processaEventos();
    void                                playerInput(sf::Keyboard::Key key, bool isPressed);
    void                                setEstado(Mundo::Estados estado);
    Estados                             getEstado()const;

private:
    void								loadTexturas();
    void								constroiCena();


private:

    enum Layer
    {
        Background,
        MiddleBack,
        MiddleTop,
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
        Cometa,
        Balao1,
        Balao2,
        Satelite,
        ObjetosTexturasCount
    };

    enum SoundFX
    {
        Lauch,
        SoundFXCount
    };
private:

    sf::RenderWindow&					            tela;
    sf::View						                mundoView;

    NodeCena							            cenaTree;
    Skills                                          skills;
    std::array<NodeCena*, LayerCount>	            layersCena;

    std::array<sf::Texture, BackTexturasCount>      background;
    std::array<sf::Texture, ObjetosTexturasCount>   objetoText;
    std::array<sf::Texture, 8>                      nuvens;
    //std::array<sf::SoundBuffer, SoundFXCount>       sounds;
    //sf::SoundBuffer sounds;

    sf::FloatRect						            mundoBounds;
    sf::Vector2f						            viewCenter;
    float								            scrollSpeed;

    Foguete*                                        player;
    SpriteNode*                                     grama;
    Estados                                         estadoAtual;

};

#endif // MUNDO_H
