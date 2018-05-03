#ifndef TEXTURECOMP_H
#define TEXTURECOMP_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

struct TextureComp : public entityx::Component<TextureComp>
{
    TextureComp(sf::Texture & tex)
        :texture(tex){}
    sf::Texture & texture;
};
#endif // TEXTURECOMP_H
