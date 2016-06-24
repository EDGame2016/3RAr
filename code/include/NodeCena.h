#ifndef NODECENA_H
#define NODECENA_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <algorithm>


class NodeCena : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    NodeCena();

    void					insereFilho(NodeCena* filho);
    void					retiraFilho(const NodeCena& node);
    std::vector<NodeCena*>  getFilhos();

    void					atualiza(sf::Time delta);

    sf::Vector2f			getWorldPosition() const;
    sf::Transform			getWorldTransform() const;
    virtual sf::FloatRect	getBoundingRect() const;
    virtual void            setOriginCenter();
    void					desenhaFilhos(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    virtual void			atualizaAtual(sf::Time delta);
    void					atualizaFihos(sf::Time delta);

    virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void			desenhaAtual(sf::RenderTarget& target, sf::RenderStates states) const;


protected:
    std::vector<NodeCena*>	filhos;
    NodeCena*				pai;
};

#endif // NODECENA_H
