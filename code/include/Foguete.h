#ifndef FOGUETE_H
#define FOGUETE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>

#include "Entidade.h"

class Foguete: public Entidade
{
public:
            Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2);
    void    setSound(sf::SoundBuffer& buffer);
    void    moveEsq();
    void    moveDir();
    void    reinicia();
    void    destroi();

    virtual sf::FloatRect   getBoundingRect() const;
    sf::Sprite              getSprite() const;
    void                    setEstado(bool);

private:
    void    desenhaAtual(sf::RenderTarget&, sf::RenderStates) const;
    void    atualizaAtual(sf::Time dt);


public:
    sf::Sprite                  sprite;
    std::array<sf::Sprite, 2>   fogo;
    sf::Sound                   partidaSound;
    int                         carga, tCarga;
    sf::Time                    tempo;
    bool                        turbo;
    bool                        estado;
};

#endif // FOGUETE_H
