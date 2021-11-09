#include <Animation.h>

vector<Animation*> Animation::allAnimations = vector<Animation*>();

void Animation::Initialize()
{
	tickCount = 0;
	currentFrame = 0;

	myShowObject = SpriteObject(Sprite());

	allAnimations.push_back(this);
}

void Animation::SetFrame(int frame)
{
	currentFrame = frame;
	myShowObject.SetSprite(animFrames[frame]);
}

Animation::Animation() : tickMax(10)
{
	Initialize();
}

Animation::Animation(int maxAnimTickCount)
{
	Initialize();

	if (maxAnimTickCount < 0)
		maxAnimTickCount *= -1;

	tickMax = maxAnimTickCount;
}

Animation::~Animation()
{
	allAnimations.erase(remove(allAnimations.begin(), allAnimations.end(), this));
}

void Animation::LoadAnimFrames(Sprite frame)
{
	animFrames.push_back(frame);
	SetFrame(currentFrame);
}

void Animation::LoadAnimFrames(vector<Sprite> frames)
{
	for (size_t i = 0; i < frames.size(); i++)
		LoadAnimFrames(frames[i]);
}

void Animation::Tick()
{
	if (!myShowObject.IsEnabled())
		return;

	tickCount++;

	if (tickCount > tickMax)
	{
		currentFrame++;
		tickCount = 0;

		if (currentFrame >= animFrames.size())
			currentFrame = 0;

		SetFrame(currentFrame);
	}
}

void Animation::SetAnimSpeed(int maxAnimTickCount)
{
	tickMax = abs(maxAnimTickCount);
}

void Animation::EnableRendering(bool var)
{
	myShowObject.EnableRendering(var);
}

vector<Animation*>* Animation::GetAllAnimations()
{
	return &allAnimations;
}

void Animation::OnPositionChange() // override Transform
{
	Transform::OnPositionChange();
	myShowObject.SetPosition(position);
}

// ******************************************************

SpawnAnimation::SpawnAnimation(Tank* tankToSpawn)
{
	spawnTank = tankToSpawn;

	int animSpeed = 5;

	myAnim = new Animation(animSpeed);
	myAnim->SetPosition(spawnTank->GetPosition());
	myAnim->EnableRendering(true);

	Sprite one = Sprite(Vector2(258, 19), Vector2(9, 9));
	Sprite two = Sprite(Vector2(273, 18), Vector2(11, 11));
	Sprite three = Sprite(Vector2(288, 17), Vector2(13, 13));
	Sprite four = Sprite(Vector2(303, 16), Vector2(15, 15));

	for (size_t i = 0; i < 3; i++)
	{
		myAnim->LoadAnimFrames(one);
		myAnim->LoadAnimFrames(two);
		myAnim->LoadAnimFrames(three);
		myAnim->LoadAnimFrames(four);
		myAnim->LoadAnimFrames(three);
		myAnim->LoadAnimFrames(two);
	}
	myAnim->LoadAnimFrames(one);

	ticksLeft = 3 * 5 + 1;
	ticksLeft *= animSpeed;
}

SpawnAnimation::~SpawnAnimation()
{
	delete myAnim;
}

void SpawnAnimation::Tick()
{
	myAnim->Tick();

	if (ticksLeft > 0)
		ticksLeft--;
	else
	{
		spawnTank->EnableRendering(true);
		delete this;
	}
}
