#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "shader.h"

static int readCode(const char *path, char **code);

int shaderInit(Shader *shader, const char *vertShaderPath, const char *fragShaderPath) {
  char *__vertShaderCode;
  if (readCode(vertShaderPath, &__vertShaderCode) != 0) return 1;

  char *__fragShaderCode;
  if (readCode(fragShaderPath, &__fragShaderCode) != 0) {
    free(__vertShaderCode);
    return 1;
  }

  unsigned int vertShader, fragShader;
  int success;
  char infoLog[512];
  const char *vertShaderCode = __vertShaderCode, *fragShaderCode = __fragShaderCode;

  vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertShaderCode, NULL);
  glCompileShader(vertShader);

  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
    printf("Error: Failed to compile vertShader: %s\n", infoLog);
    free(__vertShaderCode);
    free(__fragShaderCode);
    return 1;
  }
  
  free(__vertShaderCode);
  __vertShaderCode = NULL;

  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragShaderCode, NULL);
  glCompileShader(fragShader);

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
    printf("Error: Failed to compile fragShader: %s\n", infoLog);
    free(__fragShaderCode);
    return 1;
  }

  free(__fragShaderCode);
  __fragShaderCode = NULL;

  shader->ID = glCreateProgram();
  glAttachShader(shader->ID, vertShader);
  glAttachShader(shader->ID, fragShader);
  glLinkProgram(shader->ID);

  glGetProgramiv(shader->ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader->ID, 512, NULL, infoLog);
    printf("Error: Failed to link shader program\n");
    return 1;
  }

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
  
  return 0;
}
void shaderUse(Shader *shader) {
  glUseProgram(shader->ID);
}
void shaderSetBool(Shader *shader, const char *name, bool value) {
  glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}
void shaderSetInteger(Shader *shader, const char *name, int value) {
  glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
void shaderSetFloat(Shader *shader, const char *name, float value) {
  glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

static int readCode(const char *path, char **code) {
  FILE *fp = fopen(path, "rb");

  if (!fp) {
    perror("FILE *fp = fopen(path, \"r\")");
    return 1;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {
    perror("fseek(fp, 0, SEEK_END) != 0");
    fclose(fp);
    return 1;
  }

  long size = ftell(fp);
  if (size < 0) {
    perror("long size = ftell(fp)");
    fclose(fp);
    return 1;
  }

  rewind(fp);

  *code = (char*)malloc((size_t)size + 1);
  if (!*code) {
    perror("*code = (char*)malloc((size_t)size + 1)");
    fclose(fp);
    return 1;
  }

  if (fread(*code, 1, (size_t)size, fp) != (size_t)size) {
    perror("fread(*code, 1, (size_t)size, fp) != (size_t)size");
    free(*code);
    fclose(fp);
    return 1;
  }

  (*code)[size] = '\0';

  fclose(fp);

  return 0;
}
