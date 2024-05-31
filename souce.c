// ------------------------------------ //
// include part

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------------------------- //
// Const define part 2-2

#define LEN_MIN 15 // ��������
#define LEN_MAX 50
#define STM_MIN 0 // ������ü��
#define STM_MAX 5
#define PROB_MIN 10 // Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0 // ��׷ι���
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
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
		//2-2 ������ ü�� �߰�
		printf("madongseok stamina (%d~%d)>>", STM_MIN, STM_MAX);
		scanf_s("%d", ms);
		printf("percentile probability 'p'(%d~%d)>>", PROB_MIN, PROB_MAX);
		scanf_s("%d", p);

		//2-2 ��ȿ�� �� �Է� �ޱ�
		if ((*tl >= LEN_MIN && *tl <= LEN_MAX) &&
			(*ms >= STM_MIN && *ms <= STM_MAX) &&
			(*p >= PROB_MIN && *p <= PROB_MAX)) {
			return 0;
		}
	}
}

int main(void) {

	//tl = ���� ���̸� �޴� ����
	//ms = ���׹̳�
	//p = �����̴� Ȯ���� �޴� ����
	int tl = 0, ms = 0, p = 0;
	input01(&tl, &ms, &p);

	//������ Ȯ���� ������ ����

	srand((unsigned int)time(NULL));
	int m1 = (rand() % 100) - p;

	//2-2
	// c_agr = �ù� ��׷�
	// m_agr = ������ ��׷�
	int c_agr = 1;
	int m_agr = 1;

	//���� ���Ḧ ���� ��
	int c1, z1;
	c1 = tl + 2;
	z1 = tl;

	//������ ���� ���� �ù� ��ġ ���� ��ġ ���� ��ġ
	int cw, zw, mw;
	cw = tl - 6;
	zw = tl - 3;
	mw = tl - 2;

	//�ù�, ������, ���� �ʱ� ��ġ ����
	int m = 0;
	int c = tl - 7;
	int z = 2;

	//���� ��
	int zturn = 1;

	//���� �ʱ� ����
	tmake(tl, c, z, m);
	printf("citizen: stay %d\n", cw);
	printf("zombie: stay %d\n", zw);
	printf("\n");
	printf("\n");


	while (1) {
		//m1������ ����� ��� ������ ������ ��� �� ������
		//2-3 �ù� �̵�
		if (m1 >= 0) {
			c -= 1;
			z += 1;
			c1 += 1;
			cw -= 1;
			//�����̸� �ù� ��׷� �߰�
			c_agr += 1;
		}
		else if (m1 < 0) {
			c += 0;
			c_agr -= 1;
		}

		//��׷� �ִ� �ּ� ����
		if (c_agr > AGGRO_MAX) {
			c_agr -= 1;
		}
		else if (c_agr <= AGGRO_MIN) {
			c_agr += 1;
		}

		//������ ��� �ݴ�� ������
		//2-2 ���� �̵�
		if (zturn % 2 != 0) {
			//�̵� ������ �� ǥ��
			printf("turn : %d\n", zturn);
			printf("zombies can move\n");
			if (m1 < 0) {
				//��׷� ��ġ�� ���� �̵� ǥ��
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

		//���� ���� ����
		tmake(tl, c, z, m);
		printf("\n");

		//�����̸� ->�� ������ ǥ��
		// �� �����̸� stay�� ��ġ ǥ��
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

		// ������ ������ 1�� ��� �����̰� �������� ��ġ ��ȭ ���
		//2-3 ������ �̵�
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
		//������ ��׷� �ִ� �ּ� ����
		if (m_agr > AGGRO_MAX) {
			m_agr -= 1;
		}
		else if (m_agr <= AGGRO_MIN) {
			m_agr += 1;
		}

		//������ �ൿ ���� �� ���� ���� ����
		tmake(tl, c, z, m);
		printf("\n");

		if (m_mov == 1) {
			printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n", mw + 1, mw, m_agr, ms);
		}
		else if (m_mov == 0) {
			printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", mw, m_agr, ms);
		}
		//1������ ��

		printf("\n");
		//�ൿ ������

		//��� �ൿ ����
		if (m1 >= 0) {
			printf("citizen has moved.\n");
		}
		else {
			printf("citizen does nothing.\n");
		}

		//���� �ൿ ����
		if (c1 - z1 == 0) {
			printf("zombies attacked people.\n");
		}
		else {
			printf("zombie attacked nobody.\n");
		}

		//������ �ൿ ����
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

		//�ù��� ���� ������ ���� ���� ��
		//2-4
		if (c == 0) {
			printf("YOU WIN!");
			break;
		}
		//�ù� ���� ���� �����ϸ� ���� �� 2-4
		if (c1 - z1 == 0) {
			printf("GAME OVER!");
			break;
		}
		// ������ ü���� ���� ��� ���� �� 2-4
		if (ms == STM_MIN) {
			printf("madongseok HP 0....");
			break;
		}
		//2������ ��
	}
	return 0;
}