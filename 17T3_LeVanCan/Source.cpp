#include <iostream>
#include <time.h>
#include <random>
#include <Windows.h>
#include <stdio.h>
using namespace std;
const int maxstone = 9;
static int n, status;
int pile_pre;
struct stonePile
{
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
void player(list root);
int check_stone(list root, int k);
int special_case(list root);
int max_pile(list root, list &max);
void misere_stragety(list &root);
void two_player_mode();
void player_vs_com();
int end_game(list root);

int main()
{
	player_vs_com();
	system("pause");
	return 0;
}

int random(int min, int max)
{
	random_device r;
	uniform_int_distribution<int> distribution(min, max);
	return distribution(r);
}

void create(int n, list &root)
{
	int i = 0;
	while (n > i)
	{
		list temp;
		temp = new stonePile;
		temp->stone = random(1, maxstone);
		temp->next = root;
		root = temp;
		i++;
	}
}

void displayPile(list root)
{
	list temp = root;
	cout << "\n+--------+-------+";
	cout << "\n|   Dong | So soi|";
	cout << "\n+--------+-------+";
	int i = 1;
	while (temp != NULL)
	{
		cout << "\n|\t" << i << "|\t" << temp->stone << "|";
		temp = temp->next;
		i++;
	}
	cout << "\n+--------+-------+" << endl;
}

int gieoxu()
{
	cout << "Chuan bi tung xu";
	for (int i = 0; i < 4; i++)
	{
		Sleep(200);
		cout << ".";
	}
	if (random(0, 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void sodongsoi()
{
	cout << "Nhap so dong soi!" << endl;
	cin >> n;
	pile_pre = n;
	create(n, root);
}

int sum_nim(list root)
{
	int s;
	list temp = root;
	s = temp->stone;
	while (temp->next != NULL)
	{
		temp = temp->next;
		s = s ^ temp->stone;
	}
	return s;
}

void player(list root)
{
	list temp = root;
	int k, i, take;
	do
	{
		cout << "Moi ban chon dong: ";
		cin >> k;
	} while (k <= 0 || k > n || check_stone(root, k) == 0);
	for (i = 1; i < k; i++)
	{
		temp = temp->next;
	}
	do
	{
		cout << "So vien da muon boc: ";
		cin >> take;
	} while (take <= 0 || take > temp->stone);
	temp->stone -= take;
	if (temp->stone == 0) pile_pre--;
}

int check_stone(list root, int k)
{
	int i;
	list tmp = root;
	for (i = 1; i < k; i++)
		tmp = tmp->next;
	if (tmp->stone)
		return 1;
	else
		return 0;
}

int special_case(list root)
{
	int i = 0, j = 0;
	int pos;
	list temp = root;
	while (temp!= NULL)
	{
		if (temp->stone == 1) j++;
		else if (temp->stone >1) 
		{
			pos = i + 1;
		}
		temp = temp->next;
		i++;
	}
	if (j == pile_pre - 1) return pos;
	else return 0;
}

int max_pile(list root, list & max)
{
	list temp;
	int maxpos, i;
	max = root;
	temp = root->next;
	maxpos = 1;
	i = 2;
	while (temp != NULL)
	{
		if (temp->stone > max->stone)
		{
			max = temp;
			maxpos = i;
		}
		temp = temp->next;
		i++;
	}
	return maxpos;
}

void misere_stragety(list & root)
{
	list temp = root;
	int take, s, i;
	i = special_case(root);
	if (i) 
	{
		for (int j = 1; j < i; j++)temp = temp->next;
		if (pile_pre % 2)
		{ 
			take = temp->stone - 1;
		}	
		else
		{
			take = temp->stone;
		}
	}
	else
	{
		s = sum_nim(root);
		i = 1;
		if (s) // sum nim != 0
		{
			while ((temp->stone^s) >= temp->stone)
			{
				temp = temp->next;
				i++;
			}
			take = temp->stone - (temp->stone^s);
		}
		else
		{
			i = max_pile(root, temp);
			take = random(1, temp->stone);
		}
	}
	temp->stone -= take;
	if (temp->stone == 0)
	{
		pile_pre--;
	}
	cout << "Computer take " << take << " from " << i << endl;
}

void two_player_mode()
{
	int end;
	sodongsoi();
	status = gieoxu();
	if (status)
	{
		cout << "A di truoc" << endl;
	}
	else
	{
		cout << "B di truoc" << endl;
	}
	do
	{
		system("cls");
		displayPile(root);
		if (status == 0)
		{
			cout << "Luot cua B" << endl;
		}
		else
		{
			cout << "Luot cua A" << endl;
		}
		player(root);
		end = end_game(root);
		if (!end)
		{
			status = !status;
		}
	} while (!end);
	displayPile(root);
	if (status == 0)
	{
		cout << "A thang!!!" << endl;
	}
	else
	{
		cout << "B thang!!!" << endl;
 	}
}

void player_vs_com()
{
	int end;
	sodongsoi();
	status = gieoxu();
	if (status)
	{
		cout << "Ban di truoc" << endl;
	}
	else
	{
		cout << "Computer di truoc" << endl;
	}
	system("pause");
	do
	{
		system("cls");
		displayPile(root);
		if (status == 0)
		{
			cout << "Luot cua Computer" << endl;
			misere_stragety(root);
			system("pause");
		}
		else
		{
			cout << "Luot cua ban" << endl;
			player(root);
		}
		end = end_game(root);
		if (!end)
		{
			status = !status;
		}
	} while (!end);
	displayPile(root);
	if (status == 0)
	{
		cout << "Ban thang!!!" << endl;
	}
	else
	{
		cout << "Computer thang!!!" << endl;
	}
}

int end_game(list root)
{
	list temp;
	temp = root;
	while (temp != NULL && temp->stone == 0) 
	{
		temp = temp->next;
	}
	if (temp == NULL) return 1;
	return 0;
}
