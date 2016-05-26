#ifndef JOGOAR_H
#define JOGOAR_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <toString.h>
#include "Mundo.h"

class JogoAr
{
public:

                            JogoAr();
    void                    run();


private:

    void                    processaEventos();
    void                    atualiza(sf::Time elapsedTime);
    void                    renderiza();

    void                    playerInput(sf::Keyboard::Key key, bool isPressed);

private:

    static const sf::Time	TimePerFrame;

    sf::RenderWindow        tela;
    Mundo                   mundoDoJogo;
};

#endif // JOGOAR_H
