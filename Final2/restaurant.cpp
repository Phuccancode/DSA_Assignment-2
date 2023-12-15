

#include "main.h"

int MAXSIZE = 0;
//*----------------------------Start Prototype--------------------------//
class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;
class Gojo_Restaurant
{
	class BST;

private:
	vector<BST> area;

public:
	Gojo_Restaurant() : area((unsigned int)(MAXSIZE+1)) {}
	void insertArea(int result);
	void kokusenRemove();
	void print_LIMITLESS(int number);

private:
	class BST
	{
		class Node;

	private:
		Node *root;
		queue<int> timeGetIn;

	public:
		BST() : root(nullptr) {}
		~BST();
		int size();
		Node *insert_rec(Node *node, int result);
		void insert(int result);
		Node *remove_rec(Node *node, int result);
		int numOfNodeInTree(Node *node);
		unsigned long long DFS(Node *node, const vector<vector<long long>> &dp);
		void PascalTriangle(int n, vector<vector<long long>> &dp);
		void remove();
		void print_rec(Node *node);
		void print();

	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};
class Sukana_Restaurant
{
	class Node;

private:
	vector<Node *> area;
	list<Node *> LRU;
private:
	Node *whoFirst(Node *a, Node *b);
	void reHeapDown(int index);
	void reHeapUp(int index);
	void moveToFront(Node *node);
	void removeNode(Node *node);

public:
	Sukana_Restaurant() {}
	~Sukana_Restaurant();
	void insertArea(int result);
	void keiteikenRemove(int number);
	void traversal_preOrder(int index, int number);

private:
	class Node
	{
	private:
		int ID;
		list<int> head;
		friend class Sukana_Restaurant;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result) { head.push_front(result); }
		void remove(int number)
		{
			while (number != 0 && !head.empty())
			{
				solution << head.back() << "-" << ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << ID << "-" << *it << "\n";
			}
		}
	};
};

class HuffTree
{
	class Node;

private:
	Node *root = nullptr;

public:
	~HuffTree() { clear(root); }
	void clear(Node *node);
	char encode(char s, int k);
	bool sameType(char a, char b);
	vector<pair<char, int>> string_Processing(string &name);
	int treeHeight(Node *node);
	Node *rightRotate(Node *Node_A);
	Node *leftRotate(Node *Node_A);
	enum class BalanceState
	{
		LH,
		EH,
		RH
	};
	BalanceState getBalanceState(Node *node);
	Node *balanceNode(Node *node, int &count);
	Node *balanceTree(Node *node, int count = 0);
	Node *buildHuff(vector<pair<char, int>> frequency_2);
	void encodeHuff_rec(vector<string> &encodeList, Node *node, string s = "");
	int binaryStringToDecimal(const std::string &binaryString);
	int encodeHuff(Node *root, string name);
	int encode(string name);
	void print_rec(Node *node);
	void print_HAND() { print_rec(root); }

private:
	class Node
	{
	public:
		int weight;
		char x;
		Node *left;
		Node *right;
		friend class HuffTree;

	public:
		Node(int weight, char x = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), x(x), left(left), right(right) {}
	};
};


class Restaurant_Headquarters
{
private:
	HuffTree newCus;
	Gojo_Restaurant hash;
	Sukana_Restaurant heap;

public:
	void LAPSE(string name);
	void KOKUSEN() { hash.kokusenRemove(); }
	void LIMITLESS(int num) { hash.print_LIMITLESS(num); }
	void KEITEIKEN(int num) { heap.keiteikenRemove(num); }
	void CLEAVE(int num) { heap.traversal_preOrder(0, num); }
	void HAND() { newCus.print_HAND(); }
};

void simulate(string filename)
{

	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str;
	ss >> MAXSIZE;

	Restaurant_Headquarters *operation = new Restaurant_Headquarters();
	while (ss >> str)
	{
		if (str == "LAPSE")
		{
			ss >> name;
			operation->LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			operation->KOKUSEN();
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num;
			operation->KEITEIKEN(num);
		}
		else if (str == "HAND")
		{
			operation->HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num;
			operation->LIMITLESS(num);
		}
		else if (str == "CLEAVE")
		{
			ss >> num;
			operation->CLEAVE(num);
		}
	}
	delete operation;
}
//*---------------------------End Prototype------------------------//


//*-------------------Start Gojo_Restaurant Implementation---------------------//
void Gojo_Restaurant::insertArea(int result)
{
	int ID = result % MAXSIZE + 1;
	area[ID].insert(result);
}

void Gojo_Restaurant::kokusenRemove()
{
	for (int i = 1; i < MAXSIZE + 1; i++)
		area[i].remove();
}

void Gojo_Restaurant::print_LIMITLESS(int number)
{
	if (number <= 0 || number > MAXSIZE)
		return;
	area[number].print();
}

Gojo_Restaurant::BST::~BST()
{
	while (!timeGetIn.empty())
	{
		int temp = timeGetIn.front();
		timeGetIn.pop();
		root = remove_rec(root, temp);
	}
}

int Gojo_Restaurant::BST::size() { return timeGetIn.size(); }

Gojo_Restaurant::BST::Node *Gojo_Restaurant::BST::insert_rec(Node *node, int result)
{
	if (!node)
		return new Node(result);
	if (result < node->result)
	{
		node->left = insert_rec(node->left, result);
	}
	else
	{
		node->right = insert_rec(node->right, result);
	}
	return node;
}

void Gojo_Restaurant::BST::insert(int result)
{
	root = insert_rec(root, result);
	timeGetIn.push(result);
}

Gojo_Restaurant::BST::Node *Gojo_Restaurant::BST::remove_rec(Node *node, int result)
{
	if (!node)
		return nullptr;
	if (result < node->result)
	{
		node->left = remove_rec(node->left, result);
	}
	else if (result > node->result)
	{
		node->right = remove_rec(node->right, result);
	}
	if (node->result == result)
	{
		Node *nodeDel = node;
		if (!node->left && !node->right)
		{
			node = nullptr;
		}
		else if (!node->left)
		{
			node = node->right;
		}
		else if (!node->right)
		{
			node = node->left;
		}
		else
		{
			Node *tmp = node->right;
			while (tmp->left != nullptr)
			{
				tmp = tmp->left;
			}
			swap(tmp->result, node->result);
			node->right = remove_rec(node->right, result);
			return node;
		}
		delete nodeDel;
	}
	return node;
}

int Gojo_Restaurant::BST::numOfNodeInTree(Node *node)
{
	return !node ? 0 : 1 + numOfNodeInTree(node->left) + numOfNodeInTree(node->right);
}

unsigned long long Gojo_Restaurant::BST::DFS(Node *node, const vector<vector<long long>> &dp)
{
	if (node == NULL)
		return 1;
	int nleft = numOfNodeInTree(node->left);
	int nRight = numOfNodeInTree(node->right);
	return (unsigned long long)(dp[nleft + nRight][nleft] % MAXSIZE * (DFS(node->left, dp) % MAXSIZE * DFS(node->right, dp) % MAXSIZE) % MAXSIZE) % MAXSIZE;
}

void Gojo_Restaurant::BST::PascalTriangle(int n, vector<vector<long long>> &dp)
{
	for (int i = 0; i <= n; i++)
	{
		dp[i] = vector<long long>(i + 1, 1); // initially all 1
		for (int j = 1; j < i; j++)
		{
			dp[i][j] = (dp[i - 1][j - 1] % MAXSIZE + dp[i - 1][j] % MAXSIZE);
		}
	}
}

void Gojo_Restaurant::BST::remove()
{
	if (timeGetIn.empty())
		return;
	vector<vector<long long>> dp(timeGetIn.size() + 1);
	PascalTriangle(timeGetIn.size(), dp);
	unsigned long long number = DFS(root, dp) % MAXSIZE;

	while (number != 0 && !timeGetIn.empty())
	{
		int temp = timeGetIn.front();
		timeGetIn.pop();
		root = remove_rec(root, temp);
		number--;
	}
}

void Gojo_Restaurant::BST::print_rec(Node *node)
{
	if (node != NULL)
	{
		print_rec(node->left);
		solution << node->result << "\n";
		print_rec(node->right);
	}
}

void Gojo_Restaurant::BST::print() { print_rec(root); }
//*---------------------End Gojo_Restaurant Implementation---------------------//


//*------------------------Start Sukana Implementation----------------------------//
Sukana_Restaurant::Node *Sukana_Restaurant::whoFirst(Node *a, Node *b)
{
	for (Node *it : LRU)
	{
		if (it == a)
			return b;
		if (it == b)
			return a;
	}
	return nullptr;
}

void Sukana_Restaurant::reHeapDown(int index)
{
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	int smallest = index;

	if (leftChild < (int)area.size())
	{
		if (area[leftChild]->size() < area[smallest]->size())
		{
			smallest = leftChild;
		}
		else if (area[leftChild]->size() == area[smallest]->size())
		{
			if (whoFirst(area[leftChild], area[smallest]) == area[leftChild])
			{
				smallest = leftChild;
			}
		}
	}
	if (rightChild < (int)area.size())
	{
		if (area[rightChild]->size() < area[smallest]->size())
		{
			smallest = rightChild;
		}
		else if (area[rightChild]->size() == area[smallest]->size())
		{
			if (whoFirst(area[rightChild], area[smallest]) == area[rightChild])
			{
				smallest = rightChild;
			}
		}
	}
	if (smallest != index)
	{
		swap(area[index], area[smallest]);
		reHeapDown(smallest);
	}
}

void Sukana_Restaurant::reHeapUp(int index)
{
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (area[index]->size() < area[parent]->size() || (area[index]->size() == area[parent]->size() && whoFirst(area[index], area[parent]) == area[index]))
		{

			swap(area[index], area[parent]);
			index = parent;
		}
		else
			break;
	}
}

void Sukana_Restaurant::moveToFront(Node *node)
{
	list<Node *>::iterator it = std::find(LRU.begin(), LRU.end(), node);
	if (it != LRU.end())
	{
		LRU.erase(it);
	}
	LRU.push_front(node);
}

void Sukana_Restaurant::removeNode(Node *node)
{
	list<Node *>::iterator it = find(LRU.begin(), LRU.end(), node);
	LRU.erase(it);
}

Sukana_Restaurant::~Sukana_Restaurant()
{
	for (int i = 0; i < (int)area.size(); i++)
	{
		delete area[i];
	}
}

void Sukana_Restaurant::insertArea(int result)
{
	int ID = result % MAXSIZE + 1;
	int index = -1;
	for (int i = 0; i < (int)area.size(); i++)
	{
		if (ID == area[i]->ID)
			index = i;
	}
	if (index == -1)
	{
		area.push_back(new Node(ID));
		index = area.size() - 1;
		area[index]->insert(result);
		this->moveToFront(area[index]);
		this->reHeapUp(index);
	}
	else
	{
		area[index]->insert(result);
		this->moveToFront(area[index]);
		this->reHeapDown(index);
	}
}

void Sukana_Restaurant::keiteikenRemove(int number)
{
	if (area.size() <= 0)
		return;
	vector<Node *> newArea(area.begin(), area.end());
	queue<Node *> removeList; //! danh sách các khu cấn xóa
	for (int i = 0; area.size() && i < number; i++)
	{
		Node *removeNode = area[0];
		swap(area[0], area[area.size() - 1]);
		area.pop_back();
		this->reHeapDown(0);
		removeList.push(removeNode);
	}
	area = newArea;
	while (removeList.size())
	{
		Node *removeNode = removeList.front();
		removeList.pop();

		removeNode->remove(number);
		int index = 0;
		while (area[index] != removeNode)
			index++;
		if (removeNode->size() == 0)
		{
			swap(area[index], area[area.size() - 1]);
			this->removeNode(area[area.size() - 1]);
			delete area[area.size() - 1];
			area.pop_back();
		}
		this->reHeapDown(index);
	}
}

void Sukana_Restaurant::traversal_preOrder(int index, int number)
{
	if (index >= (int)this->area.size() || number <= 0)
		return;
	this->area[index]->print(number);
	traversal_preOrder(index * 2 + 1, number);
	traversal_preOrder(index * 2 + 2, number);
}
//*---------------------------End Sukana Implementation---------------------------//


//*--------------------------Start HuffTree Implementation---------------------------//
void HuffTree::clear(Node *node)
{
	if (node)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

char HuffTree::encode(char s, int k)
{
	if (s >= 65 && s <= 90)
	{
		return ((s - 65) + k) % 26 + 65;
	}
	else if (s >= 97 && s <= 122)
	{
		return ((s - 97) + k) % 26 + 97;
	}
	else
	{
		return s;
	}
}

bool HuffTree::sameType(char a, char b)
{
	return (a >= 65 && a <= 90 && b >= 65 && b <= 90) || (a >= 97 && a <= 122 && b >= 97 && b <= 122);
}

vector<pair<char, int>> HuffTree::string_Processing(string &name)
{
	unordered_map<char, int> mp;
	for (char &x : name)
		mp[x]++;
	vector<pair<char, int>> frequency_1;
	for (pair<char, int> x : mp)
	{
		frequency_1.push_back(x);
	}
	if (frequency_1.size() < 3)
		return {};
	for (char &x : name)
		x = encode(x, mp[x]);
	for (pair<char, int> &x : frequency_1)
		x.first = encode(x.first, x.second);

	mp.clear();
	for (pair<char, int> x : frequency_1)
	{
		mp[x.first] += x.second;
	}
	vector<pair<char, int>> frequency_2;

	unordered_map<char, int>::iterator mapIt = mp.begin();
	for (; mapIt != mp.end(); mapIt++)
	{
		frequency_2.push_back({mapIt->first, mapIt->second});
	}

	stable_sort(frequency_2.begin(), frequency_2.end(),
				[=](const pair<char, int> &a, const pair<char, int> &b) -> bool
				{
					if (a.second > b.second)
						return true;
					if (a.second == b.second)
					{
						if (sameType(a.first, b.first))
							return a.first > b.first;
						else
							return a.first < b.first;
					}
					return false;
				});
	return frequency_2;
}

int HuffTree::treeHeight(Node *node)
{
	return node ? 1 + max(treeHeight(node->left), treeHeight(node->right)) : 0;
}

HuffTree::Node *HuffTree::rightRotate(Node *Node_A)
{

	Node *Node_B = Node_A->left;  
	Node *Node_E = Node_B->right; 

	Node_A->left = Node_E;	
	Node_B->right = Node_A; 
	return Node_B; 
}

HuffTree::Node *HuffTree::leftRotate(Node *Node_A)
{
	Node *Node_C = Node_A->right;
	Node *Node_D = Node_C->left;

	Node_A->right = Node_D;
	Node_C->left = Node_A;

	return Node_C;
}

HuffTree::BalanceState HuffTree::getBalanceState(Node *node)
{
	if (!node)
		return BalanceState::EH;

	int leftHeight = treeHeight(node->left);
	int rightHeight = treeHeight(node->right);

	int balance = leftHeight - rightHeight;
	if (balance > 1)
		return BalanceState::LH;

	else if (balance < -1)
		return BalanceState::RH;
	return BalanceState::EH;
}

HuffTree::Node *HuffTree::balanceNode(Node *node, int &count)
{
	if (!node)
		return nullptr;
	BalanceState rootState = getBalanceState(node);
	Node *leftNode = node->left;
	Node *rightNode = node->right;
	int balanceLeft = 0, balanceRight = 0;
	if (leftNode)
		balanceLeft = treeHeight(leftNode->left) - treeHeight(leftNode->right);
	if (rightNode)
		balanceRight = treeHeight(rightNode->left) - treeHeight(rightNode->right);

	if (rootState == BalanceState::LH && balanceLeft >= 0)
	{
		count += 1;
		return rightRotate(node);
	}
	if (rootState == BalanceState::RH && balanceRight <= 0)
	{
		count += 1;
		return leftRotate(node);
	}
	if (rootState == BalanceState::LH && balanceLeft <= -1)
	{
		node->left = leftRotate(node->left);
		count += 1;
		return rightRotate(node);
	}
	if (rootState == BalanceState::RH && balanceRight >= 1)
	{
		node->right = rightRotate(node->right);
		count += 1;
		return leftRotate(node);
	}

	return node;
}

HuffTree::Node *HuffTree::balanceTree(Node *node, int count)
{
	if (!node || count == 1)
		return node;
	node = balanceNode(node, count);
	node->left = balanceTree(node->left, count);
	node->right = balanceTree(node->right, count);
	return node;
}

HuffTree::Node *HuffTree::buildHuff(vector<pair<char, int>> frequency_2)
{
	vector<Node *> build;
	for (int i = 0; i < (int)frequency_2.size(); i++)
	{
		Node *x = new Node(frequency_2[i].second, frequency_2[i].first);
		build.push_back(x);
	}

	while (build.size() > 1)
	{
		int count = 0;
		Node *newNode = nullptr;
		Node *left = build.back();
		build.pop_back();
		Node *right = build.back();
		build.pop_back();
		newNode = new Node(left->weight + right->weight, '\0', left, right);

		newNode = balanceTree(newNode, count);
		newNode = balanceTree(newNode, count);
		newNode = balanceTree(newNode, count);

		build.push_back(newNode);
		if (build.back() != newNode)
		{
			build.pop_back();
			build.push_back(newNode);
		}

		int newNodeIdx = build.size() - 1;
		while (newNodeIdx - 1 >= 0 && build[newNodeIdx]->weight >= build[newNodeIdx - 1]->weight)
		{
			swap(build[newNodeIdx], build[newNodeIdx - 1]);
			newNodeIdx--;
		}
	}
	return build[0];
}

void HuffTree::encodeHuff_rec(vector<string> &encodeList, Node *node, string s)
{
	if (!node)
		return;
	encodeList[node->x] = s;
	encodeHuff_rec(encodeList, node->left, s + "0");
	encodeHuff_rec(encodeList, node->right, s + "1");
}

int HuffTree::binaryStringToDecimal(const std::string &binaryString)
{
	std::bitset<16> binaryNumber(binaryString);
	return static_cast<int>(binaryNumber.to_ulong());
}

int HuffTree::encodeHuff(Node *root, string name)
{
	if (root->left == nullptr && root->right == nullptr)
		return 0;
	vector<string> encodeList(256, "");
	encodeHuff_rec(encodeList, root);

	string binary = "";
	for (int i = (int)name.length() - 1; i >= 0; i--)
	{
		binary = encodeList[(int)name[i]] + binary;
		if (binary.length() >= 10)
			break;
	}
	string res = "";
	for (int i = (int)binary.length() - 1; i >= 0; i--)
	{
		res += binary[i];
	}

	res = res.substr(0, 10);
	int result = 0;

	result = binaryStringToDecimal(res);
	return result;
}

int HuffTree::encode(string name)
{
	vector<pair<char, int>> frequency_2 = this->string_Processing(name);
	if (frequency_2.size() == 0)
		return -1;
	this->clear(root);
	root = this->buildHuff(frequency_2);
	if (root->left == nullptr && root->right == nullptr)
		return 0;

	int result = this->encodeHuff(root, name);

	return result;
}

void HuffTree::print_rec(Node *node)
{
	if (!node)
		return;
	print_rec(node->left);
	if (node->x == '\0')
		solution << node->weight << "\n";
	else
		solution << node->x << "\n";
	print_rec(node->right);
}
//*-------------------------End HuffTree Implementation---------------------------//


//* ---------------------Start Headquarters Implimentation-------------------------//
void Restaurant_Headquarters::LAPSE(string name)
{
	if(name[0] >= '0' && name[0] <= '9')
	{
		int result = stoi(name);
		if(result % 2 == 1) hash.insertArea(result);
		else heap.insertArea(result);
		return;
	}
	int result = newCus.encode(name);
	if (result == -1)
		return;

	if (result % 2 == 1)
		hash.insertArea(result);
	else
		heap.insertArea(result);
}
//* ---------------------End Headquarters Implimentation--------------------------//
