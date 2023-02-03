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
	void ACCOUNT_MAKE(); //계좌생성 함수
	int DEPOSIT(); //입금 함수
	int WITHDRAW();//출금 함수
	int SEND();//송금 함수
	int BALANCE_CHECK();//잔액조회 함수
	int PASSWORD_CHANGE();//비밀번호 변경 함수
	void ACCOUNT_LOCK(string& acc);//계좌 정지 함수
	int LOCK_CHECK(string& acc); //계좌 정지 상태 확인 함수
	int ACCOUNT_CHECK(string& acc); //계좌 유무 확인 함수

	void PASSWORD_CHECK(); //관리자 메뉴 비밀번호 확인 함수
	void SYSTEM_MENU(); // 관리자 메뉴 함수
	void BANKADD(); //은행 추가 함수
	void ACCOUNT_UNLOCK(); //계좌 정지 해제 함수
	void ATM_CHECK(); //ATM 잔고 확인 함수
	void ATM_ADD(); //ATM 잔고 추가 함수
	void SYSTEM_PASSWORD_CHANGE();// 관리자 비밀번호 변경 함수
};//은행 기본 정보

int main() {
	int menu_choice;
	bankinfo b;

	do {
		system("cls");
		cout << "=======ATM프로그램=======" << endl;
		cout << "1. 입금\n2. 출금\n3. 송금\n4. 잔액조회\n5. 계좌생성\n6. 비밀번호 변경\n7. 관리자 메뉴\n0. 프로그램 종료" << endl;
		cout << "=========================\n>> ";
		cin >> menu_choice;
		cout << endl;

		switch (menu_choice) {
		case 0: //종료
			cout << "ATM 프로그램을 종료합니다." << endl;
			break;
		case 1: //입금
			b.DEPOSIT();
			break;
		case 2: //출금
			b.WITHDRAW();
			break;
		case 3: //송금
			b.SEND();
			break;
		case 4: //잔액 조회
			b.BALANCE_CHECK();
			break;
		case 5: //계좌 생성
			b.ACCOUNT_MAKE();
			break;
		case 6: //비밀번호 변경
			b.PASSWORD_CHANGE();
			break;
		case 7: //관리자 메뉴
			b.PASSWORD_CHECK();
			break;
		default: //잘못된 수를 입력했을 때
			cout << "0~7 사이의 수를 입력해주세요." << endl;
			Sleep(1000);
			break;
		}

	} while (menu_choice != 0);

	return 0;
}

/*계좌생성함수*/
 void bankinfo::ACCOUNT_MAKE() {
	 system("cls");
	bankinfo b;
	string buffer;
	int offset;
	int count1 = 0;
	int count2 = 0;

	cout << "[계좌생성]" << endl;
	cout << "\n===등록되어 있는 은행===" << endl;
	ifstream bank;
	bank.open("은행.txt");

	if (bank.is_open())
	{
		while (getline(bank, buffer)) {
			if ((offset = buffer.find("은행", 0)) != string::npos) {
				cout << buffer << endl;
				count2++;
			}

		}
		cout << "========================" << endl;
		cout << endl;

		bank.close();

		cout << "은행 이름을 입력하시오: ";
		cin >> b.bankname;

		ifstream bank("은행.txt");
		if (!bank) {
			cerr << "파일 오픈 실패" << endl;
			exit(1);
		}

		ofstream newfile("은행 2.txt");
		if (!newfile) {
			cerr << "파일 오픈 실패" << endl;
			exit(1);
		}

		while (getline(bank, buffer)) {
			if (b.bankname == buffer) {
				newfile << buffer << endl;

				cout << "이름 : ";
				cin >> b.username;

				srand(time(NULL));
				int p = 9, c, d;
				c = (int)pow(10, 8);
				d = (int)pow(10, 8);

				cout << "계좌번호 랜덤 생성" << endl;

				b.number = (rand() % p + 1) * d + (rand() % c);
				cout << "\n계좌번호가 생성되었습니다.\n\n";
				cout << "생성된 계좌번호 : " << b.number << endl;

				newfile << b.number << endl;
			}
			else {
				if ((offset = buffer.find("은행", 0)) != string::npos) {
					count1++;
				}
				newfile << buffer << endl;
			}
		}

		if(count1==count2) {
			cout << "해당 은행은 등록되어 있지 않은 은행입니다.\n\n";
			Sleep(2500);
			bank.close();
			newfile.close();
			::remove("은행.txt");
			if (rename("은행 2.txt", "은행.txt") != 0) {
				cout << "이름 변경 실패\n";
			}
		}

		while (1) {
			cout << "비밀번호 : ";
			cin >> b.password;

			if (b.password.length() != 4) {
				cout << "\n비밀번호는 4자리 숫자로 입력해주시길 바랍니다.\n\n";
			}
			else {
				break;
			}
		}

		cout << "계좌 생성을 완료하였습니다.\n";

		Sleep(2000);

		bank.close();
		newfile.close();


		::remove("은행.txt");
		if (rename("은행 2.txt", "은행.txt") != 0) {
			cout << "이름 변경 실패\n";
		}
	}
	else {
		cout << "파일을 열 수 없습니다." << endl;
	}

	system("cls");
	cout << "======================\n\n";
	cout << "은행: " << b.bankname << endl;
	cout << "계좌번호: " << b.number << endl;
	cout << "이름: " << b.username << endl;
	cout << "비밀번호: " << b.password << endl << endl;
	cout << "======================\n";

	fstream account("계좌정보.txt", ios::app);
	if (!account) {
		cerr << "파일 오픈 실패" << endl;
		exit(1);
	}

	account << b.bankname << " " << b.username << " " << b.number << " " << b.password << "       " << "0" << endl;

	account.close();

	system("pause");
}

/*입금 함수*/
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

	 cout << "[입금]\n";
	 cout << "계좌번호 : ";
	 cin >> acc;

	 if (LOCK_CHECK(acc) == 1) {
		 return 0;
	 }

	 if (ACCOUNT_CHECK(acc) == 1) {
		 return 0;
	 }

	 ifstream account("계좌정보.txt");
	 if (account.fail()) {
		 cerr << "파일 오픈 실패" << endl;
		 exit(1);
	 }

	 ofstream newfile("계좌정보 2.txt");
	 if (newfile.fail()) {
		 cerr << "파일 오픈 실패" << endl;
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
				 cout << "비밀번호 : ";
				 cin >> pw;
				 if (a.password == pw) {
					 cout << "입금금액 : ";
					 cin >> balance;

					 if (balance <= 0) {
						 cout << "0원 이상의 금액을 입력해주세요." << endl;
						 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						 END = 1;
					 }

					 a.Mbalance += balance;

					 cout << "입금되었습니다.\n";

					 Sleep(2000);

					 system("cls");
					 cout << "======= 명세표 =======\n";
					 struct tm* t;
					 time_t timer;
					 timer = time(NULL);
					 t = localtime(&timer);

					 cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

					 cout << "은행: " << a.bankname << endl;
					 cout << "입금계좌: " << a.account << endl;
					 cout << "성명: " << a.username << endl;
					 cout << "입금금액: " << balance << endl;
					 cout << "현재잔액: " << a.Mbalance << endl;
					 cout << "======================\n";

					 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;

					 END = 1;
				 }
				 else {
					 errcount++;
					 cout << "비밀번호 오류. 다시 입력해주시길 바랍니다.\n";
					 if (errcount == 3) {
						 cout << "비밀번호 " << errcount << "회 오류. 계좌가 정지되었습니다.\n\n";
						 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						 ACCOUNT_LOCK(acc);
						 Sleep(2000);
						 END = 1;
					 }
					 else
						 cout << "비밀번호 " << errcount << "회 오류. 3회 오류시 계좌가 정지됩니다.\n";
				 }
			 }
		 }
		 else {
			 newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
		 }
	 }
 
	account.close();
	newfile.close();

	::remove("계좌정보.txt");
	if (rename("계좌정보 2.txt", "계좌정보.txt") != 0) {
		cout << "이름 변경 실패\n";
	}

	system("pause");
}

/*출금 함수*/
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

	cout << "[출금]\n";
	cout << "계좌번호 : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("계좌정보.txt");
	if (account.fail()) {
		cerr << "파일 오픈 실패" << endl;
		exit(1);
	}

	ofstream newfile("계좌정보 2.txt");
	if (newfile.fail()) {
		cerr << "파일 오픈 실패" << endl;
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
				cout << "비밀번호 : ";
				cin >> pw;
				if (a.password == pw) {
					cout << "현재 잔액 : " << a.Mbalance << endl << endl;
					cout << "출금금액 : ";
					cin >> balance;

					if (balance <= 0) {
						cout << "0원 이상의 금액을 입력해주세요." << endl;
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						END = 1;
					}

					if (a.Mbalance - balance >= 0) {
						a.Mbalance -= balance;
						cout << "출금되었습니다.\n";

						Sleep(2000);

						system("cls");
						cout << "======= 명세표 =======\n";
						struct tm* t;
						time_t timer;
						timer = time(NULL);
						t = localtime(&timer);

						cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

						cout << "은행: " << a.bankname << endl;
						cout << "출금계좌: " << a.account << endl;
						cout << "성명: " << a.username << endl;
						cout << "출금금액: " << balance << endl;
						cout << "현재잔액: " << a.Mbalance << endl;
						cout << "======================\n";

						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;

						END = 1;
					}
					else {
						cout << "잔액이 부족합니다." << endl;
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						Sleep(2000);
						END = 1;
					}
				}
				else {
					errcount++;
					cout << "비밀번호 오류. 다시 입력해주시길 바랍니다.\n";
					if (errcount == 3) {
						cout << "비밀번호 " << errcount << "회 오류. 계좌가 정지되었습니다.\n\n";
						newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
						ACCOUNT_LOCK(acc);
						Sleep(2000);
						END = 1;
					}
					else
						cout << "비밀번호 " << errcount << "회 오류. 3회 오류시 계좌가 정지됩니다.\n";
				}
			}
		}
		else {
			newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
		}
	}

	account.close();
	newfile.close();

	::remove("계좌정보.txt");
	if (rename("계좌정보 2.txt", "계좌정보.txt") != 0) {
		cout << "이름 변경 실패\n";
	}

	system("pause");
}

/*송금 함수*/
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

	cout << "[송금]\n";
	cout << "타 은행으로 송금 시 수수료 500원이 부과됩니다.\n";
	cout << "계좌번호 : ";
	cin >> acc1;

	if (LOCK_CHECK(acc1) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc1) == 1) {
		return 0;
	}

	ifstream account("계좌정보.txt");
	if (account.fail()) {
		cerr << "파일 오픈 실패" << endl;
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
				cout << "비밀번호 : ";
				cin >> pw;
				if (a.password == pw) {
					cout << "현재 잔액 : " << a.Mbalance << endl << endl;
					cout << "송금 금액 : ";
					cin >> balance;

					if (balance <= 0) {
						cout << "1원 이상의 금액을 입력해주세요." << endl;
						END = 1;
					}

					else {
						if (a.Mbalance - balance >= 0) {
							cout << "입금 계좌 : ";
							cin >> acc2;
							if (acc1 == acc2) {
								cout << "송금 계좌와 입금 계좌가 일치합니다." << endl;
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
												cout << "수수료 500원이 부과됩니다." << endl;
											}
											else {
												cout << "잔액이 부족합니다. (타 은행으로 송금 시 수수료 500원 부과)" << endl;
												a.Mbalance += balance;
												END = 1;
												Sleep(1000);
												break;
											}
										}

										cout << "송금되었습니다." << endl;
										Sleep(2000);

										system("cls");
										printf("======= 명세표 =======\n");
										struct tm* t;
										time_t timer;
										timer = time(NULL);
										t = localtime(&timer);

										cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << "    " << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << endl;

										cout << "은행: " << a.bankname << endl;
										cout << "송금 계좌: " << a.account << endl;
										cout << "예금주: " << a.username << endl << endl;
										cout << "입금 계좌: " << x.account << endl;
										cout << "성명: " << x.username << endl;
										cout << "보낸금액: " << balance << endl;
										cout << "현재잔액: " << a.Mbalance << endl;
										cout << "======================\n";

										END = 1;
									}
								}
							}
						}
						else {
							cout << "잔액이 부족합니다." << endl;
							Sleep(2000);
							END = 1;
						}
					}
				}
				else {
					errcount++;
					cout << "비밀번호 오류. 다시 입력해주시길 바랍니다.\n";
					if (errcount == 3) {
						cout << "비밀번호 " << errcount << "회 오류. 계좌가 정지되었습니다.\n\n";
						ACCOUNT_LOCK(acc1);
						Sleep(2000);
						END = 1;
					}
					else
						cout << "비밀번호 " << errcount << "회 오류. 3회 오류시 계좌가 정지됩니다.\n";
				}

			}
		}
		else {
			continue;
		}
	}

	account.close();

	ofstream newfile("계좌정보 2.txt");
	if (newfile.fail()) {
		cerr << "파일 오픈 실패" << endl;
		exit(1);
	}
	newfile << buffer << endl;


	for (bankinfo& a : binfo) {
		newfile << a.bankname << " " << a.username << " " << a.account << " " << a.password << "       " << a.Mbalance << endl;
	}
	newfile.close();

	::remove("계좌정보.txt");
	if (rename("계좌정보 2.txt", "계좌정보.txt") != 0) {
		cout << "이름 변경 실패\n";
	}

	system("pause");
}

/*잔액조회 함수*/
int bankinfo::BALANCE_CHECK(void) {
	system("cls");
	string acc;
	bankinfo b;
	vector<bankinfo> binfo;

	cout << "[잔액조회]" << endl;
	cout << "잔액 조회할 계좌를 입력하세요 : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("계좌정보.txt");
	if (account.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	while (!account.eof()) {
		account >> b.bankname >> b.username >> b.account >> b.password >> b.balance;
		binfo.push_back(b);
	}

	for (bankinfo& a : binfo) {
		if (a.account == acc) {
			cout << "현재 잔액 : " << a.balance << endl;
			account.close();
			break;
		}
	}

	system("pause");

	while (binfo.empty() != true) {
		binfo.pop_back();
	}
}

/*비밀번호 변경 함수*/
int bankinfo::PASSWORD_CHANGE() {
	system("cls");
	int END = 0, errcount = 0;
	string acc, pwcheck, new1, new2;
	bankinfo b;
	vector<bankinfo> binfo;

	cout << "[비밀번호 변경]" << endl;
	cout << "비밀번호를 변경할 계좌를 입력하세요 : ";
	cin >> acc;

	if (LOCK_CHECK(acc) == 1) {
		return 0;
	}

	if (ACCOUNT_CHECK(acc) == 1) {
		return 0;
	}

	ifstream account("계좌정보.txt");
	ofstream newfile("계좌정보2.txt");

	if (account.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "파일 열기 실패" << endl;
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
				cout << "현재 비밀번호를 입력해주세요: ";
				cin >> pwcheck;

				if (a.password == pwcheck) {
					while (END != 1) {
						cout << "\n새 비밀번호를 입력해주세요 (4자리 숫자) : ";
						cin >> new1;

						if (new1.length() != 4) {
							cout << endl << "비밀번호 형식이 맞지 않습니다. 다시 입력해주세요." << endl;
						}
						else {
							cout << endl << "새 비밀번호를 다시 입력해주세요 (4자리 숫자) : ";
							cin >> new2;

							if (new1.compare(new2) == 0) {
								a.password = new1;
								END = 1;
							}
							else {
								cout << "\n비밀번호가 일치하지 않습니다. 다시 입력해주세요." << endl;
							}
						}
					}
				}
				else {
					errcount++;
					cout << "비밀번호 오류. 다시 입력해주시길 바랍니다." << endl;
					if (errcount == 3) {
						cout << "비밀번호 " << errcount << "회 오류. 계좌가 정지되었습니다." << endl << endl;
						ACCOUNT_LOCK(acc);
						Sleep(2000);
						END = 1;
					}
					else {
						cout << "비밀번호 " << errcount << "회 오류. 3회 오류시 계좌가 정지됩니다." << endl << endl;
					}
				}
			} while (END != 1);
		}
	}

	cout << endl << "비밀번호가 변경되었습니다." << endl;

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

	::remove("계좌정보.txt");
	if (rename("계좌정보2.txt", "계좌정보.txt") != 0) {
		cout << "이름 변경 실패" << endl;
	}
	system("pause");
	return 0;
}

/*계좌 정지 함수*/
void bankinfo::ACCOUNT_LOCK(string& acc) {
	string buffer;
	int offset;
	ifstream bank("은행.txt");
	ofstream newfile("은행2.txt");

	if (bank.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "파일 열기 실패" << endl;
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

	::remove("은행.txt");
	if (rename("은행2.txt", "은행.txt") != 0) {
		printf("이름 변경 실패\n");
	}
}

/*계좌 정지 상태 확인 함수*/
int bankinfo::LOCK_CHECK(string& acc) {
	int k = 0;
	int offset;
	string buffer;
	ifstream bank("은행.txt");
	if (bank.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	while (getline(bank, buffer)) {
		if ((offset = buffer.find(acc, 0)) != string::npos) {
			if ((offset = buffer.find("x", 0)) != string::npos) {
				cout << "해당 계좌는 정지 상태입니다." << endl;
				Sleep(2000);
				k = 1;
			}
		}
	}

	bank.close();
	return k;
}

/*계좌 유무 확인 함수*/
int bankinfo::ACCOUNT_CHECK(string& acc) {
	int count1 = 0, count2 = 0;
	int offset;
	string buffer;
	ifstream bank("은행.txt");
	if (bank.fail()) {
		cerr << "파일 열기 실패" << endl;
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
		cout << "등록되어 있지 않은 계좌번호입니다." << endl;
		Sleep(2000);
		bank.close();
		return 1;
	}
}

/*관리자 메뉴 비밀번호 확인 함수*/
void bankinfo::PASSWORD_CHECK() {

	system("cls");
	bankinfo b;
	string buffer1, buffer2;
	string check;
	int offset;
	int count = 0;
	ifstream atm("atm잔고.txt");

	if (atm.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	getline(atm, buffer1);
	getline(atm, buffer2);

	do {
		cout << "관리자 메뉴 비밀번호를 입력하세요 : ";
		cin >> check;

		if ((offset = buffer2.find(check, 0)) != string::npos) {
			atm.close();
			b.SYSTEM_MENU();
			break;
		}
		else {
			cout << endl << "비밀번호가 일치하지 않습니다. 다시 입력해주세요." << endl;
			cout << "비밀번호 3회 오류시 메인메뉴로 돌아갑니다." << endl << endl;
			count++;
			if (count == 3) {
				Sleep(1000);
				break;
			}
		}
	} while (1);

	atm.close();
}

/*관리자 메뉴 함수*/
void bankinfo::SYSTEM_MENU() {
	bankinfo b;
	int choice;

	do {
		system("cls");
		cout << "=======관리자 메뉴=======" << endl;
		cout << "1. 은행 추가\n2. 계좌 정지 해제\n3. ATM잔고 확인\n4. ATM잔고 보충\n5. 관리자 비밀번호 변경\n0. 메인메뉴" << endl;
		cout << "=========================\n>> ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 0: //메인메뉴
			cout << "ATM 프로그램을 종료합니다." << endl;
			break;
		case 1: //은행 추가
			b.BANKADD();
			break;
		case 2: //계좌 정지 해제
			b.ACCOUNT_UNLOCK();
			break;
		case 3: //ATM잔고 확인
			b.ATM_CHECK();
			break;
		case 4: //ATM잔고 보충
			b.ATM_ADD();
			break;
		case 5: //관리자 비밀번호 변경
			b.SYSTEM_PASSWORD_CHANGE();
			break;
		default: //잘못된 수를 입력했을 때
			cout << "0~5 사이의 수를 입력해주세요." << endl;
			Sleep(1000);
			break;
		}

	} while (choice != 0);
}

/*은행 추가 함수*/
void bankinfo::BANKADD() {
	system("cls");

	string bank_add;
	ofstream bank("은행.txt", ios::app);

	if (bank.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	cout << "추가할 은행을 입력해주세요 : ";
	cin >> bank_add;
	bank << bank_add << endl;
	cout << bank_add << "이 추가되었습니다." << endl;

	bank.close();
	Sleep(2000);
}

/*계좌 정지 해제 함수*/
void bankinfo::ACCOUNT_UNLOCK() {
	system("cls");

	bankinfo b;
	int offset;
	int count1 = 0, count2 = 0;
	string buffer;
	string account;
	ifstream bank("은행.txt");
	ofstream newfile("은행2.txt");

	if (bank.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	cout << "정지를 해제할 계좌번호를 입력하세요 : ";
	cin >> account;

	while (getline(bank, buffer)) {
		if ((offset = buffer.find(account, 0)) != string::npos) {
			if ((offset = buffer.find("x", 0)) != string::npos) {
				newfile << account << endl;
				cout << account << " 계좌가 해제되었습니다." << endl;
			}
			else {
				cout << "해당 계좌는 정지 상태가 아닙니다." << endl;
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
		cout << account << " 계좌는 없는 계좌입니다." << endl;
	}

	bank.close();
	newfile.close();

	::remove("은행.txt");
	if (rename("은행2.txt", "은행.txt") != 0) {
		cout << "이름 변경 실패" << endl;
	}
	Sleep(2000);
}

/*ATM 잔고 확인 함수*/
void bankinfo::ATM_CHECK() {
	system("cls");

	bankinfo b;
	string buffer1;
	ifstream atm("atm잔고.txt");

	if (atm.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	getline(atm, buffer1);
	atm >> b.bankname >> b.username >> b.balance >> b.password;

	cout << "ATM의 현재 잔고는" << b.balance << "원 입니다." << endl;

	atm.close();
	Sleep(2000);
}

/*ATM 잔고 추가 함수*/
void bankinfo::ATM_ADD() {
	system("cls");

	bankinfo b;
	string buffer;
	int money;
	ifstream atm("atm잔고.txt");
	ofstream newfile("atm잔고2.txt");

	if (atm.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	getline(atm, buffer);
	atm >> b.bankname;
	atm >> b.username;
	atm >> b.Mbalance;
	atm >> b.password;
	cout << "추가할 금액을 입력하세요 : ";
	cin >> money;
	b.Mbalance += money;
	cout << "ATM의 현재 잔고는 " << b.Mbalance << "원 입니다." << endl;

	newfile << buffer << endl;
	newfile << "    " << b.bankname << "   " << b.username << "   " << b.Mbalance << "       " << b.password << endl;

	atm.close();
	newfile.close();

	::remove("atm잔고.txt");
	if (rename("atm잔고2.txt", "atm잔고.txt") != 0) {
		cout << "이름 변경 실패" << endl;
	}
	Sleep(2000);
}

/*관리자 비밀번호 변경 함수*/
void bankinfo::SYSTEM_PASSWORD_CHANGE() {
	system("cls");

	bankinfo b;
	int END = 0;
	string check, new1, new2;
	string buffer;
	ifstream atm("atm잔고.txt");
	ofstream newfile("atm잔고2.txt");

	if (atm.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}
	if (newfile.fail()) {
		cerr << "파일 열기 실패" << endl;
		exit(1);
	}

	getline(atm, buffer);
	atm >> b.bankname;
	atm >> b.username;
	atm >> b.Mbalance;
	atm >> b.password;

	do {
		cout << "현재 비밀번호를 입력해주세요 : ";
		cin >> check;

		if (check.compare(b.password) == 0) {
			while (END != 1) {
				cout << endl << "새 비밀번호를 입력해주세요 (4자리 숫자) : ";
				cin >> new1;
				if (new1.length() != 4) {
					cout << endl << "비밀번호 형식이 맞지 않습니다. 다시 입력해주세요." << endl;
				}
				else {
					cout << endl << "새 비밀번호를 다시 입력해주세요 (4자리 숫자) : ";
					cin >> new2;

					if (new1.compare(new2) == 0) {
						newfile << buffer << endl;
						newfile << "    " << b.bankname << "   " << b.username << "   " << b.Mbalance << "       " << new1 << endl;
						cout << endl << "비밀번호가 변경되었습니다." << endl;
						END = 1;
					}
					else {
						cout << endl << "비밀번호가 일치하지 않습니다. 다시 입력해주세요." << endl;
					}
				}
			}
		}
		else {
			cout << endl << "비밀번호가 일치하지 않습니다. 다시 입력해주세요." << endl << endl;
		}
	} while (END != 1);

	atm.close();
	newfile.close();

	::remove("atm잔고.txt");
	if (rename("atm잔고2.txt", "atm잔고.txt") != 0) {
		cout << "이름 변경 실패" << endl;
	}
	Sleep(2000);
}