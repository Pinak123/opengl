#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;

out vec3 vertexColor;
    
void main()
    
{
        gl_Position = vec4(aPos, 1.0);
        vertexColor = aColor;
   
}

#shader fragment
#version 330 core
out vec4 FragColor;
uniform vec3 uColor; // Color passed from CPU

void main()
{
        FragColor = vec4(uColor, 1.0); // Set fragment color
}
