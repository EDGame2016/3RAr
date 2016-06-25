#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>

static const std::size_t NUM_TEXTURES = 4;
static const unsigned int TEXTURE_SIZE = 128;
static const std::size_t NUM_STARS_PER_TEXTURE = 20;
static const std::size_t NUM_LAYERS = 6;
static const float SPEED = 150.0f;
static const float SLOWDOWN_FACTOR = 0.5f;
static const float Y_SHIFT = 15.0f;
static const unsigned int COLOR_SHIFT = 40;

static const unsigned int SCREEN_WIDTH = 800;
static const unsigned int SCREEN_HEIGHT = 600;

struct Layer {
	float speed;
	sf::Vector2f offset;
	std::size_t texture_id;
};

typedef std::vector<sf::Texture> TextureArray;
typedef std::vector<Layer> LayerArray;

int main() {
	sf::RenderWindow window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Stars example" );

	window.setFramerateLimit( 60 );

	// Init randomizer.
	std::srand( static_cast<unsigned int>( std::time( 0 ) ) );

	// Prepare textures.
	TextureArray textures( NUM_TEXTURES );

	for( std::size_t texture_id = 0; texture_id < NUM_TEXTURES; ++texture_id ) {
		sf::Image image;
		image.create( TEXTURE_SIZE, TEXTURE_SIZE, sf::Color::Black );

		// Set stars.
		for( std::size_t star_id = 0; star_id < NUM_STARS_PER_TEXTURE; ++star_id ) {
			sf::Vector2<unsigned int> star_pos(
				std::rand() % TEXTURE_SIZE,
				std::rand() % TEXTURE_SIZE
			);

			image.setPixel( star_pos.x, star_pos.y, sf::Color::White );
			image.createMaskFromColor( sf::Color::Black );
		}

		textures[texture_id].loadFromImage( image );
	}

	// Prepare layers.
	LayerArray layers( NUM_LAYERS );

	for( std::size_t layer_id = 0; layer_id < NUM_LAYERS; ++layer_id ) {
		layers[layer_id].offset = sf::Vector2f( 0, static_cast<float>( layer_id ) * Y_SHIFT );
		layers[layer_id].speed = SPEED / static_cast<float>( layer_id + 1 ) * SLOWDOWN_FACTOR;
		layers[layer_id].texture_id = layer_id % NUM_TEXTURES;
	}

	sf::Event event;
	while( window.isOpen() ) {
		while( window.pollEvent( event ) ) {
			if( event.type == sf::Event::Closed ) {
				window.close();
			}
		}

		//float frame_time( static_cast<float>( window.get ) / 1000.0f );

		window.clear();

		// Update offsets and render.
		for( int layer_id = NUM_LAYERS - 1; layer_id >= 0; --layer_id ) {
			layers[layer_id].offset.x += layers[layer_id].speed * 60/1000.f;

			while( layers[layer_id].offset.x >= static_cast<float>( TEXTURE_SIZE ) ) {
				layers[layer_id].offset.x -= static_cast<float>( TEXTURE_SIZE );
				layers[layer_id].texture_id =
					(
						layers[layer_id].texture_id +
						static_cast<std::size_t>( std::ceil( (static_cast<float>( SCREEN_HEIGHT ) + layers[layer_id].offset.y) / static_cast<float>( TEXTURE_SIZE ) ) ) +
						1
					) % NUM_TEXTURES
				;
			}

			static std::size_t texture_id;
			static sf::Vector2f target_pos;
			static sf::Sprite sprite;

			// Init initial texture ID and color.
			texture_id = layers[layer_id].texture_id;

			sprite.setColor(
				sf::Color(
					static_cast<sf::Uint8>( 255 - layer_id * COLOR_SHIFT ),
					static_cast<sf::Uint8>( 255 - layer_id * COLOR_SHIFT ),
					static_cast<sf::Uint8>( 255 - layer_id * COLOR_SHIFT )
				)
			);

			for( target_pos.x = -layers[layer_id].offset.x; target_pos.x < static_cast<float>( SCREEN_WIDTH + TEXTURE_SIZE ); target_pos.x += static_cast<float>( TEXTURE_SIZE ) ) {
				for( target_pos.y = -layers[layer_id].offset.y; target_pos.y < static_cast<float>( SCREEN_HEIGHT + TEXTURE_SIZE ); target_pos.y += static_cast<float>( TEXTURE_SIZE ) ) {
					sprite.setTexture( textures[texture_id], true );
					sprite.setPosition( target_pos );
					window.draw( sprite );

					texture_id = (texture_id + 1) % NUM_TEXTURES;
				}
			}
		}

		window.display();
	}
}
