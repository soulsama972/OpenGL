#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 t;
layout(location = 3) in float i;


uniform mat4 u_MVP;

out vec2 v_texCoord;
out float index;

void main()
{
	gl_Position = u_MVP * (position + vec4(t,0));
	v_texCoord = texCoord;
	index = i;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in float index;

uniform sampler2D u_Tex[2];

void main()
{
	color = texture(u_Tex[int(index)], v_texCoord);
};