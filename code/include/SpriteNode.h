#ifndef BOOK_SPRITENODE_HPP
#define BOOK_SPRITENODE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <NodeCena.h>

class SpriteNode : public NodeCena
{
public:
                                SpriteNode(const sf::Texture& texture);
                                SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    void                        setOriginCenter();
    virtual sf::FloatRect       getBoundingRect() const;
    sf::Sprite                  getSprite() const;

private:

    virtual void                desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite                  sprite;
};

#endif // BOOK_SPRITENODE_HPP
