#include "Menu.h"
#include <iostream>
Menu::Menu(sf::RenderWindow& window):
    tela(window),
    cenaTree(),
    logoSprite(),
    jogar(),
    layersCena(),
    texturas()
{
    constroiCena();
}

void Menu::atualiza(sf::Time dt)
{
    logoSprite->getFilhos()[0]->rotate(-dt.asSeconds());
    jogar->isPressed(tela);
}
void Menu::desenha()
{
    tela.clear(sf::Color(255,255,255,0));
    tela.draw(cenaTree);
}

void Menu::loadTexturas()
{
    texturas[Estrelas].loadFromFile("src/images/menu/estrelas.png");
    texturas[Logo].loadFromFile("src/images/menu/logo.png");
    texturas[Elementos].loadFromFile("src/images/menu/elementos.png");
    texturas[Titulo].loadFromFile("src/images/menu/titulo.png");
    texturas[JogarD].loadFromFile("src/images/menu/jogarD.png");
    texturas[JogarS].loadFromFile("src/images/menu/JogarS.png");
    texturas[SairD].loadFromFile("src/images/menu/sairD.png");
    texturas[SairS].loadFromFile("src/images/menu/sairS.png");

    for(int i = 0; i < TexturaCount; i++)
    {
        texturas[i].setSmooth(true);
    }
}

void Menu::constroiCena()
{
    int i;

    for (i = 0; i < LayerCount; i++)
    {
        NodeCena* layer;
        layer = new NodeCena;
        layersCena[i] = layer;
        cenaTree.insereFilho(layer);
    }

    loadTexturas();

    SpriteNode* backgroundSprite(new SpriteNode(texturas[Estrelas]));
    backgroundSprite->setPosition(0, 0);
    backgroundSprite->setScale(0.5,0.5);
    layersCena[Background]->insereFilho(backgroundSprite);

    logoSprite = new SpriteNode(texturas[Logo]);
    logoSprite->setOrigin(logoSprite->getGlobalBounds().width/2, logoSprite->getGlobalBounds().height/2);
    logoSprite->setPosition(backgroundSprite->getGlobalBounds().width/2,backgroundSprite->getGlobalBounds().height/2);
    backgroundSprite->insereFilho(logoSprite);

    SpriteNode* elementosSprite(new SpriteNode(texturas[Elementos]));
    elementosSprite->setOrigin(elementosSprite->getGlobalBounds().width/2, elementosSprite->getGlobalBounds().height/2);
    elementosSprite->setPosition(logoSprite->getGlobalBounds().width/2,logoSprite->getGlobalBounds().height/2);
    logoSprite->insereFilho(elementosSprite);

    SpriteNode* tituloSprite(new SpriteNode(texturas[Titulo]));
    tituloSprite->setOrigin(tituloSprite->getGlobalBounds().width/2, tituloSprite->getGlobalBounds().height/2);
    tituloSprite->setScale(0.5, 0.5);
    tituloSprite->setPosition(1000, 200);
    layersCena[Background]->insereFilho(tituloSprite);

    jogar = new Button(texturas[JogarD], texturas[JogarS]);
    jogar->setOrigin(jogar->getBoundingRect().width/2, jogar->getBoundingRect().height/2);
    //jogar->setPosition(500.f, 500.f);
    jogar->setScale(0.5, 0.5);
    layersCena[Top]->insereFilho(jogar);
}
