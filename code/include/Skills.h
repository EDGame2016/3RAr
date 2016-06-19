#ifndef SKILLS_H
#define SKILLS_H

#include "NodeCena.h"
#include "SpriteNode.h"
#include "Button.h"
#include "SkillsNode.h"
class Skills
{
public:
    enum Evento
    {
        NONE,
        JOGAR,
        SAIR
    };

    enum Textura
    {
        DescNave,
        DescCO2,
        DescCometa,
        DescGas,
        DescShield,
        DescSpeed,
        DescSpray,
        JogarD,
        JogarS,
        SairD,
        SairS,
        SkillBack0,
        SkillBack1,
        SkillNave,
        SkillCO2,
        SkillCometa,
        SkillGas,
        SkillShield,
        SkillSpeed,
        SkillSpray,
        conectionLeft,
        conectionRight,
        TexturaCount
    };

    enum Layer
    {
        Background,
        Middle,
        Top,
        LayerCount
    };


    Skills(sf::RenderWindow& window);
    ~Skills();
    int								    atualiza(sf::Time dt);
    void								desenha();
    void                                constroiArvore(SkillsNode*, float, float);
    Evento                              processaEventos();

private:

    void                                loadTexturas();
    void                                constroiCena();

    sf::RenderWindow&                   tela;
    NodeCena                            cenaTree;
    std::array<NodeCena*, LayerCount>   layersCena;
    std::array<sf::Texture,TexturaCount>texturas;

    Button* jogar;
    Button* sair;

    SkillsNode* R;
};

#endif // SKILLS_H
