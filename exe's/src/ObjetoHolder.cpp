#include "ObjetoHolder.h"

ObjetoHolder::ObjetoHolder():
    filhos()
{
    this->tipo = false;
}

void ObjetoHolder::setTipo(bool tipo)
{
    this->tipo = tipo;
}

void ObjetoHolder::insereFilho(Objeto* filho)
{
    filhos.push_back(filho);
}

void ObjetoHolder::esvaziaFilhos()
{
    this->filhos.erase(filhos.begin(),filhos.end());
}

Objeto::Tipo ObjetoHolder::verificaColisao(Foguete* player)
{
    for(unsigned int i = 0; i<filhos.size(); i++)
    {
        if(Collision::PixelPerfectTest(player->getSprite(), filhos[i]->getSprite()))
        {
            player->colidiu(filhos[i]->getTipo());
            return filhos[i]->getTipo();
        }
    }

    if(!tipo)
    {
        player->colidiu(Objeto::NONE);
        return Objeto::NONE;
    }
    else
    {
        player->colidiu(Objeto::SKILLNONE);
        return Objeto::SKILLNONE;
    }
}

std::vector<Objeto*> ObjetoHolder::getFilhos()const
{
    return filhos;
}
