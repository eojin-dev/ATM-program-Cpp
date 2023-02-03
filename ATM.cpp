#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <math.h>
#include <ctime>
using namespace std;

class bankinfo {
	string bankname;
	string username;
	string balance;
	string password;
	string account;
	int number = 0;
	int Mbalance = 0;

public:
	void ACCOUNT_MAKE(); //���»��� �Լ�
	int DEPOSIT(); //�Ա� �Լ�
	int WITHDRAW();//��� �Լ�
	int SEND();//�۱� �Լ�
	int BALANCE_CHECK();//�ܾ���ȸ �Լ�
	int PASSWORD_CHANGE();//��й�ȣ ���� �Լ�
	void ACCOUNT_LOCK(string& acc);//���� ���� �Լ�
	int LOCK_CHECK(string& acc); //���� ���� ���� Ȯ�� �Լ�
	int ACCOUNT_CHECK(string& acc); //���� ���� Ȯ�� �Լ�

	void PASSWORD_CHECK(); //������ �޴� ��й�ȣ Ȯ�� �Լ�
	void SYSTEM_MENU(); // ������ �޴� �Լ�
	void BANKADD(); //���� �߰� �Լ�
	void ACCOUNT_UNLOCK(); //���� ���� ���� �Լ�
	void ATM_CHECK(); //ATM �ܰ� Ȯ�� �Լ�
	void ATM_ADD(); //ATM �ܰ� �߰� �Լ�
	void SYSTEM_PASSWORD_CHANGE();// ������ ��й�ȣ ���� �Լ�
};//���� �⺻ ����

int main() {
	int menu_choice;
	bankinfo b;

	do {
		system("cls");
		cout << "=======ATM���α׷�=======" << endl;
		cout << "1. �Ա�\n2. ���\n3. �۱�\n4. �ܾ���ȸ\n5. ���»���\n6. ��й�ȣ ����\n7. ������ �޴�\n0. ���α׷� ����" << endl;
		cout << "=========================\n>> ";
		cin >> menu_choice;
		cout << endl;

		switch (menu_choice) {
		case 0: //����
			cout << "ATM ���α׷��� �����մϴ�." << endl;
			break;
		case 1: //�Ա�
			b.DEPOSIT();
			break;
		case 2: //���
			b.WITHDRAW();
			break;
		case 3: //�۱�
			b.SEND();
			break;
		case 4: //�ܾ� ��ȸ
			b.BALANCE_CHECK();
			break;
		case 5: //���� ����
			b.ACCOUNT_MAKE();
			break;
		case 6: //��й�ȣ ����
			b.PASSWORD_CHANGE();
			break;
		case 7: //������ �޴�
			b.PASSWORD_CHECK();
			break;
		default: //�߸��� ���� �Է����� ��
			cout << "0~7 ������ ���� �Է����ּ���." << endl;
			Sleep(1000);
			break;
		}

	} while (menu_choice != 0);

	return 0;
}

/*���»����Լ�*/
 void bankinfo::ACCOUNT_MAKE() {
	 system("cls");
	bankinfo b;
	string buffer;
	int offset;
	int count1 = 0;
	int count2 = 0;

	cout << "[���»���]" << endl;
	cout << "\n===��ϵǾ� �ִ� ����===" << endl;
	ifstream bank;
	bank.open("����.txt");

	if (bank.is_open())
	{
		while (getline(bank, buffer)) {
			if ((offset = buffer.find("����", 0)) != string::npos) {
				cout << buffer << endl;
				count2++;
			}

		}
		cout << "========================" << endl;
		cout << endl;

		bank.close();

		cout << "���� �̸��� �Է��Ͻÿ�: ";
		cin >> b.bankname;

		ifstream bank("����.txt");
		if (!bank) {
			cerr << "���� ���� ����" << endl;
			exit(1);
		}

		ofstream newfile("���� 2.txt");
		if (!newfile) {
			cerr << "���� ���� ����" << endl;
			exit(1);
		}

		while (getline(bank, buffer)) {
			if (b.bankname == buffer) {
				newfile << buffer << endl;

				cout << "�̸� : ";
				cin >> b.username;

				srand(time(NULL));
				int p = 9, c, d;
				c = (int)pow(10, 8);
				d = (int)pow(10, 8);

				cout << "���¹�ȣ ���� ����" << endl;

				b.number = (rand() % p + 1) * d + (rand() % c);
				cout << "\n���¹�ȣ�� �����Ǿ����ϴ�.\n\n";
				cout << "������ ���¹�ȣ : " << b.number << endl;

				newfile << b.number << endl;
			}
			else {
				if ((offset = buffer.find("����", 0)) != string::npos) {
					count1++;
				}
				newfile << buffer << endl;
			}
		}

		if(count1==count2) {
			cout << "�ش� ������ ��ϵǾ� ���� ���� �����Դϴ�.\n\n";
			Sleep(2500);
			bank.close();
			newfile.close();
			::remove("����.txt");
			if (rename("���� 2.txt", "����.txt") != 0) {
				cout << "�̸� ���� ����\n";
			}
		}

		while (1) {
			cout << "��й�ȣ : ";
			cin >> b.password;

			if (b.password.length() != 4) {
				cout << "\n��й�ȣ�� 4�ڸ� ���ڷ� �Է����ֽñ� �ٶ��ϴ�.\n\n";
			}
			else {
				break;
			}
		}

		cout << "���� ������ �Ϸ��Ͽ����ϴ�.\n";

		Sleep(2000);

		bank.close();
		newfile.close();


		::remove("����.txt");
		if (rename("���� 2.txt", "����.txt") != 0) {
			cout << "�̸� ���� ����\n";
		}
	}
	else {
		cout << "������ �� �� �����ϴ�." << endl;
	}

	system("cls");
	cout << "======================\n\n";
	cout << "����: " << b.bankname << endl;
	cout << "���¹�ȣ: " << b.number << endl;
	cout << "�̸�: " << b.username << endl;
	cout << "��й�ȣ: " << b.password << endl << endl;
	cout << "======================\n";

	fstream account("��������.txt", ios::app);
	if (!account) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	account << b.bankname << " " << b.username << " " << b.number << " " << b.password << "       " << "0" << endl;

	account.close();

	system("pause");
}

/*�Ա� �Լ�*/
 int bankinfo::DEPOSIT(void) {
	 system("cls");
	 string buffer;
	 string acc;
	 string pw;

	 int balance = 0;
	 int errcount = 0;
	 int END = 0;
	 vector<bankinfo> binfo;
	 bankinfo b;

	 cout << "[�Ա�]\n";
	 cout << "���¹�ȣ : ";
	 cin >> acc;

	 if (LOCK_CHECK(acc) == 1) {
		 return 0;
	 }

	 if (ACCOUNT_CHECK(acc) == 1) {
		 return 0;
	 }

	 ifstream account("��������.txt");
	 if (account.fail()) {
		 cerr << "���� ���� ����" << endl;
		 exit(1);
	 }

	 ofstream newfile("�������� 2.txt");
	 if (newfile.fail()) {
		 cerr << "���� ���� ����" << endl;
		 exit(1);
	 }

	 getline(account, buffer);
	 newfile << buffer << endl;
	 while (!account.eof()) {
		 account >> b.bankname >> b.username >> b.account >> b.password >> b.Mbalance;
		 binfo.push_back(b);
	 }
	 binfo.pop_back();

	 for (bankinfo& a : binfo) {
		 if (a.account == acc) {
			 while (END != 1) {
				 cout << "��й�ȣ : ";
				 cin >> pw;
				 if (a.password == pw) {
					 cout << "�Աݱݾ� : ";
					 cin >> balance;

					 if (balance <= 0) {
						 cout << "0�� �̻��� �ݾ��� �Է����ּ���." << endl;
						 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						 END = 1;
					 }

					 a.Mbalance += balance;

					 cout << "�ԱݵǾ����ϴ�.\n";

					 Sleep(2000);

					 system("cls");
					 cout << "======= ��ǥ =======\n";
					 struct tm* t;
					 time_t timer;
					 timer = time(NULL);
					 t = localtime(&timer);

					 cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

					 cout << "����: " << a.bankname << endl;
					 cout << "�Աݰ���: " << a.account << endl;
					 cout << "����: " << a.username << endl;
					 cout << "�Աݱݾ�: " << balance << endl;
					 cout << "�����ܾ�: " << a.Mbalance << endl;
					 cout << "======================\n";

					 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;

					 END = 1;
				 }
				 else {
					 errcount++;
					 cout << "��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n";
					 if (errcount == 3) {
						 cout << "��й�ȣ " << errcount << "ȸ ����. ���°� �����Ǿ����ϴ�.\n\n";
						 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						 ACCOUNT_LOCK(acc);
						 Sleep(2000);
						 END = 1;
					 }
					 else
						 cout << "��й�ȣ " << errcount << "ȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n";
				 }
			 }
		 }
		 else {
			 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
		 }
	 }
 
	account.close();
	newfile.close();

	::remove("��������.txt");
	if (rename("�������� 2.txt", "��������.txt") != 0) {
		cout << "�̸� ���� ����\n";
	}

	system("pause");
}

/*��� �Լ�*/
int bankinfo::WITHDRAW() {
	system("cls");
	string buffer;
	string acc;
	string pw;

	int balance = 0;
	int errcount = 0;
	int END = 0;
	vector<bankinfo> binfo;
	bankinfo b;

	cout << "[���]\n";
	cout << "���¹�ȣ : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("��������.txt");
	if (account.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	ofstream newfile("�������� 2.txt");
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(account, buffer);
	newfile << buffer << endl;
	while (!account.eof()) {
		account >> b.bankname >> b.username >> b.account >> b.password >> b.Mbalance;
		binfo.push_back(b);
	}
	binfo.pop_back();

	for (bankinfo& a : binfo) {
		if (a.account == acc) {
			while (END != 1) {
				cout << "��й�ȣ : ";
				cin >> pw;
				if (a.password == pw) {
					cout << "���� �ܾ� : " << a.Mbalance << endl << endl;
					cout << "��ݱݾ� : ";
					cin >> balance;

					if (balance <= 0) {
						cout << "0�� �̻��� �ݾ��� �Է����ּ���." << endl;
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						END = 1;
					}

					if (a.Mbalance - balance >= 0) {
						a.Mbalance -= balance;
						cout << "��ݵǾ����ϴ�.\n";

						Sleep(2000);

						system("cls");
						cout << "======= ��ǥ =======\n";
						struct tm* t;
						time_t timer;
						timer = time(NULL);
						t = localtime(&timer);

						cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

						cout << "����: " << a.bankname << endl;
						cout << "��ݰ���: " << a.account << endl;
						cout << "����: " << a.username << endl;
						cout << "��ݱݾ�: " << balance << endl;
						cout << "�����ܾ�: " << a.Mbalance << endl;
						cout << "======================\n";

						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;

						END = 1;
					}
					else {
						cout << "�ܾ��� �����մϴ�." << endl;
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						Sleep(2000);
						END = 1;
					}
				}
				else {
					errcount++;
					cout << "��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n";
					if (errcount == 3) {
						cout << "��й�ȣ " << errcount << "ȸ ����. ���°� �����Ǿ����ϴ�.\n\n";
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						ACCOUNT_LOCK(acc);
						Sleep(2000);
						END = 1;
					}
					else
						cout << "��й�ȣ " << errcount << "ȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n";
				}
			}
		}
		else {
			newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
		}
	}

	account.close();
	newfile.close();

	::remove("��������.txt");
	if (rename("�������� 2.txt", "��������.txt") != 0) {
		cout << "�̸� ���� ����\n";
	}

	system("pause");
}

/*�۱� �Լ�*/
int bankinfo::SEND() {
	system("cls");
	string buffer;
	string acc1, acc2;
	string pw;

	int balance = 0;
	int errcount = 0;
	int END = 0;
	vector<bankinfo> binfo;
	bankinfo b;

	cout << "[�۱�]\n";
	cout << "Ÿ �������� �۱� �� ������ 500���� �ΰ��˴ϴ�.\n";
	cout << "���¹�ȣ : ";
	cin >> acc1;

	if (LOCK_CHECK(acc1) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc1) == 1) {
		return 0;
	}

	ifstream account("��������.txt");
	if (account.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(account, buffer);
	while (!account.eof()) {
		account >> b.bankname >> b.username >> b.account >> b.password >> b.Mbalance;
		binfo.push_back(b);
	}
	binfo.pop_back();

	for (bankinfo& a : binfo) {
		if (a.account == acc1) {
			while (END != 1) {
				cout << "��й�ȣ : ";
				cin >> pw;
				if (a.password == pw) {
					cout << "���� �ܾ� : " << a.Mbalance << endl << endl;
					cout << "�۱� �ݾ� : ";
					cin >> balance;

					if (balance <= 0) {
						cout << "1�� �̻��� �ݾ��� �Է����ּ���." << endl;
						END = 1;
					}

					else {
						if (a.Mbalance - balance >= 0) {
							cout << "�Ա� ���� : ";
							cin >> acc2;
							if (acc1 == acc2) {
								cout << "�۱� ���¿� �Ա� ���°� ��ġ�մϴ�." << endl;
								Sleep(1500);
								END = 1;
							}

							else {
								if (LOCK_CHECK(acc2) == 1) {
									END = 1;
									break;
								}

								if (ACCOUNT_CHECK(acc2) == 1) {
									END = 1;
									break;
								}

								a.Mbalance -= balance;
								for (bankinfo& x : binfo) {
									if (x.account == acc2) {
										if (a.bankname == x.bankname) {
											x.Mbalance += balance;
										}
										else {
											if (a.Mbalance - 500 >= 0) {
												a.Mbalance -= 500;
												x.Mbalance += balance;
												cout << "������ 500���� �ΰ��˴ϴ�." << endl;
											}
											else {
												cout << "�ܾ��� �����մϴ�. (Ÿ �������� �۱� �� ������ 500�� �ΰ�)" << endl;
												a.Mbalance += balance;
												END = 1;
												Sleep(1000);
												break;
											}
										}

										cout << "�۱ݵǾ����ϴ�." << endl;
										Sleep(2000);

										system("cls");
										printf("======= ��ǥ =======\n");
										struct tm* t;
										time_t timer;
										timer = time(NULL);
										t = localtime(&timer);

										cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

										cout << "����: " << a.bankname << endl;
										cout << "�۱� ����: " << a.account << endl;
										cout << "������: " << a.username << endl << endl;
										cout << "�Ա� ����: " << x.account << endl;
										cout << "����: " << x.username << endl;
										cout << "�����ݾ�: " << balance << endl;
										cout << "�����ܾ�: " << a.Mbalance << endl;
										cout << "======================\n";

										END = 1;
									}
								}
							}
						}
						else {
							cout << "�ܾ��� �����մϴ�." << endl;
							Sleep(2000);
							END = 1;
						}
					}
				}
				else {
					errcount++;
					cout << "��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�.\n";
					if (errcount == 3) {
						cout << "��й�ȣ " << errcount << "ȸ ����. ���°� �����Ǿ����ϴ�.\n\n";
						ACCOUNT_LOCK(acc1);
						Sleep(2000);
						END = 1;
					}
					else
						cout << "��й�ȣ " << errcount << "ȸ ����. 3ȸ ������ ���°� �����˴ϴ�.\n";
				}

			}
		}
		else {
			continue;
		}
	}

	account.close();

	ofstream newfile("�������� 2.txt");
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	newfile << buffer << endl;


	for (bankinfo& a : binfo) {
		newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
	}
	newfile.close();

	::remove("��������.txt");
	if (rename("�������� 2.txt", "��������.txt") != 0) {
		cout << "�̸� ���� ����\n";
	}

	system("pause");
}

/*�ܾ���ȸ �Լ�*/
int bankinfo::BALANCE_CHECK(void) {
	system("cls");
	string acc;
	bankinfo b;
	vector<bankinfo> binfo;

	cout << "[�ܾ���ȸ]" << endl;
	cout << "�ܾ� ��ȸ�� ���¸� �Է��ϼ��� : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("��������.txt");
	if (account.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	while (!account.eof()) {
		account >> b.bankname >> b.username >> b.account >> b.password >> b.balance;
		binfo.push_back(b);
	}

	for (bankinfo& a : binfo) {
		if (a.account == acc) {
			cout << "���� �ܾ� : " << a.balance << endl;
			account.close();
			break;
		}
	}

	system("pause");

	while (binfo.empty() != true) {
		binfo.pop_back();
	}
}

/*��й�ȣ ���� �Լ�*/
int bankinfo::PASSWORD_CHANGE() {
	system("cls");
	int END = 0, errcount = 0;
	string acc, pwcheck, new1, new2;
	bankinfo b;
	vector<bankinfo> binfo;

	cout << "[��й�ȣ ����]" << endl;
	cout << "��й�ȣ�� ������ ���¸� �Է��ϼ��� : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("��������.txt");
	ofstream newfile("��������2.txt");

	if (account.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	while (!account.eof()) {
		account >> b.bankname >> b.username >> b.account >> b.password >> b.balance;
		binfo.push_back(b);
	}
	binfo.pop_back();


	for (bankinfo& a : binfo) {
		if (a.account == acc) {
			do {
				cout << "���� ��й�ȣ�� �Է����ּ���: ";
				cin >> pwcheck;

				if (a.password == pwcheck) {
					while (END != 1) {
						cout << "\n�� ��й�ȣ�� �Է����ּ��� (4�ڸ� ����) : ";
						cin >> new1;

						if (new1.length() != 4) {
							cout << endl << "��й�ȣ ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl;
						}
						else {
							cout << endl << "�� ��й�ȣ�� �ٽ� �Է����ּ��� (4�ڸ� ����) : ";
							cin >> new2;

							if (new1.compare(new2) == 0) {
								a.password = new1;
								END = 1;
							}
							else {
								cout << "\n��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl;
							}
						}
					}
				}
				else {
					errcount++;
					cout << "��й�ȣ ����. �ٽ� �Է����ֽñ� �ٶ��ϴ�." << endl;
					if (errcount == 3) {
						cout << "��й�ȣ " << errcount << "ȸ ����. ���°� �����Ǿ����ϴ�." << endl << endl;
						ACCOUNT_LOCK(acc);
						Sleep(2000);
						END = 1;
					}
					else {
						cout << "��й�ȣ " << errcount << "ȸ ����. 3ȸ ������ ���°� �����˴ϴ�." << endl << endl;
					}
				}
			} while (END != 1);
		}
	}

	cout << endl << "��й�ȣ�� ����Ǿ����ϴ�." << endl;

	newfile << binfo[0].bankname << "       " << binfo[0].username << "    " << binfo[0].account << "        " << binfo[0].password << "  " << binfo[0].balance << endl;
	binfo.erase(binfo.begin());

	for (bankinfo& a : binfo) {
		newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.balance << endl;
	}

	while (binfo.empty() != true) {
		binfo.pop_back();
	}

	newfile.close();
	account.close();

	::remove("��������.txt");
	if (rename("��������2.txt", "��������.txt") != 0) {
		cout << "�̸� ���� ����" << endl;
	}
	system("pause");
	return 0;
}

/*���� ���� �Լ�*/
void bankinfo::ACCOUNT_LOCK(string& acc) {
	string buffer;
	int offset;
	ifstream bank("����.txt");
	ofstream newfile("����2.txt");

	if (bank.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	while (getline(bank, buffer)) {
		if ((offset = buffer.find(acc, 0)) != string::npos) {
			newfile << buffer << " x" << endl;
		}
		else {
			newfile << buffer << endl;
		}
	}

	bank.close();
	newfile.close();

	::remove("����.txt");
	if (rename("����2.txt", "����.txt") != 0) {
		printf("�̸� ���� ����\n");
	}
}

/*���� ���� ���� Ȯ�� �Լ�*/
int bankinfo::LOCK_CHECK(string& acc) {
	int k = 0;
	int offset;
	string buffer;
	ifstream bank("����.txt");
	if (bank.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	while (getline(bank, buffer)) {
		if ((offset = buffer.find(acc, 0)) != string::npos) {
			if ((offset = buffer.find("x", 0)) != string::npos) {
				cout << "�ش� ���´� ���� �����Դϴ�." << endl;
				Sleep(2000);
				k = 1;
			}
		}
	}

	bank.close();
	return k;
}

/*���� ���� Ȯ�� �Լ�*/
int bankinfo::ACCOUNT_CHECK(string& acc) {
	int count1 = 0, count2 = 0;
	int offset;
	string buffer;
	ifstream bank("����.txt");
	if (bank.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	while (getline(bank, buffer)) {
		if (buffer == acc) {
			bank.close();
			return 0;
		}
		else
			count2++;
		count1++;
	}

	if (count1 == count2) {
		cout << "��ϵǾ� ���� ���� ���¹�ȣ�Դϴ�." << endl;
		Sleep(2000);
		bank.close();
		return 1;
	}
}

/*������ �޴� ��й�ȣ Ȯ�� �Լ�*/
void bankinfo::PASSWORD_CHECK() {

	system("cls");
	bankinfo b;
	string buffer1, buffer2;
	string check;
	int offset;
	int count = 0;
	ifstream atm("atm�ܰ�.txt");

	if (atm.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(atm, buffer1);
	getline(atm, buffer2);

	do {
		cout << "������ �޴� ��й�ȣ�� �Է��ϼ��� : ";
		cin >> check;

		if ((offset = buffer2.find(check, 0)) != string::npos) {
			atm.close();
			b.SYSTEM_MENU();
			break;
		}
		else {
			cout << endl << "��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl;
			cout << "��й�ȣ 3ȸ ������ ���θ޴��� ���ư��ϴ�." << endl << endl;
			count++;
			if (count == 3) {
				Sleep(1000);
				break;
			}
		}
	} while (1);

	atm.close();
}

/*������ �޴� �Լ�*/
void bankinfo::SYSTEM_MENU() {
	bankinfo b;
	int choice;

	do {
		system("cls");
		cout << "=======������ �޴�=======" << endl;
		cout << "1. ���� �߰�\n2. ���� ���� ����\n3. ATM�ܰ� Ȯ��\n4. ATM�ܰ� ����\n5. ������ ��й�ȣ ����\n0. ���θ޴�" << endl;
		cout << "=========================\n>> ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 0: //���θ޴�
			cout << "ATM ���α׷��� �����մϴ�." << endl;
			break;
		case 1: //���� �߰�
			b.BANKADD();
			break;
		case 2: //���� ���� ����
			b.ACCOUNT_UNLOCK();
			break;
		case 3: //ATM�ܰ� Ȯ��
			b.ATM_CHECK();
			break;
		case 4: //ATM�ܰ� ����
			b.ATM_ADD();
			break;
		case 5: //������ ��й�ȣ ����
			b.SYSTEM_PASSWORD_CHANGE();
			break;
		default: //�߸��� ���� �Է����� ��
			cout << "0~5 ������ ���� �Է����ּ���." << endl;
			Sleep(1000);
			break;
		}

	} while (choice != 0);
}

/*���� �߰� �Լ�*/
void bankinfo::BANKADD() {
	system("cls");

	string bank_add;
	ofstream bank("����.txt", ios::app);

	if (bank.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	cout << "�߰��� ������ �Է����ּ��� : ";
	cin >> bank_add;
	bank << bank_add << endl;
	cout << bank_add << "�� �߰��Ǿ����ϴ�." << endl;

	bank.close();
	Sleep(2000);
}

/*���� ���� ���� �Լ�*/
void bankinfo::ACCOUNT_UNLOCK() {
	system("cls");

	bankinfo b;
	int offset;
	int count1 = 0, count2 = 0;
	string buffer;
	string account;
	ifstream bank("����.txt");
	ofstream newfile("����2.txt");

	if (bank.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	cout << "������ ������ ���¹�ȣ�� �Է��ϼ��� : ";
	cin >> account;

	while (getline(bank, buffer)) {
		if ((offset = buffer.find(account, 0)) != string::npos) {
			if ((offset = buffer.find("x", 0)) != string::npos) {
				newfile << account << endl;
				cout << account << " ���°� �����Ǿ����ϴ�." << endl;
			}
			else {
				cout << "�ش� ���´� ���� ���°� �ƴմϴ�." << endl;
				newfile << buffer << endl;
			}
		}
		else {
			newfile << buffer << endl;
			count2++;
		}
		count1++;
	}
	if (count1 == count2) {
		cout << account << " ���´� ���� �����Դϴ�." << endl;
	}

	bank.close();
	newfile.close();

	::remove("����.txt");
	if (rename("����2.txt", "����.txt") != 0) {
		cout << "�̸� ���� ����" << endl;
	}
	Sleep(2000);
}

/*ATM �ܰ� Ȯ�� �Լ�*/
void bankinfo::ATM_CHECK() {
	system("cls");

	bankinfo b;
	string buffer1;
	ifstream atm("atm�ܰ�.txt");

	if (atm.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(atm, buffer1);
	atm >> b.bankname >> b.username >> b.balance >> b.password;

	cout << "ATM�� ���� �ܰ��" << b.balance << "�� �Դϴ�." << endl;

	atm.close();
	Sleep(2000);
}

/*ATM �ܰ� �߰� �Լ�*/
void bankinfo::ATM_ADD() {
	system("cls");

	bankinfo b;
	string buffer;
	int money;
	ifstream atm("atm�ܰ�.txt");
	ofstream newfile("atm�ܰ�2.txt");

	if (atm.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(atm, buffer);
	atm >> b.bankname;
	atm >> b.username;
	atm >> b.Mbalance;
	atm >> b.password;
	cout << "�߰��� �ݾ��� �Է��ϼ��� : ";
	cin >> money;
	b.Mbalance += money;
	cout << "ATM�� ���� �ܰ�� " << b.Mbalance << "�� �Դϴ�." << endl;

	newfile << buffer << endl;
	newfile << "    " << b.bankname << "   " << b.username << "   " << b.Mbalance << "       " << b.password << endl;

	atm.close();
	newfile.close();

	::remove("atm�ܰ�.txt");
	if (rename("atm�ܰ�2.txt", "atm�ܰ�.txt") != 0) {
		cout << "�̸� ���� ����" << endl;
	}
	Sleep(2000);
}

/*������ ��й�ȣ ���� �Լ�*/
void bankinfo::SYSTEM_PASSWORD_CHANGE() {
	system("cls");

	bankinfo b;
	int END = 0;
	string check, new1, new2;
	string buffer;
	ifstream atm("atm�ܰ�.txt");
	ofstream newfile("atm�ܰ�2.txt");

	if (atm.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	getline(atm, buffer);
	atm >> b.bankname;
	atm >> b.username;
	atm >> b.Mbalance;
	atm >> b.password;

	do {
		cout << "���� ��й�ȣ�� �Է����ּ��� : ";
		cin >> check;

		if (check.compare(b.password) == 0) {
			while (END != 1) {
				cout << endl << "�� ��й�ȣ�� �Է����ּ��� (4�ڸ� ����) : ";
				cin >> new1;
				if (new1.length() != 4) {
					cout << endl << "��й�ȣ ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl;
				}
				else {
					cout << endl << "�� ��й�ȣ�� �ٽ� �Է����ּ��� (4�ڸ� ����) : ";
					cin >> new2;

					if (new1.compare(new2) == 0) {
						newfile << buffer << endl;
						newfile << "    " << b.bankname << "   " << b.username << "   " << b.Mbalance << "       " << new1 << endl;
						cout << endl << "��й�ȣ�� ����Ǿ����ϴ�." << endl;
						END = 1;
					}
					else {
						cout << endl << "��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl;
					}
				}
			}
		}
		else {
			cout << endl << "��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
		}
	} while (END != 1);

	atm.close();
	newfile.close();

	::remove("atm�ܰ�.txt");
	if (rename("atm�ܰ�2.txt", "atm�ܰ�.txt") != 0) {
		cout << "�̸� ���� ����" << endl;
	}
	Sleep(2000);
}