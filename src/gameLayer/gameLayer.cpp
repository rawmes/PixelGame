#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>

struct GameplayData{
	glm::vec2 playerPos = {0, 0};
};

GameplayData gameplayData;

gl2d::Texture spaceshipTexture;
gl2d::Texture backgroundTexture;


gl2d::Renderer2D renderer;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceshipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);
	backgroundTexture.loadFromFile(RESOURCES_PATH "background1.png", true);
	
	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion
	
	renderer.renderRectangle({ gameplayData.playerPos, 100, 100}, Colors_Blue);
	
	renderer.flush();
	
	//ImGui::ShowDemoWindow();
	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
