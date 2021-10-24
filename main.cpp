#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<cstdlib>

#include"shaderClass.hpp"
#include"VAO.hpp"
#include"VBO.hpp"
#include"EBO.hpp"



// Vertices coordinates
GLfloat vertices[] =
{
	-1.0f, -1.0f, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	-1.0f, 1.0f,  0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	1.0f, -1.0f,  0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	1.0f, 1.0f,  0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
};
/* { //               COORDINATES                  /     COLORS           //
	
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
}; */

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Lower left triangle
	1, 2, 3 // Lower right triangle
};



int main()
{
	// Initialize GLFW
	glfwInit();
	
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	int width = 800;
	int height = 800;
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");  // Error here
	/* Shader swapshaderProgram("swap.vert","swap.frag");
	swapshaderProgram.setInt("screenTexture", 0);

	// Create Framebuffer
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);  

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
		std::string worked("worked fine");
		std::cout << worked;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);  
	std::cout << "hello" << std::endl; */

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	// Gets ID of uniform called "scale"
	

	GLuint xID = glGetUniformLocation(shaderProgram.ID, "xlocation");
	GLuint yID = glGetUniformLocation(shaderProgram.ID, "ylocation");
	GLuint coordID = glGetUniformLocation(shaderProgram.ID, "coordinates");
	GLuint sizeID = glGetUniformLocation(shaderProgram.ID, "size_coord");
	
	

	// Generate seed for the random number generator
	srand(static_cast <unsigned> (0));

	// Create array of ants coordinates;
	int number_ants = 100;
	int size_array_ants = 2*number_ants;
	float ant_coord[size_array_ants];

	float r2 = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/400.0f));
	for (size_t i = 0; i < size_array_ants; i++)
	{
		ant_coord[i] = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/800.0f));
	}

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Bind the framebuffer
		/* glBindFramebuffer(GL_FRAMEBUFFER, FBO); */
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		glEnable(GL_DEPTH_TEST);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		
		
		for (size_t i = 0; i < size_array_ants; i++)
		{
			float negative = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/400.0f));
			
			if(negative>200.0f)
			{
				ant_coord[i] += static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/2.0f));
			}
			else
			{
				ant_coord[i] -= static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/2.0f));
			}
			
		}

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		
		glUniform1f(xID, 10.0f);
		glUniform1f(yID, r2);
		glUniform1fv(coordID,size_array_ants,ant_coord);
		glUniform1i(sizeID,size_array_ants);

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Unbind the VAO so the main framebuffer doesnt use it
		VAO1.Unbind();
		// Delete Shader Program for this Frambuffer
		// shaderProgram.Delete();
		// Unbind the FBO

		/* glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		
		// Start buffer swapping process
		
		swapshaderProgram.Activate();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);


		VAO1.Bind();
		glDisable(GL_DEPTH_TEST);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Delete swapShaderProgram
		//swapshaderProgram.Delete();
		glBindTexture(GL_TEXTURE_2D, 0);
		VAO1.Unbind(); */

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	/* swapshaderProgram.Delete();
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texture); */
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}