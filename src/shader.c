#include <glad/glad.h>

void buildShaderProgram(size_t *shaderProgram) {
  size_t vertShader, fragShader;

  const char *vertShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec3 ourColor;\n"
  "void main() {\n"
  "  gl_Position = vec4(aPos, 1.0);\n"
  "  ourColor = aColor;\n"
  "}\n", *fragShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 ourColor;\n"
  "void main() {\n"
  "  FragColor = vec4(ourColor, 1.0);\n"
  "}\n";

  vertShader = glCreateShader(GL_VERTEX_SHADER);
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertShader, 1, &vertShaderSource, NULL);
  glShaderSource(fragShader, 1, &fragShaderSource, NULL);

  glCompileShader(vertShader);
  glCompileShader(fragShader);

  *shaderProgram = glCreateProgram();

  glAttachShader(*shaderProgram, vertShader);
  glAttachShader(*shaderProgram, fragShader);
  glLinkProgram(*shaderProgram);

  glDeleteShader(fragShader);
  glDeleteShader(vertShader);
}
