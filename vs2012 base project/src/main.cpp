#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, mYellowDiamondX(100.0f)
		, mYellowDiamondY(100.0f) {
		GenerateGrid();
	}

	void Start() {
		mEngine.Start(*this);
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 22.5f, 0.f);

		if (mEngine.GetMouseButtonDown()) {
			mYellowDiamondX = mEngine.GetMouseX();
			mYellowDiamondY = mEngine.GetMouseY();
		}
		mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);

		for (int i = 0; i < 64; ++i)
		{
			float x = 350 + (static_cast<float>(i % 8) * 43.f);
			float y = 100 + (static_cast<float>(i / 8) * 43.f);
			mEngine.Render(mGrid[i], x, y);
		}

		char buffer[1000];
		sprintf_s(buffer, "(%.0f, %.0f)", mYellowDiamondX, mYellowDiamondY);

		mEngine.Write(buffer, mYellowDiamondX, mYellowDiamondY + 40.0f);
	}

	void GenerateGrid()
	{
		for (int i = 0; i < 64; ++i)
		{
			auto jewel = static_cast<King::Engine::Texture>((rand() % 5) + 1);
			if (i > 1)
			{
				if (mGrid[i - 1] == jewel && mGrid[i - 2] == jewel)
				{
					jewel = static_cast<King::Engine::Texture>(jewel + 1);
				}
			}

			if (i > 15)
			{
				if (mGrid[i - 8] == jewel && mGrid[i - 16] == jewel)
				{
					jewel = static_cast<King::Engine::Texture>(jewel + 1);
				}
			}

			if (jewel == King::Engine::TEXTURE_MAX)
			{
				jewel = King::Engine::TEXTURE_BLUE;
			}

			mGrid[i] = jewel;
		}
	}

private:
	King::Engine mEngine;
	float mRotation;
	float mYellowDiamondX;
	float mYellowDiamondY;
	King::Engine::Texture mGrid[64];
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}


