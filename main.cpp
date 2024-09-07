#include <iostream>
#include "WorkerManager.h"

int main() {
	WorkerManager wm;
	int choice;

	while (true)
	{
		wm.showMenu();
		if (std::cin.fail()) {
			std::cout << "����������������ȷѡ�";
			std::cin.clear(); // �������״̬
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���Բ���������β
		}
		else {
			std::cout << "����ѡ��";
		}
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			return 0;
			break;
		case 2:
			wm.addEmploee();
			break;
		case 3:
			wm.deleteEmp();
			break;
		case 4:
			wm.updateEmp();
			break;
		case 5:
			wm.showAllEmp();
			break;
		case 6:
			wm.sortEmpForId();
			break;
		case 7:
			wm.deleteAllEmp();
			break;
		default:
			system("cls");
		}
	}

	return 0;
}