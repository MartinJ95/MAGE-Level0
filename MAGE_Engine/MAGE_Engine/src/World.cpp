#include "World.h"

World::World(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_viz(screenWidth, screenHeight, windowName),
	m_entities()
{

}

bool World::Initualize()
{
	if (!m_viz.initialise())
	{
		return false;
	}
	m_viz.generateShader("src\\default2DShader.vs", "src\\default2DShader.fs", "default2DShader");
	m_viz.generateTexture("resources\\mageIntro.png", "introTexture");

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices{0, 1, 2, 2, 1, 3};

	Vertex v1;
	v1.position = Vector3f(-0.5, -0.5, 0);
	v1.color = Vector3f(0, 0, 0);
	v1.normal = Vector3f(0, 0, 0);
	v1.texCoords = Vector2f(0, 0);

	Vertex v2;
	v2.position = Vector3f(0.5, -0.5, 0);
	v2.color = Vector3f(0, 0, 0);
	v2.normal = Vector3f(0, 0, 0);
	v2.texCoords = Vector2f(1, 0);

	Vertex v3;
	v3.position = Vector3f(-0.5, 0.5, 0);
	v3.color = Vector3f(0, 0, 0);
	v3.normal = Vector3f(0, 0, 0);
	v3.texCoords = Vector2f(0, 1);

	Vertex v4;
	v4.position = Vector3f(0.5, 0.5, 0);
	v4.color = Vector3f(0, 0, 0);
	v4.normal = Vector3f(0, 0, 0);
	v4.texCoords = Vector2f(1, 1);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	m_viz.generateMesh(vertices, indices, "default2DMesh");

	Entity *e = new Entity(true);
	e->addComponent<Transform>();
	e->addComponent<Mesh>();
	Component * transform = e->getComponent<Transform>();
	Transform *t = dynamic_cast<Transform*>(transform);
	t->m_position = Vector3f(m_viz.m_screenWidth / 2, m_viz.m_screenHeight / 2, 0);
	t->m_scale = Vector3f(1, 1, 1);
	t->m_rotation = Vector3f(0, 0, 0);

	Component * mesh = e->getComponent<Mesh>();
	Mesh *m = dynamic_cast<Mesh*>(mesh);
	m->m_meshName = "default2DMesh";
	m->m_shaderName = "default2DShader";
	m->m_textureName = "introTexture";

	m_entities.emplace_back(e);

	return true;
}

void World::Run()
{
	while (m_viz.isOpen())
	{
		m_viz.clear();

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Update(*this);
		}

		m_viz.display();

		glfwPollEvents();
	}
}

World::~World()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
}
