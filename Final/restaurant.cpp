#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1) {}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}

	void remove_KOKUSEN()
	{
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		if (number <= 0 || number > MAXSIZE)
			return; //! quá kí tự
		areaTable[number].print();
	}

private:
	class Tree_BST
	{
		class Node;

	private:
		Node *root;
		queue<int> queueTime;

	public:
		Tree_BST() : root(nullptr) {}
		~Tree_BST()
		{
			while (!queueTime.empty())
			{
				int temp = queueTime.front();
				queueTime.pop();
				root = remove_recursive(root, temp);
			}
		}
		int size()
		{
			return queueTime.size();
		}
		Node *insert_recursive(Node *node, int result)
		{
			if (!node)
				return new Node(result);
			if (result < node->result)
			{
				node->left = insert_recursive(node->left, result);
			}
			else
			{
				node->right = insert_recursive(node->right, result);
			}
			return node;
		}
		void insert(int result)
		{
			root = insert_recursive(root, result);
			queueTime.push(result);
		}

		Node *remove_recursive(Node *node, int result)
		{
			if (!node)
				return nullptr;
			if (result < node->result)
			{
				node->left = remove_recursive(node->left, result);
			}
			else if (result > node->result)
			{
				node->right = remove_recursive(node->right, result);
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
					node->right = remove_recursive(node->right, result);
					return node;
				}
				delete nodeDel;
			}
			return node;
		}
		int CountNode(Node *node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long DFS(Node *node, const vector<vector<long long>> &dp)
		{
			if (node == NULL)
				return 1;
			int nleft = CountNode(node->left);
			int nRight = CountNode(node->right);
			return (unsigned long long)(dp[nleft + nRight][nleft] % MAXSIZE * (DFS(node->left, dp) % MAXSIZE * DFS(node->right, dp) % MAXSIZE) % MAXSIZE) % MAXSIZE;
		}
		void PascalTriangle(int n, vector<vector<long long>> &dp)
		{
			for (int i = 0; i <= n; i++)
			{
				dp[i] = vector<long long>(i + 1, 1); // initially all 1
				for (int j = 1; j < i; j++)
				{
					dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
				}
			}
		}
		void remove()
		{
			if (this->size() == 0)
				return; //! trường hợp rỗng bỏ qua
			vector<vector<long long>> dp(queueTime.size() + 1);
			PascalTriangle(queueTime.size(), dp);
			unsigned long long number = DFS(root, dp);
			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		 //! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop();					 //! xóa nó khỏi sổ
				root = remove_recursive(root, temp); //! tới chỗ nó cho nó cút khỏi nhà hàng
				number--;
			}
		}

		//^ test case thôi nộp bài thì xóa đi nha --------------------------------------------------------------------
		string test_print_recursive(Node* node)
		{
			if(node == nullptr) return "NULL"; //! trường hợp dừng print
			if(node->left == nullptr && node->right == nullptr) return to_string(node->result); //! tr
			return to_string(node->result)+"("+test_print_recursive(node->left) +","+test_print_recursive(node->right)+")";
		}
		void test_print(){
			//! trường hợp rỗng bỏ qua
			if(this->size() == 0){
				solution << "Tree: EMPTY\n";
				return;
			}
			solution << "Tree: " << test_print_recursive(root);
			solution << "\n";
		}
		//^ ----------------------------------------------------------------------------------------------------------

		void print_recursive(Node *node)
		{
			if (node != NULL)
			{
				solution << node->result << "\n";
				print_recursive(node->left);
				print_recursive(node->right);
			}
		}
		void print()
		{
			//^ test case thôi nộp bài thì xóa đi nha --------------------------------------------------------------------
			test_print();
			//^ ----------------------------------------------------------------------------------------------------------
			// print_recursive(root);
		}

	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class Tree_BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable;
	list<Node *> LRU;

private:
	Node *whoFirst(Node *a, Node *b)
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
	void ReHeap_down(int index)
	{
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int smallest = index;

		if (leftChild < areaTable.size())
		{
			if (areaTable[leftChild]->size() < areaTable[smallest]->size())
			{
				smallest = leftChild;
			}
			else if (areaTable[leftChild]->size() == areaTable[smallest]->size())
			{
				if (whoFirst(areaTable[leftChild], areaTable[smallest]) == areaTable[leftChild])
				{
					smallest = leftChild;
				}
			}
		}
		if (rightChild < areaTable.size())
		{
			if (areaTable[rightChild]->size() < areaTable[smallest]->size())
			{
				smallest = rightChild;
			}
			else if (areaTable[rightChild]->size() == areaTable[smallest]->size())
			{
				if (whoFirst(areaTable[rightChild], areaTable[smallest]) == areaTable[rightChild])
				{
					smallest = rightChild;
				}
			}
		}
		if (smallest != index)
		{
			swap(areaTable[index], areaTable[smallest]);
			ReHeap_down(smallest);
		}
	}

	void ReHeap_up(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (areaTable[index]->size() < areaTable[parent]->size() || (areaTable[index]->size() == areaTable[parent]->size() && whoFirst(areaTable[index], areaTable[parent]) == areaTable[index]))
			{

				swap(areaTable[index], areaTable[parent]);
				index = parent;
			}
			else
				break;
		}
	}

	void moveTop(Node *node)
	{
		list<Node *>::iterator it = std::find(LRU.begin(), LRU.end(), node);
		if (it != LRU.end())
		{
			LRU.erase(it);
		}
		LRU.push_front(node);
	}

	void removeNode(Node *node)
	{
		list<Node *>::iterator it = find(LRU.begin(), LRU.end(), node);
		LRU.erase(it);
	}

public:
	RESTAURANT_Sukuna() {}
	~RESTAURANT_Sukuna()
	{
		for (int i = 0; i < areaTable.size(); i++)
			delete areaTable[i];
	}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		int index = -1;
		for (int i = 0; i < areaTable.size(); i++)
		{
			if (ID == areaTable[i]->ID)
				index = i;
		}
		if (index == -1)
		{
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if (areaTable.size() <= 0)
			return;
		vector<Node *> areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node *> listDelete; //! danh sách các khu cấn xóa
		for (int i = 0; areaTable.size() && i < number; i++)
		{
			Node *nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);
			listDelete.push(nodeDelete);
		}
		areaTable = areaTableNew;
		while (listDelete.size())
		{
			Node *nodeDelete = listDelete.front();
			listDelete.pop();

			solution << "remove customers in the area ID = " << nodeDelete->ID << "(len=" << nodeDelete->head.size() << ")"
					 << ": ";
			nodeDelete->remove(number);
			solution << "\n";

			int index = 0;
			while (areaTable[index] != nodeDelete)
				index++;

			if (nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
	}

	void print_pre_order(int index, int number)
	{
		if (index >= this->areaTable.size())
			return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number)
	{
		if (number <= 0)
			return;

		// solution << "Heap : ";
		// for(auto it : this->areaTable)
		// {
		// 	int order = 0;
		// 	for (auto ix : LRU) {
		// 		if (ix == it) break;
		// 		++order;
		// 	}
		// 	solution << it->ID << "(len="<< it->size() <<",index=" << order <<")" << " ";
		// }
		// solution << "\n";

		solution << "Heap : ";
		for (auto it : this->areaTable)
			solution << it->ID << " ";
		solution << "\n";

		solution << "list LRU : ";
		for (auto it : LRU)
			solution << it->ID << " ";
		solution << "\n";

		print_pre_order(0, number);
	}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	class Node
	{
	private:
		int ID;			//! ID của bàn đó
		list<int> head; //! lưu danh sách các result của khách hàng
		friend class RESTAURANT_Sukuna;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result) { head.push_front(result); }
		void remove(int number)
		{

			while (number-- && head.size() > 0)
			{
				solution << head.back() << " ";
				head.pop_back();
			}
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
			// if(head.size()>0) solution << head.back() << " ";
		}
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << "(len=" << head.size() << ")"
					 << ": ";
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << *it << " ";
			}
			solution << "\n";
		}
	};
};
class HuffTree_AVL
{
	class Node;

private:
	Node *root = nullptr;

public:
	~HuffTree_AVL() { clear(root); }
	void clear(Node *node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
	char encode(char s, int k)
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
	int lastVal(const vector<int> &v, int start)
	{
		while (start < v.size() - 1)
		{
			if (v[start] != v[start + 1])
				return start;
			start++;
		}
		return (int)v.size() - 1;
	}

	bool sameType(char a, char b)
	{
		return (a >= 65 && a <= 90 && b >= 65 && b <= 90) || (a >= 97 && a <= 122 && b >= 97 && b <= 122);
	}
	vector<pair<char, int>> string_Processing(string &name)
	{
		unordered_map<char, int> mp;
		for (char &x : name)
			mp[x]++;
		int numPair = mp.size();
		vector<pair<char, int>> freq_prev;
		for (pair<char, int> x : mp)
		{
			freq_prev.push_back(x);
		}

		for (char &x : name)
			x = encode(x, mp[x]);
		for (pair<char, int> &x : freq_prev)
			x.first = encode(x.first, x.second);

		mp.clear();
		for (pair<char, int> x : freq_prev)
		{
			mp[x.first] += x.second;
		}
		vector<pair<char, int>> freq;

		unordered_map<char, int>::iterator mapIt = mp.begin();
		for (; mapIt != mp.end(); mapIt++)
		{
			freq.push_back({mapIt->first, mapIt->second});
		}

		stable_sort(freq.begin(), freq.end(),
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
		return freq;
	}

	int height(Node *node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return 1 + max(height(node->left), height(node->right));
	}
	Node *rightRotate(Node *Node_A)
	{

		Node *Node_B = Node_A->left;  //! này là B
		Node *Node_E = Node_B->right; //! này là E

		Node_A->left = Node_E;	//! CẬP NHẬT NODE E
		Node_B->right = Node_A; //! CẬP NHẬT NODE A

		return Node_B; //! NODE B đang là root
	}

	Node *leftRotate(Node *Node_A)
	{
		Node *Node_C = Node_A->right;
		Node *Node_D = Node_C->left;

		Node_A->right = Node_D;
		Node_C->left = Node_A;

		return Node_C;
	}
	enum class BalanceState
	{
		LEFT_HEAVY,
		BALANCED,
		RIGHT_HEAVY
	};
	BalanceState getBalanceState(Node *node)
	{
		if (node == nullptr)
			return BalanceState::BALANCED;

		int leftHeight = height(node->left);
		int rightHeight = height(node->right);

		int balance = leftHeight - rightHeight;
		if (balance > 1)
			return BalanceState::LEFT_HEAVY;

		else if (balance < -1)
			return BalanceState::RIGHT_HEAVY;
		return BalanceState::BALANCED;
	}

	Node *balanceNode(Node *node, int &count)
	{
		// TODO
		if (!node)
			return nullptr;
		BalanceState rootState = getBalanceState(node);
		Node *leftNode = node->left;
		Node *rightNode = node->right;
		int balanceLeft = 0, balanceRight = 0;
		if (leftNode)
			balanceLeft = height(leftNode->left) - height(leftNode->right);
		if (rightNode)
			balanceRight = height(rightNode->left) - height(rightNode->right);

		if (rootState == BalanceState::LEFT_HEAVY && balanceLeft >= 0)
		{
			count += 1;
			return rightRotate(node);
		}
		if (rootState == BalanceState::RIGHT_HEAVY && balanceRight <= 0)
		{
			count += 1;
			return leftRotate(node);
		}
		if (rootState == BalanceState::LEFT_HEAVY && balanceLeft <= -1)
		{
			node->left = leftRotate(node->left);
			count += 1;
			return rightRotate(node);
		}
		if (rootState == BalanceState::RIGHT_HEAVY && balanceRight >= 1)
		{
			node->right = rightRotate(node->right);
			count += 1;
			return leftRotate(node);
		}

		return node;
	}

	Node *balanceTree(Node *node, int count=0)
	{
		if (!node || count == 1)
			return node;
		node = balanceNode(node, count);
		if (node)
		{
			node->left = balanceTree(node->left, count);
			node->right = balanceTree(node->right, count);
		}
		return node;
	}
	Node *buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node *> build;
		for (int i = 0; i < (int)freq.size(); i++)
		{
			Node *x = new Node(freq[i].second, freq[i].first);
			build.push_back(x);
		}
		Node *res = nullptr;
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
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		if (node == nullptr)
			return;
		encoding[node->c] = s;
		encodingHuffman_rec(encoding, node->left, s + "0");
		encodingHuffman_rec(encoding, node->right, s + "1");
	}

	int binaryStringToDecimal(const std::string &binaryString)
	{
		std::bitset<16> binaryNumber(binaryString);
		return static_cast<int>(binaryNumber.to_ulong());
	}

	int encodingHuffman(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr)
			return 0;
		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);

		string binary = "";
		for (int i = (int)nameCaesar.length() - 1; i >= 0; i--)
		{
			binary = encoding[(int)nameCaesar[i]] + binary;
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
		// TODO
		result = binaryStringToDecimal(res);
		return result;
	}

	int encode(string name)
	{

		if (name.length() < 3)
			return -1;

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);
		solution << "freq     : {";
		for (int i = 0; i <freq.size();i++){
			if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
			else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
		}
			solution << "}"<<endl;
		this->clear(root); //! xóa cây cũ
		//* bước 2 xây dựng cây huff
		root = this->buildHuff(freq);

		if (root->left == nullptr && root->right == nullptr)
			return 0; //! trường hợp chỉ có 1 node
		// this->print();
		// solution << "name   = " << name << endl;
		int result = this->encodingHuffman(root, name);
		// solution << "result = " << result << endl;
		return result;
	}

	void rec_print(const Node* tree) {
		if (tree == nullptr) {
			return;
		}
		if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
		else solution << "[" << tree->weight << "]";
		
		if (tree->left != nullptr || tree->right != nullptr) {
			solution << "(";
			rec_print(tree->left);
			solution << ",";
			rec_print(tree->right);
			solution << ")";
		}
	}

	void print()
	{
		solution << "root : ";rec_print(root);solution << '\n';
	}

private:
	class Node
	{
	public:
		int weight;

		char c;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
	};
};

class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;

public:
	void LAPSE(string name)
	{
		//^ test case thôi nộp bài thì xóa --------------------------------------------------------------------
		if (name[0] >= '0' && name[0] <= '9')
		{
			int result = stoi(name);
			solution << "result = " << result << endl;
			if (result % 2 == 1)
				hash.insertAreaTable(result);
			else
				heap.insertAreaTable(result);
			return;
		}
		//^ ----------------------------------------------------------------------------------------------------------

		int result = New_customers_arrive.encode(name);
		if (result == -1)
			return;

		//^ test case thôi nộp bài thì xóa đi nha --------------------------------------------------------------------
		solution << "result = " << result << endl;
		New_customers_arrive.print();
		//^ ----------------------------------------------------------------------------------------------------------

		if (result % 2 == 1)
			hash.insertAreaTable(result);
		else
			heap.insertAreaTable(result);
	}

	//* xử lí nhà hàng gojo
	void KOKUSEN() { hash.remove_KOKUSEN(); }
	void LIMITLESS(int num) { hash.print_LIMITLESS(num); }

	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num) { heap.remove_KEITEIKEN(num); }
	void CLEAVE(int num) { heap.print_LIMITLESS(num); }

	//* in ra HuffTree_AVL
	void HAND() { New_customers_arrive.print(); }
};

void simulate(string filename)
{
	solution.flush();
	//* nhập file
	ifstream ss(filename);
	if (ss.fail())
	{
		cout << "ERROR: " << filename << endl;
		return;
	}

	string str, name;
	int num;
	ss >> str;
	ss >> MAXSIZE; //* nhập maxsize đầu tiên
	JJK_RESTAURANT_OPERATIONS *NOT_LIKE_CODE = new JJK_RESTAURANT_OPERATIONS();
	// //* xử lí file
	int line = 0;
	solution << "MAXSIZE : " << MAXSIZE << "\n";
	while (ss >> str)
	{
		//^ test case thôi nộp bài thì xóa đi nha --------------------------------------------------------------------
		line ++;
		if(str == "LAPSE") solution << "LAPSE : LINE " << line << "\n";
		else if(str == "KEITEIKEN") solution << "KEITEIKEN : LINE " << line << "\n";
		else if(str == "HAND") solution << "HAND : LINE " << line << "\n";
		else if(str == "LIMITLESS") solution << "LIMITLESS : LINE " << line << "\n";
		else if(str == "CLEAVE") solution << "CLEAVE : LINE " << line << "\n";
		else if(str == "KOKUSEN") solution << "KOKUSEN : LINE " << line << "\n";
		//^ ----------------------------------------------------------------------------------------------------------

		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			NOT_LIKE_CODE->LAPSE(name);
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			NOT_LIKE_CODE->KOKUSEN();
		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->KEITEIKEN(num);
		}
		else if (str == "HAND") // HAND
		{
			NOT_LIKE_CODE->HAND();
		}
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->LIMITLESS(num);
		}
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->CLEAVE(num);
		}
	}
	delete NOT_LIKE_CODE;
}
