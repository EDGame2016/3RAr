#include "Mundo.h"

//#include <iostream>

Mundo::Mundo(sf::RenderWindow& window): tela(window),
    mundoView(window.getDefaultView()),
    cenaTree(),
    skills(tela),
    gerenciadorJanela(tela),
    layersCena(),
    camadasAtm(),
    controlCamadas(),
    background(),
    objetoText(),
    nuvensText(),
    soundsBuffer(),
    mundoBounds(0.f, 0.f, mundoView.getSize().x, 8000.f),
    viewCenter(mundoView.getSize().x / 2.f, mundoBounds.height - mundoView.getSize().y / 2.f),
    scrollSpeed(-200.f),
    player(),
    grama(),
    barra(),
    estadoAtual(INICIO)
{
    srand(time(NULL));
    constroiCena();
    controlCamadas.fill(false);
    mundoView.setCenter(viewCenter);
}

void Mundo::atualiza(sf::Time dt)
{
    if(estadoAtual == JOGANDO || estadoAtual == INICIO)
    {
        if(player->getPosition().y < viewCenter.y && player->getPosition().y > 360)
        {
            mundoView.setCenter(viewCenter.x,player->getPosition().y);
        }

        gerenciaObjetos();

        bateria->setPosition(60, mundoView.getCenter().y - 327);
        barra->setPosition(0, mundoView.getCenter().y - 380);
        cenaTree.atualiza(dt);

        if(player->dano < 0)
        {
            gerenciadorJanela.setCamada(player->getPosition().y);
            estadoAtual = PAUSADO;
            destroiCamadas();
        }
    }
    /**Ajustar essa parte**/
    else
    {
        if(estadoAtual == PAUSADO)
        {
            gerenciadorJanela.atualiza(dt);
        }
        else
        {
            switch(skills.atualiza(dt))
            {
            case(SkillsNode::NAVE):
            {
                //implementar
            }
            case(SkillsNode::SHIELD):
            {
                //implementar
                break;
            }
            case(SkillsNode::CO2):
            {
                //implementar
                break;
            }
            case(SkillsNode::SPEED):
            {
                player->turbo = true;
                break;
            }
            case(SkillsNode::GAS):
            {
                player->tCarga = 10;
                break;
            }
            case(SkillsNode::SPRAY):
            {
                //implementar
            }
            case(SkillsNode::COMETA):
            {
                //implementar
                break;
            }
            }
        }
    }
}

void Mundo::desenha()
{
    if(estadoAtual == JOGANDO || estadoAtual == INICIO)
    {
        tela.setView(mundoView);
        tela.draw(cenaTree);
    }
    else
    {
        if(estadoAtual == PAUSADO)
            gerenciadorJanela.desenha();
        else
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
    else
    {
        if(estadoAtual == PAUSADO)
        {
            if(gerenciadorJanela.processaEventos())
                estadoAtual = SKILL;
        }
        else
        {
            Skills::Evento eventoAux = skills.processaEventos();

            if(eventoAux == Skills::SAIR)
            {
                abandona();
                return BACK;
            }
            else if(eventoAux == Skills::JOGAR)
            {
                reinicia();
            }
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
        {
            estadoAtual = PAUSADO;
            gerenciadorJanela.setCamada(player->getPosition().y);
        }
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
        {
            player->setEstado(true);
            estadoAtual = JOGANDO;
        }
    }
    default:
        break;
    }
}

Mundo::Estados Mundo::getEstado()const
{
    return estadoAtual;
}

void Mundo::reinicia()
{
    player->setPosition(viewCenter.x, viewCenter.y+200);
    player->reinicia();
    mundoView.setCenter(viewCenter);
    controlCamadas.fill(false);
    estadoAtual = INICIO;
}

void Mundo::abandona()
{
    reinicia();
}

void Mundo::geraCamada(int camadaID)
{
    switch(camadaID)
    {
    case 0: /// Troposfera
    {
        for(int i = 0; i<30; i++)
        {
            Objeto* nuvem;
            nuvem = new Objeto(Objeto::NUVEM, nuvensText[rand()%8]);
            nuvem->setPosition(rand()%1200, viewCenter.y - 100 - rand()%1700);
            nuvem->setScale(0.5,0.5);
            nuvem->setVelocidade(rand()%100 - 50);
            nuvem->setColor(50,50,50,200);
            camadasAtm[0]->insereFilho(nuvem);
            layersCena[MiddleTop]->insereFilho(nuvem);
        }

        break;
    }
    case 1: /// Estratosfera
    {
        for(int i = 0; i<10; i++)
        {
            Objeto* balao;
            balao = new Objeto(Objeto::BALAO, objetoText[Balao2]);
            balao->setPosition(rand()%1200, 5800 - i*rand()%2000);
            balao->setScale(0.5,0.5);
            balao->setVelocidade(rand()%100 - 50);
            camadasAtm[1]->insereFilho(balao);
            layersCena[MiddleTop]->insereFilho(balao);
        }
        for(int i = 0; i<10; i++)
        {
            Objeto* balao;
            balao = new Objeto(Objeto::BALAO, objetoText[Balao1]);
            balao->setPosition(rand()%1200, 5800 - rand()%2000);
            balao->setScale(0.5,0.5);
            balao->setVelocidade(rand()%100 - 50);
            camadasAtm[1]->insereFilho(balao);
            layersCena[MiddleTop]->insereFilho(balao);
        }

        Objeto* ozonio;
        ozonio = new Objeto(Objeto::OZONIO, objetoText[OzonioB]);
        ozonio->setScale(0.5,0.5);
        ozonio->setPosition(viewCenter.x,3700);
        camadasAtm[1]->insereFilho(ozonio);
        layersCena[MiddleTop]->insereFilho(ozonio);

        break;
    }
    case 2: /// Mesosfera
    {
        for(int i = 0; i<10; i++)
        {
            Objeto* cometa;
            cometa = new Objeto(Objeto::COMETA, objetoText[Cometa]);
            cometa->setPosition(rand()%1200, 3700 - rand()%1400);
            cometa->setScale(0.5,0.5);
            cometa->setVelocidade(100+rand()%500);
            camadasAtm[2]->insereFilho(cometa);
            layersCena[MiddleTop]->insereFilho(cometa);
        }

        break;

    }
    case 3: /// Termosfera
    {
        for(int i = 0; i<5; i++)
        {
            Objeto* satelite;
            satelite = new Objeto(Objeto::SATELITE, objetoText[Satelite]);
            satelite->setPosition(rand()%1200, 2000 - rand()%1400);
            satelite->setScale(0.5,0.5);
            satelite->setVelocidade(rand()%100 - 50);
            camadasAtm[3]->insereFilho(satelite);
            layersCena[MiddleTop]->insereFilho(satelite);
        }

        break;
    }
    case 4: /// Exosfera
    {

    }
    }
}

void Mundo::destroiCamadas()
{
    for (int i = 0; i < 5; i++)
    {
        camadasAtm[i]->esvaziaFilhos();
    }

    layersCena[MiddleTop]->esvaziaFilhos();
}

void Mundo::gerenciaObjetos()
{
    if(player->getPosition().y > 5800) /// Troposfera
    {
        if(controlCamadas[0] == false)
        {
            geraCamada(0);
            controlCamadas[0] = true;
        }

        if(Collision::PixelPerfectTest(player->getSprite(), grama->getSprite(), 0))
        {
            player->setVelocidade(-350);
        }

        camadasAtm[0]->verificaColisao(player);
    }
    else if(player->getPosition().y > 3600) /// Estatosfera
    {
        if(controlCamadas[1] == false)
        {
            geraCamada(1);
            controlCamadas[1] = true;
        }

        camadasAtm[1]->verificaColisao(player);
    }
    else if(player->getPosition().y > 2200) /// Mesosfera
    {
        if(controlCamadas[2] == false)
        {
            geraCamada(2);
            controlCamadas[2] = true;
        }

        camadasAtm[2]->verificaColisao(player);
    }
    else if(player->getPosition().y > 800) /// Termosfera
    {
        if(controlCamadas[3] == false)
        {
            geraCamada(3);
            controlCamadas[3] = true;
        }
        camadasAtm[3]->verificaColisao(player);
    }
    else /// Exosfera
    {
        camadasAtm[4]->verificaColisao(player);
    }
}

void Mundo::loadTexturas()
{
    /*Texturas de Fundo*/
    /**Ajustar essa parte**/
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
    background[BAR].loadFromFile("src/images/background/bar.png");

    /*Texturas dos Objetos*/
    Collision::CreateTextureAndBitmask(objetoText[Nave], "src/images/objetos/nave.png");
    objetoText[Fogo1].loadFromFile("src/images/objetos/fogo1.png");
    objetoText[Fogo2].loadFromFile("src/images/objetos/fogo2.png");
    Collision::CreateTextureAndBitmask(objetoText[Satelite], "src/images/objetos/satelite.png");
    Collision::CreateTextureAndBitmask(objetoText[Balao1], "src/images/objetos/balao1.png");
    Collision::CreateTextureAndBitmask(objetoText[Balao2], "src/images/objetos/balao2.png");
    Collision::CreateTextureAndBitmask(objetoText[Cometa], "src/images/objetos/cometa.png");
    Collision::CreateTextureAndBitmask(objetoText[OzonioR], "src/images/objetos/ozonioR.png");
    Collision::CreateTextureAndBitmask(objetoText[OzonioB], "src/images/objetos/ozonioB.png");

    objetoText[BateriaCapa].loadFromFile("src/images/objetos/bateriaCapa.png");
    objetoText[BateriaCelula].loadFromFile("src/images/objetos/bateriaCelula.png");

    for(int i = 0; i < ObjetosTexturasCount; i++)
    {
        objetoText[i].setSmooth(true);
    }

    /*Texturas das Nuvens*/
    for(int i = 0; i < 8; i++)
    {
        Collision::CreateTextureAndBitmask(nuvensText[i], "src/images/objetos/nuvem"+toString(i+1)+".png");
        nuvensText[i].setSmooth(true);
    }

    /*Audios*/
    soundsBuffer[navePartindo].loadFromFile("src/sound/launch.wav");
}

void Mundo::constroiCena()
{
    // Inicializa as diferentes camadas de renderização
    for (int i = 0; i < LayerCount; i++)
    {
        NodeCena* layer;
        layer = new NodeCena;
        layersCena[i] = layer;
        cenaTree.insereFilho(layer);
    }

    // Inicializa as diferentes camadas da atmosfera
    for (int i = 0; i < 5; i++)
    {
        ObjetoHolder* camada;
        camada = new ObjetoHolder;
        camadasAtm[i] = camada;
    }

    loadTexturas();

    sf::FloatRect back1(0.f, 0.f, mundoView.getSize().x, 2150);
    sf::FloatRect back2(0.f, 0.f, mundoView.getSize().x, 2165);
    sf::FloatRect back3(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back4(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back5(0.f, 0.f, mundoView.getSize().x, 815);
    sf::FloatRect back6(0.f, 0.f, mundoView.getSize().x, 360);
    sf::FloatRect back7(0.f, 0.f, mundoView.getSize().x, 85);


    sf::IntRect texturaRect(mundoBounds);
    sf::IntRect texturaRect1(back1);
    sf::IntRect texturaRect2(back2);
    sf::IntRect texturaRect3(back3);
    sf::IntRect texturaRect4(back4);
    sf::IntRect texturaRect5(back5);
    sf::IntRect texturaRect6(back6);
    sf::IntRect texturaRect7(back7);

    background[0].setRepeated(false);
    background[1].setRepeated(true);
    background[2].setRepeated(true);
    background[3].setRepeated(true);
    background[4].setRepeated(true);
    background[6].setRepeated(true);
    background[7].setRepeated(true);
    background[8].setRepeated(true);
    background[9].setRepeated(true);
    background[10].setRepeated(true);

    SpriteNode* backgroundSprite(new SpriteNode(background[Grama], texturaRect));
    backgroundSprite->setPosition(mundoBounds.left, 7300);
    grama = backgroundSprite;
    layersCena[MiddleBack]->insereFilho(backgroundSprite);

    SpriteNode* backgroundSprite1(new SpriteNode(background[Troposfera], texturaRect1));
    backgroundSprite1->setPosition(mundoBounds.left, 5852.324);
    layersCena[Background]->insereFilho(backgroundSprite1);

    SpriteNode* backgroundSprite2(new SpriteNode(background[Estratosfera], texturaRect2));
    backgroundSprite2->setPosition(mundoBounds.left, 3692.651);
    layersCena[Background]->insereFilho(backgroundSprite2);

    SpriteNode* backgroundSprite3(new SpriteNode(background[Mesosfera], texturaRect3));
    backgroundSprite3->setPosition(mundoBounds.left, 2252.869);
    layersCena[Background]->insereFilho(backgroundSprite3);

    SpriteNode* backgroundSprite4(new SpriteNode(background[Termosfera], texturaRect4));
    backgroundSprite4->setPosition(mundoBounds.left, 813.087);
    layersCena[Background]->insereFilho(backgroundSprite4);

    SpriteNode* backgroundSprite5(new SpriteNode(background[Exosfera], texturaRect5));
    backgroundSprite5->setPosition(mundoBounds.left, mundoBounds.top);
    layersCena[Background]->insereFilho(backgroundSprite5);

    SpriteNode* backgroundSprite6(new SpriteNode(background[T1], texturaRect6));
    backgroundSprite6->setPosition(mundoBounds.left, 5852.324);
    layersCena[Background]->insereFilho(backgroundSprite6);

    SpriteNode* backgroundSprite7(new SpriteNode(background[T2], texturaRect6));
    backgroundSprite7->setPosition(mundoBounds.left, 3693);
    layersCena[Background]->insereFilho(backgroundSprite7);

    SpriteNode* backgroundSprite8(new SpriteNode(background[T3], texturaRect6));
    backgroundSprite8->setPosition(mundoBounds.left, 2253);
    layersCena[Background]->insereFilho(backgroundSprite8);

    SpriteNode* backgroundSprite9(new SpriteNode(background[T4], texturaRect6));
    backgroundSprite9->setPosition(mundoBounds.left, 814);
    layersCena[Background]->insereFilho(backgroundSprite9);

    player = new Foguete(objetoText[Nave], objetoText[Fogo1], objetoText[Fogo2]);
    player->setPosition(viewCenter.x, viewCenter.y+200);
    layersCena[Top]->insereFilho(player);

    /**Ajustar essa parte**/
    player->setSound(soundsBuffer[navePartindo]);

    barra = new SpriteNode(background[BAR], texturaRect7);
    layersCena[Top]->insereFilho(barra);

    bateria = new Bateria(objetoText[BateriaCapa], objetoText[BateriaCelula]);
    bateria->setCarga(&(player->carga));
    layersCena[Top]->insereFilho(bateria);
}
