#include "Menu.h"
#include <iostream>
Menu::Menu(sf::RenderWindow& window):
    tela(window),
    cenaTree(),
    logoSprite(),
    musica(),
    jogar(),
    sair(),
    layersCena(),
    texturas()
{
    constroiCena();
}

void Menu::atualiza(sf::Time dt)
{
    logoSprite->getFilhos()[0]->rotate(-dt.asSeconds());

    jogar->isPressed(tela);
    sair->isPressed(tela);
}

Menu::Evento Menu::processaEventos()
{
    sf::Event event;

    while (tela.pollEvent(event))
    {
        switch (event.type)
        {
        case (sf::Event::MouseButtonReleased):
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(jogar->isSelected(tela))
                    return JOGAR;
                else if(sair->isSelected(tela))
                    return SAIR;
                else
                    return NONE;
            }
            else
                return NONE;
        }
        case (sf::Event::KeyPressed):
        {
            if(event.key.code == sf::Keyboard::Escape)
                tela.close();
            break;
        }
        default:
            return NONE;
            break;
        }
    }
}

void Menu::desenha()
{
    tela.clear(sf::Color(255,255,255,0));
    tela.draw(cenaTree);
}

void Menu::playMusic()
{
    musica.play();
}
void Menu::stopMusic()
{
    musica.stop();
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

    musica.openFromFile("src/sound/mainMenu.ogg");
    musica.setLoop(true);
}

void Menu::constroiCena()
{
    sf::Vector2f telaSize = tela.getDefaultView().getSize();

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
    logoSprite->setOriginCenter();
    logoSprite->setPosition(backgroundSprite->getBoundingRect().width/2, backgroundSprite->getBoundingRect().height/2);
    backgroundSprite->insereFilho(logoSprite);

    SpriteNode* elementosSprite(new SpriteNode(texturas[Elementos]));
    elementosSprite->setOriginCenter();
    logoSprite->insereFilho(elementosSprite);

    SpriteNode* tituloSprite(new SpriteNode(texturas[Titulo]));
    tituloSprite->setScale(0.5, 0.5);
    tituloSprite->setOriginCenter();
    tituloSprite->setPosition(16*telaSize.x/20.f, 2.5*telaSize.y/10.f);
    layersCena[Background]->insereFilho(tituloSprite);

    jogar = new Button(texturas[JogarD], texturas[JogarS]);
    jogar->setPosition(16*telaSize.x/20.f, 6*telaSize.y/10.f);
    jogar->setOriginCenter();
    jogar->setScale(0.5, 0.5);
    layersCena[Top]->insereFilho(jogar);

    sair = new Button(texturas[SairD], texturas[SairS]);
    sair->setPosition(0, 300.f);
    jogar->insereFilho(sair);

    playMusic();
}
