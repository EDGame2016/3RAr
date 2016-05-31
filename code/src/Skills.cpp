#include "Skills.h"

Skills::Skills(sf::RenderWindow& window):
    tela(window),
    cenaTree(),
    jogar(),
    sair(),
    layersCena(),
    texturas(),
    R()
{
    constroiCena();
}

void Skills::atualiza(sf::Time dt)
{
    jogar->isPressed(tela);
    sair->isPressed(tela);

    R->isPressed(tela);

    R->Dir->isPressed(tela);
    R->Esq->isPressed(tela);

    R->Dir->Dir->isPressed(tela);
    R->Dir->Esq->isPressed(tela);

    R->Esq->Dir->isPressed(tela);
    R->Esq->Esq->isPressed(tela);


    cenaTree.atualiza(dt);
}

void Skills::desenha()
{
    tela.clear(sf::Color(108,127,131,0));
    tela.draw(cenaTree);
}

Skills::Evento Skills::processaEventos()
{
    sf::Event event;

    while (tela.pollEvent(event))
    {
        switch(event.type)
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
        default:
            return NONE;
            break;
        }
    }
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

    SpriteNode* tituloSprite(new SpriteNode(texturas[SkillShield]));
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

    R = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillNave], texturas[DescNave]);
    R->simbolo[3].setTexture(texturas[conectionLeft]);
    R->simbolo[3].setScale(1.55, 1.55);
    R->simbolo[3].setPosition(-240.f, 120.f);
    R->simbolo[4].setTexture(texturas[conectionRight]);
    R->simbolo[4].setScale(1.55, 1.55);
    R->simbolo[4].setPosition(145.f, 120.f);


    R->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCO2], texturas[DescCO2]);
    R->Dir->simbolo[3].setTexture(texturas[conectionLeft]);
    R->Dir->simbolo[3].setScale(1.55, 1.55);
    R->Dir->simbolo[3].setPosition(-240.f, 165.f);
    R->Dir->simbolo[3].rotate(-10);
    R->Dir->simbolo[4].setTexture(texturas[conectionRight]);
    R->Dir->simbolo[4].setScale(1.55, 1.55);
    R->Dir->simbolo[4].setPosition(145.f, 120.f);
    R->Dir->simbolo[4].rotate(10);


    R->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillShield], texturas[DescShield]);
    R->Esq->simbolo[3].setTexture(texturas[conectionLeft]);
    R->Esq->simbolo[3].setScale(1.55, 1.55);
    R->Esq->simbolo[3].setPosition(-240.f, 165.f);
    R->Esq->simbolo[3].rotate(-10);
    R->Esq->simbolo[4].setTexture(texturas[conectionRight]);
    R->Esq->simbolo[4].setScale(1.55, 1.55);
    R->Esq->simbolo[4].setPosition(145.f, 120.f);
    R->Esq->simbolo[4].rotate(10);

    R->Dir->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCometa], texturas[DescCometa]);
    R->Dir->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpray], texturas[DescSpray]);

    R->Esq->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillGas], texturas[DescGas]);
    R->Esq->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpeed], texturas[DescSpeed]);

    constroiArvore(R, 400.f, 100.f);
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

Skills::~Skills()
{
    //dtor
}
