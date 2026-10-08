#include "SoundEffect.h"
#include "MenuGame.h"

bool isMusicOn = true;
std::atomic<bool> IsMusicPaused(false);
std::thread bgmThread;
std::mutex soundMutex;

void backgroundMusicThread()
{
	mciSendString(L"open \"Sounds/BackgroundMusic.wav\" type mpegvideo alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);

	while (isMusicOn)
	{
		if (IsMusicPaused)
		{
			mciSendString(L"pause bgm", NULL, 0, NULL);
			while (IsMusicPaused) Sleep(50);
			mciSendString(L"resume bgm", NULL, 0, NULL);
		}
		Sleep(100);
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	// D?ng và dóng nh?c n?n khi k?t thúc
	mciSendString(L"stop bgm", NULL, 0, NULL);
	mciSendString(L"close bgm", NULL, 0, NULL);
}

// Hàm b?t d?u phát nh?c n?n
void playBackgroundMusic()
{
	if (!isSoundOn) return; // N?u t?t ti?ng thì không ch?y

	if (isMusicOn && !bgmThread.joinable())
	{
		bgmThread = std::thread(backgroundMusicThread);
	}
}

void StopBackGroundMusic()
{
	IsMusicPaused = true;
}

void ContinuePlayBackGroundMusic()
{
	IsMusicPaused = false;
}

// Hàm phát âm thanh click
void playClickSound()
{
	if (isSoundOn) { // Ki?m tra
		PlaySound(L"Sounds/Clicksound.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}

// Hàm phát âm thanh win
void playWinSound()
{
	StopBackGroundMusic(); 
	if (isSoundOn) {
		PlaySound(L"Sounds/EffectWin.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}
//Hàm phát âm thanh khi ch?n menu
void playClickMenuSound()
{
	if (isSoundOn) {
		PlaySound(L"Sounds/SoundClickMenu.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}

void playChooseMenuSound()
{
	if (isSoundOn) {
		PlaySound(L"Sounds/SoundChoose.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}
