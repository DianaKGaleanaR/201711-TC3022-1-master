#include "Boid.h"

//MANDAR A LLAMAR A LOS BOIDS 30 VECES POR SEGUNDO

Boid::Boid(float x, float y, float z, int i)
{
	acceleration = glm::vec3(0, 0, 0);
	float vel = (float)(rand() / (double)(RAND_MAX + 1));
	vel = vel * 2 - 1;
	velocity = glm::vec3(vel, vel, vel); //poner un valor fijo para las velocidades, checar el codigo
	r = 4.0;
	maxspeed = 0.2f;
	maxforce = 0.09f;
	position = glm::vec3(i, i, 15);
	indice = i;
	//std::cout << "constructor " << i << std::endl;
	col = false;
}

void Boid::SetBoids(std::vector<Boid> boidsList)
{
	boids = boidsList;
}

void Boid::run(float time, std::vector<Boid>& boids)
{
	flock(boids);
	update();
	limits(0);
}

void Boid::runC(std::vector<Boid> &boids, float z)
{
	//_transform.SetRotation(time, time, time);
	//_transform.SetScale(0.2, 0.2, 0.2);
	flock(boids);
	limits(z);
	update();

}

void Boid::applyForce(glm::vec3 force)
{
	// We could add mass here if we want A = F / M
	acceleration += force;
}

void Boid::flock(std::vector<Boid> &boids)
{
	glm::vec3 sep = separate(boids);
	glm::vec3 ali = align(boids);
	glm::vec3 coh = cohesion(boids);

	sep = sep*2.0f; //Pesos
	ali = ali * 0.5f; //Pesos
	coh = coh*0.5f; //Pesos

	//std::cout << "sep: " << sep.x << ", " << sep.y << ", " << sep.z << ", " << std::endl;
	//std::cout << "ali: " << ali.x << ", " << ali.y << ", " << ali.z << ", " << std::endl;
	//std::cout << "coh: " << coh.x << ", " << coh.y << ", " << coh.z << ", " << std::endl;
	applyForce(sep); //le suma la fuerza a la aceleracion
	applyForce(ali);
	applyForce(coh);
}

void Boid::update()
{
	velocity += acceleration;
	velocity = glm::normalize(velocity);
	velocity = velocity* maxforce;
	position += velocity;
	acceleration = acceleration * 0.0f;               
	_transform.SetPosition(position);
	//_transform.SetPosition(position.x, position.y, 0);
	//_transform.SetRotation(time, time, time);
	//std::cout << position.x << ", " << position.y << ", " << position.z << ", " << std::endl;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
glm::vec3 Boid::seek(glm::vec3 target)
{
	glm::vec3 desired = target - position;
	desired = glm::normalize(desired);
	desired = desired*maxspeed;

	glm::vec3 steer = desired - velocity;
	velocity = glm::normalize(velocity);
	velocity = velocity* maxforce;
	return steer;
}

//dibuja la abeja
void Boid::draw(int i)
{
	

	std::vector<glm::vec3> positions;
	// Cara trasera
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	// Cara derecha
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	// Cara frontal
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	// Cara izquierda
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// Cara arriba
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// Cara abajo
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));

	std::vector<glm::vec3> colors;
	// Cara trasera
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// Cara derecha
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Cara frontal
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Cara izquierda
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	// Cara arriba
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	// Cara abajo
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));
	colors.push_back(glm::vec3(0.3f, 0.5f, 0.7f));

	std::vector<glm::vec3> normals;
	// Cara trasera
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	// Cara derecha
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// Cara frontal
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Cara izquierda
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	// Cara arriba
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Cara abajo
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	std::vector<glm::vec2> texCoords;
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };

	_mesh.CreateMesh(24);
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh.SetTexCoordsAttribute(texCoords, GL_STATIC_DRAW, 3);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);

	_transform.SetPosition(i, i, i);
	_transform.SetScale(1, 1, 1);
}

//render lo mueve y lo actualiza, se va a mandar a llamar cada cuadro
void Boid::render()
{
	
	_mesh.Draw(GL_TRIANGLES);
	//std::cout << position.x << ", " << position.y << ", " << position.z << ", " << std::endl;
}


glm::mat4 Boid::GetModelMatrix()
{
	return _transform.GetModelMatrix();
}

// Separation
// Method checks for nearby boids and steers away
glm::vec3 Boid::separate(std::vector<Boid> &boids)
{
	float desiredseparation = 7.0f;
	glm::vec3 steer = glm::vec3(0, 0, 0);
	int count = 0;
	for (size_t i = 0; i < boids.size(); i++)
	{
	
		Boid &other = boids[i];
		if (other.indice != indice)
		{
			//glm::vec3 diff = position - other.position;
			float d = glm::distance(position, other.position);
			if (d < 0) d *= -1;
			//std::cout << d << std::endl;
			//float d = glm::length(diff); creo que length es para la magnitud
			if ((d < desiredseparation))
			{
				glm:: vec3 diff = position - other.position;
				diff = glm::normalize(diff);
				diff /= d;
				steer += diff;
				count++;
			}
		}
	}
	if (count > 0)
	{
		steer /= (float)count;
	}
	if (glm::length(steer) > 0)
	{
		steer = glm::normalize(steer);
		steer *= maxspeed;
		steer -= velocity;
		// creo que estas siguientes dos lineas remplazan a PVecotor.limit(PVector)
		steer = glm::normalize(steer);
		steer = steer * maxforce;
	}
	return steer;
}

// Alignment
// For every nearby boid in the system, calculate the average velocity
glm::vec3 Boid::align(std::vector<Boid> &boids)
{
	float neighboardist = 5.0f;
	glm::vec3 sum = glm::vec3(0, 0, 0);
	int count = 0;
	for (size_t i = 0; i < boids.size(); i++)
	{
		Boid &other = boids[i];
		if (other.indice != indice)
		{
			//glm::vec3 distance = position - other.position;
			float d = glm::distance(position, other.position);
			if ((d > 0) && (d < neighboardist))
			{
				sum += other.velocity;
				count++;
			}
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		sum = glm::normalize(sum);
		sum *= maxspeed;
		glm::vec3 steer = sum - velocity;
		// creo que estas siguientes dos lineas remplazan a PVecotor.limit(PVector)
		steer = glm::normalize(steer);
		steer = steer * maxforce;
		return steer;
	}
	else {
		return glm::vec3(0, 0, 0);
	}

}

// Cohesion
// For the average position (i.e. center) of all nearby boids, calculate steering vector towards that position
glm::vec3 Boid::cohesion(std::vector<Boid> &boids)
{
	float neighbordist = 5.0f; //creo que esto se puede cambiar a una variable global
	glm::vec3 sum = glm::vec3(0, 0, 0);
	int count = 0;
	for (size_t i = 0; i < boids.size(); i++)
	{
		Boid &other = boids[i];
		if (other.indice != indice)
		{
			//glm::vec3 distance = position - other.position;
			float d = glm::distance(position, other.position);
			if ((d > 0) && (d < neighbordist))
			{
				sum += other.position;
				count++;
			}
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		return seek(sum);
	}
	else {
		return glm::vec3(0, 0, 0);
	}
}

void Boid::limits(float z)
{
	if (position.x < -18) position.x = 34; //el panal va de (-18, 34) en x
	if (position.y <= 4) position.y += 51; //el panal va de (4, 52) en y
	if (position.z < z-5) position.z = z + 39; //le deje que no pudieran ir detras de la camara

	if (position.x > 35 + r) position.x = -17;
	if (position.y > 52 + r) position.y = 5;
	if (position.z > z + 40) position.z = z-4; //les deje 30 unidades hacia enfrente de la camara para moverse

}
/*
void Boid::limits(float x, float y, float z)
{
	/*if (position.x > 3 || position.x < -3 )
	{
		velocity.x = velocity.x * -1;
		acceleration.x = acceleration.x *-1;
		//position.x = position.x * -1;
	}
	if (position.y >3 || position.y < -3)
	{
		velocity.y = velocity.y * -1;
		acceleration.y = acceleration.y*-1;
		//position.y = position.y * -1;
	}
	if (position.z >3 || position.z < -3)
	{
		velocity.z = velocity.z * -1;
		acceleration.z = acceleration.z *-1;
		//position.z = position.z * -1;
	}*/
	/*if (position.x < -r) position.x = 5 + r;
	if (position.y < -r) position.y = 5 + r;
	if (position.z < -r/2) position.y = 5 + r;

	if (position.x > 5 + r) position.x = -r;
	if (position.y > 5 + r) position.y = -r;
	if (position.z > 0 + r) position.y = -r;


	if (position.x < -x) position.x = 5 + x;
	if (position.y < -y) position.y = 5 + y;
	if (position.z < -z / 2) position.y = 5 + z;

	if (position.x > 5 + x) position.x = -x;
	if (position.y > 5 + y) position.y = -y;
	if (position.z > 0 + z) position.y = -z;

}*/

glm::vec3 Boid::GetPosition()
{
	return position;
}

void Boid::SetCenter(glm::vec3 centerGoal)
{
	_transform.SetCenter(centerGoal);
}

void Boid::SetRadius(float radius)
{
	_transform.SetRadius(radius);
}

bool Boid::GetDraw()
{
	return col;
}

void Boid::SetDraw(bool newdraw)
{
	col = newdraw;
}

bool Boid::IntersectedCircle(glm::vec3 beeHeadCenter, float beeHeadRadius)
{
	return _transform.IntersectedCircle(beeHeadCenter, beeHeadRadius);
}