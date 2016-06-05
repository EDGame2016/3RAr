#include "JogoAr.h"
#include <iostream>
const sf::Time JogoAr::TimePerFrame = sf::seconds(1.f/60.f);

JogoAr::JogoAr(): tela(sf::VideoMode(1280, 720), "3R - Ar"), mundoDoJogo(tela), mainMenu(tela), skills(tela)
{
    estado = false;
    pausado = false;
}

void JogoAr::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (tela.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processaEventos();
            atualiza(TimePerFrame);

        }
        renderiza();
    }
}

void JogoAr::processaEventos()
{
    sf::Event event;
    if(!estado)
    {
        switch(mainMenu.processaEventos())
        {
        case(Menu::JOGAR):
        {
            estado = true;
            break;
        }
        case(Menu::SAIR):
        {
            tela.close();
            break;
        }
        default:
            break;
        }


        switch(skills.processaEventos())
        {
        case(Skills::JOGAR):
        {
            estado = true;
            break;
        }
        case(Skills::SAIR):
        {
            tela.close();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        Mundo::Evento est = mundoDoJogo.processaEventos();
        if(est == Mundo::PAUSA)
        {
                pausado = true;
                estado = false;
        }
    }

   }


void JogoAr::atualiza(sf::Time elapsedTime)
{
    if(estado)
        mundoDoJogo.atualiza(elapsedTime);
    else if(pausado)
        skills.atualiza(elapsedTime);
    else
        mainMenu.atualiza(elapsedTime);
}

void JogoAr::renderiza()
{
    tela.clear(sf::Color(255, 255, 255, 0));

    if(estado)
        mundoDoJogo.desenha();
    else if(pausado)
        skills.desenha();
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
           // tela.close();
           pausado = true;
           estado = false;
        break;
    }
    default:
        break;
    }
}

