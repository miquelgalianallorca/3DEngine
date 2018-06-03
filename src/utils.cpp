#include "utils.h"
#include "common.h"

bool Init()
{
    bool initOk = false;
    if (glewInit() == GLEW_OK)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_SCISSOR_TEST);
        initOk = true;
    }
    return initOk;
}
