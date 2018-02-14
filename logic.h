#pragma once

extern const int NUM_BALLS;
extern const WCHAR* STR_INPUT;
extern const WCHAR* STR_INCORRECT_INPUT;
extern const WCHAR* STR_RESULT;
extern const WCHAR* STR_NOTHING;
extern const WCHAR* STR_END;

// �ʱ�ȭ
void Init(std::vector<int>& randVector, std::vector<int>& inputVector);

// ���� ���� 3�� ����
bool MakeRandProc(std::vector<int>& randVector);
int getRandNum(std::vector<int>& randVector);

// �ߺ� ���� �˻�
bool isDupclication(std::vector<int>& param, int randNum);

// vector �� �ֱ�
bool inputVector(std::vector<int>& param, int randNum);

// ���� ���ڸ� �Է¹޴´�
bool InputUserNumProc(std::vector<int>& inputVector);
int getUserInput(void);

// TODO : ��ȿ�� �˻�
bool isVaild(std::vector<int>& inputVector, int inputNum);

// �Է¹��� ���� 3���� �и��ؼ� �ߺ��˻�
bool numToVector(std::vector<int>& inputVector, int inputParam);

// �迭�� Ư�� �ε���<����> ��� ���� �ִ���
int valueInVector(std::vector<int>& inputVector, int idx, int value);

// �迭�� Ư�� �ε����� <����>�ϰ� ��� ���� �ִ���
int valueInVectorEx(std::vector<int>& inputVector, int idx, int value);

// �������ڿ� �Է¹��� ���� ��
// �����ڸ� ���� ���ڸ� ��Ʈ����ũ
int CheckStirke(std::vector<int>& randVector, std::vector<int>& inputVector);

// �ٸ��ڸ� ���� ���ڸ� ��
int CheckBall(std::vector<int>& randVector, std::vector<int>& inputVector);

// ��Ʈ����ũ�� 3���� ��
bool CheckResult(int strike, int ball);