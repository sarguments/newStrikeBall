#include "stdafx.h"
#include "logic.h"

void Init(std::vector<int>& randVector, std::vector<int>& inputVector)
{
	// ���� �ʱ�ȭ
	randVector.reserve(NUM_BALLS);
	inputVector.reserve(NUM_BALLS);

	srand((unsigned int)time(NULL));

	MakeRandProc(randVector);
}

bool MakeRandProc(std::vector<int>& randVector)
{
	// �ִ´�. �� ��������.
	while (randVector.size() != NUM_BALLS) {
		int randNum = getRandNum(randVector);
		inputVector(randVector, randNum);
	}

	return true;
}

int getRandNum(std::vector<int>& randVector)
{
	// 1 ~ 9 ���� ���� ���� �� 
	int randNum = rand() % 9 + 1;

	// �ߺ� ���� �˻��ϰ�
	while (isDupclication(randVector, randNum)) {
		// �ߺ��̸� ���� �ٽ� ���Ѵ�
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

	// �Է¹��� ���� 3���� �и�
	numToVector(inputVector, localUserNum);

	while (!isVaild(inputVector, localUserNum)) {
		// �˻��ؼ� �ƴϸ� �ٽ� �Է¹ް� �и�
		std::wcout << STR_INCORRECT_INPUT;
		localUserNum = getUserInput();
		numToVector(inputVector, localUserNum);
	}

	return true;
}

int getUserInput(void)
{
	int localUserNum = -1;

	// �Է¹ް�
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

	// ���� �������� �ٸ� ��ġ�� ��
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
