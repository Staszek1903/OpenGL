#ifndef SKYBOX_H
#define SKYBOX_H

#include <AutisticGL/object.h>
#include <memory>

namespace agl {

    class SkyBox : public agl::Object
    {
    private:
        static SkyBox * instance;
    public:
        static SkyBox & getRef();
        static void deleteRef();

    protected:
        SkyBox();

        agl::ShadingProgram shad_prog;
        agl::Model model;
        sf::Texture texture;

    };
}

#endif // SKYBOX_H
