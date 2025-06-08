#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, TexCoord) * vec4(vertexColor, 1.0);
}