#include <iostream>
#include <time.h>
#include <random>
#include <Windows.h>
using namespace std;
const int maxstone = 30;
struct stonePile
{
	int stone; // stone = soi
	stonePile *next;
};

typedef stonePile *list;
list root = NULL;
void create(int i, list &root);
void displayPile(list root);
int gieoxu();
void sodongsoi();
int sum_nim(list root);
int main()
{
	sodongsoi();
	displayPile(root);
	system("pause");
	return 0;
}

void create(int n, list &root)
{
	int i = 0;
	while (n > i)
	{
		random_device r;
		uniform_int_distribution<int> distribution(1, maxstone);
		list temp;
		temp = new stonePile;
		srand(time(NULL));
		temp->stone = distribution(r);
		temp->next = root;
		root = temp;
		i++;
	}
}

void displayPile(list root)
{
	list temp = root;
	while (temp != NULL)
	{
		cout << temp->stone << endl;
		temp = temp->next;
	}
}

int gieoxu()
{
	random_device r;
	uniform_int_distribution<int> distribution(0, 1);
	cout << "Chuan bi tung xu";
	for (int i = 0; i < 4; i++)
	{
		Sleep(1);
		cout << ".";
	}
	if (distribution(r))
	{
		cout << "\nBan di truoc" << endl;
		return 1;
	}
	else
	{
		cout << "\nMay di truoc" << endl;
		return 0;
	}
}

void sodongsoi()
{
	cout << "Nhap so dong soi!" << endl;
	int n;
	cin >> n;
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
