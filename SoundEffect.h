#include <windows.h>      // mciSendString, xử lý file âm thanh
#include <mmsystem.h>     // Multimedia API (bắt buộc cho MCI)
#pragma comment(lib, "winmm.lib")   // liên kết thư viện âm thanh

#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include<atomic>
using namespace std;

extern atomic<bool>IsMusicPaused;

void playWinSound();
void playClickSound();
void playClickMenuSound();
void playChooseMenuSound();
void playBackgroundMusic();
void StopBackGroundMusic();
void backgroundMusicThread();
void ContinuePlayBackGroundMusic();