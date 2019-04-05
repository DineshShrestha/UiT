uniform sampler2D tex;
uniform sampler2D tex2;
varying vec2 texCoord;			  
void main () 
{  
   gl_FragColor = texture2D(tex,texCoord.xy)*0.5 + texture2D(tex2,texCoord.xy)*0.5; 
}