#include "PrecompileHeader.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

std::atomic_bool GameEngineThread::End = false;

GameEngineThread::GameEngineThread()
{
}

GameEngineThread::GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	Start(_ThreadName, _CallBack);
}

GameEngineThread::~GameEngineThread()
{
	Join();
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	CallBack = _CallBack;
	Thread = std::thread(ThreadBaseFunction, this, _ThreadName);

}

void GameEngineThread::ThreadBaseFunction(GameEngineThread* Thread, std::string Name)
{
	// 쓰레드는 절대 일정하지 않다.
	// 애초에 그게 병렬처리.

	std::wstring WName = GameEngineString::AnsiToUniCode(Name);
	// GetCurrentThreadId() 우리가 쓰레드 요청하면 윈도우는 우리 쓰레드에 id를 부여함
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	Thread->CallBack(Thread);
}

void GameEngineThread::Join()
{


	if (nullptr != CallBack)
	{
		Thread.join();
		CallBack = nullptr;
	}
}