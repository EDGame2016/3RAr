#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <NodeCena.h>

class Entidade : public NodeCena
{
	public:
                            Entidade();
                            ~Entidade();
        void                setVelocidade(sf::Vector2f);
        void                setVelocidade(float, float);
        sf::Vector2f        getVelocidade() const;


	private:
		virtual void		atualizaAtual(sf::Time delta);
		sf::Vector2f        velocidade;

};

#endif // ENTIDADE_H
