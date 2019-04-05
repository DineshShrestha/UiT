uniform sampler2D water;
 varying vec3 texCoord;
void main() {
    // Set the output color of our current pixel
    gl_FragColor = texture2D(water, texCoord);

	

	}
	
	