#ifndef OBSTACULO_H
#define OBSTACULO_H


class Obstaculo : public Entidade
{
    public:
        enum Type
        {

        };

    public:
        Obstaculo(Type);
        virtual ~Obstaculo();
        int getDano();

    private:
        Type tipo;
        int dano;
};

#endif // OBSTACULO_H
