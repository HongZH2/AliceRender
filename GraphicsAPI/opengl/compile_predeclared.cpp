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
    printf("%s\n", "GLEW::Initialization Success!");
    printf("OpenGL %s\n is used.", glGetString(GL_VERSION));
}


InitGraphic::~InitGraphic() {

}

}
