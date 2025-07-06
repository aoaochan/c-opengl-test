#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>
#include <glad/glad.h>

typedef struct {
  unsigned int ID;
} Shader;

int shaderInit(Shader *shader, const char *vertShaderPath, const char *fragShaderPath);
void shaderUse(Shader *shader);
void shaderSetBool(Shader *shader, const char *name, bool value);
void shaderSetInteger(Shader *shader, const char *name, int value);
void shaderSetFloat(Shader *shader, const char *name, float value);

#endif
