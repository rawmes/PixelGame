#include "glm/geometric.hpp"
#include <iterator>
#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <tiledRenderer.h>

const int SPEED = 900;
constexpr int BACKGROUNDS = 3;

struct GameplayData{
	glm::vec2 playerPos = {100, 100};
};

GameplayData gameplayData;

gl2d::Texture spaceshipTexture;
gl2d::Texture backgroundTexture[BACKGROUNDS];

TiledRenderer tiledRenderer[BACKGROUNDS];


gl2d::Renderer2D renderer;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceshipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);

	backgroundTexture[0].loadFromFile(RESOURCES_PATH "background1.png", true);
	backgroundTexture[1].loadFromFile(RESOURCES_PATH "background3.png", true);
	backgroundTexture[2].loadFromFile(RESOURCES_PATH "background4.png", true);

	tiledRenderer[0].texture = backgroundTexture[0];
	tiledRenderer[1].texture = backgroundTexture[1];
	tiledRenderer[2].texture = backgroundTexture[2];

	tiledRenderer[0].parallaxStrength = 0;
	tiledRenderer[1].parallaxStrength = 0.5;
	tiledRenderer[2].parallaxStrength = 0.7;

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

#pragma region movement
	glm::vec2 move = {};
	
	if (
		platform::isButtonHeld(platform::Button::W) ||
		platform::isButtonHeld(platform::Button::Up)
	){
		move.y = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::A) ||
		platform::isButtonHeld(platform::Button::Left)
	){
		move.x = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::S) ||
		platform::isButtonHeld(platform::Button::Down)
	){
		move.y = 1;
	}
	if (
		platform::isButtonHeld(platform::Button::D) ||
		platform::isButtonHeld(platform::Button::Right)
	){
		move.x = 1;
	}

	if(move.x != 0 || move.y != 0) {
		move = glm::normalize(move);
		move *= deltaTime * SPEED;
		gameplayData.playerPos += move;
	}

#pragma end region
	
	for(int i = 0; i < BACKGROUNDS; i++){
		tiledRenderer[i].render(renderer);
	}

	renderer.currentCamera.zoom = 0.5;
	renderer.currentCamera.follow(gameplayData.playerPos, SPEED * deltaTime * 0.9, 10, 200, w, h);
	renderer.renderRectangle({gameplayData.playerPos, 100, 100}, spaceshipTexture);
	
	renderer.flush();
	
	//ImGui::ShowDemoWindow();
	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
