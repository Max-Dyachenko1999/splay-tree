#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *left, *right;
};

/* Функція, яка виділяє новий вузол з заданою клавішею та
NULL лівий та правий вказівники. */
struct node* newNode(int key)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->key = key;
	node->left = node->right = NULL;
	return (node);
}

// Функція корисності для правильного повороту піддерево з кореневою корінням за допомогою y
// Дивитись діаграму, наведену вище.
struct node *rightRotate(struct node *x)
{
	struct node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

// Функція корисності для лівого повороту поддерево з коренем x
// Дивитись діаграму, наведену вище.
struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// Ця функція призводить ключ до кореня, якщо ключ у дереві.
// Якщо ключ відсутній, то він додає останній доступний елемент до
//коріня Ця функція змінює дерево і повертає новий корінь
struct node *splay(struct node *root, int key)
{
	// Базові випадки: корінь NULL або ключ у кореневому каталозі
	if (root == NULL || root->key == key)
		return root;

	// Ключ лежить у лівому піддереві
	if (root->key > key)
	{
		// Ключ не в дереві, ми закінчили
		if (root->left == NULL) return root;

		// Zig-Zig (Left Left)
		if (root->left->key > key)
		{
			// Спочатку рекурсивно вводbvj ключ як корінь left - left
			root->left->left = splay(root->left->left, key);

			// Зробіть перше обертання для кореня, друге обертання виконується за іншим
			root = rightRotate(root);
		}
		else if (root->left->key < key) // Zig-Zag (Left Right)
		{
			// Спочатку рекурсивно введимо ключ як корінь зліва направо
			root->left->right = splay(root->left->right, key);

			// Перше обертання для root->left
			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

		// друге обертання для root
		return (root->left == NULL)? root: rightRotate(root);
	}
	else // Ключ лежить у правильному піддереві
	{
		// Ключ не в дереві, ми закінчили
		if (root->right == NULL) return root;

		// Zag-Zig (Right Left)
		if (root->right->key > key)
		{
			// Приведіть ключ як корінь праворуч і ліворуч
			root->right->left = splay(root->right->left, key);

			// Перше обертання для root->right
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)// Zag-Zag (Right Right)
		{
			// Вводимо ключ як root of right-right і до першого обертання
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		// Друге обертання для root
		return (root->right == NULL)? root: leftRotate(root);
	}
}

// Функція пошуку для дерева Splay.  ця функція
// повертає новий корінь Splay Tree. Якщо ключ знаходиться в дереві
// потім, він переміщений до root.
struct node *search(struct node *root, int key)
{
	return splay(root, key);
}

// Функція корисності для друку попереднього порядку переходу дерева.
// Функція також друкує висоту кожного вузла
void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/*Програма перевіряє приведені вище функції */
int main()
{
	struct node *root = newNode(100);
	root->left = newNode(50);
	root->right = newNode(200);
	root->left->left = newNode(40);
	root->left->left->left = newNode(30);
	root->left->left->left->left = newNode(20);

	root = search(root, 20);
	printf("Preorder traversal of the modified Splay tree is \n");
	preOrder(root);
	return 0;
}
