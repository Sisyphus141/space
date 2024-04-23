#include "includes.h"

// Function declarations
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void drawArrow();

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Player position
float playerX = SCR_WIDTH / 2.0f;
float playerY = SCR_HEIGHT / 2.0f;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW Window", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawArrow();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  const float speed = 10.0f;
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    playerY += speed;
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    playerY -= speed;
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    playerX -= speed;
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    playerX += speed;
}
// Assuming playerX and playerY are the center of the screen
void drawArrow() {
  float arrowWidth = 20.0f;
  float arrowHeight = 30.0f;

  // Convert to OpenGL coordinates if necessary
  float glX = (playerX / SCR_WIDTH) * 2.0f - 1.0f;
  float glY = (playerY / SCR_HEIGHT) * 2.0f - 1.0f;

  // Adjust for height/width of the arrow
  glX -= (arrowWidth / SCR_WIDTH);
  glY += (arrowHeight / SCR_HEIGHT);

  glBegin(GL_TRIANGLES);
  glVertex2f(glX, glY + arrowHeight / 2);                  // top
  glVertex2f(glX - arrowWidth / 2, glY - arrowHeight / 2); // bottom left
  glVertex2f(glX + arrowWidth / 2, glY - arrowHeight / 2); // bottom right
  glEnd();
}
