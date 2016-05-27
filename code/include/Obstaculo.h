#ifndef OBSTACULO_H
#define OBSTACULO_H


class Obstaculo : public Entidade
{
    public:
        enum Type
        {
            Aviao,
            Chuva,
            Jato,
            Meteoro,
            Onibus,
            Satalite,
        };

    public:
        Obstaculo(Type);
        virtual ~Obstaculo();
        int getDano();

    private:
        Type tipo;
        int dano;

        sf::Texture& obstaculo[2];
};

#endif // OBSTACULO_H
