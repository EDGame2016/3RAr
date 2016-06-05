#ifndef SKILLSNODE_H
#define SKILLSNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Entidade.h"
#include "NodeCena.h"
#include "SpriteNode.h"

#include <stdio.h>

class SkillsNode: public NodeCena
{
    public:
        enum Aprimoramento
        {
            NAVE,
            SHIELD,
            CO2,
            SPEED,
            GAS,
            SPRAY,
            COMETA
        };
                        SkillsNode(const sf::Texture&, const sf::Texture&, const sf::Texture&, const sf::Texture&, int);
                        ~SkillsNode();
        sf::FloatRect   getBoundingRect() const;
        void            desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;

        int             getAltura();
        bool            mouseIntersects(sf::RenderWindow& window);
        bool            isPressed(sf::RenderWindow& window);
        bool            isSelected(sf::RenderWindow& window);


        SkillsNode*     Dir;
        SkillsNode*     Esq;

        bool            status, desc;
        std::array<sf::Sprite,5> simbolo; // status= false -> simbolo[0], status= true -> simbolo[1]
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int             aprimoramento;
};

#endif // SKILLSNODE_H
