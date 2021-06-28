// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "btBulletDynamicsCommon.h"
#include "glad/glad.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

// Custom Class Headers
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// System Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Define Some Constants
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

#endif //~ Glitter Header
