#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Transform.h"

class Boid
{
private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float r;
	float maxforce;
	float maxspeed;
	int indice;
	Mesh _mesh;
	Transform _transform;
	std::vector<Boid> boids;
	bool col;
	
public:
	Boid(float x, float y, float z, int i);
	void SetBoids(std::vector<Boid> boidsList);
	void run(float time, std::vector<Boid> &boids);
	void runC( std::vector<Boid> &boids, float z);
	void applyForce(glm::vec3 force);
	void flock(std::vector<Boid> &boids);
	void update();
	glm::vec3 seek(glm::vec3 target);
	void draw(int i);
	void render();
	glm::mat4 GetModelMatrix();
	glm::vec3 separate(std::vector<Boid> &boids);
	glm::vec3 align(std::vector<Boid> &boids);
	glm::vec3 cohesion(std::vector<Boid> &boids);
	void limits(float z);
	//void limits(float x, float y, float z);
	glm::vec3 GetPosition();
	void SetCenter(glm::vec3 centerGoal);
	void SetRadius(float radius);
	bool GetDraw();
	void SetDraw(bool newdraw);
	bool IntersectedCircle(glm::vec3  beeHeadCenter, float beeHeadRadius);


	
};
