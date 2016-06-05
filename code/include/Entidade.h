#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "NodeCena.h"

class Entidade : public NodeCena
{
public:
    Entidade();
    void                setVelocidade(float);
    //void                setVelocidade(float, float);
    sf::Vector2f        getDirecao() const;
    virtual void        atualizaAtual(sf::Time delta);

private:
//protected:    sf::Vector2f        velocidade;
protected:
    float velocidade;
    sf::Vector2f direcao;

};

#endif // ENTIDADE_H
