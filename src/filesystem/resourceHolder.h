//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_FILE_MANAGER_H
#define INC_2D_GAME_FILE_MANAGER_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>


#include "core/shader.h"
#include "core/texture.h"
#include "core/log2.h"
#include "../../deps/stb/stb_image.h"

using string_view = std::string_view;

class ResourceHolder {
public:
    static Shader load_shader_program(std::string name, const GLchar *vert_file, const GLchar *frag_file, const GLchar *geom_file = nullptr);
    static const Shader& get_shader(std::string shader_name);
    static Texture2d load_texture(const std::string& img_file, bool alpha, std::string name);
    static const Texture2d& get_texture(std::string texture_name);
    static void clean();

    ResourceHolder() = delete;
    ResourceHolder(const ResourceHolder& other) = delete;
    ResourceHolder(ResourceHolder&& other) = delete;
    ResourceHolder &operator=(const ResourceHolder& other) = delete;
    ResourceHolder &operator=(ResourceHolder&& other) = delete;

private:
    static std::unordered_map<std::string, Shader> shaders;
    static std::unordered_map<std::string, Texture2d> textures;
    static std::string load_shader(const GLchar *file_path);
};


#endif //INC_2D_GAME_FILE_MANAGER_H
