#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)

int NUM_ADS = 7;
char* ADS[] = {
	"������: �������� �������, ��������������, � ������� �������� �����, ����� �����, ���������, ����������",
	"������: �������� �������, ��������, ���������, ����� ��������, ����, �����",
	"����: �������� �������, ����������������, ��������, ����� �����, �����, ��������",
	"����: ����������� �������, ��������, ����� ���������, ����� � �������� ������",
	"�����: �������� �������, �����, ����� �������, ������������� � ���� � ��������",
	"����: �������� �������, �����, ����� �����, ���� � �����",
	"����: ����������� �������, ��������������, ����� �����, ����� � ����������"
};

void find() {
	int i;
	puts("Search results:");
	puts("----------------------------");
	
	for (int i; i < NUM_ADS; i++) {
		if (strstr(ADS[i], "�����")
			&& !strstr(ADS[i], "�����")) {
			printf("%s\n", ADS[i]);
		}
	}
	puts("----------------------------");
}

int main() {



	return 0;
}