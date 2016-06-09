#version 120

uniform vec3 ka;
uniform int selected;


void main()
{
	
	vec3 color = ka;
	if (selected == 1) {
		color += vec3(.2, .2, .2);
	}
	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
