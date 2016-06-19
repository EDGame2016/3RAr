#include "JogoAr.h"

const sf::Time JogoAr::TimePerFrame = sf::seconds(1.f/60.f);

JogoAr::JogoAr():
    tela(sf::VideoMode(1280, 720), "3R - Ar"),
    mundoDoJogo(tela),
    mainMenu(tela)
{
    estado = false;
}

void JogoAr::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (tela.isOpen())
    {
        timeSinceLastUpdate += clock.restart();

        if(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate = sf::Time::Zero;
            processaEventos();
            atualiza(TimePerFrame);
        }

        renderiza();
    }
}

void JogoAr::processaEventos()
{
    if(!estado)
    {
        switch(mainMenu.processaEventos())
        {
        case(Menu::SAIR):
        {
            tela.close();
            break;
        }
        case(Menu::JOGAR):
        {
            estado = true;
            mainMenu.stopMusic();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        if(mundoDoJogo.processaEventos() == Mundo::BACK)
        {
            estado = false;
            mainMenu.playMusic();
        }
    }
}

void JogoAr::atualiza(sf::Time elapsedTime)
{
    if(estado)
        mundoDoJogo.atualiza(elapsedTime);
    else
        mainMenu.atualiza(elapsedTime);
}

void JogoAr::renderiza()
{
    tela.clear(sf::Color(255, 255, 255, 0));

    if(estado)
        mundoDoJogo.desenha();
    else
        mainMenu.desenha();

    tela.setView(tela.getDefaultView());
    tela.display();
}

void JogoAr::playerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
    case (sf::Keyboard::Escape):
    {
        if(isPressed)
            tela.close();
        break;
    }
    default:
        break;
    }
}

