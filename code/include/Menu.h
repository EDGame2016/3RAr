#ifndef MENU_H
#define MENU_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Entidade.h"
#include "Button.h"

class Menu
{
public:

    Menu(sf::RenderWindow& window);

    void atualiza(sf::Time dt);
    void desenha();


private:

    void loadTexturas();
    void constroiCena();

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
    Button* jogar;
    std::array<NodeCena*, LayerCount> layersCena;
    std::array<sf::Texture, TexturaCount> texturas;
};

#endif // MENU_H
