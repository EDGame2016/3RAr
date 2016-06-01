#include "Mundo.h"

#include <iostream>

Mundo::Mundo(sf::RenderWindow& window): tela(window),
    mundoView(window.getDefaultView()),
    cenaTree(),
    skills(tela),
    layersCena(),
    background(),
    objetoText(),
    nuvens(),
    //sounds(),
    mundoBounds(0.f, 0.f, mundoView.getSize().x, 8000.f),
    viewCenter(mundoView.getSize().x / 2.f, mundoBounds.height - mundoView.getSize().y / 2.f),
    scrollSpeed(-200.f),
    player(),
    grama(),
    estadoAtual(INICIO)
{
    constroiCena();
    mundoView.setCenter(viewCenter);
}

void Mundo::atualiza(sf::Time dt)
{
    if(estadoAtual == JOGANDO)
    {
        if(player->getPosition().y < viewCenter.y && player->getPosition().y > 360)
        {
            mundoView.setCenter(viewCenter.x,player->getPosition().y);
        }
        if(Collision::PixelPerfectTest(player->getSprite(), grama->getSprite(), 0))
        {
            player->setVelocidade(-2*player->getVelocidade());
        }

        //Se o jogador tocar as bordas, inverte sua direção
        if((player->getPosition().x <= mundoBounds.left+50)||(player->getPosition().x >= mundoBounds.left + mundoBounds.width-50))
        {
            player->colidiuLateral();
        }
        cenaTree.atualiza(dt);
    }
    else if(estadoAtual == PAUSADO)
    {
        skills.atualiza(dt);
    }

}

void Mundo::desenha()
{
    if(estadoAtual == JOGANDO || estadoAtual == INICIO)
    {
        tela.setView(mundoView);
        tela.draw(cenaTree);
    }
    else if(estadoAtual == PAUSADO)
    {
        skills.desenha();
    }
}

Mundo::Evento Mundo::processaEventos()
{
    sf::Event event;

    if(estadoAtual == JOGANDO || estadoAtual == INICIO)
    {
        while (tela.pollEvent(event))
        {
            switch (event.type)
            {
            case (sf::Event::Closed):
            {
                tela.close();
                break;
            }
            case (sf::Event::KeyPressed):
            {
                playerInput(event.key.code, true);
                if(event.key.code == sf::Keyboard::P)
                    estadoAtual = PAUSADO;
                break;
            }

            case sf::Event::KeyReleased:
            {
                playerInput(event.key.code, false);
                break;
            }
            default:
                break;
            }
        }
    }
    else if(estadoAtual == PAUSADO)
    {
        Skills::Evento eventoAux = skills.processaEventos();
        if(eventoAux == Skills::SAIR)
        {
            return BACK;
        }
        else if(eventoAux == Skills::JOGAR)
        {
            estadoAtual = INICIO;
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
            estadoAtual = PAUSADO;
        break;
    }
    case (sf::Keyboard::Right):
    {
        if(estadoAtual == JOGANDO)
            player->moveDir();
        break;
    }
    case (sf::Keyboard::Left):
    {
        if(estadoAtual == JOGANDO)
            player->moveEsq();
        break;
    }
    case (sf::Keyboard::Space):
    {
        if(estadoAtual == INICIO)
            estadoAtual = JOGANDO;
    }
    default:
        break;
    }
}

void Mundo::setEstado(Mundo::Estados estado)
{
    this->estadoAtual = estado;
}

Mundo::Estados Mundo::getEstado()const
{
    return estadoAtual;
}


void Mundo::loadTexturas()
{
    /*Texturas de Fundo*/
    Collision::CreateTextureAndBitmask(background[Grama], "src/images/background/grama.png");
    background[Troposfera].loadFromFile("src/images/background/troposfera.png");
    background[T1].loadFromFile("src/images/background/t1.png");
    background[Estratosfera].loadFromFile("src/images/background/estratosfera.png");
    background[T2].loadFromFile("src/images/background/t2.png");
    background[Mesosfera].loadFromFile("src/images/background/mesosfera.png");
    background[T3].loadFromFile("src/images/background/t3.png");
    background[Termosfera].loadFromFile("src/images/background/termosfera.png");
    background[T4].loadFromFile("src/images/background/t4.png");
    background[Exosfera].loadFromFile("src/images/background/exosfera.png");

    /*Texturas dos Objetos*/
    Collision::CreateTextureAndBitmask(objetoText[Nave], "src/images/objetos/nave.png");
    objetoText[Fogo1].loadFromFile("src/images/objetos/fogo1.png");
    objetoText[Fogo2].loadFromFile("src/images/objetos/fogo2.png");

    for(int i = 0; i < ObjetosTexturasCount; i++)
    {
        objetoText[i].setSmooth(true);
    }

    /*Texturas das Nuvens*/
    for(int i = 0; i < 8; i++)
    {
        nuvens[i].loadFromFile("src/images/objetos/nuvem"+toString(i+1)+".png");
        nuvens[i].setSmooth(true);
    }

    /*Audios*/
    //sounds.loadFromFile("src/sound/launch.wav");
    //player->setSound(sounds);
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
    SpriteNode* backgroundSprite(new SpriteNode(background[0], texturaRect));
    backgroundSprite->setPosition(mundoBounds.left, 7300);
    grama = backgroundSprite;
    layersCena[MiddleBack]->insereFilho(backgroundSprite);

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

    player = new Foguete(objetoText[Nave], objetoText[Fogo1], objetoText[Fogo2]);
    player->setPosition(viewCenter.x, viewCenter.y+200);
    layersCena[MiddleTop]->insereFilho(player);
}
