#ifndef FOGUETE_H
#define FOGUETE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

#include <array>

#include "Entidade.h"
#include "SpriteNode.h"

class Foguete: public Entidade
{
public:
                                Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2);
    virtual sf::FloatRect       getBoundingRect() const;
    void                        setSound(sf::SoundBuffer& buffer);
    void                        moveEsq();
    void                        moveDir();
    void                        colidiuLateral();
    sf::Sprite                  getSprite() const;

private:
    void                        desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
    void                        atualizaAtual(sf::Time dt);

public:
    sf::Sprite                  sprite;
    std::array<sf::Sprite, 2>   fogo;
    sf::Sound                   launchSound;
};

#endif // FOGUETE_H
