#include "SkillsNode.h"


SkillsNode::SkillsNode(const sf::Texture& desativado, const sf::Texture& ativado, const sf::Texture& desenho, const sf::Texture& desc)
{
    simbolo[0].setTexture(desativado);
    simbolo[1].setTexture(ativado);
    simbolo[2].setTexture(desenho);
    this->Dir = NULL;
    this->Esq = NULL;
    this->status = false;
    this->setOriginCenter();

    SpriteNode *aux = new SpriteNode(desc);

    aux->setPosition(200.f,155.f);
    this->insereFilho(aux);

    this->desc = false;
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
    {

        target.draw(simbolo[1], states);
        if(this->Dir != NULL && this->Esq !=  NULL)
        {
                target.draw(simbolo[3], states);
                target.draw(simbolo[4], states);
        }
    }
    else
        target.draw(simbolo[0], states);
    target.draw(simbolo[2], states);
    if(desc)
        this->desenhaFilhos(target, states);
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
        status = true;
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
        desc=true;
        return true;
    }
    else
    {
        desc=false;
        return false;
    }
}

void SkillsNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    desenhaAtual(target, states);
    //desenhaFilhos(target, states);
}
