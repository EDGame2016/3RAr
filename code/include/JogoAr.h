#ifndef JOGOAR_H
#define JOGOAR_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Skills.h"
#include "Mundo.h"
#include "Menu.h"

class JogoAr
{
public:
    JogoAr();
    void    run();


private:
    void    processaEventos();
    void    atualiza(sf::Time dt);
    void    renderiza();
    void    playerInput(sf::Keyboard::Key key, bool isPressed);

private:

    static const sf::Time   TimePerFrame;

    sf::RenderWindow    tela;

    Mundo   mundoDoJogo;
    Menu    mainMenu;
    bool    estado; // false se está no menu inicial e true se está jogando
};

#endif // JOGOAR_H
