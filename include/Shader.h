#ifndef SHADER_H  
#define SHADER_H  

#include <string>  
#include <unordered_map>  
#include <glad/glad.h>  

class Shader  
{  
public:  
   Shader(const std::string& filepath);  
   ~Shader();  

   void Bind() const;  
   void Unbind() const;  

   void SetUniform3f(const std::string& name, float v0, float v1, float v2);  
   void SetUniform1i(const std::string& name, int value); // Add this declaration  

private:  
   struct ShaderProgramSource {  
       std::string VertexSource;  
       std::string FragmentSource;  
   };  

   unsigned int m_RendererID;  
   std::unordered_map<std::string, int> m_UniformLocationCache;  

   ShaderProgramSource ParseShader(const std::string& filepath);  
   unsigned int CompileShader(unsigned int type, const std::string& source);  
   unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);  
   int GetUniformLocation(const std::string& name);  
};  

#endif // SHADER_H
