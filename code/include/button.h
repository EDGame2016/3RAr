#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "NodeCena.h"

class Button : public NodeCena
{
public:
    Button(const sf::Texture& d, const sf::Texture& s);
    bool isSelected(sf::RenderWindow& window);
    bool isPressed(sf::RenderWindow& window);
    sf::FloatRect getBoundingRect() const;

private:

    virtual void			atualizaAtual(sf::Time delta);
    virtual void			desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const;
    bool                    mouseIntersects(sf::RenderWindow& window);

private:
    sf::Sprite deselected;
    sf::Sprite selected;
    bool estado;
};

#endif // BUTTON_H
