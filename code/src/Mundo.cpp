#include "Mundo.h"

#include <iostream>

Mundo::Mundo(sf::RenderWindow& window): tela(window),
mundoView(window.getDefaultView()),
//texturas(),
cenaTree(),
layersCena(),
//player();
mundoBounds(0.f, 0.f, mundoView.getSize().x, 8000.f),
viewCenter(mundoView.getSize().x / 2.f, mundoBounds.height - mundoView.getSize().y / 2.f),
scrollSpeed(-50.f)
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
	for (int i = 0; i < LayerCount; ++i)
	{
	    std::cout<<i<<std::endl;
		NodeCena* layer;
		layer = new NodeCena;
		layersCena[i] = layer;
		cenaTree.insereFilho(layer);
	}

	// Prepare the tiled background
	if(!background[0].loadFromFile("src/images/background/grama.png"))
    {
        tela.close();
    }
    if(!background[1].loadFromFile("src/images/background/troposfera.png"))
    {
        tela.close();
    }
    if(!background[2].loadFromFile("src/images/background/estratosfera.png"))
    {
        tela.close();
    }
    if(!background[3].loadFromFile("src/images/background/mesosfera.png"))
    {
        tela.close();
    }
    if(!background[4].loadFromFile("src/images/background/termosfera.png"))
    {
        tela.close();
    }
    if(!background[5].loadFromFile("src/images/background/exosfera.png"))
    {
        tela.close();
    }
    if(!background[6].loadFromFile("src/images/background/t1.png"))
    {
        tela.close();
    }
    if(!background[7].loadFromFile("src/images/background/t2.png"))
    {
        tela.close();
    }
    if(!background[8].loadFromFile("src/images/background/t3.png"))
    {
        tela.close();
    }
    if(!background[9].loadFromFile("src/images/background/t4.png"))
    {
        tela.close();
    }


    sf::FloatRect back1(0.f, 0.f, mundoView.getSize().x, 2150);
    sf::FloatRect back2(0.f, 0.f, mundoView.getSize().x, 2165);
    sf::FloatRect back3(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back4(0.f, 0.f, mundoView.getSize().x, 1445);
    sf::FloatRect back5(0.f, 0.f, mundoView.getSize().x, 815);
    sf::FloatRect back6(0.f, 0.f, mundoView.getSize().x, 360);
    sf::FloatRect back7(0.f, 0.f, mundoView.getSize().x, 360);
    sf::FloatRect back8(0.f, 0.f, mundoView.getSize().x, 360);
    sf::FloatRect back9(0.f, 0.f, mundoView.getSize().x, 360);

	sf::IntRect texturaRect(mundoBounds);
	sf::IntRect texturaRect1(back1);
	sf::IntRect texturaRect2(back2);
	sf::IntRect texturaRect3(back3);
	sf::IntRect texturaRect4(back4);
	sf::IntRect texturaRect5(back5);
	sf::IntRect texturaRect6(back6);
	sf::IntRect texturaRect7(back7);
	sf::IntRect texturaRect8(back8);
	sf::IntRect texturaRect9(back9);

	background[0].setRepeated(false);
	background[1].setRepeated(true);
	background[2].setRepeated(true);
	background[3].setRepeated(true);
	background[4].setRepeated(true);
	background[6].setRepeated(true);
	background[7].setRepeated(true);
	background[8].setRepeated(true);
	background[9].setRepeated(true);


	// Add the background sprite to the scene

	SpriteNode* backgroundSprite1(new SpriteNode(background[1], texturaRect1));
	backgroundSprite1->setPosition(mundoBounds.left, 5852.324);
	layersCena[Background]->insereFilho(backgroundSprite1);

    SpriteNode* backgroundSprite2(new SpriteNode(background[2], texturaRect2));
	backgroundSprite2->setPosition(mundoBounds.left, 3692.651);
	layersCena[Background]->insereFilho(backgroundSprite2);

	SpriteNode* backgroundSprite3(new SpriteNode(background[3], texturaRect3));
	backgroundSprite3->setPosition(mundoBounds.left, 2252.869);
	layersCena[Background]->insereFilho(backgroundSprite3);

	SpriteNode* backgroundSprite4(new SpriteNode(background[4], texturaRect4));
	backgroundSprite4->setPosition(mundoBounds.left, 813.087);
	layersCena[Background]->insereFilho(backgroundSprite4);

	SpriteNode* backgroundSprite5(new SpriteNode(background[5], texturaRect5));
	backgroundSprite5->setPosition(mundoBounds.left, mundoBounds.top);
	layersCena[Background]->insereFilho(backgroundSprite5);

	SpriteNode* backgroundSprite(new SpriteNode(background[0], texturaRect));
	backgroundSprite->setPosition(mundoBounds.left, 7300);
	layersCena[Background]->insereFilho(backgroundSprite);

	SpriteNode* backgroundSprite6(new SpriteNode(background[6], texturaRect6));
	backgroundSprite6->setPosition(mundoBounds.left, 5852.324);
	layersCena[Background]->insereFilho(backgroundSprite6);

	SpriteNode* backgroundSprite7(new SpriteNode(background[7], texturaRect7));
	backgroundSprite7->setPosition(mundoBounds.left, 3693);
	layersCena[Background]->insereFilho(backgroundSprite7);

	SpriteNode* backgroundSprite8(new SpriteNode(background[8], texturaRect8));
	backgroundSprite8->setPosition(mundoBounds.left, 2253);
	layersCena[Background]->insereFilho(backgroundSprite8);

	SpriteNode* backgroundSprite9(new SpriteNode(background[9], texturaRect9));
	backgroundSprite9->setPosition(mundoBounds.left, 814);
	layersCena[Background]->insereFilho(backgroundSprite9);


	// Add player's
	/*if (!test2.loadFromFile("src/images/nave.png"))
    {
        tela.close();
    }

	SpriteNode* nave(new SpriteNode(test2));
	nave->setPosition(viewCenter);
	layersCena[Middle]->insereFilho(nave);
    */
}
