#ifndef _SHADER_H_
#define _SHADER_H_
#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
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
        void setFilePath(const char* vertexPath, const char* fragmentPath)//��������ɫ��
        {
            // ���ļ�·���л�ȡ����/Ƭ����ɫ��
        // �洢�ļ�������
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            // ��֤ifstream��������׳��쳣��
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // ���ļ�
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // ��ȡ�ļ��Ļ������ݵ���������
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // �ر��ļ�������
                vShaderFile.close();
                fShaderFile.close();
                // ת����������string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                cout << "��ɫ���ļ���ȡʧ��\n";
                exit(-1);
            }
            // ת����C�ַ����Ա��������
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // ������ɫ��
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            // ������ɫ��
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            // ��ӡ�����������еĻ���
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "������ɫ���������\n" << infoLog << std::endl;
            }

            // ����Ƭ����ɫ��
            int success1;
            char infoLog1[512];
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            // ��ӡ�����������еĻ���
            glGetShaderiv(fragment, GL_FRAGMENT_SHADER, &success1);
            if (!success1)
            {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog1);
                std::cout << "Ƭ����ɫ���������\n" << infoLog1 << std::endl;
            }

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertex);
            glAttachShader(shaderProgram, fragment);
            glLinkProgram(shaderProgram);
            // ��ӡ���Ӵ�������еĻ���
            int success2;
            char infoLog2[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success2);
            if (!success2)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog2);
                std::cout << "�����������ʧ��\n" << infoLog2 << std::endl;
            }

            // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        GLuint getShaderID()//��ȡ��ɫ���������ID
        {
            return shaderProgram;
        }

        void use()//������ɫ���������
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
            //std::is_integral<glm::vec4>; // ���ģ�������Ƿ���int
            glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(vec));
        }
    };
}

#endif // _SHADER_H_