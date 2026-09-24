#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>
#include <limits>

using namespace std;

// 学习任务结构体
struct Task
{
    int id;         // 任务编号
    string course;  // 课程名称
    string content; // 学习内容
    string goal;    // 学习目标
    string plan;    // 任务安排
    bool completed; // 完成状态
};

// 链表节点
struct Node
{
    Task data;  // 保存一个学习任务的数据(即一个节点处有一个Tsak)
    Node *next; // 指向下一个节点
};

Node *head = nullptr; // 链表头指针为空

// 添加任务函数
void addTask()
{
    int maxId = 0;
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.id > maxId)
        {
            maxId = current->data.id;
        }

        current = current->next;
    }

    if (maxId == numeric_limits<int>::max())
    {
        cout << "任务编号已达到最大，无法继续添加！" << endl;
        return;
    }

    Node *newNode = new Node;
    newNode->data.id = maxId + 1;
    cout << "新任务编号为：" << newNode->data.id << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "请输入课程名称：" << endl;
    getline(cin, newNode->data.course);

    cout << "请输入学习内容：" << endl;
    getline(cin, newNode->data.content);

    cout << "请输入学习目标：" << endl;
    getline(cin, newNode->data.goal);

    cout << "请输入任务安排：" << endl;
    getline(cin, newNode->data.plan);

    newNode->data.completed = false;

    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = newNode;
    }
}

// 查看学习任务函数
void showTask()
{
    if (head == nullptr)
    {
        cout << "当前没有学习任务" << endl;
        return;
    }
    else
    {
        Node *p = head;
        while (p != nullptr)
        { // 打印任务
            cout << "任务编号：" << p->data.id << endl;
            cout << "课程名称：" << p->data.course << endl;
            cout << "学习内容：" << p->data.content << endl;
            cout << "学习目标：" << p->data.goal << endl;
            cout << "任务安排：" << p->data.plan << endl;

            if (p->data.completed)
            {
                cout << "完成状态：已完成" << endl;
            }
            else
            {
                cout << "完成状态：未完成" << endl;
            }

            p = p->next; // 节点继续向后
        }
    }
}

// 修改任务函数
void modifyTask()
{
    int Id;
    while (true)
    {
        cout << "请输入要修改的任务编号" << endl;

        cin >> Id;

        if (cin)
        {
            break;
        }

        if (cin.eof())
        {
            return;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除错误输入行，以便重新读取

        cout << "输入错误，请输入整数编号！" << endl;
    }

    // 清除读取成功后的换行，为getline做准备
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Node *p = head;

    while (p != nullptr)
    {
        if (p->data.id == Id)
        {
            cout << "已找到要修改的任务" << endl;

            Task updated = p->data;

            cout << "请输入新课程名称：" << endl;
            getline(cin, updated.course);

            cout << "请输入新学习内容：" << endl;
            getline(cin, updated.content);

            cout << "请输入新学习目标：" << endl;
            getline(cin, updated.goal);

            cout << "请输入新任务安排：" << endl;
            getline(cin, updated.plan);

            int status;
            while (true)
            {
                cout << "请输入任务完成状态（0-未完成，1-已完成）：" << endl;
                cin >> status;

                if (!cin)
                {
                    if (cin.eof())
                    {
                        return;
                    }

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "输入错误，请输入整数0或1！" << endl;
                    continue;
                }

                if (status == 0)
                {
                    updated.completed = false;
                    break;
                }
                else if (status == 1)
                {
                    updated.completed = true;
                    break;
                }
                else
                {
                    cout << "只能输入0或1，请重新输入！" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            p->data = updated;
            cout << "任务修改成功！" << endl;

            return;
        }
        p = p->next;
    }
    cout << "未找到要修改的任务" << endl;
}

// 删除任务函数
void deleteTask()
{
    if (head == nullptr)
    {
        cout << "当前没有学习任务！" << endl;
        return;
    }

    int id;

    while (true)
    {
        cout << "请输入要删除的任务编号：" << endl;

        cin >> id;

        if (cin)
        {
            break;
        }

        if (cin.eof())
        {
            return;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "输入错误，请输入整数编号！" << endl;
    }

    Node *p = head;
    Node *prev = nullptr;

    while (p != nullptr)
    {
        if (p->data.id == id)
        {
            cout << "找到要删除的任务了！" << endl;
            if (p == head)
            {
                head = p->next;
                delete p;
                cout << "任务删除成功！" << endl;
                return;
            }
            else
            {
                prev->next = p->next;
                delete p;
                cout << "任务删除成功！" << endl;
                return;
            }
        }
        else
        {
            prev = p;
            p = p->next;
        }
    }

    cout << "未找到要删除的任务！" << endl;
}

// 任务完成函数
void completeTask()
{
    int id;

    while (true)
    {
        cout << "请输入完成状态改变的任务编号：" << endl;

        cin >> id;

        if (cin)
        {
            break;
        }

        if (cin.eof())
        {
            return;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "输入错误，请输入整数编号！" << endl;
    }

    Node *p = head;

    while (p != nullptr)
    {
        if (p->data.id == id)
        {
            cout << "找到目标任务了！" << endl;
            p->data.completed = true;
            cout << "任务已完成！" << endl;
            return;
        }
        else
        {
            p = p->next;
        }
    }

    cout << "未找到目标任务！" << endl;
}

// 保存文件函数
bool saveToFile()
{
    ofstream file("tasks.txt"); // 打开文件

    if (!file)
    {
        return false;
    }

    Node *p = head;

    while (p != nullptr)
    {
        file << p->data.id << '\n';
        file << p->data.course << '\n';
        file << p->data.content << '\n';
        file << p->data.goal << '\n';
        file << p->data.plan << '\n';
        file << p->data.completed << '\n';

        p = p->next;
    }

    file.close();

    if (!file)
    {
        cout << "保存任务失败！" << endl;
        return false;
    }

    return true;
}

// 读取文件函数
bool loadFromFile()
{
    // 打开文件，并确确认可以读取
    ifstream file("tasks.txt");
    if (!file)
    {
        // 检查文件是否存在
        error_code error;
        bool exists = filesystem::exists("tasks.txt", error);

        // 文件不存在
        if (!error && !exists)
        {
            return true;
        }

        cout << "无法读取任务文件，停止启动以保护原始数据！" << endl;
        return false;
    }

    // 准备一个任务变量，尝试读取编号，并继续读取任务信息
    Task task{};
    while (true)
    {
        file >> ws; // 跳过任务之间的空格，换行等空白字符

        if (file.bad())
        {
            cout << "读取文件时发生错误！" << endl;
            return false;
        }

        if (file.eof())
        {
            break;
        }

        if (!(file >> task.id))
        {
            cout << ("任务编号格式错误！") << endl;
            return false;
        }

        file.ignore();

        getline(file, task.course);
        getline(file, task.content);
        getline(file, task.goal);
        getline(file, task.plan);
        file >> task.completed;

        if (!file)
        {
            cout << "任务内容不完整或格式错误！" << endl;
            return false;
        }

        // 创建新节点，保存读取到的任务
        Node *newNode = new Node;
        newNode->data = task;
        newNode->next = nullptr;

        // 尾插到链表
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = newNode;
        }
    }
    return true;
}

// 释放链表函数
void clearTasks()
{
    while (head != nullptr)
    {
        Node *p = head;
        head = head->next;
        delete p;
    }
}

int main()
{
    if (!loadFromFile())
    {
        clearTasks();
        return 1;
    }

    int choice;

    while (true)
    {
        cout << "1.添加任务" << endl;
        cout << "2.查看任务" << endl;
        cout << "3.修改任务" << endl;
        cout << "4.删除任务" << endl;
        cout << "5.完成任务" << endl;
        cout << "0.退出" << endl;

        cout << "请选择：" << endl;
        if (!(cin >> choice))
        {
            if (cin.eof())
            {
                cout << "输入正常，程序正在保存并退出！" << endl;

                if (!saveToFile())
                {
                    cout << "任务保存失败！" << endl;
                    clearTasks();
                    return 1;
                }

                clearTasks();
                return 0;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "输入错误，请输入菜单中的数字！" << endl;
            continue;
        }

        if (choice == 1)
        {
            addTask();
        }
        else if (choice == 2)
        {
            showTask();
        }
        else if (choice == 3)
        {
            modifyTask();
        }
        else if (choice == 4)
        {
            deleteTask();
        }
        else if (choice == 5)
        {
            completeTask();
        }

        else if (choice == 0)
        {
            if (saveToFile())
            {
                clearTasks();
                break;
            }

            cout << "任务尚未保存，请处理问题后重试！" << endl;
        }
        else
        {
            cout << "输入错误，只能输入整数0-5，请重新输入！" << endl;
        }
    }

    return 0;
}