#include "Tela.h"

Tela::Tela(sf::RenderWindow& window):
    tela(window),
    texturas(),
    icone(),
    info(),
    continuar()
{
    constroiCena();
}

void Tela::atualiza(sf::Time dt)
{
    continuar->isPressed(tela);
}

void Tela::setCamada(int altura)
{

    if(altura > 5800) /// Troposfera
    {
        info->setTexture(texturas[0]);
    }
    else if(altura > 3600) /// Estatosfera
    {
        info->setTexture(texturas[1]);
    }
    else if(altura > 2200) /// Mesosfera
    {
        info->setTexture(texturas[2]);
    }
    else if(altura > 800) /// Termosfera
    {
        info->setTexture(texturas[3]);
    }
    else /// Exosfera
    {
        //info->setTexture(texturas[4]);
    }
}

bool Tela::processaEventos()
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
                if(continuar->isSelected(tela))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        case (sf::Event::KeyPressed):
        {
            if(event.key.code == sf::Keyboard::Escape)
                tela.close();
            break;
        }
        default:
            break;
        }
    }

    return false;
}

void Tela::desenha()
{
    tela.clear(sf::Color(255,255,255,0));

    tela.draw(cenaTree);
}

void Tela::loadTexturas()
{
    texturas[0].loadFromFile("src/images/telas/c1.png");
    texturas[1].loadFromFile("src/images/telas/c2.png");
    texturas[2].loadFromFile("src/images/telas/c3.png");
    texturas[3].loadFromFile("src/images/telas/c4.png");
    texturas[5].loadFromFile("src/images/telas/continuarD.png");
    texturas[6].loadFromFile("src/images/telas/continuarS.png");
    texturas[7].loadFromFile("src/images/telas/foguete.png");


    for(int i = 0; i < 8; i++)
    {
        texturas[i].setSmooth(true);
    }
}

void Tela::constroiCena()
{
    sf::Vector2f telaSize = tela.getDefaultView().getSize();

    loadTexturas();

    icone = new SpriteNode(texturas[7]);
    icone->setOriginCenter();
    icone->setPosition(telaSize.x/4, 100 + telaSize.y/2);
    icone->setScale(0.5,0.5);
    cenaTree.insereFilho(icone);

    info = new SpriteNode(texturas[0]);
    info->setOriginCenter();
    info->setPosition(3*telaSize.x/4.f, telaSize.y/2);
    cenaTree.insereFilho(info);

    continuar = new Button(texturas[5], texturas[6]);
    continuar->setPosition(3*telaSize.x/4.f, 8*telaSize.y/10.f);
    continuar->setOriginCenter();
    continuar->setScale(0.5, 0.5);
    cenaTree.insereFilho(continuar);
}
