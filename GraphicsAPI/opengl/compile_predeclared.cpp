//
// Created by zhanghong50 on 2022/1/28.
//

#include "complie_predeclared.h"

namespace AliceAPI {


InitGraphic::InitGraphic() {
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
    }
    printf("OpenGL %s is used.\n", glGetString(GL_VERSION));
}


InitGraphic::~InitGraphic() {

}

}
