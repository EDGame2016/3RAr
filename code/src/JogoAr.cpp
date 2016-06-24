#include "JogoAr.h"

const sf::Time JogoAr::TimePerFrame = sf::seconds(1.f/90.f);

JogoAr::JogoAr():
    tela(sf::VideoMode(1280, 720), "3R - Ar"),
    mundoDoJogo(tela),
    mainMenu(tela)
{
    tela.setFramerateLimit(120);
    estado = false; //Inicia com o menu inicial
}

void JogoAr::run()
{
    sf::Clock clock; //Gerencia o tempo de execução
    sf::Time timeSinceLastUpdate = sf::Time::Zero; //Gerencia o tempo desde que a ultima atualização foi realizada

    while (tela.isOpen())
    {
        timeSinceLastUpdate += clock.restart();

        if(timeSinceLastUpdate > TimePerFrame) //Controla a taxa de atualização do jogo em função do tempo
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

void JogoAr::atualiza(sf::Time dt)
{
    if(estado)
        mundoDoJogo.atualiza(dt);
    else
        mainMenu.atualiza(dt);
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

