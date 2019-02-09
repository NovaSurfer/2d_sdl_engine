//
// Created by Maksim Ruts on 29-Aug-18.
//

#include "resourceHolder.h"

std::unordered_map<std::string, Shader> ResourceHolder::shaders;
std::unordered_map<std::string, Texture2d> ResourceHolder::textures;

Shader ResourceHolder::load_shader_program(std::string name, const GLchar *vert_file,
        const GLchar *frag_file, const GLchar *geom_file) {
    Shader shader{};
    std::string v_shader, f_shader, g_shader;
    v_shader = load_shader(vert_file);
    f_shader = load_shader(frag_file);
    if(geom_file != nullptr) g_shader = load_shader(geom_file);
    shader.compile(v_shader.c_str(), f_shader.c_str(), geom_file != nullptr ? g_shader.c_str() : nullptr);
    shaders.insert({name, shader});
    return shaders[name];
}


const Shader& ResourceHolder::get_shader(std::string shader_name) {
    return shaders[shader_name];
}

Texture2d ResourceHolder::load_texture(const std::string& img_file, bool alpha, std::string name) {
    int width, height, nr_channels;
    unsigned char *image = stbi_load(img_file.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);

    textures[name] = Texture2d(image, width, height, alpha ? GL_RGBA : GL_RGB);
    return textures[name];
}

const Texture2d& ResourceHolder::get_texture(std::string texture_name){
    return textures[texture_name];
}

void ResourceHolder::clean() {
    for (auto s : shaders)
        glDeleteProgram(s.second.get_program());
    for (auto t : textures)
        glDeleteTextures(1, &t.second.get_obj_id());
}

// TODO: remove C++ streams and exceptions 
std::string ResourceHolder::load_shader(const GLchar *file_path) {
    try
    {
        std::ifstream shader_file(file_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        return shader_stream.str();

    }catch (const std::exception &e)
    {
        log_err_file("Failed to read shader file %s", file_path);
    }
    return{};
}