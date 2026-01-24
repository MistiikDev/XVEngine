//
// Created by User on 28/11/2025.
//


#ifndef GLShader_H
#define GLShader_H

#include <core/log/log.h>
#include <core/io/rwxv.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEFAULT_VERTEX_SHADER "engine/src/graphics/opengl/shaders/default.vert"
#define DEFAULT_FRAG_SHADER "engine/src/graphics/opengl/shaders/default.frag"

class GLShader
{
    public:
        GLuint ID;
        GLShader( const char* vertexShader, const char* fragmentShader );

        void SetInt( const char* uniform, const int value);
        void SetBool( const char* uniform, const bool value);
        void SetFloat( const char* uniform, const float value );
        
        void SetMatrix4f( const char* uniform, const glm::mat4& matrix );
        void SetVector3f( const char* uniform, const glm::vec3& vector );
        
        static void CompilationErrors( unsigned int ShaderID, const char* shaderCompilationType );

        void Activate();
        void Destroy();

    private:
        bool m_isActive;
};


#endif //GGLENGINE_GLShader_H