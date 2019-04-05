uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;
varying vec3 texCoord;
void main(void)
{
float waveWidth = 10.0;
float waveHeight = 8.0;
  vec3 texCoord = gl_MultiTexCoord0.xzy;
    vec4 v = gl_Vertex;
    v.y += sin(waveWidth * v.x + waveTime) * cos(waveWidth * v.z + waveTime) * waveHeight;
     gl_Position = gl_ModelViewProjectionMatrix * v;
        }