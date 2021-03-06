#include "Entidade.h"

Entidade::Entidade():
    velocidade(0.f),
    aceleracao(0.f),
    direcao(0,0)
{

}

void Entidade::atualizaAtual(sf::Time delta)
{

}

void Entidade::setVelocidade(float value)
{
    this->velocidade = value;
}

void Entidade::setAceleracao(float aceleracao)
{
    this->aceleracao = aceleracao;
}

void Entidade::setDirecao(float x, float y)
{
    this->direcao.x = x;
    this->direcao.y = y;
}

float Entidade::getVelocidade() const
{
    return this->velocidade;
}

float Entidade::getAceleracao() const
{
    return this->aceleracao;
}

sf::Vector2f Entidade::getDirecao() const
{
    return this->direcao;
}

void Entidade::acelera(float value)
{
    this->aceleracao += value;
}

void Entidade::atualizaVelocidade()
{
    this->velocidade += this->aceleracao;
}

