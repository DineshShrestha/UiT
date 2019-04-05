#include "ParticleGen.hpp"
#include<iostream>

#include"glm\glm\matrix.hpp"

ParticleGenerators::ParticleGenerators()
{
	isShaderExist_ = false;
	privateInit();
	std::string lifeboat = "D:\\fluidNsimulation\\FluidMechanics\\fluidSimulation\\velocityNDensity.txt";

	f_ = std::make_shared<Datahandler>();
	dP_ = f_->loadData(lifeboat);
	matrix_ = glm::translate(glm::mat4(), glm::vec3(-15.0f, 0.0f, 0.0f));

	/*mode_ = mode;
	if (mode_ == 1)
	{
		//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 3.0f, 0.0f));
		
	}
	else if (mode_ == 0)
	{
		matrix_ = glm::translate(glm::mat4(), glm::vec3(-10.0f, 5.0f, -50.0f));
	}*/
/*	GLfloat colorsN[12][3] =		// Rainbow Of Colors
	{
		{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
		{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
		{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
	};
	memcpy(colors, colorsN, sizeof(colorsN));
	*/
}

ParticleGenerators::~ParticleGenerators()
{

}

void ParticleGenerators::privateInit() // All Setup For OpenGL Goes Here
{
	if (isShaderExist_) {
		return;
	}
	/*
	tex_2d = SOIL_load_OGL_texture
		(
			"D:\\fluidNsimulation\\FluidMechanics\\fluidSimulation\\IMAGES\\particle.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);*/

	/* check for an error during the load process */
	/*if (0 == tex_2d)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}


	for (int loop = 0; loop<MAX_PARTICLES; loop++)				// Initials All The Textures
	{
		particle[loop].active = true;								// Make All The Particles Active
		particle[loop].life = 1.0f;								// Give All The Particles Full Life
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
		particle[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particle[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particle[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg = -0.8f;								// Set Vertical Pull Downward
		particle[loop].zg = 0.0f;									// Set Pull On Z Axis To Zero
	}
	
	*/

}

void ParticleGenerators::privateRender()
{
	boatFloat();
	/*
	if (mode_ == 0)
	{
		explosion();
	}
	else if (mode_ == 1)
	{
		beam();
	}*/
}

void ParticleGenerators::boatFloat() {
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, tex_2d);			// Select Our Texture

	for (int loop = 0; loop < dP_.size(); loop++) {				// Loop Through All The Particles

		float x = dP_[loop].x;						// Grab Our Particle X Position
		float z = dP_[loop].y;						// Grab Our Particle Y Position
		float y = dP_[loop].z;					    // Particle Z Pos + Zoom
		float rho = dP_[loop].rho;

		float c_;
		float v_ = 1;
		float s_ = 1;
		c_ = v_*s_;
		float h_ = rho / 1000.0f * 360.0f;
		float x_ = c_*(1.0f - std::abs(((int)h_ / (int)60.0f) % (int)2.0f - 1.0f));
		float m_ = v_ - c_;
		float Rm;
		float Gm;
		float Bm;
		if (0.0f <= h_  && h_ < 60.0f) {
			Rm = c_;
			Gm = x_;
			Bm = 0;
		}
		if (60.0f <= h_  && h_ < 120.0f) {
			Rm = x_;
			Gm = c_;
			Bm = 0;
		}
		if (120 <= h_  && h_ < 180) {
			Rm = 0;
			Gm = c_;
			Bm = x_;
		}
		if (180.0f <= h_  && h_ < 240.0f) {
			Rm = 0;
			Gm = x_;
			Bm = c_;
		}
		if (240.0f <= h_  && h_ < 300.0f) {
			Rm = x_;
			Gm = 0;
			Bm = c_;
		}
		if (300.0f <= h_  && h_ < 360.0f) {
			Rm = c_;
			Gm = 0;
			Bm = x_;
		}
		glDisable(GL_CULL_FACE);
		glColor4f((Rm + m_) * 255.0f, (Gm + m_) * 255.0f, (Bm + m_) * 255.0f, 1.0f);

		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
		glVertex3f(x + 0.1f, y + 0.1f, z); // Top Right
		glVertex3f(x - 0.1f, y + 0.1f, z); // Top Left
		glVertex3f(x + 0.1f, y - 0.1f, z); // Bottom Right
		glVertex3f(x - 0.1f, y - 0.1f, z); // Bottom Left
		glEnd();						   // Done Building Triangle Strip

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

}
	/*
void ParticleGenerators::beam()
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PEECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);			// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, tex_2d);



	for (int loop = 0; loop < MAX_PARTICLES; loop++)		// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			float x = particle[loop].x;						// Grab Our Particle X Position
			float y = particle[loop].y;						// Grab Our Particle Y Position
			float z = particle[loop].z;						// Particle Z Pos + Zoom

															// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle[loop].x += particle[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
			particle[loop].y += particle[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
			particle[loop].z += particle[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

			particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life -= particle[loop].fade;		// Reduce Particles Life By 'Fade'


			if (particle[loop].life < 0.0f)					// If Particle Is Burned Out
			{
				particle[loop].life = 1.0f;					// Give It New Life
				particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
				particle[loop].x = 0.0f;						// Center On X Axis
				particle[loop].y = 0.0f;						// Center On Y Axis
				particle[loop].z = 0.0f;						// Center On Z Axis
				particle[loop].xi = 50 + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
				particle[loop].yi = 50 + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
				particle[loop].zi = float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
				particle[loop].r = colors[0][0];			// Select Red From Color Table
				particle[loop].g = colors[0][1];			// Select Green From Color Table
				particle[loop].b = colors[0][2];			// Select Blue From Color Table
			}

		}

	}
	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Disable Depth Testing
	glDisable(GL_BLEND);								// Enable Blending
	glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping
*/
}
void ParticleGenerators::explosion()
{/*
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);			// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, tex_2d);



	for (int loop = 0; loop < MAX_PARTICLES; loop++)		// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			float x = particle[loop].x;						// Grab Our Particle X Position
			float y = particle[loop].y;						// Grab Our Particle Y Position
			float z = particle[loop].z;						// Particle Z Pos + Zoom

															// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle[loop].x += particle[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
			particle[loop].y += particle[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
			particle[loop].z += particle[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

			particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life -= particle[loop].fade;		// Reduce Particles Life By 'Fade'



		}

	}
	glEnable(GL_DEPTH_TEST);							// Disable Depth Testing
	glDisable(GL_BLEND);								// Enable Blending
	glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping
*/}
void ParticleGenerators::privateUpdate()
{

}
void ParticleGenerators::moveRight()
{
	
	//matrix_ = glm::translate(matrix_, glm::vec3(0.5f, 0.0f, 0.0f));
}
void ParticleGenerators::moveLeft()
{
	//matrix_ = glm::translate(matrix_, glm::vec3(-0.5f, 0.0f, 0.0f));
}
void ParticleGenerators::moveForward()
{
	//matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
void ParticleGenerators::moveBackward()
{
	//matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 0.5f));
}