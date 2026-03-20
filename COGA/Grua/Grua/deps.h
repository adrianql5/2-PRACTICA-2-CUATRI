#ifndef DEPS_H
#define DEPS_H

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#if defined(__linux__)
#include <GL/glew.h>
#elif defined(__has_include)
#if __has_include(<glad/glad.h>)
#include <glad/glad.h>
#elif __has_include("glad.h")
#include "glad.h"
#elif __has_include(<glad.h>)
#include <glad.h>
#else
#error "No se encontro glad.h. Instala GLAD o anade su directorio de includes al Makefile."
#endif
#else
#include "glad.h"
#endif

#if defined(__has_include)
#if __has_include(<GLFW/glfw3.h>)
#include <GLFW/glfw3.h>
#elif __has_include(<glfw3.h>)
#include <glfw3.h>
#else
#error "No se encontro glfw3.h. Instala GLFW o anade su directorio de includes al Makefile."
#endif
#else
#include <GLFW/glfw3.h>
#endif

#if defined(__has_include)
#if __has_include(<glm/glm.hpp>)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#else
#error "No se encontro GLM. Instala GLM o anade su directorio de includes al Makefile."
#endif
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#endif
