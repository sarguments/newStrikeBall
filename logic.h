#pragma once

extern const int NUM_BALLS;
extern const WCHAR* STR_INPUT;
extern const WCHAR* STR_INCORRECT_INPUT;
extern const WCHAR* STR_RESULT;
extern const WCHAR* STR_NOTHING;
extern const WCHAR* STR_END;

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
int getUserInput(void);

// TODO : 유효성 검사
bool isVaild(std::vector<int>& inputVector, int inputNum);

// 입력받은 숫자 3개로 분리해서 중복검사
bool numToVector(std::vector<int>& inputVector, int inputParam);

// 배열의 특정 인덱스<까지> 어떠한 값이 있는지
int valueInVector(std::vector<int>& inputVector, int idx, int value);

// 배열의 특정 인덱스를 <제외>하고 어떠한 값이 있는지
int valueInVectorEx(std::vector<int>& inputVector, int idx, int value);

// 랜덤숫자와 입력받은 숫자 비교
// 같은자리 같은 숫자면 스트라이크
int CheckStirke(std::vector<int>& randVector, std::vector<int>& inputVector);

// 다른자리 같은 숫자면 볼
int CheckBall(std::vector<int>& randVector, std::vector<int>& inputVector);

// 스트라이크가 3개면 끝
bool CheckResult(int strike, int ball);