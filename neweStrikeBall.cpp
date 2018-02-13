#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

#if _DEBUG
int g_debug_int = 0;
#endif

const int NUM_BALLS = 3;
const WCHAR* STR_INPUT = L"INPUT NUMBER : ";
const WCHAR* STR_RESULT = L"STRIKE : %d, BALL : %d";
const WCHAR* STR_NOTHING = L"NOTHING";
const WCHAR* STR_END = L"END";

// 초기화
void Init(std::vector<int>& param_1, std::vector<int>& param_2);

// 랜덤 숫자 3개 생성
bool MakeRandProc(std::vector<int>& param);
int getRandNum(std::vector<int>& param);

// 중복 여부 검사
bool isDupclication(std::vector<int>& param, int randNum);

// vector 에 넣기
bool inputVector(std::vector<int>& param, int randNum);

// 숫자 세자리 입력받는다
// 입력받은 숫자 3개로 분리
// 랜덤숫자와 입력받은 숫자 비교
	// 같은자리 같은 숫자면 스트라이크
	// 다른자리 같은 숫자면 볼
// 스트라이크가 3개면 끝

int main()
{
	// 필요한것 : 랜덤숫자 저장, 입력숫자 저장, 스트라이크 저장, 볼 저장
	std::vector<int> randArr;
	std::vector<int> inputArr;
	int strike, ball = 0;

	Init(randArr, inputArr);
	MakeRandProc(randArr);

#if _DEBUG
	for (auto i : randArr)
	{
		std::wcout << i << std::endl;
	}

	std::wcout << L"Rand Loop Count : " << g_debug_int << std::endl;
#endif

    return 0;
}

void Init(std::vector<int>& param_1, std::vector<int>& param_2)
{
	// 벡터 초기화
	param_1.reserve(NUM_BALLS);
	param_2.reserve(NUM_BALLS);

	srand((unsigned int)time(NULL));
}

bool MakeRandProc(std::vector<int>& param)
{
	// 넣는다. 꽉 찰때까지.
	while (param.size() != NUM_BALLS)
	{
		int randNum = getRandNum(param);
		inputVector(param, randNum);
	}

	return true;
}

int getRandNum(std::vector<int>& param)
{
	// 1 ~ 9 랜덤 숫자 생성 후 
	int randNum = rand() % 9 + 1;

	// 중복 여부 검사하고
	while (isDupclication(param, randNum))
	{
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
	{
		return false;
	}

	return true;
}

bool inputVector(std::vector<int>& param, int randNum)
{
	param.push_back(randNum);
	return true;
}
