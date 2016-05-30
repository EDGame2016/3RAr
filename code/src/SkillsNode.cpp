#include "SkillsNode.h"


SkillsNode::SkillsNode(const sf::Texture& desativado, const sf::Texture& ativado, const sf::Texture& desenho)
{
    simbolo[0].setTexture(desativado);
    simbolo[1].setTexture(ativado);
    simbolo[2].setTexture(desenho);
    this->Dir = NULL;
    this->Esq = NULL;
    this->status = false;
    this->setOriginCenter();


    this->desc = "Olá";
}

int SkillsNode::getAltura()
{
    if(this->Dir == NULL && this->Esq == NULL)
        return 1;
    else
        return this->Dir->getAltura()+1;
}



void SkillsNode::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(status)
        target.draw(simbolo[1], states);
    else
        target.draw(simbolo[0], states);
    target.draw(simbolo[2], states);
}


bool SkillsNode::mouseIntersects(sf::RenderWindow& window)
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


sf::FloatRect SkillsNode::getBoundingRect() const
{
    return getWorldTransform().transformRect(simbolo[2].getGlobalBounds());
}

bool SkillsNode::isPressed(sf::RenderWindow& window)
{
    if(isSelected(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))

        status = !status;
        return true;
    }
    else
    {
        return false;
    }

}

bool SkillsNode::isSelected(sf::RenderWindow& window)
{
    if(mouseIntersects(window))
    {
        return true;
    }
    else
    {
        return false;
    }
}

