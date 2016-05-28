#ifndef MUNDO_H
#define MUNDO_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Entidade.h"

class Mundo
{
public:

                                        Mundo(sf::RenderWindow& window);
    void								atualiza(sf::Time dt);
    void								desenha();


private:
    void								loadTexturas();
    void								constroiCena();


private:

    enum Layer
    {
        Background,
        Middle,
        Top,
        LayerCount
    };


private:

    sf::RenderWindow&					tela;
    sf::View							mundoView;

    NodeCena							cenaTree;
    std::array<NodeCena*, LayerCount>	layersCena;

    sf::FloatRect						mundoBounds;
    sf::Vector2f						viewCenter;
    float								scrollSpeed;

    //sf::Texture background[5];
    sf::Texture test;
    sf::Texture test2;
};

#endif // MUNDO_H
