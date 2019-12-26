#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;
const int maxstone = 10;
int n, status;
int pile_pre;
struct stonePile {
	int stone; // stone = soi
	stonePile *next;
};

typedef stonePile *list;
list root = NULL;

int random(int min, int max);
void create(int i, list &root);
void displayPile(list root);
int gieoxu();
void sodongsoi();
int sum_nim(list root);
void player_turn(list root);
int check_stone(list root, int k);
int special_case(list root);
int max_pile(list root, list &max);
void computer_turn(list &root);
void two_player_mode();
void player_vs_com();
int end_game(list root);
void menu();
void guide();

int main() {
	srand(time(NULL));
	int mode;
	do {
		menu();
		cin >> mode;
		switch (mode) {
		case 1:
			system("cls");
			player_vs_com();
			root = NULL;
			break;
		case 2:
			system("cls");
			two_player_mode();
			root = NULL;
			break;
		case 3:
			guide();
			break;
		default:
			break;
		}
	} while (mode);
	system("pause");
	return 0;
}

int random(int min, int max) {
	return rand() % max + min;
}

void create(int n, list &root) {
	int i = 0;
	while (n > i) {
		list temp;
		temp = new stonePile;
		temp->stone = random(1, maxstone);
		temp->next = root;
		root = temp;
		i++;
	}
}

void displayPile(list root) {
	list temp = root;
	cout << "\n+---------------+---------------+";
	cout << "\n|     Dong      |     So soi    |";
	cout << "\n+---------------+---------------+";
	int i = 1;
	while (temp != NULL) {
		cout << "\n|\t" << i << "\t|\t" << temp->stone << "\t|";
		temp = temp->next;
		i++;
	}
	cout << "\n+---------------+---------------+" << endl;
}

int gieoxu() {
	cout << "Chuan bi tung xu";
	for (int i = 0; i < 4; i++) {
		Sleep(200);
		cout << ".";
	}
	if (rand()%2 == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void sodongsoi() {
	cout << "Nhap so dong soi!" << endl;
	cin >> n;
	pile_pre = n;
	create(n, root);
}

int sum_nim(list root) {
	int s;
	list temp = root;
	s = temp->stone;
	while (temp->next != NULL) {
		temp = temp->next;
		s = s ^ temp->stone;
	}
	return s;
}

void player_turn(list root) {
	list temp = root;
	int k, i, take;
	do {
		cout << "Moi ban chon dong: ";
		cin >> k;
	} while (k <= 0 || k > n || check_stone(root, k) == 0);
	for (i = 1; i < k; i++) {
		temp = temp->next;
	}
	do {
		cout << "So vien da muon boc: ";
		cin >> take;
	} while (take <= 0 || take > temp->stone);
	temp->stone -= take;
	if (temp->stone == 0)
		pile_pre--;
}

int check_stone(list root, int k) {
	int i;
	list tmp = root;
	for (i = 1; i < k; i++)
		tmp = tmp->next;
	if (tmp->stone)
		return 1;
	else
		return 0;
}

int special_case(list root) {
	int i = 0, j = 0;
	int pos = 0;
	list temp = root;
	while (temp != NULL) {
		if (temp->stone == 1)
			j++;
		else if (temp->stone > 1) {
			pos = i + 1;
		}
		temp = temp->next;
		i++;
	}
	if (j == pile_pre - 1)
		return pos;
	else
		return 0;
}

int max_pile(list root, list &max) {
	list temp;
	int maxpos, i;
	max = root;
	temp = root->next;
	maxpos = 1;
	i = 2;
	while (temp != NULL) {
		if (temp->stone > max->stone) {
			max = temp;
			maxpos = i;
		}
		temp = temp->next;
		i++;
	}
	return maxpos;
}

void computer_turn(list &root) {
	list temp = root;
	int take, s, i;
	i = special_case(root);
	if (i) {
		for (int j = 1; j < i; j++)
			temp = temp->next;
		if (pile_pre % 2) {
			take = temp->stone - 1;
		}
		else {
			take = temp->stone;
		}
	}
	else {
		s = sum_nim(root);
		i = 1;
		if (s) {
			while ((temp->stone ^ s) >= temp->stone) {
				temp = temp->next;
				i++;
			}
			take = temp->stone - (temp->stone ^ s);
		}
		else {
			i = max_pile(root, temp);
			take = random(1, temp->stone);
		}
	}
	temp->stone -= take;
	if (temp->stone == 0) {
		pile_pre--;
	}
	cout << "Computer take " << take << " from " << i << endl;
}

void two_player_mode() {
	int end;
	sodongsoi();
	status = gieoxu();
	if (status) {
		cout << "A di truoc" << endl;
	}
	else {
		cout << "B di truoc" << endl;
	}
	do {
		displayPile(root);
		if (status == 0) {
			cout << "Luot cua B" << endl;
		}
		else {
			cout << "Luot cua A" << endl;
		}
		player_turn(root);
		end = end_game(root);
		if (!end) {
			status = !status;
		}
	} while (!end);
	displayPile(root);
	if (status == 0) {
		cout << "A thang!!!" << endl;
	}
	else {
		cout << "B thang!!!" << endl;
	}
}

void player_vs_com() {
	int end;
	sodongsoi();
	status = gieoxu();
	if (status) {
		cout << "Ban di truoc" << endl;
	}
	else {
		cout << "Computer di truoc" << endl;
	}
	system("pause");
	do {
		displayPile(root);
		if (status == 0) {
			cout << "Luot cua Computer" << endl;
			computer_turn(root);
			system("pause");
		}
		else {
			cout << "Luot cua ban" << endl;
			player_turn(root);
		}
		end = end_game(root);
		if (!end) {
			status = !status;
		}
	} while (!end);
	displayPile(root);
	if (status == 0) {
		cout << "Ban thang!!!" << endl;
	}
	else {
		cout << "Computer thang!!!" << endl;
	}
}

int end_game(list root) {
	list temp;
	temp = root;
	while (temp != NULL && temp->stone == 0) {
		temp = temp->next;
	}
	if (temp == NULL) return 1;
	return 0;
}

void menu() {
	cout << "Main menu:" << endl;
	cout << "\n1. One player";
	cout << "\n2. Two players";
	cout << "\n3. Guide";
	cout << "\n0. Exit game";
	cout << "\n Lua chon: ";
}

void guide() {
	fstream f;
	f.open("guide.txt", ios::in);
	system("cls");
	string line;
	while (!f.eof())
	{
		getline(f, line);
		cout << line << endl;
	}
	f.close();
}