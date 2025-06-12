#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 u_MVP;
out vec2 TexCoord;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec2 TexCoord;

out vec4 FragColor;
uniform vec3 uColor; // Color passed from CPU
uniform sampler2D uTexture; // Texture sampler

void main()
{
     FragColor = texture(uTexture, TexCoord) * vec4(uColor, 1.0);
     //FragColor = vec4(1, 1, 0, 1);
}
