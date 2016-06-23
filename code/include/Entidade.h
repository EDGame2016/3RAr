#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "NodeCena.h"

class Entidade : public NodeCena
{
public:
    Entidade();
    void            setVelocidade(float velocidade);
    void            setAceleracao(float aceleracao);
    void            setDirecao(float x, float y);
    float           getVelocidade() const;
    float           getAceleracao()const;
    sf::Vector2f    getDirecao() const;
    void            acelera(float value);
    void            atualizaVelocidade();

    virtual void    atualizaAtual(sf::Time delta);

private:
    float           velocidade;
    float           aceleracao;
    sf::Vector2f    direcao;

};

#endif // ENTIDADE_H
