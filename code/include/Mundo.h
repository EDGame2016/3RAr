#ifndef MUNDO_H
#define MUNDO_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>
#include <stdlib.h>
#include <time.h>
#include "toString.h"

#include "Skills.h"
#include "NodeCena.h"
#include "SpriteNode.h"
#include "Foguete.h"
#include "Bateria.h"
#include "Tela.h"
#include "Objeto.h"
#include "ObjetoHolder.h"

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
        SKILL,
        JOGANDO,
        INICIO
    };

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
        BAR,
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
        OzonioR,
        OzonioB,
        BateriaCapa,
        BateriaCelula,
        ObjetosTexturasCount
    };

    enum SoundFX
    {
        navePartindo,
        SoundFXCount
    };

public:
    Mundo(sf::RenderWindow& window);
    void    atualiza(sf::Time dt);
    void    desenha();
    Evento  processaEventos();
    void    playerInput(sf::Keyboard::Key key, bool isPressed);
    Estados getEstado()const;
    void    reinicia();
    void    abandona();

private:
    void    geraCamada(int camadaID);
    void    destroiCamadas();
    void    gerenciaObjetos();
    void    loadTexturas();
    void    constroiCena();

private:
    sf::RenderWindow&   tela;
    sf::View            mundoView;

    NodeCena    cenaTree;
    Skills      skills;
    Tela        gerenciadorJanela;

    std::array<NodeCena*, LayerCount>               layersCena;
    std::array<ObjetoHolder*, 5>                    camadasAtm;
    std::array<bool, 5>                             controlCamadas;

    std::array<sf::Texture, BackTexturasCount>      background;
    std::array<sf::Texture, ObjetosTexturasCount>   objetoText;
    std::array<sf::Texture, 8>                      nuvensText;
    std::array<sf::SoundBuffer, SoundFXCount>       soundsBuffer;

    sf::FloatRect   mundoBounds;
    sf::Vector2f    viewCenter;
    float           scrollSpeed;

    Foguete*    player;
    SpriteNode* grama;
    SpriteNode* barra;

    Bateria*    bateria;
    Estados     estadoAtual;
};

#endif // MUNDO_H
