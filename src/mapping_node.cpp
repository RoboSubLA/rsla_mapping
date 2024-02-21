#include <chrono>
#include <functional>
#include <memory>
#include <string>

// #define VISUALIZER
#ifdef VISUALIZER
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
#include "./common/shader.hpp"
#endif

#include "./mapping.hpp"
#include "./mapping_node.hpp"
// #include "./process_monitor.cpp"

using namespace std::chrono_literals;

MappingNode::MappingNode()
    : Node("MappingNode")
    , count_(0)
{
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic_out", 10);
    // subscription_ = this->create_subscription<std_msgs::msg::String>(
    //     "topic", 10, std::bind(&mapping::topic_callback, this, std::placeholders::_1));
    timer_ = this->create_wall_timer(5000ms, std::bind(&MappingNode::timer_callback, this));
}

MappingNode::~MappingNode()
{
}

void MappingNode::timer_callback()
{
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}

void MappingNode::topic_callback(const std_msgs::msg::String& msg) const
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

#ifdef VISUALIZER
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1280, 720, "SDF MAP VISUALIZER", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the "
                        "2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1,
        1,
        0,
        -1,
        -1,
        0,
        1,
        -1,
        0,
        1,
        -1,
        0,
        1,
        1,
        0,
        -1,
        1,
        0,

    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // assumes you are running from workspace folder
    // if you get shader compile errors you probably need to change this
    std::string path = "./src/rsla_mapping/src/shaders/";

    std::string vshader = path + "vshader.glsl";
    std::string fshader = path + "fshader.glsl";

    // const char *vshader = "/home/silver1063/ros2_ws/src/lanturn_mapping/src/shaders/vshader.glsl";
    // const char *fshader = "/home/silver1063/ros2_ws/src/lanturn_mapping/src/shaders/fshader.glsl";

    GLuint programID = load_shaders(vshader.c_str(), fshader.c_str());

    GLuint timeUniformLocation = glGetUniformLocation(programID, "iTime");

    // Set the time uniform to the current time each frame.

    // hehehehehe
    while (true) {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there
        // nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = glfwGetTime();
        glUniform1f(timeUniformLocation, time);

        // Draw nothing, see you in tutorial 2 !
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            (void*)0 // array buffer offset
        );
        glUseProgram(programID);
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0)
            break;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

#endif

#ifndef VISUALIZER
    Mapping mapping;
    // process_mem_usage();
    // rclcpp::spin(std::make_shared<MappingNode>());
#endif

    rclcpp::shutdown();
    return 0;
}