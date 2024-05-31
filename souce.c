// ------------------------------------ //
// include part

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------------------------- //
// Const define part 2-2

#define LEN_MIN 15 // 기차길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로범위
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// ------------------------------------- //
// Function part 2-1



void print_hash(int count) {
	for (int i = 0; i < count; i++) {
		printf("#");
	}
}

void print_space(int count) {
	for (int i = 0; i < count; i++) {
		printf(" ");
	}
}

// Train Make
void tmake(int tl, int c, int z, int m) {
	print_hash(tl);
	printf("\n#");

	print_space(c);
	printf("C");
	print_space(z);
	printf("Z");
	print_space(m);
	printf("M");
	printf("#\n");

	print_hash(tl);
	printf("\n");
}

void input01(int* tl, int* ms, int* p) {

	while (1) {
		printf("train length(%d~%d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", tl);
		//2-2 마동석 체력 추가
		printf("madongseok stamina (%d~%d)>>", STM_MIN, STM_MAX);
		scanf_s("%d", ms);
		printf("percentile probability 'p'(%d~%d)>>", PROB_MIN, PROB_MAX);
		scanf_s("%d", p);

		//2-2 유효한 값 입력 받기
		if ((*tl >= LEN_MIN && *tl <= LEN_MAX) &&
			(*ms >= STM_MIN && *ms <= STM_MAX) &&
			(*p >= PROB_MIN && *p <= PROB_MAX)) {
			return 0;
		}
	}
}

int main(void) {

	//tl = 기차 길이를 받는 변수
	//ms = 스테미나
	//p = 움직이는 확률을 받는 변수
	int tl = 0, ms = 0, p = 0;
	input01(&tl, &ms, &p);

	//랜덤한 확률로 움직임 구현

	srand((unsigned int)time(NULL));
	int m1 = (rand() % 100) - p;

	//2-2
	// c_agr = 시민 어그로
	// m_agr = 동석이 어그로
	int c_agr = 1;
	int m_agr = 1;

	//게임 종료를 위한 값
	int c1, z1;
	c1 = tl + 2;
	z1 = tl;

	//눈으로 보기 위한 시민 위치 좀비 위치 동석 위치
	int cw, zw, mw;
	cw = tl - 6;
	zw = tl - 3;
	mw = tl - 2;

	//시민, 마동석, 좀비 초기 위치 구현
	int m = 0;
	int c = tl - 7;
	int z = 2;

	//좀비 턴
	int zturn = 1;

	//열차 초기 상태
	tmake(tl, c, z, m);
	printf("citizen: stay %d\n", cw);
	printf("zombie: stay %d\n", zw);
	printf("\n");
	printf("\n");


	while (1) {
		//m1변수가 양수일 경우 움직임 음수일 경우 안 움직임
		//2-3 시민 이동
		if (m1 >= 0) {
			c -= 1;
			z += 1;
			c1 += 1;
			cw -= 1;
			//움직이면 시민 어그로 추가
			c_agr += 1;
		}
		else if (m1 < 0) {
			c += 0;
			c_agr -= 1;
		}

		//어그로 최대 최소 제한
		if (c_agr > AGGRO_MAX) {
			c_agr -= 1;
		}
		else if (c_agr <= AGGRO_MIN) {
			c_agr += 1;
		}

		//좀비의 경우 반대로 움직임
		//2-2 좀비 이동
		if (zturn % 2 != 0) {
			//이동 가능한 턴 표시
			printf("turn : %d\n", zturn);
			printf("zombies can move\n");
			if (m1 < 0) {
				//어그로 수치에 따라 이동 표현
				if (c_agr >= m_agr) {
					z -= 1;
					m += 1;
					z1 += 1;
					zw -= 1;
				}
				else if (c_agr < m_agr) {
					z += 1;
					m -= 1;
					z1 -= 1;
					zw += 1;
				}
			}
			else if (m1 >= 0) {
				z += 0;
			}
		}
		else if (zturn % 2 == 0) {
			printf("turn : %d\n", zturn);
			printf("zombies can't move\n");
		}

		//열차 상태 구현
		tmake(tl, c, z, m);
		printf("\n");

		//움직이면 ->로 움직임 표시
		// 안 움직이면 stay로 위치 표시
		if (m1 >= 0) {
			printf("citizen: %d -> %d (aggro: %d)\n", cw + 1, cw, c_agr);
		}
		else if (m1 < 0) {
			printf("citizen: stay %d (aggro: %d)\n", cw, c_agr);
		}

		if (m1 < 0) {
			printf("zombie: %d -> %d\n", zw + 1, zw);
		}
		else if (m1 >= 0) {
			printf("zombie: stay %d\n", zw);
		}
		zturn++;
		printf("\n");

		// 마동석 움직임 1일 경우 움직이고 마동석의 위치 변화 출력
		//2-3 마동석 이동
		int m_mov;
		while (1) {
			printf("madongseok move(0:stay, 1:left)>>");
			scanf_s("%d", &m_mov);

			if (m_mov <= 1) {
				if (m_mov == 1) {
					mw -= 1;
					m_agr += 1;
					break;
				}
				else if (m_mov == 0) {
					m_agr -= 1;
					break;
				}
			}
		}
		//마동석 어그로 최대 최소 제한
		if (m_agr > AGGRO_MAX) {
			m_agr -= 1;
		}
		else if (m_agr <= AGGRO_MIN) {
			m_agr += 1;
		}

		//마동석 행동 정의 후 열차 상태 구현
		tmake(tl, c, z, m);
		printf("\n");

		if (m_mov == 1) {
			printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n", mw + 1, mw, m_agr, ms);
		}
		else if (m_mov == 0) {
			printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", mw, m_agr, ms);
		}
		//1페이즈 끝

		printf("\n");
		//행동 페이즈

		//사람 행동 정의
		if (m1 >= 0) {
			printf("citizen has moved.\n");
		}
		else {
			printf("citizen does nothing.\n");
		}

		//좀비 행동 정의
		if (c1 - z1 == 0) {
			printf("zombies attacked people.\n");
		}
		else {
			printf("zombie attacked nobody.\n");
		}

		//마동석 행동 정의
		int Behavior;
		printf("madongseok action(0.rest, 1.provoke)>>");
		scanf_s("%d", &Behavior);

		printf("\n");
		if (Behavior == 0) {
			printf("madongseok rests...\n");
		}
		else if (Behavior == 1) {
			printf("madongseok provoke!\n");
		}

		printf("madongseok: %d (aggro: %d, stamina: %d)\n", mw, m_agr, ms);
		printf("\n");

		//시민이 열차 끝으로 가면 게임 끝
		//2-4
		if (c == 0) {
			printf("YOU WIN!");
			break;
		}
		//시민 옆에 좀비가 도착하면 게임 끝 2-4
		if (c1 - z1 == 0) {
			printf("GAME OVER!");
			break;
		}
		// 마동석 체력이 없을 경우 게임 끝 2-4
		if (ms == STM_MIN) {
			printf("madongseok HP 0....");
			break;
		}
		//2페이즈 끝
	}
	return 0;
}