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
    texturas[Titulo].loadFromFile("src/images/menu/titulo.png");
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
    R = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillNave]);

    R->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCO2]);
    R->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillShield]);

    R->Dir->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillCometa]);
    R->Dir->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpray]);

    R->Esq->Dir = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillGas]);
    R->Esq->Esq = new SkillsNode(texturas[SkillBack0], texturas[SkillBack1], texturas[SkillSpeed]);

    constroiArvore(R, 500.f, 100.f);
}

void Skills::constroiArvore(SkillsNode* R, float x, float y)
{
        R->setScale(0.6, 0.6);
        R->setPosition(x,y);
        layersCena[Top]->insereFilho(R);
    if(R->Dir != NULL && R->Esq != NULL)
    {
        constroiArvore(R->Dir,x+(100*R->getAltura()/2), y+100);
        constroiArvore(R->Esq,x-(100*R->getAltura()/2), y+100);
    }
}

Skills::~Skills()
{
    //dtor
}
