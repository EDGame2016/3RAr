#ifndef OBJETOHOLDER_H
#define OBJETOHOLDER_H

#include <vector>

#include "Foguete.h"
#include "Objeto.h"
#include "Collision.h"
#include <iostream>

class ObjetoHolder
{
public:
    ObjetoHolder();
    void setTipo(bool);
    void insereFilho(Objeto* filho);
    Objeto::Tipo verificaColisao(Foguete*);
    std::vector<Objeto*> getFilhos()const;
    void esvaziaFilhos();

private:
    std::vector<Objeto*> filhos;
    bool                 tipo;
};

#endif // OBJETOHOLDER_H
