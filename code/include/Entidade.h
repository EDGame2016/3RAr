#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <NodeCena.h>

class Entidade : public NodeCena
{
	public:
                            Entidade();
                            ~Entidade();

	private:
		virtual void		atualizaAtual(sf::Time delta);

};

#endif // ENTIDADE_H
