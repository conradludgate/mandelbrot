#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int compile_shader(int shader_type, const GLchar * const * source)
{
	int shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, source, NULL);
    glCompileShader(shader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}