#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

#if _DEBUG
int g_debug_int = 0;
#endif

const int NUM_BALLS = 3;
const WCHAR* STR_INPUT = L"INPUT NUMBER : ";
const WCHAR* STR_RESULT = L"STRIKE : %d, BALL : %d\n";
const WCHAR* STR_NOTHING = L"NOTHING\n";
const WCHAR* STR_END = L"END\n";

// 초기화
void Init(std::vector<int>& randVector, std::vector<int>& inputVector);

// 랜덤 숫자 3개 생성
bool MakeRandProc(std::vector<int>& randVector);
int getRandNum(std::vector<int>& randVector);

// 중복 여부 검사
bool isDupclication(std::vector<int>& param, int randNum);

// vector 에 넣기
bool inputVector(std::vector<int>& param, int randNum);

// 숫자 세자리 입력받는다
bool InputUserNumProc(std::vector<int>& inputVector);

// TODO : 유효성 검사
bool isVaild(std::vector<int>& inputVector, int inputNum);

// 입력받은 숫자 3개로 분리해서 중복검사
bool numToVector(std::vector<int>& inputVector, int inputParam);

// 배열의 특정 인덱스<까지> 어떠한 값이 있는지
int valueInVector(std::vector<int>& inputVector, int idx, int value);

// 배열의 특정 인덱스를 <제외>하고 어떠한 값이 있는지
int valueInArrEx(std::vector<int>& inputVector, int idx, int value);

// 랜덤숫자와 입력받은 숫자 비교
	// 같은자리 같은 숫자면 스트라이크
int CheckStirke(std::vector<int>& randVector, std::vector<int>& inputVector);

	// 다른자리 같은 숫자면 볼
int CheckBall(std::vector<int>& randVector, std::vector<int>& inputVector);

// 스트라이크가 3개면 끝
bool CheckResult(int strike, int ball);

int main()
{
	// 필요한것 : 랜덤숫자 저장, 입력숫자 저장, 스트라이크 저장, 볼 저장
	std::vector<int> randVector;
	std::vector<int> inputVector;

	Init(randVector, inputVector);

#if _DEBUG
	for (auto i : randVector) {
		std::wcout << i << std::endl;
	}

	std::wcout << L"Rand Loop Count : " << g_debug_int << std::endl;
#endif

	while (1) {
		int strike, ball = 0;

		InputUserNumProc(inputVector);
		strike = CheckStirke(randVector, inputVector);
		ball = CheckBall(randVector, inputVector);

		if (CheckResult(strike, ball)) break;
	}

	return 0;
}

void Init(std::vector<int>& randVector, std::vector<int>& inputVector)
{
	// 벡터 초기화
	randVector.reserve(NUM_BALLS);
	inputVector.reserve(NUM_BALLS);

	srand((unsigned int)time(NULL));

	MakeRandProc(randVector);
}

bool MakeRandProc(std::vector<int>& randVector)
{
	// 넣는다. 꽉 찰때까지.
	while (randVector.size() != NUM_BALLS) {
		int randNum = getRandNum(randVector);
		inputVector(randVector, randNum);
	}

	return true;
}

int getRandNum(std::vector<int>& randVector)
{
	// 1 ~ 9 랜덤 숫자 생성 후 
	int randNum = rand() % 9 + 1;

	// 중복 여부 검사하고
	while (isDupclication(randVector, randNum))	{
		// 중복이면 랜덤 다시 구한다
		randNum = rand() % 9 + 1;
#if _DEBUG
		g_debug_int++;
#endif
	}

	return randNum;
}

bool isDupclication(std::vector<int>& param, int randNum)
{
	auto iter = std::find(param.begin(), param.end(), randNum);
	if (iter == param.end())
		return false;

	return true;
}

bool inputVector(std::vector<int>& inputVector, int randNum)
{
	inputVector.push_back(randNum);
	return true;
}

bool InputUserNumProc(std::vector<int>& inputVector)
{
	// 입력받고
	std::wcout << STR_INPUT;

	int localUserNum = -1;
	std::wcin >> localUserNum;

	// 입력받은 숫자 3개로 분리
	numToVector(inputVector, localUserNum);

	while (!isVaild(inputVector, localUserNum))	{
		// 검사해서 아니면 다시 입력받고 분리
		std::wcout << STR_INPUT;
		std::wcin >> localUserNum;
		numToVector(inputVector, localUserNum);
	}

	return true;
}

bool isVaild(std::vector<int>& inputVector, int inputNum)
{
	if (inputNum < 0 || inputNum >= (int)pow(10, NUM_BALLS))
		return false;

	if (isDupclication(inputVector, 0))
		return false;

	for (int i = 0; i < NUM_BALLS; i++)	{
		if (valueInVector(inputVector, i, inputVector[i]) != -1)
			return false;
	}

	return true;
}

bool numToVector(std::vector<int>& inputVector, int inputParam)
{
	inputVector.clear();
	int mod = (int)pow(10, NUM_BALLS);
	int divide = mod / 10;

	for (int i = 0; i < NUM_BALLS; i++)	{
		int toPushNum = (inputParam % mod) / divide;
		inputVector.push_back(toPushNum);
		mod /= 10;
		divide /= 10;
	}

	return true;
}

int valueInVector(std::vector<int>& inputVector, int idx, int value)
{
	for (int i = 0; i < idx; i++) {
		if (inputVector[i] == value)
			return i;
	}

	return -1;
}

int valueInArrEx(std::vector<int>& inputVector, int idx, int value)
{
	for (int i = 0; i < NUM_BALLS; i++) {
		if (i == idx)
			continue;

		if (inputVector[i] == value)
			return i;
	}

	return -1;
}

int CheckStirke(std::vector<int>& randVector, std::vector<int>& inputVector)
{
	int localStrike = 0;

	for (int i = 0; i < NUM_BALLS; i++)	{
		if (randVector[i] == inputVector[i]) {
			localStrike++;
		}
	}

	return localStrike;
}

int CheckBall(std::vector<int>& randVector, std::vector<int>& inputVector)
{
	int localBall = 0;

	// 같은 숫자지만 다른 위치면 볼
	for (int i = 0; i < NUM_BALLS; i++) {
		if (valueInArrEx(randVector, i, inputVector[i]) != -1) {
			localBall++;
		}
	}

	return localBall;
}

bool CheckResult(int strike, int ball)
{
	if (strike == 0 && ball == 0)
		std::wcout << STR_NOTHING;

	wprintf(STR_RESULT, strike, ball);

	if (strike == 3) {
		std::wcout << STR_END;
		return true;
	}

	return false;
}
