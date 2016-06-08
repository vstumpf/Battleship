#version 120

uniform vec3 lightPos0;
uniform float lightInt0;
uniform vec3 lightPos1;
uniform float lightInt1;
uniform float threshold;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec4 pos;
varying vec4 norm;

void main()
{
	vec3 n = normalize(norm.xyz);
	
	vec3 color;
	
	vec3 cam = normalize(-pos.xyz);
	if (dot(cam, n) < .3) {
		color = vec3(0., 0., 0.);
	} else {
		color = vec3(1., 1., 1.);
	}
	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
