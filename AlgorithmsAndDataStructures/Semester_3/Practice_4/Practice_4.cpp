// Вариант 5

#include <iostream>
#include <string>

#define N 15

using namespace std;

class Tree {
public:
	struct node {
		float value = 0;
		node* left = NULL;
		node* right = NULL;

		node(float value = 0, node* left = NULL, node* right = NULL)
			: value(value), left(left), right(right)
		{
		}
	};

	Tree() = default;

	//Строит идеально сбалансированное дерево
	void insert_balanced_complete(float* values, int size = 0) {
		bubble_sort(values, size);
		float* inserted = new float[size];
		insert_balanced(values, inserted, 0, size);
		delete[] inserted;
	}

	int insert(float val) {
		if (!root) {
			root = new node(val);
			return 1;
		}
		else {
			insertcur(val, root);
			return 0;
		}
	}

	void print() {
		if (!existence_check()) return;
		rotated_tree_display(root);
	}

	//Вычисление средних арифметических левого и правого поддерева
	float* avg_left_right() {
		if (!existence_check()) return NULL;
		float avg_array[2];
		float sum = 0;
		int quantity = 0;
		if (root->left) {
			avg(root->left, sum, quantity);
			avg_array[0] = sum / quantity;
		}
		sum = 0;
		quantity = 0;
		if (root->right) {
			avg(root->right, sum, quantity);
			avg_array[1] = sum / quantity;
		}
		return avg_array;
	}

	void delete_tree() {
		if (!existence_check()) return;
		delete_tree_recursion(root);
		root = NULL;
	}

	int existence_check() {
		if (root) return 1;
		else {
			cout << "\nError: Tree doesn't exist.\n";
			return 0;
		}
	}

private:
	node* root = NULL;

	node* insertcur(float val, node* cur) {
		if (cur == NULL)
			cur = new node(val);
		else if (val > cur->value)
			cur->right = insertcur(val, cur->right);
		else
			cur->left = insertcur(val, cur->left);
		return cur;
	}

	void rotated_tree_display(node* node, int offset = 0) {
		if (node->right != NULL) {
			rotated_tree_display(node->right, offset + 4);
			for (int i = 0; i < offset + 3; i++) {
				cout << ' ';
			}
			cout << '/' << '\n';
		}
		for (int i = 0; i < offset; i++) {
			cout << ' ';
		}
		cout << node->value << '\n';
		if (node->left != NULL) {
			for (int i = 0; i < offset + 3; i++) {
				cout << ' ';
			}
			cout << '\\' << '\n';
			rotated_tree_display(node->left, offset + 4);
		}
	}

	//Используется для сортировки передаваемого массива значений перед построением дерева
	void bubble_sort(float values[], int size) {
		float temp = 0;
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (values[j] > values[j + 1]) {
					temp = values[j];
					values[j] = values[j + 1];
					values[j + 1] = temp;
				}
			}
		}
	}

	//Функция, обеспечивающие балансировку дерева
	void insert_balanced(float* values, float* inserted, int start = 0, int end = 0, int size = 0) {
		int index = (end - start) / 2 + start;

		for (int i = 0; i < size + 1; i++) {
			if (values[index] == inserted[i]) return;
		}

		insert(values[index]);
		inserted[size] = values[index];
		size++;
		if (end - start > 1) {
			insert_balanced(values, inserted, start, index, size);
			insert_balanced(values, inserted, index, end, size);
		}
	}

	//Вычисление среднего арифметического поддерева
	void avg(node* node, float& sum, int& quantity) {
		sum += node->value;
		quantity += 1;
		if (node->right) {
			avg(node->right, sum, quantity);
		}
		if (node->left) {
			avg(node->left, sum, quantity);
		}
	}

	//Рекурсивное удаление всех узлов
	void delete_tree_recursion(node* cur) {
		if (cur->right) {
			delete_tree_recursion(cur->right);
		}
		if (cur->left) {
			delete_tree_recursion(cur->left);
		}
		cout << "\ndeleted: " << cur->value;
		delete cur;
	}
};


void app() {
	int choice = 0;
	char choice2;
	float values[N];
	float avg[2];
	Tree mytree;

	while (1) {
		cout << "Options:\n";
		cout << "1. Create tree\n";
		cout << "2. Display tree\n";
		cout << "3. Calculate averages for left and right subtrees\n";
		cout << "4. Delete tree\n";
		cout << "5. Exit app\n";

		cin >> choice;

		switch (choice) {
		case 1:
			cout << "\nUse template? (15 random numbers) [y/n]: ";
			cin >> choice2;
			if (choice2 == 'y') {
				srand(time(0));
				cout << "\nValues: ";
				for (int i = 0; i < N; i++) {
					values[i] = floor(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100) / 100;
					cout << values[i] << ' ';
				}
				cout << '\n';
				mytree.insert_balanced_complete(values, N);
			}
			else {
				cout << "\nInput number of values to insert: (<= " << N << ") ";
				cin >> choice;
				for (int i = 0; i < choice; i++) {
					cout << "\nInput value: ";
					cin >> values[i];
				}
				mytree.insert_balanced_complete(values, choice);
			}
			break;
		case 2:
			mytree.print();
			break;
		case 3:
			if (!mytree.avg_left_right()) {
				break;
			}
			avg[0] = mytree.avg_left_right()[0];
			avg[1] = mytree.avg_left_right()[1];
			cout << "Left subtree average: " << avg[0] << '\n';
			cout << "Right subtree average: " << avg[1] << '\n';
			break;
		case 4:
			mytree.delete_tree();
			cout << '\n';
			break;
		case 5:
			return;
		}
	}
}

int main() {
	app();
	return 0;
}
