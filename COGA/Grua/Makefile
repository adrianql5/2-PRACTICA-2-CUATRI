PROJECT_DIR := Grua
TARGET := $(PROJECT_DIR)/grua
BUILD_DIR := build

PKG_CONFIG ?= pkg-config
CXX ?= g++
CC ?= gcc
GLAD_DIR ?=
GLM_DIR ?=
STB_DIR ?=
GLFW_DIR ?=

INCLUDE_DIRS := $(PROJECT_DIR) $(GLAD_DIR) $(GLM_DIR) $(STB_DIR) $(GLFW_DIR)

CPPFLAGS += $(addprefix -I,$(filter-out ,$(INCLUDE_DIRS))) $(EXTRA_CPPFLAGS)
CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic $(EXTRA_CXXFLAGS)
CFLAGS += -std=c11 -Wall -Wextra -pedantic $(EXTRA_CFLAGS)
LDLIBS += $(EXTRA_LDLIBS)

GLFW_CFLAGS := $(shell $(PKG_CONFIG) --cflags glfw3 2>/dev/null)
GLFW_LIBS := $(shell $(PKG_CONFIG) --libs glfw3 2>/dev/null)
GLEW_CFLAGS := $(shell $(PKG_CONFIG) --cflags glew 2>/dev/null)
GLEW_LIBS := $(shell $(PKG_CONFIG) --libs glew 2>/dev/null)

ifeq ($(shell uname -s),Linux)
GL_LOADER_CFLAGS := $(GLEW_CFLAGS)
GL_LOADER_LIBS := $(GLEW_LIBS)
GLAD_SRC :=
else ifneq ($(shell $(PKG_CONFIG) --exists glad && echo yes),)
GLAD_CFLAGS := $(shell $(PKG_CONFIG) --cflags glad 2>/dev/null)
GLAD_LIBS := $(shell $(PKG_CONFIG) --libs glad 2>/dev/null)
GLAD_SRC :=
GL_LOADER_CFLAGS := $(GLAD_CFLAGS)
GL_LOADER_LIBS := $(GLAD_LIBS)
else
GLAD_SRC := $(PROJECT_DIR)/glad.c
GL_LOADER_CFLAGS :=
GL_LOADER_LIBS :=
endif

CPPFLAGS += $(GLFW_CFLAGS) $(GL_LOADER_CFLAGS)
LDLIBS += $(GLFW_LIBS) $(GL_LOADER_LIBS) -lGL -ldl -lm

CPP_SOURCES := \
	$(PROJECT_DIR)/main.cpp \
	$(PROJECT_DIR)/camara.cpp \
	$(PROJECT_DIR)/objetos.cpp

C_SOURCES := $(GLAD_SRC)
OBJECTS := $(CPP_SOURCES:%.cpp=$(BUILD_DIR)/%.o) $(C_SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	cd $(PROJECT_DIR) && ./$(notdir $(TARGET))

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
