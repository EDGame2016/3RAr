#include "NodeCena.h"
#include <stdio.h>
NodeCena::NodeCena(): filhos(), pai(nullptr)
{
}

void NodeCena::insereFilho(NodeCena* filho)
{
    filho->pai = this;
    filhos.push_back(filho);
}

NodeCena* NodeCena::retiraFilho(const NodeCena& node)
{

}

std::vector<NodeCena*>  NodeCena::getFilhos()
{
    return filhos;
}

void NodeCena::atualiza(sf::Time dt)
{
    atualizaAtual(dt);
    atualizaFihos(dt);
}

void NodeCena::atualizaAtual(sf::Time dt)
{
    // Do nothing by default
}

void NodeCena::atualizaFihos(sf::Time dt)
{
    for (int i=0; i<filhos.size(); i++)
        filhos[i]->atualiza(dt);
}

void NodeCena::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    desenhaAtual(target, states);
    desenhaFilhos(target, states);
}

void NodeCena::desenhaAtual(sf::RenderTarget&, sf::RenderStates) const
{
    // Do nothing by default
}

void NodeCena::desenhaFilhos(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i=0; i<filhos.size(); i++)
        filhos[i]->draw(target, states);
}

sf::Vector2f NodeCena::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform NodeCena::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const NodeCena* node = this; node != nullptr; node = node->pai)
        transform = node->getTransform() * transform;

    return transform;
}

sf::FloatRect NodeCena::getBoundingRect() const
{
	return sf::FloatRect();
}
