#ifndef _SHADER_H_
#define _SHADER_H_
#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
namespace wo
{
    class Shader
    {
    private:
        GLuint shaderProgram = 0;
    public:
        Shader() {}

        Shader(const char* vertexPath, const char* fragmentPath)
        {
            setFilePath(vertexPath, fragmentPath);
        }

        ~Shader()
        {
            glDeleteShader(shaderProgram);
        }
    public:
        void setFilePath(const char* vertexPath, const char* fragmentPath)//绑定链接着色器
        {
            // 从文件路径中获取顶点/片段着色器
        // 存储文件的内容
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            // 保证ifstream对象可以抛出异常：
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // 打开文件
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // 读取文件的缓冲内容到数据流中
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // 关闭文件处理器
                vShaderFile.close();
                fShaderFile.close();
                // 转换数据流到string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                cout << "着色器文件读取失败\n";
                exit(-1);
            }
            // 转换成C字符串以便后续编译
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // 编译着色器
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            // 顶点着色器
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            // 打印编译错误（如果有的话）
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "顶点着色器编译错误\n" << infoLog << std::endl;
            }

            // 编译片段着色器
            int success1;
            char infoLog1[512];
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            // 打印编译错误（如果有的话）
            glGetShaderiv(fragment, GL_FRAGMENT_SHADER, &success1);
            if (!success1)
            {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog1);
                std::cout << "片段着色器编译错误\n" << infoLog1 << std::endl;
            }

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertex);
            glAttachShader(shaderProgram, fragment);
            glLinkProgram(shaderProgram);
            // 打印连接错误（如果有的话）
            int success2;
            char infoLog2[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success2);
            if (!success2)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog2);
                std::cout << "程序对象链接失败\n" << infoLog2 << std::endl;
            }

            // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        GLuint getShaderID()//获取着色器程序对象ID
        {
            return shaderProgram;
        }

        void use()//激活着色器程序对象
        {
            glUseProgram(shaderProgram);
        }
    public:
        void setUniform(const char* name, float v1)
        {
            glUniform1f(glGetUniformLocation(shaderProgram, name), v1);
        }

        void setUniform(const char* name, float v1, float v2)
        {
            glUniform2f(glGetUniformLocation(shaderProgram, name), v1, v2);
        }

        void setUniform(const char* name, float v1, float v2, float v3)
        {
            glUniform3f(glGetUniformLocation(shaderProgram, name), v1, v2, v3);
        }

        void setUniform(const char* name, float v1, float v2, float v3, float v4)
        {
            glUniform4f(glGetUniformLocation(shaderProgram, name), v1, v2, v3, v4);
        }

        void setUniform(const char* name, int v1)
        {
            glUniform1i(glGetUniformLocation(shaderProgram, name), v1);
        }

        void setUniform(const char* name, int v1, int v2)
        {
            glUniform2i(glGetUniformLocation(shaderProgram, name), v1, v2);
        }

        void setUniform(const char* name, int v1, int v2, int v3)
        {
            glUniform3i(glGetUniformLocation(shaderProgram, name), v1, v2, v3);
        }

        void setUniform(const char* name, int v1, int v2, int v3, int v4)
        {
            glUniform4i(glGetUniformLocation(shaderProgram, name), v1, v2, v3, v4);
        }

        void setUniform(const char* name, glm::mat2& mat)
        {
            glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(mat));
        }

        void setUniform(const char* name, glm::mat3& mat)
        {
            glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(mat));
        }

        void setUniform(const char* name, glm::mat4& mat)
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(mat));
        }

        void setUniform(const char* name, glm::vec2& vec)
        {
            glUniform2fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(vec));
        }

        void setUniform(const char* name, glm::vec3& vec)
        {
            glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(vec));
        }

        void setUniform(const char* name, glm::vec4& vec)
        {
            //std::is_integral<glm::vec4>; // 检查模板类型是否是int
            glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(vec));
        }
    };
}

#endif // _SHADER_H_