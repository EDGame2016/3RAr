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
    void                        setSound(sf::SoundBuffer& buffer);
    void                        moveEsq();
    void                        moveDir();
    void                        colidiuLateral();
    virtual sf::FloatRect       getBoundingRect() const;
    sf::Sprite                  getSprite() const;
    int                         getCarga()const;
    void                        reinicia(int);
    bool                        turbo;

private:
    void                        desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
    void                        atualizaAtual(sf::Time dt);


public:
    sf::Sprite                  sprite;
    std::array<sf::Sprite, 2>   fogo;
    sf::Sound                   partidaSound;
    int                         carga, tCarga;
    sf::Time                    tempo;
};

#endif // FOGUETE_H
