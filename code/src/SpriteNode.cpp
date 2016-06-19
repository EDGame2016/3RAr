#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture): sprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect): sprite(texture, textureRect)
{

}

void SpriteNode::setOriginCenter()
{
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void SpriteNode::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

sf::FloatRect SpriteNode::getBoundingRect() const
{
	return sprite.getGlobalBounds();
}

sf::Sprite SpriteNode::getSprite() const
{
    sf::Sprite aux;
    aux = this->sprite;
    aux.setScale(getScale());
    aux.setPosition(this->getWorldPosition());
    aux.setRotation(this->getRotation());

    return aux;
}
