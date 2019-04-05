uniform samplerCube skybox;
varying vec3 texCoord;

void main(void)
{

	// Reflective ray (when hitting the object)
	//vec3 ref = reflect(-view_vec, obj_normal);


	// Cube map lookup
	//gl_FragColor = textureCube(skybox, texCoord);
	//gl_FragColor.xyz = texCoord.xyz;
	 gl_FragColor = texture(skybox, texCoord);
	
	
}