#include "Button.h"
#include <iostream>
Button::Button(const sf::Texture& d, const sf::Texture& s):
    deselected(d),
    selected(s)
{
    estado = false;
}

bool Button::isSelected(sf::RenderWindow& window)
{
    if(mouseIntersects(window))
    {
        estado = true;
        return true;
    }
    else
    {
        estado = false;
        return false;
    }
}

bool Button::isPressed(sf::RenderWindow& window)
{
    if(isSelected(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        estado = false;

        return true;
    }
    else
    {
        return false;
    }

}

sf::FloatRect Button::getBoundingRect() const
{
    return getWorldTransform().transformRect(deselected.getGlobalBounds());
}

bool Button::mouseIntersects(sf::RenderWindow& window)
{
    sf::FloatRect aux;
    aux = getBoundingRect();

    if(sf::Mouse::getPosition(window).x >= aux.left
            && sf::Mouse::getPosition(window).x <= aux.left + aux.width
            && sf::Mouse::getPosition(window).y >= aux.top
            && sf::Mouse::getPosition(window).y <= aux.top + aux.height)
    {
        return true;
    }
    else
    {
        return false;
    }


}

void Button::atualizaAtual(sf::Time delta)
{

}

void Button::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!estado)
        target.draw(deselected, states);
    else
        target.draw(selected, states);
}
