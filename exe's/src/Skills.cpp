#include "Skills.h"
#include <iostream>

Skills::Skills(sf::RenderWindow& window):
    R(),
    tela(window),
    cenaTree(),
    layersCena(),
    texturas(),
    jogar(),
    sair()
{
    constroiCena();
}

Skills::~Skills()
{
    delete R;
}

void Skills::reinicia()
{
    R->Esq->status=false;
    R->Dir->status=false;

    R->Esq->Esq->status=false;
    R->Esq->Dir->status=false;

    R->Dir->Esq->status=false;
    R->Dir->Dir->status=false;
}

int Skills::atualiza(sf::Time dt)
{
    int aux = 0;
    if(jogar->isPressed(tela))
        atualizacao = false;
    sair->isPressed(tela);

    if(R->status)
    {
        aux = SkillsNode::NAVE;
        atualizacao = true;
    }
    if(R->Dir->status)
    {
        aux = SkillsNode::CO2;
        atualizacao = true;
    }
    if(R->Esq->status)
    {
        aux = SkillsNode::SHIELD;
        atualizacao = true;
    }
    if(R->Dir->Dir->status)
    {
        aux = SkillsNode::COMETA;
        atualizacao = true;
    }
    if(R->Dir->Esq->status)
    {
        aux = SkillsNode::SPRAY;
        atualizacao = true;
    }
    if(R->Esq->Dir->status)
    {
        aux = SkillsNode::GAS;
        atualizacao = true;
    }
    if(R->Esq->Esq->status)
    {
        aux = SkillsNode::SPEED;
        atualizacao = true;
    }
    cenaTree.atualiza(dt);

    return aux;
}

void Skills::desenha()
{
    tela.clear(sf::Color(77,77,77));
    tela.draw(cenaTree);
}

Skills::Evento Skills::processaEventos()
{
    sf::Event event;

    while (tela.pollEvent(event))
    {
        switch(event.type)
        {
        case (sf::Event::Closed):
        {
            tela.close();
            break;
        }
        case (sf::Event::MouseButtonReleased):
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(jogar->isSelected(tela))
                    return JOGAR;
                else if(sair->isSelected(tela))
                    return SAIR;
            }

            break;
        }
        case (sf::Event::KeyPressed):
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                tela.close();
            }

            break;
        }
        default:
            break;
        }
    }

    return NONE;
}

void Skills::loadTexturas()
{
    texturas[DescNave].loadFromFile("src/images/skills/descNave.png");
    texturas[DescCometa].loadFromFile("src/images/skills/descCometa.png");
    texturas[DescCO2].loadFromFile("src/images/skills/descCO2.png");
    texturas[DescShield].loadFromFile("src/images/skills/descShield.png");
    texturas[DescGas].loadFromFile("src/images/skills/descGas.png");
    texturas[DescSpeed].loadFromFile("src/images/skills/descSpeed.png");
    texturas[DescSpray].loadFromFile("src/images/skills/descSpray.png");
    texturas[JogarD].loadFromFile("src/images/skills/jogarD.png");
    texturas[JogarS].loadFromFile("src/images/skills/JogarS.png");
    texturas[SairD].loadFromFile("src/images/skills/abandonarD.png");
    texturas[SairS].loadFromFile("src/images/skills/abandonarS.png");
    texturas[SkillBack0].loadFromFile("src/images/skills/skillBack0.png");
    texturas[SkillBack1].loadFromFile("src/images/skills/skillBack1.png");
    texturas[SkillNave].loadFromFile("src/images/skills/skillNave.png");
    texturas[SkillCO2].loadFromFile("src/images/skills/skillCO2.png");
    texturas[SkillCometa].loadFromFile("src/images/skills/skillCometa.png");
    texturas[SkillGas].loadFromFile("src/images/skills/skillGas.png");
    texturas[SkillShield].loadFromFile("src/images/skills/skillShield.png");
    texturas[SkillSpeed].loadFromFile("src/images/skills/skillSpeed.png");
    texturas[SkillSpray].loadFromFile("src/images/skills/skillSpray.png");
    texturas[conectionLeft].loadFromFile("src/images/skills/conectionLeft.png");
    texturas[conectionRight].loadFromFile("src/images/skills/conectionRight.png");


    for(int i = 0; i < TexturaCount; i++)
    {
        texturas[i].setSmooth(true);
    }
}

void Skills::constroiCena()
{
    sf::Vector2f telaSize = tela.getDefaultView().getSize();

    for(int i=0; i<LayerCount; i++)
    {
        NodeCena* layer;
        layer = new NodeCena;
        layersCena[i] = layer;
        cenaTree.insereFilho(layer);
    }

    loadTexturas();


    jogar = new Button(texturas[JogarD], texturas[JogarS]);
    jogar->setPosition(5*telaSize.x/20, 18*telaSize.y/20);
    jogar->setOriginCenter();
    jogar->setScale(0.5, 0.5);
    layersCena[Top]->insereFilho(jogar);

    sair = new Button(texturas[SairD], texturas[SairS]);
    sair->setPosition(telaSize.x, 0);
    jogar->insereFilho(sair);

    R = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillNave], texturas[DescNave], SkillsNode::NAVE);
    R->simbolo[3].setTexture(texturas[conectionLeft]);
    R->simbolo[3].setScale(1.55, 1.55);
    R->simbolo[3].setPosition(-240.f, 120.f);
    R->simbolo[4].setTexture(texturas[conectionRight]);
    R->simbolo[4].setScale(1.55, 1.55);
    R->simbolo[4].setPosition(145.f, 120.f);
    R->status = true;


    R->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCO2], texturas[DescCO2], SkillsNode::CO2);
    R->Dir->simbolo[3].setTexture(texturas[conectionLeft]);
    R->Dir->simbolo[3].setScale(1.55, 1.55);
    R->Dir->simbolo[3].setPosition(-240.f, 165.f);
    R->Dir->simbolo[3].rotate(-10);
    R->Dir->simbolo[4].setTexture(texturas[conectionRight]);
    R->Dir->simbolo[4].setScale(1.55, 1.55);
    R->Dir->simbolo[4].setPosition(145.f, 120.f);
    R->Dir->simbolo[4].rotate(10);
    R->Dir->status = false;

    R->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillShield], texturas[DescShield], SkillsNode::SHIELD);
    R->Esq->simbolo[3].setTexture(texturas[conectionLeft]);
    R->Esq->simbolo[3].setScale(1.55, 1.55);
    R->Esq->simbolo[3].setPosition(-240.f, 165.f);
    R->Esq->simbolo[3].rotate(-10);
    R->Esq->simbolo[4].setTexture(texturas[conectionRight]);
    R->Esq->simbolo[4].setScale(1.55, 1.55);
    R->Esq->simbolo[4].setPosition(145.f, 120.f);
    R->Esq->simbolo[4].rotate(10);
    R->Esq->status = false;

    R->Dir->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCometa], texturas[DescCometa], SkillsNode::COMETA);
    R->Dir->Dir->status = false;
    R->Dir->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpray], texturas[DescSpray], SkillsNode::SPRAY);
    R->Dir->Esq->status = false;

    R->Esq->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillGas], texturas[DescGas], SkillsNode::GAS);
    R->Esq->Dir->status = false;
    R->Esq->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpeed], texturas[DescSpeed], SkillsNode::SPEED);
    R->Esq->Esq->status = false;

    constroiArvore(R, telaSize.x/2, 2*telaSize.y/20 + 10);
}

void Skills::constroiArvore(SkillsNode* R, float x, float y)
{
    R->setScale(0.6, 0.6);
    R->setPosition(x,y);
    layersCena[Top]->insereFilho(R);
    if(R->Dir != NULL && R->Esq != NULL)
    {
        constroiArvore(R->Dir,x+(100*R->getAltura()/1.5), y+200);
        constroiArvore(R->Esq,x-(100*R->getAltura()/1.5), y+200);
    }
}
