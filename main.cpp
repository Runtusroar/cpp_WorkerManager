#include <iostream>
#include "WorkerManager.h"

int main() {
	WorkerManager wm;
	int choice;

	while (true)
	{
		wm.showMenu();
		if (std::cin.fail()) {
			std::cout << "输入有误，请输入正确选项：";
			std::cin.clear(); // 清除错误状态
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略并丢弃至行尾
		}
		else {
			std::cout << "输入选择：";
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