#version 120

uniform vec3 lightPos0;
uniform float lightInt0;
uniform vec3 lightPos1;
uniform float lightInt1;
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

	vec3 l0 = normalize(lightPos0 - pos.xyz);
	vec3 l1 = normalize(lightPos1 - pos.xyz);
	
	vec3 cd0 = kd * max(0, dot(l0, n));
	vec3 cd1 = kd * max(0, dot(l1, n));

	vec3 cam = normalize(-pos.xyz);
	
	vec3 cs0 = ks * pow(max(0, dot(normalize(l0 + cam), n)), s);
	vec3 cs1 = ks * pow(max(0, dot(normalize(l1 + cam), n)), s);

	color = lightInt0 * (ka + cd0 + cs0) + lightInt1 * (ka + cd1 + cs1);
	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
