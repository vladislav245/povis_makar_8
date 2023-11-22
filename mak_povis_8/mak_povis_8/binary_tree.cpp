#include <stack>
#include "binary_tree.h"



std::vector<std::string> storage;





//в insertAt находим путь и создаем его 
//в binary_tree проходим по этому пути и делаем вставку элемента
void binary_tree::class_ptr::find_path(int ind, string* path) {


	int two = 1; //все элементы на этом уровне
	int all = 0; //все элементы дерева до этого уровня (не включительно)
	int lvl = 0; //итоговый уровень
	//ищем ее уровень
	while (two + all < (ind + 1)) {
		all += two;
		two *= 2;
		lvl++;
	}


	while (ind > 0) {

		if (ind % 2 == 0) *path += "R";
		else *path += "L";
		//необходимый сдвиг
		if (ind % 2 == 0) --ind;

		//1
		//N - кол-во элементов правее данного элемента на этой строке
		int N = (ind - (pow(2, lvl) - 1)) / 2;
		//2
		//номер след. элемента, который ссылался на наше число
		ind -= ((N * 2) + (pow(2, lvl - 1) - N));

		lvl--;
	}

	reverse(path->begin(), path->end());
}

int binary_tree::class_ptr::find_ind(string* path) {

	int result = 0;
	auto it = path->begin();


	while (it != path->end()) {
		result *= 2;
		if (*it == 'L') result += 1;
		else result += 2;
		++it;
	}
	return result;
}

void binary_tree::InsertAt(Interface* obj, int index) {

	if (index == 0) {
		if (cl_ptr == nullptr) cl_ptr = new class_ptr;
		cl_ptr->obj = obj;
		return;
	}

	string path;
	cl_ptr->find_path(index, &path);
	class_ptr* ptr = cl_ptr;

	for (auto it = path.begin(); it != path.end(); ++it) {

		if (*it == 'L') {
			if (ptr->left == nullptr && (it + 1) != path.end()) return;
			else if (ptr->left == nullptr && (it + 1) == path.end()) {
				ptr->left = new class_ptr(obj, index);
				//ptr->left->left = nullptr;
				//ptr->left->right = nullptr;
				//ptr->left->obj = obj;
			}
			else if (ptr->left != nullptr && (it + 1) == path.end()) ptr->left->obj = obj;
			ptr = ptr->left;
		}
		else {
			if (ptr->right == nullptr && (it + 1) != path.end()) return;
			else if (ptr->right == nullptr && (it + 1) == path.end()) {
				ptr->right = new class_ptr(obj, index);
				/*ptr->right->left = nullptr;
				ptr->right->right = nullptr;
				ptr->right->obj = obj;*/
			}
			else if (ptr->right != nullptr && (it + 1) == path.end()) ptr->right->obj = obj;

			ptr = ptr->right;
		}
	}
}

void binary_tree::RemoveAt(int index) {

	class_ptr* ptr = cl_ptr;
	class_ptr* next = ptr;
	if (index != 0) {

		string path;
		cl_ptr->find_path(index, &path);

		//доходим до опред. элемента или останавливаем если до него нельзя дойти
		for (auto it = path.begin(); it != path.end(); ++it) {
			if (*it == 'L') {
				//если дошли до конца, а путь до элемента незакончен, то ошибка
				if (ptr->left == nullptr && (it + 1) != path.end()) return;
				//если дошли до конца, а путь до элемента незакончен, то ошибка
				else if (ptr->left == nullptr && (it + 1) == path.end()) {
					return;
				}
				//если дошли до элемента
				else if (ptr->left != nullptr && (it + 1) == path.end()) {
					next = ptr->left;
					break;
				}
				ptr = ptr->left;
			}
			else {
				//если дошли до конца, а путь до элемента незакончен, то ошибка
				if (ptr->right == nullptr && (it + 1) != path.end()) return;
				//если дошли до конца, а путь до элемента незакончен, то ошибка
				else if (ptr->right == nullptr && (it + 1) == path.end()) {
					return;
				}
				//если дошли до элемента
				else if (ptr->right != nullptr && (it + 1) == path.end()) {
					next = ptr->right;
					break;
				}

				ptr = ptr->right;
			}

		}
	}

	//если нет путей
	if (next->left == nullptr && next->right == nullptr) {
		if (ptr->left == next) ptr->left = nullptr;
		else if (ptr->right == next) ptr->right = nullptr;
		delete next;
	}
	//если есть оба путь
	else if (next->left != nullptr && next->right != nullptr) {
		class_ptr* tmp = next;
		class_ptr* next_tmp;
		while (tmp->left != nullptr || tmp->right != nullptr) {
			if (tmp->right != nullptr) {
				if (tmp->right->left == nullptr && tmp->right->right == nullptr) {
					next_tmp = tmp;
					tmp = tmp->right;
					next_tmp->right = nullptr;
					break;
				}
				tmp = tmp->right;
			}
			if (tmp->left != nullptr) {
				if (tmp->left->left == nullptr && tmp->left->right == nullptr) {
					next_tmp = tmp;
					tmp = tmp->left;
					next_tmp->left = nullptr;
					break;
				}
				tmp = tmp->left;
			}
		}
		next->obj = tmp->obj;
		//next->ind = index;
	}
	//если есть один путь
	else if (next->left != nullptr || next->right != nullptr) {
		if (next->left != nullptr) {
			next->obj = next->left->obj;
			next->right = next->left->right;
			next->left = next->left->left;
		}
		else if (next->right != nullptr) {
			next->obj = next->right->obj;
			next->left = next->right->left;
			next->right = next->right->right;
		}
		//next->ind = index;
	}
}

binary_tree::~binary_tree() {
	if (cl_ptr != nullptr)
	{
		delete cl_ptr;
	}
}

binary_tree::class_ptr::class_ptr() {
	obj = nullptr;
	left = nullptr;
	right = nullptr;
	//ind = 0;
}

binary_tree::class_ptr::class_ptr(Interface* obj, int index) {
	this->obj = obj;
	//ind = index;
	left = nullptr;
	right = nullptr;
}

void binary_tree::display_tree(class_ptr* tree, string direction) {

	if (tree->left != nullptr) {
		display_tree(tree->left, direction + "L");
	}

	if (tree->right != nullptr) {
		display_tree(tree->right, direction + "R");
	}

	cout << direction << endl;
	tree->obj->Output();
	cout << endl;
}

void binary_tree::display() {
	string tmp = "H";
	display_tree(cl_ptr, tmp);
}


void binary_tree::AddNameClass(std::string name) {
	storage.push_back(name);
}


void binary_tree::Serialize(const char* path) {

	if (cl_ptr == nullptr) return;

	std::fstream f(path, 'w');

	string direction = "";

	if (find(storage.begin(), storage.end(), cl_ptr->obj->Name()) != storage.end()) {
		f << cl_ptr->obj->Name() << '\n';
		f << 0 << '\n';
		cl_ptr->obj->Serialize(f);
	}

	if (cl_ptr->left != nullptr) { 
		recursion(f, cl_ptr->left, direction + "L");
	}
	if (cl_ptr->right != nullptr) {
		recursion(f, cl_ptr->right, direction + "R");
	}

	f.close();
}

void binary_tree::recursion(fstream& f, class_ptr* ptr, string direction) {

	if (find(storage.begin(), storage.end(), ptr->obj->Name()) != storage.end()) {
		f << ptr->obj->Name() << '\n';
		f << ptr->find_ind(&direction) << '\n';
		ptr->obj->Serialize(f);
	}

	if (ptr->left != nullptr) {
		recursion(f, ptr->left, direction + "L");
	}
	if (ptr->right != nullptr) {
		recursion(f, ptr->right, direction + "R");
	}
}


void binary_tree::Deserialize(const char* path) {


	std::fstream f(path);
	Interface* tmp = nullptr;
	
	while (!f.eof()) {

		char buffer[256];
		int index = 0;

		//проблема с вводом
		//после первого объекта ничего не вводит
		f >> buffer;
		f >> index;

		if (find(storage.begin(), storage.end(), buffer) != storage.end()) {
			if (strcmp(buffer, "Employee") == 0) tmp = new Employee;
			else if (strcmp(buffer, "Self_Employeed") == 0) tmp = new Self_Employeed(0);
			else if (strcmp(buffer, "Businessman") == 0) tmp = new Businessman("word", 0);
			else if (strcmp(buffer, "Translator") == 0) tmp = new Translator("lolka");
			else continue;

			tmp->Deserialize(f);
			InsertAt(tmp, index);
		}
	}
	f.close();
}





binary_tree::class_ptr::~class_ptr(){
	if (left != nullptr) {
		delete left;
		left = nullptr;
	}
	if (right != nullptr) {
		right = nullptr;
		delete left;
	}
}