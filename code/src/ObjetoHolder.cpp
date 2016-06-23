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
    for(int i = 0; i<filhos.size(); i++)
    {
        if(Collision::PixelPerfectTest(player->getSprite(), filhos[i]->getSprite()))
        {
            std::cout<<"Colide"<<std::endl;
        }
    }
}

std::vector<Objeto*> ObjetoHolder::getFilhos()const
{
    return filhos;
}
