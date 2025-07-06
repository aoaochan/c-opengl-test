#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void buildShaderProgram(size_t *shaderProgram);
void processInput(GLFWwindow *window);

const size_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

int main(void) {
  // === 1. Init ===
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // === 2. Create window ===
  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  // === 3. Build shader ===
  size_t shaderProgram;
  buildShaderProgram(&shaderProgram);

  // === 4. Create triangle ===
  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // === 5. Render loop ===
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // === 6. Cleanup ==
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}

void framebufferSizeCallback(GLFWwindow *_, int width, int height) {
  glViewport(0, 0, width, height);
}
void buildShaderProgram(size_t *shaderProgram) {
  size_t vertShader, fragShader;

  const char *vertShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
  "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\n", *fragShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
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
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
}
