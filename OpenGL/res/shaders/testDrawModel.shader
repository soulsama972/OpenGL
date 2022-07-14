#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;
out vec2 t;

void main()
{
	gl_Position = u_MVP * position;
	t = tex;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
in vec2 t;

uniform sampler2D tex;

void main()
{
	color = texture(tex, t);
};


