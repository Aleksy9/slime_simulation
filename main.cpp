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

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Lower left triangle
	1, 2, 3 // Lower right triangle
};

float rectangleVertices[] =
{
	// Coords    // texCoords
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
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

	Shader combiningProgram("combining.vert","combining.frag");
	combiningProgram.Activate();
	glUniform1i(glGetUniformLocation(combiningProgram.ID, "screenTexture"), 0);
	
	Shader swapProgram("swap.vert", "swap.frag"); // ERROR HERE

	swapProgram.Activate();
	glUniform1i(glGetUniformLocation(swapProgram.ID, "screenTexture"), 0);
	
	// Prepare framebuffer rectangle VBO and VAO
	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	// Create Frame Buffer Object
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create Framebuffer Texture
	unsigned int swapTexture;
	glGenTextures(1, &swapTexture);
	glBindTexture(GL_TEXTURE_2D, swapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, swapTexture, 0);

	
	// Error checking framebuffer
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create Frame Buffer Object
	unsigned int storeFBO;
	glGenFramebuffers(1, &storeFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, storeFBO);

	// Create Framebuffer Texture
	unsigned int storeTexture;
	glGenTextures(1, &storeTexture);
	glBindTexture(GL_TEXTURE_2D, storeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, storeTexture, 0);

	
	// Error checking framebuffer
	auto fboStatus2 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus2 != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus2 << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

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
	int number_ants = 500;
	int size_array_ants = 2*number_ants;
	float ant_coord[size_array_ants];

	float r2 = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/400.0f));
	for (size_t i = 0; i < size_array_ants; i++)
	{
		//ant_coord[i] = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/800.0f));
		ant_coord[i] = 100.0f+ static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/600.0f));
	}

	int counter = 0;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		
		for (size_t i = 0; i < size_array_ants; i++)
		{
			float negative = static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/400.0f));
			
			if(negative>200.0f)
			{
				ant_coord[i] += static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/1.0f));
			}
			else
			{
				ant_coord[i] -= static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/1.0f));
			}
			
		}
		
		if(counter == 0)
		{
			// Render to storage FBO
			// Bind the custom framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, storeFBO);
			// Specify the color of the background
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and depth buffer
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Enable depth testing since it's disabled when drawing the framebuffer rectangle
			glEnable(GL_DEPTH_TEST);
			// Tell OpenGL which Shader Program we want to use
			shaderProgram.Activate();

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
			
			// Bind the default framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			counter += 1;
		}
		// ------------------------------------------------------------------------------------
		// Render to combining FBO using the ants locations and the texture from the storage FBO
		// Bind the custom framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth testing since it's disabled when drawing the framebuffer rectangle
		glEnable(GL_DEPTH_TEST);
		// Tell OpenGL which Shader Program we want to use
		combiningProgram.Activate();
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		
		glUniform1f(xID, 10.0f);
		glUniform1f(yID, r2);
		glUniform1fv(coordID,size_array_ants,ant_coord);
		glUniform1i(sizeID,size_array_ants);

		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
		glBindTexture(GL_TEXTURE_2D, storeTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glBindVertexArray(0);
		// Bind the default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ------------------------------------------------------------------------------------

		// Update storage FBO with combining FBO texture
		glBindFramebuffer(GL_FRAMEBUFFER, storeFBO);
		// Specify the color of the background
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth testing since it's disabled when drawing the framebuffer rectangle
		//glEnable(GL_DEPTH_TEST);

		swapProgram.Activate();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
		glBindTexture(GL_TEXTURE_2D, swapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ------------------------------------------------------------------------------------
		// Push combining FBO texture to main back buffer

		// Draw the framebuffer rectangle
		swapProgram.Activate();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
		glBindTexture(GL_TEXTURE_2D, swapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

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
	swapProgram.Delete();
	glDeleteFramebuffers(1, &FBO);
	/* swapshaderProgram.Delete();
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texture); */
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}