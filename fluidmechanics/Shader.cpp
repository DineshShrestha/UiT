#define _CRT_SECURE_NO_DEPRECATE

#include "Shader.hpp"
#include <windows.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::initShaders(char *fileName)
{
  int vSize, fSize;

  // Allocate memory to hold the source of our shaders.
  vSize = shaderSize(fileName, V_SHADER);
  fSize = shaderSize(fileName, F_SHADER);

  if((vSize == -1) || (fSize == -1))
  {
    cout << "Cannot determine size of the shader " << fileName << endl;
    return false;
  }

  vertexShaderSource_ = (GLchar *) malloc(vSize);
  fragmentShaderSource_ = (GLchar *) malloc(fSize);

  // Read the source code
  if(!readShader(fileName, V_SHADER, vertexShaderSource_, vSize))
  {
    printf("Cannot read the file %s.vert\n", fileName);
    return false;
  }

  if(!readShader(fileName, F_SHADER, fragmentShaderSource_, fSize))
  {
    printf("Cannot read the file %s.frag\n", fileName);
    return false;
  }

  GLint vertCompiled, fragCompiled;    // status values
  GLint linked;
  int infologLength = 0;
  int charsWritten  = 0;
  GLchar *infoLog;

  // Create a vertex shader object and a fragment shader object
  vs_ = glCreateShader(GL_VERTEX_SHADER);
  fs_ = glCreateShader(GL_FRAGMENT_SHADER);

  const char *vertS = vertexShaderSource_;
  const char *fragS = fragmentShaderSource_;
  // Load source code strings into shaders
  glShaderSource(vs_, 1, &vertS, NULL);
  glShaderSource(fs_, 1, &fragS, NULL);

  // Compile the vertex shader, and print out
  // the compiler log file.
  glCompileShader(vs_);
  glGetShaderiv(vs_, GL_COMPILE_STATUS, &vertCompiled);
  glGetShaderiv(vs_, GL_INFO_LOG_LENGTH, &infologLength);
  if (infologLength > 0)
  {
    infoLog = (GLchar *)malloc(infologLength);
    if (infoLog == NULL)
    {
      printf("ERROR: Could not allocate InfoLog buffer\n");
      exit(1);
    }
    glGetShaderInfoLog(vs_, infologLength, &charsWritten, infoLog);
    printf("Shader InfoLog:\n%s\n\n", infoLog);
    free(infoLog);
  }

  // Compile the fragment shader, and print out
  // the compiler log file.

  glCompileShader(fs_);
  glGetShaderiv(fs_, GL_COMPILE_STATUS, &fragCompiled);
  glGetShaderiv(fs_, GL_INFO_LOG_LENGTH, &infologLength);
  if (infologLength > 0)
  {
    infoLog = (GLchar *)malloc(infologLength);
    if (infoLog == NULL)
    {
      printf("ERROR: Could not allocate InfoLog buffer\n");
      exit(1);
    }
    glGetShaderInfoLog(fs_, infologLength, &charsWritten, infoLog);
    printf("Shader InfoLog:\n%s\n\n", infoLog);
    free(infoLog);
  }

  if (!vertCompiled || !fragCompiled)
      return false;

  // Create a program object and attach the two compiled shaders
  prog_ = glCreateProgram();
  glAttachShader(prog_, vs_);
  glAttachShader(prog_, fs_);

  // Link the program object and print out the info log

  glLinkProgram(prog_);
  glGetProgramiv(prog_, GL_LINK_STATUS, &linked);
  glGetProgramiv(prog_, GL_INFO_LOG_LENGTH, &infologLength);
  if (infologLength > 0)
  {
    infoLog = (GLchar *)malloc(infologLength);
    if (infoLog == NULL)
    {
      printf("ERROR: Could not allocate InfoLog buffer\n");
      exit(1);
    }
    glGetProgramInfoLog(prog_, infologLength, &charsWritten, infoLog);
    printf("Program InfoLog:\n%s\n\n", infoLog);
    free(infoLog);
  }
  if (!linked)
    return false;

  return true;
}



int Shader::shaderSize(char *fileName, ShaderType shaderType)
{
  // Returns the size in bytes of the shader fileName.
  // If an error occurred, it returns -1.
  //
  // File name convention:
  //
  // <fileName>.vert
  // <fileName>.frag
  //
  int fd;
  char name[100];
  int count = -1;

  strcpy(name, fileName);

  switch(shaderType)
  {
    case V_SHADER:
      strcat(name, ".vert");
      break;
    case F_SHADER:
      strcat(name, ".frag");
      break;
    default:
      cout << "ERROR: unknown shader file type " << endl;
      exit(1);
      break;
  }

  // Open the file, seek to the end to find its length (WIN32)
  fd = _open(name, _O_RDONLY);
  if (fd != -1)
  {
    count = _lseek(fd, 0, SEEK_END) + 1;
    _close(fd);
  }
  return count;
}

int Shader::readShader(char *fileName, ShaderType shaderType, char *shaderText, int size)
{
  // Reads a shader from the supplied file and returns the shader in the
  // arrays passed in. Returns 1 if successful, 0 if an error occurred.
  // The parameter size is an upper limit of the amount of bytes to read.
  // It is ok for it to be too big.
  FILE *fh;
  char name[100];
  int count;

  strcpy(name, fileName);

  switch (shaderType) 
  {
    case V_SHADER:
      strcat(name, ".vert");
      break;
    case F_SHADER:
      strcat(name, ".frag");
      break;
    default:
      printf("ERROR: unknown shader file type\n");
      exit(1);
      break;
  }

  // Open the file
  fh = fopen(name, "r");
  if (!fh)
    return -1;

  // Get the shader from a file.
  fseek(fh, 0, SEEK_SET);
  count = (int) fread(shaderText, 1, size, fh);
  shaderText[count] = '\0';

  if (ferror(fh))
      count = 0;

  fclose(fh);
  return count;
}

void Shader::enable()
{
  glUseProgram(prog_);
}
void Shader::disable()
{
  glUseProgram(0);
}

GLuint Shader::getProg()
{
  return prog_;
}

