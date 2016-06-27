#ifndef FOGUETE_H
#define FOGUETE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>

#include "SkillsNode.h"
#include "Entidade.h"
#include "Objeto.h"

class Foguete: public Entidade
{
public:
            Foguete(const sf::Texture& foguete, const sf::Texture& fogo1, const sf::Texture& fogo2);
    void    setSound(sf::SoundBuffer& buffer);
    void    moveEsq();
    void    moveDir();
    void    colidiu(Objeto::Tipo);
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
    int                         dano;
    int                         shield;
    bool                        aprimoramento[7];
    bool                        ignoraNuvem;
    bool                        camadaOzonio;

    sf::Time                    tempo;

    bool                        turbo;
    bool                        estado;
    bool                        isColliding;
};

#endif // FOGUETE_H
