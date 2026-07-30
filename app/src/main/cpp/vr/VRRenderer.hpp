#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLES3/gl3.h>

enum class Eye { Left, Right };

class VRRenderer {
public:
    void initialise();
    void renderEye(GLuint swapchainImage, GLuint gdTexture, const glm::mat4& view, const glm::mat4& proj);
    void drawToScreen(GLuint gdTexture);
    void setScreenDistance(float distance);
    void shutdown();
private:
    GLuint m_roomShader;
    GLuint m_fbo;
    GLuint m_screenVAO;
    float m_screenDistance = -2.0f;
    GLuint createProgram(const char* vertSource, const char* fragSource);
};
