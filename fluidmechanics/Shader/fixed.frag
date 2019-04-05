
uniform vec3 ObjColor;
varying float LightIntensity;

void main(void)
{   
	vec3 col = ObjColor * LightIntensity;
    gl_FragColor = vec4(col, 1.0);
}