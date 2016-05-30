#ifndef SKILLSNODE_H
#define SKILLSNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Entidade.h"
#include "NodeCena.h"
#include <cstdio>
#include <stdio.h>



class SkillsNode:public NodeCena
{
    public:
        SkillsNode(const sf::Texture&, const sf::Texture&, const sf::Texture&);

        sf::FloatRect   getBoundingRect() const;
        void            desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
        void            desenhaFilhos(sf::RenderTarget& target, sf::RenderStates states) const;

        int             getAltura();
        bool            mouseIntersects(sf::RenderWindow& window);
        bool            isPressed(sf::RenderWindow& window);
        bool            isSelected(sf::RenderWindow& window);


        SkillsNode*     Dir;
        SkillsNode*     Esq;

        bool            status;
        std::string          desc;
        sf::Sprite      simbolo[3]; // status= false -> simbolo[0], status= true -> simbolo[1]
};

#endif // SKILLSNODE_H
