#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Rendering/Renderer.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"

#include "Utils/Shape.h"
#include "GameObjects/Player.h"


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Sets the OpenGl version to 3 and sets the OpenGL profile to CORE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Sets the refresh rate to the monitor refresh rate
    // glfwSwapInterval(2); // 120Hz
    glfwSwapInterval(1); // 60Hz

    GLenum err;
    err = glewInit();

    if (err != GLEW_OK) {
        std::cout << "GLEW ERROR!" << std::endl;
        std::cout << glewGetErrorString(err) << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float triangle[] = {
           -0.95f, 0.0f, // 0
           -0.55f, 0.75f, // 1
           -0.55f, 0.0f, // 2
        };

        unsigned int triangleIndices[] = {
            0, 1, 2,
        };

        Shader shader;

        Renderer renderer;
        
        Shape sq(100, 100, SQUARE);
        Shape tr(100, 100, TRIANGLE);
        tr.setPos(-200, 200);

        float r = 0.0f;
        float increment = 0.05f;

        Player pl;
        pl.setPos(-200, -200);
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            shader.Bind();
            sq.setColor({ r, 0.8f, 0.8f, 1.0f }, shader);
            sq.Rotate((float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            sq.Draw(renderer, shader);
            tr.setColor({ r, 0.8f, 0.8f, 1.0f }, shader);
            // tr.Rotate(-(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            //tr.Translate(shader);
            tr.Draw(renderer, shader);

            pl.setColor({ 0.1f, 1.0f, 0.0f, 1.0f }, shader);
            pl.Inputs(window);
            pl.Draw(renderer, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
