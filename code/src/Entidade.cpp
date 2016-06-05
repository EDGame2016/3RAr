#include "Entidade.h"

Entidade::Entidade():
    direcao(0,-1)
{

}

void Entidade::atualizaAtual(sf::Time delta)
{

}

void Entidade::setVelocidade(float value)
{
    velocidade = value;
}
/*void Entidade::setVelocidade(float x, float y)
{
    velocidade.x = x;
    velocidade.y = y;

}*/
sf::Vector2f Entidade::getDirecao() const
{
    return direcao;
}
