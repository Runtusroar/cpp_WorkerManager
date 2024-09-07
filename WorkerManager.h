#pragma once
#include <string>


// �������������������
void clearcin();


// ְ������
class Worker {
public:
	Worker(int id, std::string name, int deptId, int salary);

	// ��ʾ������Ϣ
	virtual void showinfo() = 0;


	// ְ�����
	int m_id;
	// ְ������
	std::string m_name;
	//���ű��
	int m_deptId;
	// ְ��н��
	int m_salary;
};


// Ա����
class Employee : public Worker {
public:
	//���캯��
	Employee(int id, std::string name, int deptId, int salary);

	//��ʾ��λְ��
	virtual void showinfo();
};


// ������
class Manager : public Worker {
public:
	Manager(int id, std::string name, int deptId, int salary);

	//��ʾ��λְ��
	virtual void showinfo();
};


// �ϰ���
class Boss : public Worker {
public:
	Boss(int id, std::string name, int depid, int salary);

	// ��ʾ��λְ��
	virtual void showinfo();
};


// ְ������ϵͳ��
class WorkerManager {
public:
	Worker** allEmp = nullptr;

	// �˵�չʾ����
	void showMenu();

	// ���ְ������
	void addEmploee();

	// ���ְ����Ϣ����
	void showAllEmp() const;

	// ɾ��ְ������
	void deleteEmp();

	// �޸�ְ������
	void updateEmp();

	// ɾ������ְ��
	void deleteAllEmp();

	// �����ݱ��浽�ļ��У����ǣ�
	void saveDataToFile();

	// ��Ա����id����
	void sortEmpForId();

	// ְ������
	int num;

	// ְ��id
	int id;

	// �޲ι��캯��
	WorkerManager();

	// �вι��캯��
	WorkerManager(int pramaId, int paramNum);

	// ��������
	~WorkerManager();
};