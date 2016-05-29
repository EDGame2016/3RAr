#ifndef FOGUETE_H
#define FOGUETE_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entidade.h"
#include "SpriteNode.h"

class Foguete: public Entidade
{
public:
    //Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2);
    Foguete(const sf::Texture& foguete);
    virtual sf::FloatRect getBoundingRect() const;
    void moveEsq();
    void moveDir();

private:
    void desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
    void atualizaAtual(sf::Time dt);

private:
    sf::Sprite sprite;
    //std::array<sf::Texture&,2> texturas;
};

#endif // FOGUETE_H
