#include "Header.h"
#include "binary_tree.h"


int operator || (const char* ptr, const Businessman& obj1) {

	int count = min(strlen(ptr), strlen(obj1.get_business()));

	if (count < 2) throw("error symbol\n");

	return strncmp(ptr + 2, obj1.get_business() + 2, count - 1);
}


void operator - (char* str, const Businessman& obj1) {
	if (obj1.get_business() == nullptr || str == nullptr || strlen(str) < 2) throw("error symbol\n");

	char* tmp = str;
	str = new char[strlen(str) + strlen(tmp) + 1]{ '\0' };
	str[0] = tmp[0];
	strcat(str, obj1.get_business());
	strcat(str, tmp + 1);
}




int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	binary_tree* a = new binary_tree;

	a->AddNameClass("Employee");
	a->AddNameClass("Self_Employeed");
	a->AddNameClass("Businessman");
	a->AddNameClass("Translator");

	char var;
	while (1) {

		var = ' ';

		std::cout << "1 - добавить\n2 - закончить" << std::endl;
		std::cin >> var;

		if (var == '2') break;

		std::cout << "¬ведите тип:\n0 - Employee\n1 - Self_Employeed\n2 - Businessman\n3 - Translator\n" << std::endl;
		std::cin >> var;
		getchar();
		Interface* tmp = nullptr;
		if (var == '0') {
			tmp = new Employee;
			tmp->Input();
		}
		if (var == '1') {
			tmp = new Self_Employeed(1);
			tmp->Input();
		}
		if (var == '2') {
			tmp = new Businessman("none", 1);
			tmp->Input();
		}
		if (var == '3') {
			tmp = new Translator("none");
			tmp->Input();
		}

		int ind = 0;
		printf("\n¬ведите индекс добавлени€ ");
		cin >> ind;

		if (tmp != nullptr) a->InsertAt(tmp, ind);
	}

	while (1) {

		var = ' ';

		std::cout << "1 - удалить\n2 - закончить" << std::endl;
		std::cin >> var;

		if (var == '2') break;

		int ind = 0;
		printf("\n¬ведите индекс удалени€ ");
		cin >> ind;

		a->RemoveAt(ind);
	}

	a->display();
	a->Serialize("data.txt");

	delete a;

	binary_tree b;
	b.Deserialize("data.txt");

	return 0;
}
