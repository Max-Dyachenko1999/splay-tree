#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *left, *right;
};

/* �������, ��� ������ ����� ����� � ������� ������� ��
NULL ���� �� ������ ���������. */
struct node* newNode(int key)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->key = key;
	node->left = node->right = NULL;
	return (node);
}

// ������� ��������� ��� ����������� �������� �������� � ��������� ������� �� ��������� y
// �������� �������, �������� ����.
struct node *rightRotate(struct node *x)
{
	struct node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

// ������� ��������� ��� ����� �������� ��������� � ������� x
// �������� �������, �������� ����.
struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// �� ������� ���������� ���� �� ������, ���� ���� � �����.
// ���� ���� �������, �� �� ���� ������� ��������� ������� ��
//����� �� ������� ����� ������ � ������� ����� �����
struct node *splay(struct node *root, int key)
{
	// ����� �������: ����� NULL ��� ���� � ���������� �������
	if (root == NULL || root->key == key)
		return root;

	// ���� ������ � ����� �������
	if (root->key > key)
	{
		// ���� �� � �����, �� ��������
		if (root->left == NULL) return root;

		// Zig-Zig (Left Left)
		if (root->left->key > key)
		{
			// �������� ���������� ����bvj ���� �� ����� left - left
			root->left->left = splay(root->left->left, key);

			// ������ ����� ��������� ��� ������, ����� ��������� ���������� �� �����
			root = rightRotate(root);
		}
		else if (root->left->key < key) // Zig-Zag (Left Right)
		{
			// �������� ���������� ������� ���� �� ����� ���� �������
			root->left->right = splay(root->left->right, key);

			// ����� ��������� ��� root->left
			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

		// ����� ��������� ��� root
		return (root->left == NULL)? root: rightRotate(root);
	}
	else // ���� ������ � ����������� �������
	{
		// ���� �� � �����, �� ��������
		if (root->right == NULL) return root;

		// Zag-Zig (Right Left)
		if (root->right->key > key)
		{
			// �������� ���� �� ����� �������� � ������
			root->right->left = splay(root->right->left, key);

			// ����� ��������� ��� root->right
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)// Zag-Zag (Right Right)
		{
			// ������� ���� �� root of right-right � �� ������� ���������
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		// ����� ��������� ��� root
		return (root->right == NULL)? root: leftRotate(root);
	}
}

// ������� ������ ��� ������ Splay.  �� �������
// ������� ����� ����� Splay Tree. ���� ���� ����������� � �����
// ����, �� ���������� �� root.
struct node *search(struct node *root, int key)
{
	return splay(root, key);
}

// ������� ��������� ��� ����� ������������ ������� �������� ������.
// ������� ����� ����� ������ ������� �����
void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/*�������� �������� �������� ���� ������� */
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
