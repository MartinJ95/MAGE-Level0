#pragma once
#include <unordered_map>
#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MeshGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>
#include <cctype>

#define PI 3.14159265

class Camera;
class World;

void frameBufferSizeCallback(GLFWwindow *window, int screenWidth, int screenHeight);

class Visualization
{
public:
	Visualization(const int screenWidth, const int screenHeight, const std::string &windowName);
	bool initialise();
	void generateShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &shaderName);
	bool isOpen() const;
	GLFWwindow* getWindow() const;
	void clear();
	void render2D(const std::string &meshName, const std::string &textureName, const std::string &shaderName, const glm::mat4 transformMatrix);
	void render3D(const std::string &meshName, const std::string &textureName, const std::string &shaderName, const glm::mat4 transformMatrix, Camera &camera, Vector3f &worldUp, World &world);
	void display();
	void generateTexture(const std::string &textureFilePath, const std::string &textureName);
	void generateFace(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, const Vector3f &minSize, const Vector3f &maxSize, const Vector2f &minTexcoord, const Vector2f &maxTexcoord, const Vector3f &normal, const int &offset);
	void generateMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::string &meshName);
	void generateSquareMesh(const int &minSize, const int &maxSize, const int &minTexCoord, const int &maxTexCoord, const std::string &meshName);
	void generateBoxMesh(const int &minSize, const int &maxSize, const int &minTexCoord, const int &maxTexCoord, const std::string &meshName);
	void generateSphereMesh(const Vector3f &center, const float &radius, const int &details, const std::string &meshName);
	void generateSphereVertices(std::vector<Vertex>& vertices, const Vector3f &center, const int & details, Vector3f &newPos, float &theta, float &theta1, float &cs, float &sn, float &cs1, float &sn1);
	void generateSphereColumn(std::vector<Vertex>& vertices, const Vector3f &center, const int & details, Vector3f &newPos, float &theta, float &theta1, float &cs, float &sn, float &cs1, float &sn1);
	void generateSphereIndices(std::vector<unsigned int> &indices, const int &details);
	void loadObject(const std::string &filePath, const std::string &fileName, const std::string &fileType = ".obj");
	void useShader(const std::string &shaderName);
	void setShaderTexture(const std::string &textureUniform, const std::string &textureName, const std::string &shaderName, const int textureIndex);
	void setShaderUniformFloat(const std::string &shaderName, const std::string &uniformName, const float value);
	void setShaderUniformInt(const std::string &shaderName, const std::string &uniformName, const int value);
	void setShaderUniformBool(const std::string &shaderName, const std::string &uniformName, const bool value);
	void setShaderUniformMatrix4f(const std::string &shaderName, const std::string &uniformName, const glm::mat4 &matrix);
	void setShaderUniformVector3f(const std::string &shaderName, const std::string &uniformName, const Vector3f &vector);
	~Visualization();
	int m_screenWidth, m_screenHeight;
private:
	GLuint compileShader(const std::string &shaderType, const std::string &shaderFileName);
	GLFWwindow* m_window;
	std::string m_windowName;
	std::unordered_map <std::string, MeshGL*> m_meshes;
	std::unordered_map <std::string, GLuint> m_textures;
	std::unordered_map <std::string, GLuint> m_shaderPrograms;
};

