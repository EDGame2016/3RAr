#include "Mundo.h"

#include <iostream>

Mundo::Mundo(sf::RenderWindow& window): tela(window),
mundoView(window.getDefaultView()),
//texturas(),
cenaTree(),
layersCena(),
//player();
mundoBounds(0.f, 0.f, mundoView.getSize().x, 2000.f),
viewCenter(mundoView.getSize().x / 2.f, mundoBounds.height - mundoView.getSize().y / 2.f),
scrollSpeed(-50.f),
test()
{
	loadTexturas();
	constroiCena();

	mundoView.setCenter(viewCenter);
}

void Mundo::atualiza(sf::Time dt)
{
	mundoView.move(0.f, scrollSpeed * dt.asSeconds());
    /*
	sf::Vector2f position = player->getPosition();
	sf::Vector2f velocity = player->getVelocity();

	//Se o jogador tocar as bordas, inverte sua velocidade X
	if (position.x <= mundoBounds.left + 150.f || position.x >= mundoBounds.left + mundoBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		player->setVelocity(velocity);
	}*/

	// Apply movements
	cenaTree.atualiza(dt);
}

void Mundo::desenha()
{

	tela.setView(mundoView);
	tela.draw(cenaTree);
}

void Mundo::loadTexturas()
{

}

void Mundo::constroiCena()
{
	// Inicializa as diferentes camadas (Layers)
	for (int i = 0; i < LayerCount; i++)
	{
		NodeCena* layer;
		layer = new NodeCena;
		layersCena[i] = layer;
		cenaTree.insereFilho(layer);
	}

	// Prepare the tiled background
	if(!test.loadFromFile("src/images/back.png"))
    {
        tela.close();
    }

	sf::IntRect texturaRect(mundoBounds);
	test.setRepeated(true);

	// Add the background sprite to the scene
	SpriteNode* backgroundSprite(new SpriteNode(test, texturaRect));
	backgroundSprite->setPosition(mundoBounds.left, mundoBounds.top);
	layersCena[Background]->insereFilho(backgroundSprite);

	// Add player's
	if (!test2.loadFromFile("src/images/nave.png"))
    {
        tela.close();
    }

	SpriteNode* nave(new SpriteNode(test2));
	nave->setPosition(viewCenter);
	layersCena[Middle]->insereFilho(nave);
}
