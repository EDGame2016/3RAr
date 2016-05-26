#ifndef IDRESOURCES_H_INCLUDED
#define IDRESOURCES_H_INCLUDED

namespace sf
{
    class Texture;
}

namespace Textures
{
	enum ID
	{
	    BACK,
	    NAVE
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // IDRESOURCES_H_INCLUDED
