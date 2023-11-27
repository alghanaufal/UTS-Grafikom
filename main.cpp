#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader/shader_s.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1700;
const unsigned int SCR_HEIGHT = 1600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "UTS Grafikom", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("4.2.texture.vs", "4.2.texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
        0.08f, 0.36f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kc 0
        0.02f, 0.35f, 0.0f, 1.0f, 0.1f, 0.0f, 0.0f, 0.0f,  // kd 1
        0.02f, 0.37f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // ke 2
        -0.01f, 0.35f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // kf 3
        -0.07f, 0.36f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kg 4
        -0.07f, 0.31f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kh 5
        -0.1f, 0.31f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // ki 6
        -0.16f, 0.32f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kj 7
        -0.15f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kk 8
        -0.14f, 0.24f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kl 9

        -0.22f, 0.27f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // km 10
        -0.22f, 0.22f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // kn 11
        -0.26f, 0.22f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // ko 12
        -0.23f, 0.18f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // kp 13
        -0.18f, 0.12f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kq 14
        -0.29f, 0.13f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kr 15
        -0.26f, 0.06f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // ks 16
        -0.3f, 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // kt 17
        -0.25f, 0.02f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // ku 18
        -0.15f, -0.01f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kv 19

        -0.17f, -0.03f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kw 20
        -0.26f, -0.03f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // kz 21
        -0.15f, -0.05f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // ka1 22
        -0.08f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // kb1 23
        -0.16f, -0.13f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kc1 24
        -0.17f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kd1 25
        -0.12f, -0.18f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // ke1 26
        -0.07f, -0.16f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kf1 27
        -0.02f, -0.13f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kg1 28
        -0.06f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // kh1 29

        -0.02f, -0.19f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // ki1 30
        -0.07f, -0.26f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // kj1 31
        -0.06f, -0.15f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // kk1 32
        -0.12f, -0.18f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // kl1 33
        -0.14f, -0.14f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // km1 34
        0.17f, -0.21f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kn1 35
        0.2f, -0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // ko1 36
        0.22f, -0.11f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kp1 37
        0.24f, -0.16f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kq1 38
        0.27f, -0.07f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // kr1 39

        0.26f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // ks1 40
        0.29f, -0.09f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // kt1 41
        0.29f, -0.04f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // ku1 42
        0.32f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f    // kv1 43
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2,
        1, 3, 5,
        2, 3, 4,
        2, 4, 5,
        4, 5, 6,
        4, 6, 7,
        6, 8, 7,
        5, 6, 9,
        6, 8, 9,

        8, 9, 10,
        7, 8, 10,
        9, 10, 11,
        10, 11, 12,
        9, 14, 13,
        9, 11, 13,
        11, 13, 12,
        13, 12, 15,
        14, 13, 15,
        14, 16, 15,

        16, 15, 17,
        18, 16, 17,
        14, 19, 16,
        19, 16, 18,
        18, 17, 21,
        20, 18, 21,
        19, 20, 18,
        19, 22, 20,
        22, 20, 21,
        22, 24, 21,

        23, 19, 22,
        24, 25, 21,
        23, 22, 24,
        23, 26, 24,
        28, 23, 27,
        27, 23, 26,
        26, 24, 25,
        27, 29, 26,
        26, 29, 25,

        30, 28, 27,
        32, 30, 28,
        31, 30, 29,
        33, 32, 30,
        33, 31, 30,
        34, 33, 32,
        35, 33, 31,
        36, 34, 33,
        36, 35, 33,

        37, 36, 34,
        38, 36, 35,
        40, 37, 36,
        40, 38, 36,
        41, 40, 38,
        39, 40, 37,
        41, 39, 40,
        42, 41, 39,
        43, 42, 41};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(2, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    float borderColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("image/moon.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // data = stbi_load("image/grafikom.jpg", &width, &height, &nrChannels, 0);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.039f, 0.243f, 0.245f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 300, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}