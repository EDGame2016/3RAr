#include "ObjetoHolder.h"

ObjetoHolder::ObjetoHolder():
    filhos()
{

}
void ObjetoHolder::insereFilho(Objeto* filho)
{
    filhos.push_back(filho);
}
bool ObjetoHolder::verificaColisao(Foguete* player)
{
    std::cout<<filhos.size()<<std::endl;
    for(unsigned int i = 0; i<filhos.size(); i++)
    {
        if(Collision::PixelPerfectTest(player->getSprite(), filhos[i]->getSprite()))
        {
            player->colidiu(filhos[i]->getTipo());
            return true;
        }
    }

    player->colidiu(Objeto::NONE);
    return false;
}

std::vector<Objeto*> ObjetoHolder::getFilhos()const
{
    return filhos;
}
