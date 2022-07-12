#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_texCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
uniform sampler2D u_Tex;

void main()
{
	color = texture(u_Tex, v_texCoord);
};