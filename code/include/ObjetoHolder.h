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
    void insereFilho(Objeto* filho);
    bool verificaColisao(Foguete*);
    std::vector<Objeto*> getFilhos()const;

private:
    std::vector<Objeto*> filhos;
};

#endif // OBJETOHOLDER_H
