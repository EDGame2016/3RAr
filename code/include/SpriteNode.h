#ifndef BOOK_SPRITENODE_HPP
#define BOOK_SPRITENODE_HPP

#include <NodeCena.h>

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public NodeCena
{
	public:
                            SpriteNode(const sf::Texture& texture);
							SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);


	private:
		virtual void		desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Sprite			sprite;
};

#endif // BOOK_SPRITENODE_HPP
