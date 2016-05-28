#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture): sprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect): sprite(texture, textureRect)
{

}

void SpriteNode::desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
sf::FloatRect SpriteNode::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}
