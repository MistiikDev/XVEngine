#include <graphics/api/opengl/buffers/GLShader.h>

GLShader::GLShader( const char* vertexShader, const char* fragmentShader ) {
    std::string vertexShaderCode = XV_READ_FILE(vertexShader);
    std::string fragmentShaderCode = XV_READ_FILE(fragmentShader);

    XV_LOG_DEBUG("{} - {} : {} / {}", "OpenGL Shader", "Loaded", vertexShader, fragmentShader);

    const char* vertexSource = vertexShaderCode.c_str();
    const char* fragSource = fragmentShaderCode.c_str();

    unsigned int vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderObject);

    unsigned int fragShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderObject, 1, &fragSource, NULL);
    glCompileShader(fragShaderObject);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragShaderObject);
    glLinkProgram(shaderProgram);

    this->ID = shaderProgram;
    
    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragShaderObject);

    XV_LOG_DEBUG("{} : {}", "OpenGL Shader", "Program Compilation Successfull");
}

void GLShader::Activate() {
    this->m_isActive = true;

    glUseProgram(this->ID);
}

void GLShader::SetMatrix4f( const char* uniform, const glm::mat4& matrix ) {
    if (!this->m_isActive) { 
        XV_LOG_DEBUG("{} {} : {}", "OpenGL WARN", "SHADER_COMPILATION_ERR", "Tried accessing shader when not active!\n");

        throw;
    }

    glUniformMatrix4fv(glGetUniformLocation(this->ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLShader::SetVector3f( const char* uniform, const glm::vec3& vector ) {
    if (!this->m_isActive) { 
        XV_LOG_DEBUG("{} {} : {}", "OpenGL WARN", "SHADER_COMPILATION_ERR", "Tried accessing shader when not active!\n");

        throw;
    }

    glUniform3f(glGetUniformLocation(this->ID, uniform), vector.x, vector.y, vector.z);
}

void GLShader::SetFloat( const char* uniform, const float value ) {
    if (!this->m_isActive) { 
        XV_LOG_DEBUG("{} {} : {}", "OpenGL WARN", "SHADER_COMPILATION_ERR", "Tried accessing shader when not active!\n");

        return;
    }

    glUniform1f(glGetUniformLocation(this->ID, uniform), value);
}

void GLShader::SetInt( const char* uniform, const int value ) {
    if (!this->m_isActive) { 
        XV_LOG_DEBUG("{} {} : {}", "OpenGL WARN", "SHADER_COMPILATION_ERR", "Tried accessing shader when not active!\n");

        return;
    }

    glUniform1i(glGetUniformLocation(this->ID, uniform), value);
}

void GLShader::SetBool( const char* uniform, const bool value) {
        if (!this->m_isActive) { 
        XV_LOG_DEBUG("{} {} : {}", "OpenGL WARN", "SHADER_COMPILATION_ERR", "Tried accessing shader when not active!\n");

        return;
    }

    glUniform1i(glGetUniformLocation(this->ID, uniform), value ? 1 : 0);
}

void GLShader::CompilationErrors( unsigned int ShaderID, const char* shaderCompilationType ) {
    GLint hasCompiled;
    const size_t infoLogBufSize = 512;
    char infoLog[infoLogBufSize];

    if (shaderCompilationType == (const char*)"PROGRAM") {
        glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &hasCompiled);

        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(ShaderID, infoLogBufSize, NULL, infoLog);

            XV_LOG_ERROR("{} {} : {}", "GLSHADER ERR", "SHADER_COMPILATION_ERR", std::string(infoLog));
        }
    } else {
        glGetProgramiv(ShaderID, GL_COMPILE_STATUS, &hasCompiled);

        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(ShaderID, infoLogBufSize, NULL, infoLog);

            XV_LOG_ERROR("{} {} : {}", "GLSHADER ERR", "SHADER_LINK_ERR", std::string(infoLog));
        }
    }
}

void GLShader::Destroy() {
    this->m_isActive = false;
    
    glDeleteProgram(this->ID);
}
