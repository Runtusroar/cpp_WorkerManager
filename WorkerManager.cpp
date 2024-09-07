#include "WorkerManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

// �����ļ�·����
#define FILEPATH "empData.txt"


// ������뻺��������
void clearcin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// �ж��ļ������Ƿ�Ϊ��
bool isFileEmpty(const std::string& fileName) {
	std::ifstream file(fileName);
	return file.peek() == std::ifstream::traits_type::eof();
}

// �����ݱ��浽�ļ��У����ǣ�
void WorkerManager::saveDataToFile() {
	// ���ļ���Ĭ�ϸ���ģʽ��
	std::ofstream fs;

	// ���û��Ա�����ݣ�������ļ�
	if (this->allEmp == nullptr) {
		fs.open(FILEPATH, std::ios::trunc); // ����ļ�
	}
	else {
		fs.open(FILEPATH, std::ios::out); // ����д��ģʽ
		// ����Ա�����ݵ��ļ�
		for (int i = 0; i < this->num; i++) {
			fs << this->allEmp[i]->m_id << " "
				<< this->allEmp[i]->m_name << " "
				<< this->allEmp[i]->m_deptId << " "
				<< this->allEmp[i]->m_salary << std::endl;
		}
	}

	// �ر��ļ�
	fs.close();
}


// Worker���캯��
Worker::Worker(int id, std::string name, int deptId, int salary) :m_id(id), m_name(name), m_deptId(deptId), m_salary(salary) {};



// Employee��Դ����
// ���캯��
Employee::Employee(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};

// showinfo
void Employee::showinfo(){
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Complete the work tasks assigned by the manager" << std::endl;
}


// Manager���캯��
Manager::Manager(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};

void Manager::showinfo() {
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Complete the work tasks assigned by the boss" << std::endl;
}


// Boss
Boss::Boss(int id, std::string name, int deptId, int salary) :Worker(id, name, deptId, salary) {};
void Boss::showinfo() {
	std::cout << std::left << std::setw(10) << this->m_id << std::setw(10) << this->m_name << std::setw(10) << this->m_deptId << std::setw(10) << this->m_salary << std::setw(40) << "Responsible for deceiving Party A" << std::endl;
}



// WorkerManager�޲ι��캯��
WorkerManager::WorkerManager() :id(0), num(0) {
	// �ж��ļ��Ƿ����
	std::ifstream fs(FILEPATH, std::ios::in);
	if (!fs.is_open()) { return; }

	// �ж��ļ������Ƿ�Ϊ��
	if (isFileEmpty(FILEPATH)) { return; }

	// ͳ���ļ��ж�����
	std::string line;
	while (std::getline(fs, line)) {
		this->num++;
	}
	fs.close();


	// ���´��ļ�����ȡ����
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
			// ��������������磬�����ѷ�����ڴ棩
		}
	}
	fs.close();
}

// WorkerManager�вι��캯��
WorkerManager::WorkerManager(int paramId = 0, int paramNum = 0):id(paramId),num(paramNum) {

}

// WorkerManager��������
WorkerManager::~WorkerManager() {
	if (this->allEmp != nullptr) {
		for (int i = 0; i < this->num; i++) {
			delete this->allEmp[i];
		}
		delete[] this->allEmp;
		this->allEmp = nullptr;
	}
}

// �˵�չʾ����
void WorkerManager::showMenu() {
	system("cls");
	std::cout << "  --------- clay ְ������ϵͳ ---------  " << std::endl;
	std::cout << "  |          01.�˳��������          |  " << std::endl;
	std::cout << "  |          02.���ְ����Ϣ          |  " << std::endl;
	std::cout << "  |          03.ɾ��ְ����Ϣ          |  " << std::endl;
	std::cout << "  |          04.�޸�ְ����Ϣ          |  " << std::endl;
	std::cout << "  |          05.���ְ����Ϣ          |  " << std::endl;
	std::cout << "  |          06.���ݱ������          |  " << std::endl;
	std::cout << "  |          07.���������Ϣ          |  " << std::endl;
	std::cout << "  -------------------------------------  " << std::endl;
}


// ���Ա������
void WorkerManager::addEmploee() {
	int salary;
	std::string name;
	int depid;

	system("cls");

	std::cout << "����Ա��������";
	clearcin();
	std::cin >> name;

	std::cout << "����Ա�����ű�ţ�1���ϰ壬2������3����ͨԱ������";
	while (true) {
		clearcin();
		std::cin >> depid;
		if (depid == 1 || depid == 2 || depid == 3) {
			break;
		}
		else {
			std::cout << "��������ȷ�ı�ţ�";
		}
	}
	std::cout << "����н�ʣ�";
	clearcin();
	std::cin >> salary;


	// ��������
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

	// �����������ȴ�����ʱ������
	Worker** tempArr = new Worker * [this->num + 1];
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp != nullptr) {
			tempArr[i] = this->allEmp[i];
		}
	}
	tempArr[this->num] = w;

	// ɾ�������ݣ�ָ��������
	if (this->allEmp != nullptr) {
		delete[] this->allEmp;
	}
	this->allEmp = tempArr;

	// Ա��������1
	this->num++;
	// ְ��id��1
	this->id++;

	// �����ݴ����ļ���
	std::ofstream fs(FILEPATH, std::ios::app);
	fs << w->m_id << " "
		<< w->m_name << " "
		<< w->m_deptId << " "
		<< w->m_salary << std::endl;
	fs.close();

	std::cout << "��ӳɹ������س������ز˵�...";
	clearcin();
	std::cin.get();
}


// �������ְ����Ϣ����
void WorkerManager::showAllEmp() const {
	system("cls");
	std::cout << std::left << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::setw(40) << "responsibility" << std::endl;
	for (int i = 0; i < this->num; i++) {
		this->allEmp[i]->showinfo();
	}

	std::cout << "���س������ز˵�...";
	clearcin();
	std::cin.get();
}


// ɾ��ְ������
void WorkerManager::deleteEmp() {
	system("cls");
	std::cout << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::endl;
	for (int i = 0; i < this->num; i++) {
		std::cout << std::setw(10) << this->allEmp[i]->m_id << std::setw(10) << this->allEmp[i]->m_name << std::setw(10) << this->allEmp[i]->m_deptId << std::setw(10) << this->allEmp[i]->m_salary << std::endl;
	}
	int id;
	bool isExist = false;

	std::cout << "����Ҫɾ����ְ��id��";
	clearcin();
	std::cin >> id;


	// ���жϸ�id�Ƿ����
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp[i]->m_id == id) {
			isExist = true;
		}
	}

	if (isExist) {
		if (this->num > 1) {
			Worker** tempArr = new Worker * [this->num - 1];
			int index = 0; // ���ڸ��� tempArr �е�����
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

		// ���µ��ļ���
		this->saveDataToFile();

		std::cout << "ɾ����Ա" << id << "�ɹ���" << std::endl;
	}
	else {
		std::cout << "��Ա��id�����ڣ�" << std::endl;
	}


	clearcin();
	std::cout << "���س������ز˵�...";
	std::cin.get();
}


// ����ְ����Ϣ
void WorkerManager::updateEmp() {
	system("cls");
	std::cout << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::endl;
	for (int i = 0; i < this->num; i++) {
		std::cout << std::setw(10) << this->allEmp[i]->m_id << std::setw(10) << this->allEmp[i]->m_name << std::setw(10) << this->allEmp[i]->m_deptId << std::setw(10) << this->allEmp[i]->m_salary << std::endl;
	}

	clearcin();
	int id;
	bool isExist = false;
	std::cout << "ѡ��Ҫ�޸ĵ�Ա��id��";
	std::cin >> id;

	// ���жϸ�id�Ƿ����
	for (int i = 0; i < this->num; i++) {
		if (this->allEmp[i]->m_id == id) {
			isExist = true;
		}
	}

	if (isExist) {
		std::string newName;
		int newDeptId;
		int newSalary;

		std::cout << "����Ա������������";
		clearcin();
		std::cin >> newName;

		std::cout << "����Ա�����ŵ��±�ţ�1���ϰ壬2������3����ͨԱ������";
		clearcin();
		std::cin >> newDeptId;

		std::cout << "�����µ�н�ʣ�";
		clearcin();
		std::cin >> newSalary;

		// ��������
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

		// ���µ��ļ���
		this->saveDataToFile();

		std::cout << "Ա��" << id << "���ݸ��³ɹ�" << std::endl;
	}
	else {
		std::cout << "��Ա��������" << std::endl;
	}

	clearcin();
	std::cout << "���س������ز˵�...";
	std::cin.get();
}


// ɾ������Ա��
void WorkerManager::deleteAllEmp() {
	int isTrue = 2;
	system("cls");
	std::cout << "ȷ���������ְ����Ϣ�𣿣�1��ȷ�ϣ�2��ȡ������";
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

		// ���µ��ļ���
		this->saveDataToFile();

		std::cout << "����Ա����Ϣ�������" << std::endl;
	}
	else {
		std::cout << "������ȡ����" << std::endl;
	}

	clearcin();
	std::cout << "���س������ز˵�...";
	std::cin.get();
}


// ��Ա����id��������
void WorkerManager::sortEmpForId() {
	system("cls");
	std::cout << "��Ա��id��������1������2�����򣩣�";
	clearcin();
	int select;
	std::cin >> select;
	
	// ������forѭ��������ð������
	for (int i = 0; i < this->num; i++) {
		// ����һ�����֣����ڴ洢��һ��ѭ���У�ÿ��ѭ����id���ֵ������Сֵ�������±�
		int minOrMax = i;

		if (select == 1) {	//��������
			for (int j = i; j < this->num; j++) {
				if (this->allEmp[i]->m_id > this->allEmp[j]->m_id) {
					minOrMax = j;
				}
			}
		}
		else {	// ��������
			for (int j = i; j < this->num; j++) {
				if (this->allEmp[i]->m_id < this->allEmp[j]->m_id) {
					minOrMax = j;
				}
			}
		}

		// ����ʱ�±��id������Сֵ��ӦԪ���±겻�����������ݽ���
		if (i != minOrMax) {
			Worker* temp = this->allEmp[i];
			this->allEmp[i] = this->allEmp[minOrMax];
			this->allEmp[minOrMax] = temp;
		}

	}

	// ������ɣ��������ݵ��ļ���
	this->saveDataToFile();

	std::cout << std::left << std::setw(10) << "id" << std::setw(10) << "name" << std::setw(10) << "deptId" << std::setw(10) << "salary" << std::setw(40) << "responsibility" << std::endl;
	for (int i = 0; i < this->num; i++) {
		this->allEmp[i]->showinfo();
	}

	std::cout << "���س������ز˵�...";
	clearcin();
	std::cin.get();
}