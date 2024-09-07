#pragma once
#include <string>


// 清空输入流缓存区函数
void clearcin();


// 职工基类
class Worker {
public:
	Worker(int id, std::string name, int deptId, int salary);

	// 显示个人信息
	virtual void showinfo() = 0;


	// 职工编号
	int m_id;
	// 职工姓名
	std::string m_name;
	//部门编号
	int m_deptId;
	// 职工薪资
	int m_salary;
};


// 员工类
class Employee : public Worker {
public:
	//构造函数
	Employee(int id, std::string name, int deptId, int salary);

	//显示岗位职责
	virtual void showinfo();
};


// 经理类
class Manager : public Worker {
public:
	Manager(int id, std::string name, int deptId, int salary);

	//显示岗位职责
	virtual void showinfo();
};


// 老板类
class Boss : public Worker {
public:
	Boss(int id, std::string name, int depid, int salary);

	// 显示岗位职责
	virtual void showinfo();
};


// 职工管理系统类
class WorkerManager {
public:
	Worker** allEmp = nullptr;

	// 菜单展示函数
	void showMenu();

	// 添加职工函数
	void addEmploee();

	// 输出职工信息函数
	void showAllEmp() const;

	// 删除职工函数
	void deleteEmp();

	// 修改职工函数
	void updateEmp();

	// 删除所有职工
	void deleteAllEmp();

	// 将数据保存到文件中（覆盖）
	void saveDataToFile();

	// 对员工按id排序
	void sortEmpForId();

	// 职工人数
	int num;

	// 职工id
	int id;

	// 无参构造函数
	WorkerManager();

	// 有参构造函数
	WorkerManager(int pramaId, int paramNum);

	// 析构函数
	~WorkerManager();
};