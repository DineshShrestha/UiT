varying vec2 texCoord;
uniform sampler2D tex1;

void main()
{
	texCoord = gl_MultiTexCoord0.xy;
    gl_FrontColor = gl_Color;
	vec4 pos = gl_Vertex;
	pos.y = (texture2D(tex1,texCoord)*250.0).x-250.0;
	pos.x *= 5.0;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
}