#include "WorkerManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

// 定义文件路径宏
#define FILEPATH "empData.txt"


// 清空输入缓冲区函数
void clearcin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// 判断文件内容是否为空
bool isFileEmpty(const std::string& fileName) {
	std::ifstream file(fileName);
	return file.peek() == std::ifstream::traits_type::eof();
}

// 将数据保存到文件中（覆盖）
void WorkerManager::saveDataToFile() {
	// 打开文件（默认覆盖模式）
	std::ofstream fs;

	// 如果没有员工数据，则清空文件
	if (this->allEmp == nullptr) {
		fs.open(FILEPATH, std::ios::trunc); // 清空文件
	}
	else {
		fs.open(FILEPATH, std::ios::out); // 正常写入模式
		// 保存员工数据到文件
		for (int i = 0; i < this->num; i++) {
			fs << this->allEmp[i]->m_id << " "
				<< this->allEmp[i]->m_name << " "
				<< this->allEmp[i]->m_deptId << " "
				<< this->allEmp[i]->m_salary << std::endl;
		}
	}

	// 关闭文件
	fs.close();
}


// Worker构造函数
Worker::Worker(int id, std::string name, int deptId, int salary) :m_id(id), m_name(name), m_deptId(deptId), m_salary(salary) {};



// Employee类源代码
// 构造函数
Employee::Employee(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};

// showinfo
void Employee::showinfo(){
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Complete the work tasks assigned by the manager" << std::endl;
}


// Manager构造函数
Manager::Manager(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};

void Manager::showinfo() {
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Complete the work tasks assigned by the boss" << std::endl;
}


// Boss
Boss::Boss(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};
void Boss::showinfo() {
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Responsible for deceiving Party A" << std::endl;
}



// WorkerManager无参构造函数
WorkerManager::WorkerManager() :id(0), num(0) {
	// 判断文件是否存在
	std::ifstream fs(FILEPATH, std::ios::in);
	if (!fs.is_open()) { return; }

	// 判断文件内容是否为空
	if (isFileEmpty(FILEPATH)) { return; }

	// 统计文件有多少行
	std::string line;
	while (std::getline(fs, line)) {
		this->num++;
	}
	fs.close();


	// 重新打开文件并读取数据
	fs.open(FILEPATH);
	int i = 0;
	this->allEmp = new Worker * [this->num];
	while (std::getline(fs, line)) {
		std::istringstream iss(line);
		int id, deptId, salary;
		std::string name;
		if (iss >> id >> name >> deptId >> salary) {
			if (deptId == 1) {
				this->allEmp[i++] = new Boss(id, name, deptId, salary);
			}
			else if (deptId == 2) {
				this->allEmp[i++] = new Manager(id, name, deptId, salary);
			}
			else {
				this->allEmp[i++] = new Employee(id, name, deptId, salary);
			}

			if (this->id < id) {
				this->id = id;
			}
		}
		else {
			std::cerr << "Error: Failed to parse line." << std::endl;
			// 处理解析错误（例如，清理已分配的内存）
		}
	}
	fs.close();
}

// WorkerManager有参构造函数
WorkerManager::WorkerManager(int paramId = 0, int paramNum = 0):id(paramId),num(paramNum) {

}

// WorkerManager析构函数
WorkerManager::~WorkerManager() {
	if (this->allEmp != nullptr) {
		for (int i = 0; i < this->num; i++) {
			delete this->allEmp[i];
		}
		delete[] this->allEmp;
		this->allEmp = nullptr;
	}
}

// 菜单展示函数
void WorkerManager::showMenu() {
	system("cls");
	std::cout << "  --------- clay 职工管理系统 ---------  " << std::endl;
	std::cout << "  |          01.退出管理程序          |  " << std::endl;
	std::cout << "  |          02.添加职工信息          |  " << std::endl;
	std::cout << "  |          03.删除职工信息          |  " << std::endl;
	std::cout << "  |          04.修改职工信息          |  " << std::endl;
	std::cout << "  |          05.输出职工信息          |  " << std::endl;
	std::cout << "  |          06.根据编号排序          |  " << std::endl;
	std::cout << "  |          07.清空所有信息          |  " << std::endl;
	std::cout << "  -------------------------------------  " << std::endl;
}


// 添加员工函数
void WorkerManager::addEmploee() {
	int salary;
	std::string name;
	int depid;

	system("cls");

	std::cout << "输入员工姓名：";
	clearcin();
	std::cin >> name;

	std::cout << "输入员工部门编号（1：老板，2：经理，3：普通员工）：";
	while (true) {
		clearcin();
		std::cin >> depid;
		if (depid == 1 || depid == 2 || depid == 3) {
			break;
		}
		else {
			std::cout << "请输入正确的编号：";
		}
	}
	std::cout << "输入薪资：";
	clearcin();
	std::cin >> salary;


	// 创建基类
	Worker* w = nullptr;

	if (depid == 1) {
		w = new Boss(this->id + 1, name, depid, salary);
	}
	else if (depid == 2) {
		w = new Manager(this->id + 1, name, depid, salary);
	}
	else if (depid == 3) {
		w = new Employee(this->id + 1, name, depid, salary);
	}

	// 将所有数据先存入临时数组中
	Worker** tempArr = new Worker * [this->num + 1];
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp != nullptr) {
			tempArr[i] = this->allEmp[i];
		}
	}
	tempArr[this->num] = w;

	// 删除旧数据，指向新数据
	if (this->allEmp != nullptr) {
		delete[] this->allEmp;
	}
	this->allEmp = tempArr;

	// 员工计数加1
	this->num++;
	// 职工id加1
	this->id++;

	// 将数据存入文件中
	std::ofstream fs(FILEPATH, std::ios::app);
	fs << w->m_id << " "
		<< w->m_name << " "
		<< w->m_deptId << " "
		<< w->m_salary << std::endl;
	fs.close();

	std::cout << "添加成功，按回车键返回菜单...";
	clearcin();
	std::cin.get();
}


// 输出所有职工信息函数
void WorkerManager::showAllEmp() const {
	system("cls");
	std::cout << std::left << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::setw(40) << "responsibility" << std::endl;
	for (int i = 0; i < this->num; i++) {
		this->allEmp[i]->showinfo();
	}

	std::cout << "按回车键返回菜单...";
	clearcin();
	std::cin.get();
}


// 删除职工函数
void WorkerManager::deleteEmp() {
	system("cls");
	std::cout << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::endl;
	for (int i = 0; i < this->num; i++) {
		std::cout << std::setw(10) << this->allEmp[i]->m_id << std::setw(10) << this->allEmp[i]->m_name << std::setw(10) << this->allEmp[i]->m_deptId << std::setw(10) << this->allEmp[i]->m_salary << std::endl;
	}
	int id;
	bool isExist = false;

	std::cout << "输入要删除的职工id：";
	clearcin();
	std::cin >> id;


	// 先判断该id是否存在
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp[i]->m_id == id) {
			isExist = true;
		}
	}

	if (isExist) {
		if (this->num > 1) {
			Worker** tempArr = new Worker * [this->num - 1];
			int index = 0; // 用于跟踪 tempArr 中的索引
			for (int i = 0; i < this->num; i++) {
				if (this->allEmp[i]->m_id != id) {
					tempArr[index++] = this->allEmp[i];
				}
			}
			
			for (int i = 0; i < this->num; i++) {
				delete this->allEmp[i];
				this->allEmp[i] = nullptr;
			}
			delete[] this->allEmp;
			this->allEmp = tempArr;
		}
		else {
			for (int i = 0; i < this->num; i++) {
				delete this->allEmp[i];
				this->allEmp[i] = nullptr;
			}
			delete[] this->allEmp;
			this->allEmp = nullptr;
		}

		this->num--;

		// 更新到文件中
		this->saveDataToFile();

		std::cout << "删除成员" << id << "成功！" << std::endl;
	}
	else {
		std::cout << "该员工id不存在！" << std::endl;
	}


	clearcin();
	std::cout << "按回车键返回菜单...";
	std::cin.get();
}


// 更新职工信息
void WorkerManager::updateEmp() {
	system("cls");
	std::cout << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::endl;
	for (int i = 0; i < this->num; i++) {
		std::cout << std::setw(10) << this->allEmp[i]->m_id << std::setw(10) << this->allEmp[i]->m_name << std::setw(10) << this->allEmp[i]->m_deptId << std::setw(10) << this->allEmp[i]->m_salary << std::endl;
	}

	clearcin();
	int id;
	bool isExist = false;
	std::cout << "选择要修改的员工id：";
	std::cin >> id;

	// 先判断该id是否存在
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp[i]->m_id == id) {
			isExist = true;
		}
	}

	if (isExist) {
		std::string newName;
		int newDeptId;
		int newSalary;

		std::cout << "输入员工的新姓名：";
		clearcin();
		std::cin >> newName;

		std::cout << "输入员工部门的新编号（1：老板，2：经理，3：普通员工）：";
		clearcin();
		std::cin >> newDeptId;

		std::cout << "输入新的薪资：";
		clearcin();
		std::cin >> newSalary;

		// 创建基类
		Worker* w = nullptr;

		if (newDeptId == 1) {
			w = new Boss(id, newName, newDeptId, newSalary);
		}
		else if (newDeptId == 2) {
			w = new Manager(id, newName, newDeptId, newSalary);
		}
		else if (newDeptId == 3) {
			w = new Employee(id, newName, newDeptId, newSalary);
		}

		for (int i = 0; i < this->num; i++) {
			if (id == this->allEmp[i]->m_id) {
				this->allEmp[i] = w;
			}
		}

		// 更新到文件中
		this->saveDataToFile();

		std::cout << "员工" << id << "数据更新成功" << std::endl;
	}
	else {
		std::cout << "该员工不存在" << std::endl;
	}

	clearcin();
	std::cout << "按回车键返回菜单...";
	std::cin.get();
}


// 删除所有员工
void WorkerManager::deleteAllEmp() {
	int isTrue = 2;
	system("cls");
	std::cout << "确认清除所有职工信息吗？（1：确认，2：取消）：";
	clearcin();
	std::cin >> isTrue;
	if (isTrue == 1) {
		for (int i = 0; i < this->num; i++) {
			delete this->allEmp[i];
			this->allEmp[i] = nullptr;
		}
		delete[] this->allEmp;
		this->allEmp = nullptr;

		this->num = 0;
		this->id = 0;

		// 更新到文件中
		this->saveDataToFile();

		std::cout << "所有员工信息已清除！" << std::endl;
	}
	else {
		std::cout << "操作已取消！" << std::endl;
	}

	clearcin();
	std::cout << "按回车键返回菜单...";
	std::cin.get();
}


// 对员工按id进行排序
void WorkerManager::sortEmpForId() {
	system("cls");
	std::cout << "按员工id进行排序（1：升序，2：降序）：";
	clearcin();
	int select;
	std::cin >> select;
	
	// 用两个for循环，进行冒泡排序
	for (int i = 0; i < this->num; i++) {
		// 定义一个数字，用于存储第一层循环中，每次循环的id最大值或者最小值的数字下标
		int minOrMax = i;

		if (select == 1) {	//升序排序
			for (int j = i; j < this->num; j++) {
				if (this->allEmp[i]->m_id > this->allEmp[j]->m_id) {
					minOrMax = j;
				}
			}
		}
		else {	// 降序排序
			for (int j = i; j < this->num; j++) {
				if (this->allEmp[i]->m_id < this->allEmp[j]->m_id) {
					minOrMax = j;
				}
			}
		}

		// 若此时下标和id最大或最小值对应元素下标不符，进行数据交换
		if (i != minOrMax) {
			Worker* temp = this->allEmp[i];
			this->allEmp[i] = this->allEmp[minOrMax];
			this->allEmp[minOrMax] = temp;
		}

	}

	// 排序完成，更新数据到文件中
	this->saveDataToFile();

	std::cout << std::left << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::setw(40) << "responsibility" << std::endl;
	for (int i = 0; i < this->num; i++) {
		this->allEmp[i]->showinfo();
	}

	std::cout << "按回车键返回菜单...";
	clearcin();
	std::cin.get();
}