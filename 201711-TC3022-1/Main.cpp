
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <IL/il.h>
#include <chrono>
#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Time.h"
#include "Boid.h"

#include "Texture2D.h"//hace uso de devil, carga datos a tarjeta de video, hacer todo relacionado a texturas
#include "Terrain.h"
#include "Bee.h"
#include "Display.h"

#include <iostream>
#include <vector>

float secondsJugar;
std::vector<Boid> _boids;
ShaderProgram _boidShaderProgram;
Texture2D _boidTexture;


int beeCount = 0;



Camera _camera;

ShaderProgram _ShaderProgram;
ShaderProgram _beeShaderProgram;
ShaderProgram _displayShaderProgram;


Mesh _Mesh;
Mesh _BeeMesh;
Mesh _displayMesh;

Transform _terrainTransform;
Transform _terrainTransformWall;
Transform _terrainTransformWall2;
Transform _terrainTransformRoof;

Transform _beeTransform;
Transform _beeBodyTransform;
Transform _beeHeadTransform;
Transform _beeEyesTransform;
Transform _beeEyesTransform2;

Transform _displayPointsTransform;
Transform _displayTimeTransform;
Transform _displayPointsTens;
Transform _displayPointsDigits;
Transform _displayTimeTens;
Transform _displayTimeDigits;

Transform _displayCrown;
Transform _displayPortada;
Transform _displayTrono;
Transform _displayWin;
Transform _displayLost;

Transform _Goal;

Texture2D _terrainTexture;
Texture2D _terrainHeightmap;
Texture2D _beeTexture;
Texture2D _beeBodyTexture;
Texture2D _beeEyesTexture;
Texture2D _time;
Texture2D _points;

Texture2D _crown;
Texture2D _portada;
Texture2D _trono;
Texture2D _lost;
Texture2D _win;


Texture2D _0;
Texture2D _1;
Texture2D _2;
Texture2D _3;
Texture2D _5;
Texture2D _4;
Texture2D _6;
Texture2D _7;
Texture2D _8;
Texture2D _9;

Terrain _terrain;
Bee _bee;
Display _display;

bool jugar;
bool avanzar;
bool win;
bool lose;


void Initialize()
{
	jugar = false;
	//avanza = true;
	//BOIDS
	for (int i = 0; i <30; i++)
	{
		//Boid b = Boid(_camera.GetPosition().x, _camera.GetPosition().y - 3.0f, _camera.GetPosition().z + 7.2f, i);
		Boid b = Boid(0, 0, 0, i);
		_boids.push_back(b);
		//std::cout << "lista boids " << i << std::endl;
		//std::cout << "lista boids " << i << std::endl;
	}


	for (size_t i = 0; i < _boids.size(); i++)
	{
		_boids[i].draw(i);
		//_boids[i].SetPosition(centerGoal);
		_boids[i].SetCenter(_boids[i].GetPosition());
		_boids[i].SetRadius(5.0f);
	}


	_boidShaderProgram.CreateProgram();
	_boidShaderProgram.Activate();
	_boidShaderProgram.AttachShader("PhongShading.vert", GL_VERTEX_SHADER);
	_boidShaderProgram.AttachShader("PhongShading.frag", GL_FRAGMENT_SHADER);
	_boidShaderProgram.SetAttribute(0, "VertexPosition");
	_boidShaderProgram.SetAttribute(1, "VertexColor");
	_boidShaderProgram.SetAttribute(2, "VertexNormal");
	_boidShaderProgram.SetAttribute(3, "VertexTexCoord");
	_boidShaderProgram.LinkProgram();
	_boidShaderProgram.Deactivate();

	_boidTexture.LoadTexture("bee.jpg");

	_boidShaderProgram.Activate();
	//_shaderProgram.SetUniformf("iResolution", 400.0f, 400.0f);
	_boidShaderProgram.SetUniformf("LightPosition", 0.0f, 3.0f, 5.0f);
	_boidShaderProgram.SetUniformf("LightColor", 1.0f, 1.0f, 1.0f);
	_boidShaderProgram.SetUniformf("CameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, -_camera.GetPosition().z);
	_boidShaderProgram.SetUniformi("DiffuseTexture", 0);
	_boidShaderProgram.Deactivate();

	//FIN BOIDS

	Time::Init();

	_terrain.Init("hm.png");
	float width = _terrain.GetWidth();

	float depth = _terrain.GetDepth();

	float sizeTerrain = width*depth;




	//TERRENO MESH
	_Mesh.CreateMesh(sizeTerrain);
	_Mesh.SetPositionAttribute(_terrain.GetPositions(), GL_STATIC_DRAW, 0);
	_Mesh.SetTexCoordsAttribute(_terrain.GetTexCoords(), GL_STATIC_DRAW, 1);
	_Mesh.SetIndices(_terrain.GetIndices(), GL_STATIC_DRAW);

	_ShaderProgram.CreateProgram();
	_ShaderProgram.Activate();
	_ShaderProgram.AttachShader("HeightMap.vert", GL_VERTEX_SHADER);
	_ShaderProgram.AttachShader("HeightMap.frag", GL_FRAGMENT_SHADER);

	_ShaderProgram.SetAttribute(0, "VertexPosition");
	_ShaderProgram.SetAttribute(1, "VertexTexCoords");

	_ShaderProgram.LinkProgram();
	_ShaderProgram.Deactivate();

	_terrainTexture.LoadTexture("yellow-texture-26.jpg");
	_terrainHeightmap.LoadTexture("HMZFlatFill.tif");
	//_beeTexture.LoadTexture("bee.jpg");

	_ShaderProgram.Activate();
	_ShaderProgram.SetUniformi("DiffuseTexture", 0);
	_ShaderProgram.SetUniformi("HeightMap", 1);

	//_ShaderProgram.SetUniformi("BeeTexture", 2);

	_ShaderProgram.Deactivate();

	//BEE
	_bee.CreateBee();

	_BeeMesh.CreateMesh(24);
	_BeeMesh.SetPositionAttribute(_bee.GetPositions(), GL_STATIC_DRAW, 0);
	_BeeMesh.SetTexCoordsAttribute(_bee.GetTexCoords(), GL_STATIC_DRAW, 1);
	_BeeMesh.SetColorAttribute(_bee.GetColors(), GL_STATIC_DRAW, 2);

	_BeeMesh.SetIndices(_bee.GetIndices(), GL_STATIC_DRAW);

	_beeShaderProgram.CreateProgram();
	_beeShaderProgram.Activate();
	_beeShaderProgram.AttachShader("DefaultTexture.vert", GL_VERTEX_SHADER);
	_beeShaderProgram.AttachShader("DefaultTexture.frag", GL_FRAGMENT_SHADER);

	_beeShaderProgram.SetAttribute(0, "VertexPosition");
	_beeShaderProgram.SetAttribute(1, "VertexTexCoord");
	_beeShaderProgram.SetAttribute(2, "VertexColor");

	_beeShaderProgram.LinkProgram();
	_beeShaderProgram.Deactivate();

	_beeTexture.LoadTexture("bee.jpg");
	_beeBodyTexture.LoadTexture("beeBody.jpg");
	_beeEyesTexture.LoadTexture("beeEyes.jpg");


	_beeShaderProgram.Activate();
	_beeShaderProgram.SetUniformi("BeeTexture", 0);

	_beeShaderProgram.Deactivate();

	_display.Init();

	_displayMesh.CreateMesh(4);
	_displayMesh.SetPositionAttribute(_display.GetPositions(), GL_STATIC_DRAW, 0);
	_displayMesh.SetTexCoordsAttribute(_display.GetTexCoords(), GL_STATIC_DRAW, 1);
	_displayMesh.SetIndices(_display.GetIndices(), GL_STATIC_DRAW);

	_displayShaderProgram.CreateProgram();
	_displayShaderProgram.Activate();
	_displayShaderProgram.AttachShader("DefaultTexture2.vert", GL_VERTEX_SHADER);
	_displayShaderProgram.AttachShader("DefaultTexture2.frag", GL_FRAGMENT_SHADER);

	_displayShaderProgram.SetAttribute(0, "VertexPosition");
	_displayShaderProgram.SetAttribute(1, "VertexTexCoord");
	_displayShaderProgram.LinkProgram();
	_displayShaderProgram.Deactivate();

	_crown.LoadTexture("Crown.png");
	_portada.LoadTexture("Portada.png");
	_trono.LoadTexture("Trono.png");
	_lost.LoadTexture("LOSTScreen.png");
	_win.LoadTexture("WINScreen.png");

	_points.LoadTexture("super-big-cute-bumble-bee.png");
	_time.LoadTexture("Time-PNG-Image.png");
	_0.LoadTexture("0.jpg");
	_1.LoadTexture("1.jpg");
	_2.LoadTexture("2.jpg");
	_3.LoadTexture("3.jpg");
	_4.LoadTexture("4.jpg");
	_5.LoadTexture("5.jpg");
	_6.LoadTexture("6.jpg");
	_7.LoadTexture("7.jpg");
	_8.LoadTexture("8.jpg");
	_9.LoadTexture("9.jpg");

	_displayShaderProgram.Activate();
	_displayShaderProgram.SetUniformi("DisplayTexture", 0);

	_displayShaderProgram.Deactivate();

	_terrainTransform.SetPosition(-24.0f, -4.0f, 0.0f);
	_terrainTransform.SetScale(1.1f, 1.1f, 1.1f);
	_terrainTransformWall.SetPosition(-24.0f, width - 4.0, 0.0f);
	_terrainTransform.SetScale(1.1f, 1.1f, 1.1f);
	_terrainTransformWall.SetRotation(0.0f, 0.0f, -90.0f);
	_terrainTransformWall2.SetPosition(width - 24.0f, -4.0f, 0.0f);
	_terrainTransformWall2.SetScale(1.1f, 1.1f, 1.1f);
	_terrainTransformWall2.SetRotation(0.0f, 0.0f, -270.0f);
	_terrainTransformRoof.SetPosition(39.0f, width - 4.0f, 0.0f);
	_terrainTransformRoof.SetScale(1.1f, 1.1f, 1.1f);
	_terrainTransformRoof.SetRotation(0.0f, 0.0f, -180.0f);

	_camera.SetPosition(5.0f, 7.0f, -7.0f);
	//_camera.SetPosition(0.0f, 0.0f, -5.0f);
	_camera.SetRotation(-20.0f, 0.0f, 0.0f);

	_beeBodyTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 4.0f, _camera.GetPosition().z + 7.0f);
	_beeBodyTransform.SetScale(0.5f, 0.5f, 0.5f);

	_beeTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 5.0f, _camera.GetPosition().z + 5.8f);
	_beeTransform.SetScale(0.7f, 0.7f, 0.7f);

	_beeHeadTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 3.0f, _camera.GetPosition().z + 7.2f);
	_beeHeadTransform.SetScale(0.3f, 0.3f, 0.3f);

	//ObjectCollitions
	glm::vec3 center(_camera.GetPosition().x, _camera.GetPosition().y - 3.0f, _camera.GetPosition().z + 7.2f);
	_beeHeadTransform.SetCenter(center);
	_beeHeadTransform.SetRadius(5.0f);

	_beeEyesTransform.SetPosition(_camera.GetPosition().x - 0.2f, _camera.GetPosition().y - 2.7f, _camera.GetPosition().z + 7.2f);
	_beeEyesTransform.SetScale(0.1f, 0.1f, 0.1f);

	_beeEyesTransform2.SetPosition(_camera.GetPosition().x + 0.2f, _camera.GetPosition().y - 2.7f, _camera.GetPosition().z + 7.2f);
	_beeEyesTransform2.SetScale(0.1f, 0.1f, 0.1f);

	_displayPointsTransform.SetScale(0.3f, 0.3f, 0.3f);
	_displayPointsTransform.SetPosition(_camera.GetPosition().x + 2.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayTimeTransform.SetScale(0.3f, 0.3f, 0.3f);
	_displayTimeTransform.SetPosition(_camera.GetPosition().x - 2.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayPointsTens.SetScale(0.2f, 0.2f, 0.2f);
	_displayPointsTens.SetRotation(0.0f, 00.0f, 90.0f);
	_displayPointsTens.SetPosition(_camera.GetPosition().x + 1.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayPointsDigits.SetScale(0.2f, 0.2f, 0.2f);
	_displayPointsDigits.SetRotation(0.0f, 00.0f, 90.0f);
	_displayPointsDigits.SetPosition(_camera.GetPosition().x + 1.5f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayTimeTens.SetScale(0.2f, 0.2f, 0.2f);
	_displayTimeTens.SetRotation(0.0f, 00.0f, 90.0f);
	_displayTimeTens.SetPosition(_camera.GetPosition().x - 1.5f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayTimeDigits.SetScale(0.2f, 0.2f, 0.2f);
	_displayTimeDigits.SetRotation(0.0f, 00.0f, 90.0f);
	_displayTimeDigits.SetPosition(_camera.GetPosition().x - 1.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);

	_displayCrown.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.3f, _camera.GetPosition().z + 7.2f);
	_displayPortada.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
	_displayPortada.SetRotation(-20.0f, 0.0f, 0.0f);
	_displayPortada.SetScale(1.15f, 1.15f, 1.15f);

	_displayWin.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
	_displayWin.SetRotation(-20.0f, 0.0f, 0.0f);
	_displayWin.SetScale(1.15f, 1.15f, 1.15f);

	_displayLost.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
	_displayLost.SetRotation(-20.0f, 0.0f, 0.0f);
	_displayLost.SetScale(1.15f, 1.15f, 1.15f);

}

void Idle()
{
	glutPostRedisplay();
}

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (jugar == false && win == false && lose== false)
	{
		_displayShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		_portada.Bind();

		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPortada.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);
		_portada.Unbind();
		_displayShaderProgram.Deactivate();
	}
	
	if (jugar == false && win == true)
	{
		_displayShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		_win.Bind();
		_displayWin.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayWin.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);
		_win.Unbind();
		_displayShaderProgram.Deactivate();
	}

	if (jugar == false && lose == true)
	{
		//std::cout << "pierdeeeee" << std::endl;
		_displayShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		_lost.Bind();
		_displayLost.SetPosition (_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayLost.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);
		_lost.Unbind();
		_displayShaderProgram.Deactivate();
	}
	

	if (jugar == true)
	{
		
		// Siempre es recomendable borrar la información anterior del framebuffer.
		// En este caso estamos borrando la información de color,
		// y la información de profundidad.

		//glActiveTexture(GL_TEXTURE0);//DEFINICION DEL NUMERO PARA EL UNIFORM al final de GL_TEXTURE#
		Time::Tick();
		_boidShaderProgram.Activate();
		_boidTexture.Bind();
		glActiveTexture(GL_TEXTURE0);

		int secondsBoids = Time::GetDeltaTime().count() + Time::GetElapsedTime().count();
		//std::cout << secondsBoids<< std::endl;

		//actualiza 
		_beeHeadTransform.SetCenter(_beeHeadTransform.GetPosition());

		for (size_t i = 0; i < _boids.size(); i++)
		{
			_boids[i].SetCenter(_boids[i].GetPosition());
			//_boids[i].SetRadius(3.0f);
		}

		for (size_t i = 0; i < _boids.size(); i++)
		{
			if (_boids[i].GetDraw() == false)
			{
				_boids[i].SetDraw(_boids[i].IntersectedCircle(_beeHeadTransform.GetCenter(), _beeHeadTransform.GetRadius()));
				if (_boids[i].GetDraw() == true)
				{
					printf("Bee Count: %d", beeCount);
					beeCount += 1;
				}
			}
		}

		//_Boidstexture.Bind();

		for (size_t i = 0; i < _boids.size(); i++)
		{
			_boids[i].runC(_boids, _camera.GetPosition().z);
			//_boids[i].run(0.5f, _boids);
			_boidShaderProgram.SetUniformMatrix("ModelMatrix", _boids[i].GetModelMatrix());
			_boidShaderProgram.SetUniformMatrix("NormalMatrix", glm::mat3(glm::transpose(glm::inverse(_boids[i].GetModelMatrix()))));
			_boidShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _boids[i].GetModelMatrix());
			//_boids[i].render();
			if (_boids[i].GetDraw() == false)
			{
				_boids[i].render();
			}

		}

		_boidTexture.Unbind();

		_boidShaderProgram.Deactivate();



		/*_terrainTransform.MoveForward(-0.002f,true);
		_terrainTransformWall.MoveForward(-0.002f, true);
		_terrainTransformWall2.MoveForward(-0.002f, true);
		_terrainTransformRoof.MoveForward(-0.002f, true);*/

		_camera.MoveForward(0.07f, true);
		_beeTransform.MoveForward(0.07f, true);
		_beeBodyTransform.MoveForward(0.07f, true);
		_beeHeadTransform.MoveForward(0.07f, true);
		_beeEyesTransform.MoveForward(0.07f, true);
		_beeEyesTransform2.MoveForward(0.07f, true);

		_displayPointsTransform.MoveForward(0.07f, true);
		_displayTimeTransform.MoveForward(0.07f, true);
		_displayPointsTens.MoveForward(0.07f, true);
		_displayPointsDigits.MoveForward(0.07f, true);
		_displayTimeTens.MoveForward(0.07f, true);
		_displayTimeDigits.MoveForward(0.07f, true);

		_displayCrown.MoveForward(0.07f, true);

		_ShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		_terrainTexture.Bind();

		glActiveTexture(GL_TEXTURE1);
		_terrainHeightmap.Bind();

		float universalWidth = _terrain.GetWidth();
		float universalDepth = _terrain.GetDepth();
		float universalDepthMod = 0.0f;
		//float rango = 0.0f;

		for (int i = 0; i < 6; i++)
		{
			_ShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_terrainTransform.GetModelMatrix());
			_Mesh.Draw(GL_TRIANGLES);

			_ShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_terrainTransformWall.GetModelMatrix());
			_Mesh.Draw(GL_TRIANGLES);

			_ShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_terrainTransformWall2.GetModelMatrix());
			_Mesh.Draw(GL_TRIANGLES);

			_ShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_terrainTransformRoof.GetModelMatrix());
			_Mesh.Draw(GL_TRIANGLES);

			_terrainTransform.SetPosition(-24.0f, -4.0f, 0.0f + universalDepthMod);
			_terrainTransformWall.SetPosition(-24.0f, universalWidth - 4.0, 0.0f + universalDepthMod);
			_terrainTransformWall2.SetPosition(universalWidth - 24.0f, -4.0f, 0.0f + universalDepthMod);
			_terrainTransformRoof.SetPosition(39.0f, universalWidth - 4.0f, 0.0f + universalDepthMod);

			universalDepthMod += universalDepth;
		}

		glActiveTexture(GL_TEXTURE1);
		_terrainHeightmap.Unbind();

		glActiveTexture(GL_TEXTURE0);
		_terrainTexture.Unbind();
		_ShaderProgram.Deactivate();

		_beeShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		_beeTexture.Bind();

		//_ShaderProgram.SetUniformf("time", time);
		_beeShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_beeTransform.GetModelMatrix());
		_BeeMesh.Draw(GL_TRIANGLES);

		_beeBodyTexture.Bind();
		//_beeTransform.SetPosition(1.0f,1.0f,1.0f);
		//_beeTransform.SetScale();
		_beeShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_beeBodyTransform.GetModelMatrix());
		_BeeMesh.Draw(GL_TRIANGLES);

		_beeShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_beeHeadTransform.GetModelMatrix());
		_BeeMesh.Draw(GL_TRIANGLES);

		_beeBodyTexture.Unbind();

		_beeEyesTexture.Bind();

		_beeShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_beeEyesTransform.GetModelMatrix());
		_BeeMesh.Draw(GL_TRIANGLES);

		_beeShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_beeEyesTransform2.GetModelMatrix());
		_BeeMesh.Draw(GL_TRIANGLES);

		_beeEyesTexture.Unbind();

		glActiveTexture(GL_TEXTURE0);

		_beeTexture.Unbind();

		_beeShaderProgram.Deactivate();

		//DISPLAY
		_displayShaderProgram.Activate();
		glActiveTexture(GL_TEXTURE0);
		/*_crown.Bind();
		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayCrown.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);
		_crown.Unbind();*/

		_points.Bind();

		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTransform.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);


		_points.Unbind();

		_time.Bind();

		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTransform.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);

		_time.Unbind();

		_trono.Bind();
		_displayTrono.SetPosition(7.0f, 27.0f, universalDepthMod);
		_displayTrono.SetScale(30.0f, 30.0f, 30.0f);
		_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTrono.GetModelMatrix());
		_displayMesh.Draw(GL_TRIANGLES);
		_trono.Unbind();

		//TIME CALCULATIONS
		float seconds = Time::GetDeltaTime().count() + Time::GetElapsedTime().count() - secondsJugar;
		int millares = seconds / 1000;
		int centenas = (seconds - (millares * 1000)) / 100;
		int decenas = (seconds - (millares * 1000 + centenas * 100)) / 10;
		int unidades = seconds - (millares * 1000 + centenas * 100 + decenas * 10);

		//BEE COUNT CALCULATIONS
		int millaresBee = beeCount / 1000;
		int centenasBee = (beeCount - (millaresBee * 1000)) / 100;
		int decenasBee = (beeCount - (millaresBee * 1000 + centenasBee * 100)) / 10;
		int unidadesBee = beeCount - (millaresBee * 1000 + centenasBee * 100 + decenasBee * 10);

		//BEEEE
		//digitos
		if (unidadesBee == 0)
		{
			_0.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_0.Unbind();
		}
		if (unidadesBee == 1)
		{
			_1.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_1.Unbind();
		}
		if (unidadesBee == 2)
		{
			_2.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_2.Unbind();
		}
		if (unidadesBee == 3)
		{
			_3.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_3.Unbind();
		}
		if (unidadesBee == 4)
		{
			_4.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_4.Unbind();
		}
		if (unidadesBee == 5)
		{
			_5.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_5.Unbind();
		}
		if (unidadesBee == 6)
		{
			_6.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_6.Unbind();
		}
		if (unidadesBee == 7)
		{
			_7.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_7.Unbind();
		}
		if (unidadesBee == 8)
		{
			_8.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_8.Unbind();
		}
		if (unidadesBee == 9)
		{
			_9.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_9.Unbind();
		}
		//decenas
		if (decenasBee == 0)
		{
			_0.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_0.Unbind();
		}
		if (decenasBee == 1)
		{
			_1.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_1.Unbind();
		}
		if (decenasBee == 2)
		{
			_2.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_2.Unbind();
		}
		if (decenasBee == 3)
		{
			_3.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_3.Unbind();
		}
		if (decenasBee == 4)
		{
			_4.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_4.Unbind();
		}
		if (decenasBee == 5)
		{
			_5.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_5.Unbind();
		}
		if (decenasBee == 6)
		{
			_6.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_6.Unbind();
		}
		if (decenasBee == 7)
		{
			_7.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_7.Unbind();
		}
		if (decenasBee == 8)
		{
			_8.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_8.Unbind();
		}
		if (decenasBee == 9)
		{

			_9.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayPointsTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_9.Unbind();
		}


		//printf("%d", decenas); TIIIIIMEEEE
		if (decenas == 0)
		{
			_5.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_5.Unbind();
		}
		if (decenas == 1)
		{
			_4.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_4.Unbind();
		}
		if (decenas == 2)
		{
			_3.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_3.Unbind();
		}
		if (decenas == 3)
		{
			_2.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_2.Unbind();
		}
		if (decenas == 4)
		{
			_1.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_1.Unbind();
		}
		if (decenas == 5)
		{
			_0.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeTens.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_0.Unbind();
		}

		//digitos
		if (unidades == 0)
		{
			_9.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_9.Unbind();
		}
		if (unidades == 1)
		{
			_8.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_8.Unbind();
		}
		if (unidades == 2)
		{
			_7.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_7.Unbind();
		}
		if (unidades == 3)
		{
			_6.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_6.Unbind();
		}
		if (unidades == 4)
		{
			_5.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_5.Unbind();
		}
		if (unidades == 5)
		{
			_4.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_4.Unbind();
		}
		if (unidades == 6)
		{
			_3.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_3.Unbind();
		}
		if (unidades == 7)
		{
			_2.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_2.Unbind();
		}
		if (unidades == 8)
		{
			_1.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_1.Unbind();
		}
		if (unidades == 9)
		{
			_0.Bind();
			_displayShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_displayTimeDigits.GetModelMatrix());
			_displayMesh.Draw(GL_TRIANGLES);
			_0.Unbind();
		}

		//std::cout << seconds << std::endl;
		if (_beeHeadTransform.GetPosition().z >= 340 || seconds >= 60)
		{
			jugar = false;
			if (_beeHeadTransform.GetPosition().z >= 340) win = true;
			if (seconds >= 60 && _beeHeadTransform.GetPosition().z <= 340) lose = true;
		}

		_displayShaderProgram.Deactivate();
		
	}

	glutSwapBuffers();
}


//nueva funcion para ingreso en freeglut 
//clase input, necesitas saber cuando se dejó de presionar, generar en gameloop sobre todas las veces que es llamada
//funcion para teclas especiales
bool* keyStates = new bool[256];
bool* keySpecialKeys = new bool[246];
void Keyboard(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	//&& keyStates[key] == true
	if (keyStates['w'] == true) {
		if (_beeHeadTransform.GetPosition().y <= 52 && _beeHeadTransform.GetPosition().y >= 3)
		{
			//keyStates[key] = true;
			_camera.MoveUp(1.0f, true);
			_beeTransform.MoveUp(1.0f, true);
			_beeBodyTransform.MoveUp(1.0f, true);
			_beeHeadTransform.MoveUp(1.0f, true);
			_beeEyesTransform.MoveUp(1.0f, true);
			_beeEyesTransform2.MoveUp(1.0f, true);

			_displayPointsTransform.MoveUp(1.0f, true);
			_displayTimeTransform.MoveUp(1.0f, true);
			_displayPointsTens.MoveUp(1.0f, true);
			_displayPointsDigits.MoveUp(1.0f, true);
			_displayTimeTens.MoveUp(1.0f, true);
			_displayTimeDigits.MoveUp(1.0f, true);
			_displayCrown.MoveUp(1.0f, true);
			/*
			_terrainTransform.MoveUp(-1.0f, true);
			_terrainTransformWall.MoveUp(-1.0f, true);
			_terrainTransformWall2.MoveUp(-1.0f, true);
			_terrainTransformRoof.MoveUp(-1.0f, true);*/
		}
	}
	if (keyStates['s'] == true) {
		if (_beeHeadTransform.GetPosition().y <= 53 && _beeHeadTransform.GetPosition().y >= 4)
		{
			//keyStates[key] = true;
			_camera.MoveUp(-1.0f, true);
			_beeTransform.MoveUp(-1.0f, true);
			_beeBodyTransform.MoveUp(-1.0f, true);
			_beeHeadTransform.MoveUp(-1.0f, true);
			_beeEyesTransform.MoveUp(-1.0f, true);
			_beeEyesTransform2.MoveUp(-1.0f, true);

			_displayPointsTransform.MoveUp(-1.0f, true);;
			_displayTimeTransform.MoveUp(-1.0f, true);;
			_displayPointsTens.MoveUp(-1.0f, true);;
			_displayPointsDigits.MoveUp(-1.0f, true);;
			_displayTimeTens.MoveUp(-1.0f, true);;
			_displayTimeDigits.MoveUp(-1.0f, true);;
			_displayCrown.MoveUp(-1.0f, true);
			/*
			_terrainTransform.MoveUp(1.0f, true);
			_terrainTransformWall.MoveUp(1.0f, true);
			_terrainTransformWall2.MoveUp(1.0f, true);
			_terrainTransformRoof.MoveUp(1.0f, true);*/
		}
	}
	/*if (keyStates['d'] == true) {
	//keyStates[key] = true;
	_terrainTransform.Rotate(0.0f, 1.0f, 0.0f, true);
	_terrainTransformWall.Rotate(0.0f, 1.0f, 0.0f, true);
	_terrainTransformWall2.Rotate(0.0f, 1.0f, 0.0f, true);
	}
	if (keyStates['a'] == true) {
	//keyStates[key] = true;
	_terrainTransform.Rotate(0.0f, -1.0f, 0.0f, true);
	_terrainTransformWall.Rotate(0.0f, -1.0f, 0.0f, true);
	_terrainTransformWall2.Rotate(0.0f, -1.0f, 0.0f, true);
	}*/

	if (keyStates['p'] == true)
	{
		glm::vec3 positionbee = _beeHeadTransform.GetPosition();
		//std::cout << positionbee.x << ", " << positionbee.y << ", " << positionbee.z << ", " << std::endl;
		jugar = true;
		secondsJugar = Time::GetDeltaTime().count() + Time::GetElapsedTime().count();

		if (win == true || lose == true)
		{
			_camera.SetPosition(5.0f, 7.0f, -7.0f);
			_beeBodyTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 4.0f, _camera.GetPosition().z + 7.0f);
			_beeTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 5.0f, _camera.GetPosition().z + 5.8f);
			_beeHeadTransform.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 3.0f, _camera.GetPosition().z + 7.2f);
			_beeEyesTransform.SetPosition(_camera.GetPosition().x - 0.2f, _camera.GetPosition().y - 2.7f, _camera.GetPosition().z + 7.2f);
			_beeEyesTransform2.SetPosition(_camera.GetPosition().x + 0.2f, _camera.GetPosition().y - 2.7f, _camera.GetPosition().z + 7.2f);
			_displayPointsTransform.SetPosition(_camera.GetPosition().x + 2.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayTimeTransform.SetPosition(_camera.GetPosition().x - 2.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayPointsTens.SetPosition(_camera.GetPosition().x + 1.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayPointsDigits.SetPosition(_camera.GetPosition().x + 1.5f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayTimeTens.SetPosition(_camera.GetPosition().x - 1.5f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayTimeDigits.SetPosition(_camera.GetPosition().x - 1.0f, _camera.GetPosition().y + 0.5f, _camera.GetPosition().z + 5.0f);
			_displayCrown.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.3f, _camera.GetPosition().z + 7.2f);
			_displayPortada.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
			_displayWin.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
			_displayLost.SetPosition(_camera.GetPosition().x, _camera.GetPosition().y - 1.1f, _camera.GetPosition().z + 3.0f);
			beeCount = 0;
			win = false;
			lose = false;
		}

	}
}


void UnKeyboard(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

//funcion para teclas especiales
void SpecialKeys(int key, int x, int y)
{
	keySpecialKeys[key] = true;
	if (keySpecialKeys[GLUT_KEY_UP] == true)//UP
	{
		if (_beeHeadTransform.GetPosition().z >= 1 && _beeHeadTransform.GetPosition().z <= 1800)
		{
			_camera.MoveForward(0.5f, true);
			_beeTransform.MoveForward(0.5f, true);
			_beeBodyTransform.MoveForward(0.5f, true);
			_beeHeadTransform.MoveForward(0.5f, true);
			_beeEyesTransform.MoveForward(0.5f, true);
			_beeEyesTransform2.MoveForward(0.5f, true);

			_displayPointsTransform.MoveForward(0.5f, true);
			_displayTimeTransform.MoveForward(0.5f, true);
			_displayPointsTens.MoveForward(0.5f, true);
			_displayPointsDigits.MoveForward(0.5f, true);
			_displayTimeTens.MoveForward(0.5f, true);
			_displayTimeDigits.MoveForward(0.5f, true);
			_displayCrown.MoveForward(0.5f, true);
			//keySpecialKeys[key] = true;
			/*_terrainTransform.MoveForward(-0.5f, true);
			_terrainTransformWall.MoveForward(-0.5f, true);
			_terrainTransformWall2.MoveForward(-0.5f, true);
			_terrainTransformRoof.MoveForward(-0.5f, true);*/
		}
	}
	if (keySpecialKeys[GLUT_KEY_DOWN] == true)//DOWN
	{
		if (_beeHeadTransform.GetPosition().z >= 1 && _beeHeadTransform.GetPosition().z <= 1800)
		{
			//keySpecialKeys[key] = true;
			/*_terrainTransform.MoveForward(0.5f, true);
			_terrainTransformWall.MoveForward(0.5f, true);
			_terrainTransformWall2.MoveForward(0.5f, true);
			_terrainTransformRoof.MoveForward(0.5f, true);*/

			_camera.MoveForward(-1.2f, true);
			_beeTransform.MoveForward(-1.2f, true);
			_beeBodyTransform.MoveForward(-1.2f, true);
			_beeHeadTransform.MoveForward(-1.2f, true);
			_beeEyesTransform.MoveForward(-1.2f, true);
			_beeEyesTransform2.MoveForward(-1.2f, true);

			_displayPointsTransform.MoveForward(-1.2f, true);
			_displayTimeTransform.MoveForward(-1.2f, true);
			_displayPointsTens.MoveForward(-1.2f, true);
			_displayPointsDigits.MoveForward(-1.2f, true);
			_displayTimeTens.MoveForward(-1.2f, true);
			_displayTimeDigits.MoveForward(-1.2f, true);
			_displayCrown.MoveForward(-1.2f, true);
		}
	}
	if (keySpecialKeys[GLUT_KEY_RIGHT] == true)//RIGHT
	{
		if (_beeHeadTransform.GetPosition().x <= 35 && _beeHeadTransform.GetPosition().x >= -20)
		{
			//keySpecialKeys[key] = true;
			_camera.MoveRight(0.5f, true);
			_beeTransform.MoveRight(0.5f, true);
			_beeBodyTransform.MoveRight(0.5f, true);
			_beeHeadTransform.MoveRight(0.5f, true);
			_beeEyesTransform.MoveRight(0.5f, true);
			_beeEyesTransform2.MoveRight(0.5f, true);

			_displayPointsTransform.MoveRight(0.5f, true);
			_displayTimeTransform.MoveRight(0.5f, true);
			_displayPointsTens.MoveRight(0.5f, true);
			_displayPointsDigits.MoveRight(0.5f, true);
			_displayTimeTens.MoveRight(0.5f, true);
			_displayTimeDigits.MoveRight(0.5f, true);
			_displayCrown.MoveRight(0.5f, true);

			/*_terrainTransform.MoveRight(-0.5f, true);
			_terrainTransformWall.MoveRight(-0.5f, true);
			_terrainTransformWall2.MoveRight(-0.5f, true);
			_terrainTransformRoof.MoveRight(-0.5f, true);*/
		}
	}
	if (keySpecialKeys[GLUT_KEY_LEFT] == true)//LEFT
	{
		if (_beeHeadTransform.GetPosition().x <= 36 && _beeHeadTransform.GetPosition().x >= -19)
		{
			_camera.MoveRight(-0.5f, true);
			_beeTransform.MoveRight(-0.5f, true);
			_beeBodyTransform.MoveRight(-0.5f, true);
			_beeHeadTransform.MoveRight(-0.5f, true);
			_beeEyesTransform.MoveRight(-0.5f, true);
			_beeEyesTransform2.MoveRight(-0.5f, true);

			_displayPointsTransform.MoveRight(-0.5f, true);
			_displayTimeTransform.MoveRight(-0.5f, true);
			_displayPointsTens.MoveRight(-0.5f, true);
			_displayPointsDigits.MoveRight(-0.5f, true);
			_displayTimeTens.MoveRight(-0.5f, true);
			_displayTimeDigits.MoveRight(-0.5f, true);
			_displayCrown.MoveRight(-0.5f, true);
			/*//keySpecialKeys[key] = true;
			_terrainTransform.MoveRight(0.5f, true);
			_terrainTransformWall.MoveRight(0.5f, true);
			_terrainTransformWall2.MoveRight(0.5f, true);
			_terrainTransformRoof.MoveRight(0.5f, true);*/
		}
	}
}

void UnSpecialKeys(int key, int x, int y)
{
	keySpecialKeys[key] = false;
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	_camera.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);
}

int main(int argc, char* argv[])
{
	// Inicialización de Freeglut.
	// Freeglut se encarga de crear una ventana
	// En donde vamos a poder dibujar
	glutInit(&argc, argv);
	// Freeglut es el encargado de solicitar un contexto
	// de OpenGL. El contexto se refiere a las capacidades
	// que va a tener nuestra aplicación gráfica.
	glutInitContextVersion(4, 4);
	// Tenemos que informar que queremos trabajar únicamente con
	// el pipeline programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la venta.
	// Un evento que nos interesa es cuando alguien cierra la venta.
	// En este caso simplemente dejamos de renderear y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando
	// un buffer true color RGBA, un buffer de profundidad y un segundo buffer
	// para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	// Le damos un nombre a la ventana y la creamos.
	glutCreateWindow("Terrain");
	// Asociamos una funcion de render. Esta función se
	// mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	glutIdleFunc(Idle);

	//glutIgnoreKeyRepeat(GL_TRUE);

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(UnKeyboard);

	glutSpecialFunc(SpecialKeys);
	glutSpecialUpFunc(UnSpecialKeys);

	glutReshapeFunc(ReshapeWindow);



	// Inicializar GLEW. Esta librería se encarga
	// de obtener el API de OpenGL de nuestra tarjeta
	// de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configuramos OpenGL. Este es el color
	// por default del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glPointSize(5);

	//como poner imagenes transparentes. Degradado de particulas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Inicializar DevIL+
	ilInit(); // Inicializamos la librería y sus recursos
	ilEnable(IL_ORIGIN_SET); // Le decimos que queremos cambiar
							 // el punto de origen
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT); // Cambiarlo y configurarlo
										// como abajo a la izquerda. Hace match con las
										// coordenadas de textura.

	Initialize();

	// Iniciar la aplicación. El main se pausará en esta
	// línea hasta que se cierre la ventana de OpenGL.
	glutMainLoop();

	// Terminar.
	return 0;
}