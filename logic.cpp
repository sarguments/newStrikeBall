#include "stdafx.h"
#include "logic.h"

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
	while (isDupclication(randVector, randNum)) {
		// 중복이면 랜덤 다시 구한다
		randNum = rand() % 9 + 1;
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
	int localUserNum = getUserInput();

	// 입력받은 숫자 3개로 분리
	numToVector(inputVector, localUserNum);

	while (!isVaild(inputVector, localUserNum)) {
		// 검사해서 아니면 다시 입력받고 분리
		std::wcout << STR_INCORRECT_INPUT;
		localUserNum = getUserInput();
		numToVector(inputVector, localUserNum);
	}

	return true;
}

int getUserInput(void)
{
	int localUserNum = -1;

	// 입력받고
	std::wcout << STR_INPUT;
	std::wcin >> localUserNum;

	return localUserNum;
}

bool isVaild(std::vector<int>& inputVector, int inputNum)
{
	if (inputNum < 0 || inputNum >= (int)pow(10, NUM_BALLS))
		return false;

	if (isDupclication(inputVector, 0))
		return false;

	for (int i = 0; i < NUM_BALLS; i++) {
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

	for (int i = 0; i < NUM_BALLS; i++) {
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

int valueInVectorEx(std::vector<int>& inputVector, int idx, int value)
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

	for (int i = 0; i < NUM_BALLS; i++) {
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
		if (valueInVectorEx(randVector, i, inputVector[i]) != -1) {
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
