#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

#include"AVL.h"

int main() {

	AVLTree myAVLTree;
	ofstream outf("Adm.txt");
	ifstream inf("Adm.txt");

	int i = 0;

	do {
		cout << "******************************        主         菜          单        *********************************" << endl << endl;
		cout << "			|                   1.用户登录			|\n" << endl;
		cout << "			|                   2.用户注册			|\n" << endl;
		cout << "			|                   3.用户注销			|\n" << endl;
		cout << "			|                   4.输出所有用户信息		|\n" << endl;
		cout << "			|                   5.退出			|\n" << endl;
		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		cout << "					输入您的菜单选项编号(0-5):" << endl;
		cin >> i;
		switch (i) {

			case 1: {
				if (myAVLTree.empty()) {
					system("cls");
					cout << "当前未注册用户" << endl;
				}
				else {
					system("cls");
					string un, pw;
					cout << "输入用户名：";
					cin >> un;
					if (myAVLTree.search(un)) {
						cout << "输入密码：";
						cin >> pw;
						if (myAVLTree.search(un)->password == pw) {
							cout << "\n登录成功" << endl;
							cout << "1.修改密码" << endl;
							cout << "2.退出\n" << endl;
							int i;
							cin >> i;
							if (i == 1) {
								cout << "输入新密码：";
								string pw1;
								cin >> pw1;
								myAVLTree.setPW(un, pw1);
								myAVLTree.foutFile();
								cout << "修改密码成功\n";
							}
						}
						else {
							cout << "密码错误" << endl;
						}
					}
					else {
						cout << "用户名不存在" << endl;
					}
				}
			}break;

			case 2: {
				system("cls");
				cout << "请输入用户名：";
				string pw2, un2;
				cin >> un2;

				while (myAVLTree.search(un2)) {
					cout << "该用户名已存在，请重试：";
					cin >> un2;
				}
				cout << "请输入密码：";
				cin >> pw2;
				
				myAVLTree.insert(un2, pw2);
				myAVLTree.foutFile();
				cout << "用户创建成功" << endl;
			}break;

			case 3: {
				system("cls");
				cout << "请输入用户名：";
				string un3;
				cin >> un3;
				cout << "请输入密码：";
				string pw3;
				cin >> pw3;

				if (!myAVLTree.search(un3)) {
					cout << "未找到该用户" << endl;
				}
				else{
					cout << "已找到，是否注销（1.是 2.否）：";
					int i;
					cin >> i;
					if (i == 1) {
						myAVLTree.remove(un3);
						myAVLTree.foutFile();
						cout << "注销成功" << endl;
					}
				}
			}break;

			case 4: {
				system("cls");
				int count = 0;
				myAVLTree.print();
			}break;
		}
		if (i != 5) {
			cout << "输入任意值返回菜单：";
			string cat; 
			cin >> cat;
			system("cls");
		}
	} while (i != 5);

	system("cls");
	inf.close();
	outf.close();
	cout << "欢迎下次使用\n";
}