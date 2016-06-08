#version 120

uniform mat4 P;
uniform mat4 MV;

attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

varying vec4 pos;
varying vec4 norm;


void main()
{
	gl_Position = P * MV * aPos;
	pos = MV * aPos;
	norm = MV * vec4(aNor, 0);
}
