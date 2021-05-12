// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Custom Class Headers
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <Shader.h>
#include <Texture.h>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Define Some Constants
const int WIDTH = 800;
const int HEIGHT = 600;

#endif //~ Glitter Header
