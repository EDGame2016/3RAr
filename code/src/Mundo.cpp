#include "Mundo.h"

#include <iostream>

Mundo::Mundo(sf::RenderWindow& window): tela(window),
    mundoView(window.getDefaultView()),
    cenaTree(),
    layersCena(),
    background(),
    objetoText(),
    mundoBounds(0.f, 0.f, mundoView.getSize().x, 8000.f),
    viewCenter(mundoView.getSize().x / 2.f, mundoBounds.height - mundoView.getSize().y / 2.f),
    scrollSpeed(-200.f),
    player(),
    estado(INICIO)
{
    constroiCena();
    mundoView.setCenter(viewCenter);
}

void Mundo::atualiza(sf::Time dt)
{
    mundoView.setCenter(viewCenter.x,player->getPosition().y);

    //Se o jogador tocar as bordas, inverte sua velocidade X
    /*if (position.x <= mundoBounds.left || position.x >= mundoBounds.left + mundoBounds.width)
    {
        velocity.x = -velocity.x;
        player->setVelocidade(velocity);
    }*/

    // Apply movements
    if(estado == JOGANDO)
        cenaTree.atualiza(dt);
}

void Mundo::desenha()
{

    tela.setView(mundoView);
    tela.draw(cenaTree);
}

Mundo::Evento Mundo::processaEventos()
{
    sf::Event event;

    while (tela.pollEvent(event))
    {
        switch (event.type)
        {
        /*case (sf::Event::MouseButtonReleased):
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {

            }
            else
                return NONE;
        }*/
        case (sf::Event::Closed):
        {
            tela.close();
            break;
        }
        case (sf::Event::KeyPressed):
        {
            playerInput(event.key.code, true);
            break;
        }

        case sf::Event::KeyReleased:
        {
            playerInput(event.key.code, false);
            break;
        }
        default:
            return NONE;
            break;
        }
    }

    return NONE;
}

void Mundo::playerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
    case (sf::Keyboard::Escape):
    {
        if(!isPressed)
            estado = PAUSADO;
        break;
    }
    case (sf::Keyboard::Right):
    {
        player->moveDir();
        break;
    }
    case (sf::Keyboard::Left):
    {
        player->moveEsq();
        break;
    }
    case (sf::Keyboard::Space):
    {
        if(estado == INICIO)
            estado = JOGANDO;
    }
    default:
        break;
    }
}


void Mundo::loadTexturas()
{
    background[Grama].loadFromFile("src/images/background/grama.png");
    background[Troposfera].loadFromFile("src/images/background/troposfera.png");
    background[T1].loadFromFile("src/images/background/t1.png");
    background[Estratosfera].loadFromFile("src/images/background/estratosfera.png");
    background[T2].loadFromFile("src/images/background/t2.png");
    background[Mesosfera].loadFromFile("src/images/background/mesosfera.png");
    background[T3].loadFromFile("src/images/background/t3.png");
    background[Termosfera].loadFromFile("src/images/background/termosfera.png");
    background[T4].loadFromFile("src/images/background/t4.png");
    background[Exosfera].loadFromFile("src/images/background/exosfera.png");

    objetoText[Nave].loadFromFile("src/images/objetos/nave.png");
    objetoText[Fogo1].loadFromFile("src/images/objetos/fogo1.png");
    objetoText[Fogo2].loadFromFile("src/images/objetos/fogo2.png");

    for(int i = 0; i < ObjetosTexturasCount; i++)
    {
        objetoText[i].setSmooth(true);
    }
}

void Mundo::constroiCena()
{
    // Inicializa as diferentes camadas (Layers)
    for (int i = 0; i < LayerCount; i++)
    {
        NodeCena* layer;
        layer = new NodeCena;
        layersCena[i] = layer;
        cenaTree.insereFilho(layer);
    }

    loadTexturas();

    sf::FloatRect back1(0.f, 0.f, mundoView.getSize().x, 2150);
    sf::FloatRect back2(0.f, 0.f, mundoView.getSize().x, 2165);
    sf::FloatRect back3(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back4(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back5(0.f, 0.f, mundoView.getSize().x, 815);
    sf::FloatRect back6(0.f, 0.f, mundoView.getSize().x, 360);

    sf::IntRect texturaRect(mundoBounds);
    sf::IntRect texturaRect1(back1);
    sf::IntRect texturaRect2(back2);
    sf::IntRect texturaRect3(back3);
    sf::IntRect texturaRect4(back4);
    sf::IntRect texturaRect5(back5);
    sf::IntRect texturaRect6(back6);

    background[0].setRepeated(false);
    background[1].setRepeated(true);
    background[2].setRepeated(true);
    background[3].setRepeated(true);
    background[4].setRepeated(true);
    background[6].setRepeated(true);
    background[7].setRepeated(true);
    background[8].setRepeated(true);
    background[9].setRepeated(true);


    // Add the background sprite to the scene

    SpriteNode* backgroundSprite1(new SpriteNode(background[1], texturaRect1));
    backgroundSprite1->setPosition(mundoBounds.left, 5852.324);
    layersCena[Background]->insereFilho(backgroundSprite1);

    SpriteNode* backgroundSprite2(new SpriteNode(background[2], texturaRect2));
    backgroundSprite2->setPosition(mundoBounds.left, 3692.651);
    layersCena[Background]->insereFilho(backgroundSprite2);

    SpriteNode* backgroundSprite3(new SpriteNode(background[3], texturaRect3));
    backgroundSprite3->setPosition(mundoBounds.left, 2252.869);
    layersCena[Background]->insereFilho(backgroundSprite3);

    SpriteNode* backgroundSprite4(new SpriteNode(background[4], texturaRect4));
    backgroundSprite4->setPosition(mundoBounds.left, 813.087);
    layersCena[Background]->insereFilho(backgroundSprite4);

    SpriteNode* backgroundSprite5(new SpriteNode(background[5], texturaRect5));
    backgroundSprite5->setPosition(mundoBounds.left, mundoBounds.top);
    layersCena[Background]->insereFilho(backgroundSprite5);

    SpriteNode* backgroundSprite(new SpriteNode(background[0], texturaRect));
    backgroundSprite->setPosition(mundoBounds.left, 7300);
    layersCena[Background]->insereFilho(backgroundSprite);

    SpriteNode* backgroundSprite6(new SpriteNode(background[6], texturaRect6));
    backgroundSprite6->setPosition(mundoBounds.left, 5852.324);
    layersCena[Background]->insereFilho(backgroundSprite6);

    SpriteNode* backgroundSprite7(new SpriteNode(background[7], texturaRect6));
    backgroundSprite7->setPosition(mundoBounds.left, 3693);
    layersCena[Background]->insereFilho(backgroundSprite7);

    SpriteNode* backgroundSprite8(new SpriteNode(background[8], texturaRect6));
    backgroundSprite8->setPosition(mundoBounds.left, 2253);
    layersCena[Background]->insereFilho(backgroundSprite8);

    SpriteNode* backgroundSprite9(new SpriteNode(background[9], texturaRect6));
    backgroundSprite9->setPosition(mundoBounds.left, 814);
    layersCena[Background]->insereFilho(backgroundSprite9);

    player = new Foguete(objetoText[Nave]);
    player->setPosition(viewCenter.x, viewCenter.y);
    //player->setVelocidade(-200);
    layersCena[Middle]->insereFilho(player);
}
