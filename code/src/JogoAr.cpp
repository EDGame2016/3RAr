#include "JogoAr.h"

const sf::Time JogoAr::TimePerFrame = sf::seconds(1.f/60.f);

JogoAr::JogoAr(): tela(sf::VideoMode(1280, 720), "Test"), mundoDoJogo(tela)

{

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

	while (tela.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				playerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				playerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				tela.close();
				break;
		}
	}
}

void JogoAr::atualiza(sf::Time elapsedTime)
{
	mundoDoJogo.atualiza(elapsedTime);
}

void JogoAr::renderiza()
{
	tela.clear(sf::Color(0,150,255,0));

	mundoDoJogo.desenha();

	tela.setView(tela.getDefaultView());
	tela.display();
}

void JogoAr::playerInput(sf::Keyboard::Key, bool)
{

}

