#pragma once

#include <Transform.h>
#include <Sprite.h>
#include <SpriteObject.h>
#include <vector>
#include <GameObjects.h>

using namespace std;

class Animation : public Transform
{
public:
	Animation();
	Animation(int maxAnimTickCount);
	~Animation();

	void LoadAnimFrames(Sprite frame);
	void LoadAnimFrames(vector<Sprite> frames);

	void Tick();

	void SetAnimSpeed(int maxAnimTickCount);

	void EnableRendering(bool var);

	static vector<Animation*>* GetAllAnimations();

	void OnPositionChange() override;
private:
	static vector<Animation*> allAnimations;

	int tickCount, tickMax, currentFrame;
	vector<Sprite> animFrames;
	SpriteObject myShowObject;

	void Initialize();
	void SetFrame(int frame);
};

class SpawnAnimation : public Tickable
{
public:
	SpawnAnimation(Tank* tankToSpawn);
	~SpawnAnimation();

	void Tick() override;
private:
	Tank* spawnTank;
	Animation* myAnim;
	int ticksLeft;
};