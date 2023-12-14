
#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	//* cứ hiểu mỗi phần tử areaTable là các khu ăn trong đó sẽ có 1 nhân viên quản lí thêm vào và xóa ra chủ không cần quản lí mấy này
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1)
	{
	}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}

	void remove_KOKUSEN()
	{
		//* tới từng khu ăn kêu nhân viên tìm thằng nào gián điệp đấm nó rồi đuổi cổ nó đi
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra
		if (number <= 0 || number > MAXSIZE)
			return; //! quá kí tự
		areaTable[number].print();
	}

private:
	//* Tree_BST giống như các nhân viên
	class Tree_BST
	{
		class Node;

	private:
		Node *root;			  //! cây của khách hàng vị trí khách hàng
		queue<int> queueTime; //! thời gian khách hàng đến có thể hiểu như là sổ ghi thông tin khách hàng

	public:
		Tree_BST() : root(nullptr)
		{
		}
		~Tree_BST()
		{
			DestroyRecursive(root);
		}
		void DestroyRecursive(Node *node)
		{
			if (node)
			{
				DestroyRecursive(node->left);
				DestroyRecursive(node->right);
				delete node;
			}
		}
		int size()
		{
			return queueTime.size();
		}

		//^hàm thêm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên được chủ giao cho bố trí khách hàng có result
		Node *insert_recursive(Node *node, int result)
		{
			// TODO TODO TODO  TODO TODO TODO
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
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm xóa ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên sẽ tới tận nơi đuổi cổ khách hàng gián điệp ra khỏi nhà hàng với result là khách hàng gián điệp
		Node *remove_recursive(Node *node, int result)
		{
			// TODO TODO TODO  TODO TODO TODO
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
			// return C(CountNode(node->left),CountNode(node->right)+CountNode(node->left))*DFS(node->left)*DFS(node->right);
			int nleft = CountNode(node->left);
			int nRight = CountNode(node->right);
			return (unsigned long long) (dp[nleft + nRight][nleft]%MAXSIZE * (DFS(node->left, dp)%MAXSIZE * DFS(node->right, dp)%MAXSIZE)%MAXSIZE) % MAXSIZE;
		}
		void PascalTriangle(int n, vector<vector<long long>> &dp)
		{
			for (int i = 0; i <= n; i++)
			{
				dp[i] = vector<long long>(i + 1, 1); // initially all 1
				// Now Apply combination logic of adding prev_row and prev_col
				for (int j = 1; j < i; j++)
				{
					dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
				}
			}
		}
		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
		void remove()
		{
			if (this->size() == 0)
				return; //! trường hợp rỗng bỏ qua
			//* bước 1: đếm số lượng node cần xóa
			//^ tìm hiểu : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
			// TODO: tính số lượng number
			vector<vector<long long>> dp(queueTime.size() + 1);
			PascalTriangle(queueTime.size(), dp);
			unsigned long long number = DFS(root, dp);
			//* bước 2: xóa node trong cây với số lượng đã tính trên
			//* kiểm tra xem đã xóa đủ số lượng chưa hay cây đã hết node để xóa
			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		 //! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop();					 //! xóa nó khỏi sổ
				root = remove_recursive(root, temp); //! tới chỗ nó cho nó cút khỏi nhà hàng
				number--;
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node *node)
		{
			if (node == nullptr)
				return "NULL"; //! trường hợp dừng print

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);

			if (node->left == nullptr && node->right == nullptr)
				return to_string(node->result); //! tr
			return to_string(node->result) + "(" + left + "," + right + ")";
		}
		void print()
		{
			//! trường hợp rỗng bỏ qua
			if (this->size() == 0)
			{
				solution << "EMPTY";
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(root);
			solution << "\nTree: " << s;
			std::queue<int> tempQueue = queueTime;
			solution << "\nQueue: ";
			while (!tempQueue.empty())
			{
				solution << tempQueue.front() << " ";
				tempQueue.pop();
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

//* nhà hàng su cờ na
class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable; //! nơi lưu trữ các khu vực
	list<Node *> LRU;		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:
	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
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
		// TODO: với giá trị xét là areaTable[index].size()
		// TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		// TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khách vào gần nhất dùng list<Node* > LRU;
		// TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
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
		// TODO: với giá trị xét là areaTable[index].size()
		// TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		// TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất
		// TODO: này xử lí tương tự reheap_down
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

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node *node)
	{
		// TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		list<Node *>::iterator it = std::find(LRU.begin(), LRU.end(), node);
		// TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		if (it != LRU.end())
		{
			LRU.erase(it);
		}
		LRU.push_front(node);
	}

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
	void removeNode(Node *node)
	{
		// TODO:
		list<Node *>::iterator it = find(LRU.begin(), LRU.end(), node);
		LRU.erase(it);
	}

public:
	RESTAURANT_Sukuna() {}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		// TODO bước 1
		for (int i = 0; i < areaTable.size(); i++)
		{
			if (ID == areaTable[i]->ID)
				index = i;
		}
		//*bước 2: xem thử có khu này trong heap chưa để thêm vô
		if (index == -1)
		{
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hành reheap down bàn này xuống vì có số khách đông hơn
		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;

		//* TẠO ra heap mới sao chép từ heap cũ
		vector<Node* > areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node* > listDelete; //! danh sách các khu cấn xóa
		for(int i = 0; i < areaTable.size() && i < number; i++)
		{
			//* lấy ra phần tử đầu tiên trong heap
			Node* nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);

			//* đưa vào danh sách cần xóa
			listDelete.push(nodeDelete);
		}

		//* trả lại heap
		areaTable = areaTableNew;

		//* đuổi num khách hàng tại num khu vực
		while(listDelete.size()){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			Node* nodeDelete = listDelete.front();
			listDelete.pop();

			solution << "remove customers in the area ID = " << nodeDelete->ID <<"(len=" <<nodeDelete->head.size()<< ")" << ": ";
			nodeDelete->remove(number);
			solution << "\n";

			//* tìm vị trí của nó trong heap
			int index = 0;
			while(areaTable[index] !=  nodeDelete) index++;

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
 	}
	//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void print_pre_order(int index, int number)
	{
		if (index >= this->areaTable.size())
			return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_CLEAVE(int number)
	{
		if (number <= 0)
			return;

		solution << "Heap : ";
		for (auto it : this->areaTable)
		{
			int order = 0;
			for (auto ix : LRU)
			{
				if (ix == it)
					break;
				++order;
			}
			solution << it->ID << "(len=" << it->size() << ",index=" << order << ")"
					 << " ";
		}
		solution << "\n";

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
		//* thêm vô đầu danh sách
		void insert(int result) { head.push_front(result); }
		//* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
		void remove(int number)
		{
			// TODO: xóa number khách hàng ở cuối danh sách tương ứng với vô sớm nhất

			while (number-- && head.size() > 0)
			{
				solution << head.back() << " ";
				head.pop_back();
			}
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
			// if(head.size()>0) solution << head.back() << " ";
		}
		//* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << ": ";
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
	//* đầu vào là 1 chuỗi -> đầu ra chuỗi name đã được mã hóa Caesar và trả về danh sách freq có thứ tự giảm dần
	vector<pair<char, int>> string_Processing(string &name)
	{
		//* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
		//* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau
		//! VD : name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		// TODO

		unordered_map<char, int> mp;
		for (char &x : name)
			mp[x]++;
		int numPair = mp.size();
		vector<pair<char, int>> freq_prev;
		for (pair<char, int> x : mp)
		{
			freq_prev.push_back(x);
		}

		//* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev
		//! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]
		// TODO
		for (char &x : name)
			x = encode(x, mp[x]);
		for (pair<char, int> &x : freq_prev)
			x.first = encode(x.first, x.second);

		//* bước 3: công dồn freq_prev với các kí tự giống nhau sau khi mã hóa
		//^ chú ý cộng dồn lên phái đầu ví dụ dưới 'e' có 2 chỗ nên ta chọn đầu vector để giữ lại
		//! vd freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] -> kq:  freq = [{e,5}, {E,1}, {f,4}]
		// TODO
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
		//* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
		//^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
		// TODO
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
		//* vẽ ra mới thấy nha các bạn ngồi nghĩ chắc tới mai
		//* ví dụ cây này đi A (B (D, E), C)  xem mấy này là node nha thật ra là cây con ví dụ cây con chỉ có 1 node cho dễ
		/*
		 *            A                                          B
		 *           / \                                        / \
		 *          B   C        <--right router-->            D   A
		 *         / \                                            / \
		 *        D   E                                          E   C
		 */
		Node *Node_B = Node_A->left;  //! này là B
		Node *Node_E = Node_B->right; //! này là E

		Node_A->left = Node_E;	//! CẬP NHẬT NODE E
		Node_B->right = Node_A; //! CẬP NHẬT NODE A

		return Node_B; //! NODE B đang là root
	}

	Node *leftRotate(Node *Node_A)
	{
		//* vẽ ra mới thấy nha các bạn ngồi nghĩ chắc tới mai
		//* ví dụ cây này đi A (B (D, E), C)  xem mấy này là node nha thật ra là cây con ví dụ cây con chỉ có 1 node cho dễ
		/*
		 *            A                                          C
		 *           / \                                        / \
		 *          B   C        <-- left router-->            A   E
		 *             / \                                    / \
		 *            D   E                                  B   D
		 */

		Node *Node_C = Node_A->right; //! này là C
		Node *Node_D = Node_C->left;  //! này là D

		Node_A->right = Node_D; //! CẬP NHẬT NODE D
		Node_C->left = Node_A;	//! CẬP NHẬT NODE A

		return Node_C; //! NODE C đang là root
	}
	enum class BalanceState
	{
		LEFT_HEAVY,
		BALANCED,
		RIGHT_HEAVY
	};
	BalanceState getBalanceState(Node *node)
	{
		//* rỗng thì hight cây con bên trái = hight cây con bên phải -> nên cân bằng
		if (node == nullptr)
			return BalanceState::BALANCED;

		//* lấy chiều cao cây con bên trái và bên phải
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);

		//* xem thử lệch bên nào rồi
		int balance = leftHeight - rightHeight;

		//* lệch bên trái rồi chiều cao bên trái cao hơn -> (lệch ở đây nghĩ là bên trái cao hơn thôi còn cao hơn nhiêu thì khôn cần biết)
		if (balance > 1)
			return BalanceState::LEFT_HEAVY;
		//* lệch bên phải rồi
		else if (balance < -1)
			return BalanceState::RIGHT_HEAVY;
		//* cân bằng Là 2 chiều cao không lệch nhau quá 1 đơn vị
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

		//* LEFT OF LEFT -> nghĩa là cây con bên trái đang cao hơn cây con bên phải 2 đơn vị:  left - right = 2, với thêm bên trái của cây con bên trái
		if (rootState == BalanceState::LEFT_HEAVY && balanceLeft >= 0)
		{
			//* mất cân bằng bên trái thì quay phải thôi
			//* ví dụ dễ hiểu nhất là A (B (C))  -> link list bên trái
			count += 1;
			return rightRotate(node);
		}
		//* RIGHT OF RIGHT -> nghĩa là cây con bên trái đang thấp hơn cây con bên phải 2 đơn vị:  left - right = -2, với thêm bên phải của cây con bên phải
		if (rootState == BalanceState::RIGHT_HEAVY && balanceRight <= 0)
		{
			//* mất cân bằng bên phải thì quay trái thôi
			//* ví dụ dễ hiểu nhất là A (null, B (null , C))  -> link list bên phải
			count += 1;
			return leftRotate(node);
		}
		//* LEFT OF RIGHT -> nghĩa là cây con bên trái đang cao hơn cây con bên phải 2 đơn vị:  left - right = 2, với thêm bên phải của cây con bên trái
		if (rootState == BalanceState::LEFT_HEAVY && balanceLeft <= -1)
		{
			//* xoay phải cây con bên trái trước
			//* ví dụ dễ hiểu nhất là A (B (null, C)) sau xoay A (C (B)) -> đã trở thành LEFT OF LEFT
			node->left = leftRotate(node->left);
			count += 1;
			//* cây đã thành LEFT OF LEFT -> giống trên
				return rightRotate(node);
		}

		//* RIGHT OF LEFT -> nghĩa là cây con bên trái đang thấp hơn cây con bên phải 2 đơn vị:  left - right = -2, với thêm bên trái của cây con bên phải
		if (rootState == BalanceState::RIGHT_HEAVY && balanceRight >= 1)
		{
			//* xoay trái cây con bên phải trước
			//* ví dụ dễ hiểu nhất là A (Null, B (C)) sau xoay A (Null,B (Null,C)) -> đã trở thành RIGHT OF RIGHT
			node->right = rightRotate(node->right);
			count += 1;
			//* cây đã thành RIGHT OF RIGHT -> giống trên
				return leftRotate(node);
		}

		//* không bị mất cân bằng thì thôi
		return node;
	}

	//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
	Node *balanceTree(Node *node, int &count)
	{
		// TODO
		if (!node || count >= 3)
			return node;
		node = balanceNode(node, count);
		node = balanceNode(node, count);
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
		//* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
		// TODO: này không làm được đăng kí môn đi nha
		vector<Node *> build;
		for (int i = 0; i < (int)freq.size(); i++)
		{
			Node *x = new Node(freq[i].second, freq[i].first);
			build.push_back(x);
		}
		Node *res = nullptr;
		while (build.size() > 1)
		{
			// TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
			// TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node
			// TODO: nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
			//^ chú ý : cập nhật height, weight
			int count = 0;
			Node *newNode = nullptr;
			Node *left = build.back();
			build.pop_back();
			Node *right = build.back();
			build.pop_back();
			newNode = new Node(left->weight + right->weight, '\0', left, right);

			// TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
			//^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn
			build.push_back(newNode);
			newNode = balanceTree(newNode, count);
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
	//* TIẾN HÀNH đệ quy để lấy ra ra kết quả encoding
	//^ chú ý: cứ node bên trái thì mã hóa là '0', node bên phải mã hóa là '1'.
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		// TODO
		if (node == nullptr)
			return;
		encoding[node->c] = s;
		encodingHuffman_rec(encoding, node->left, s + "0");
		encodingHuffman_rec(encoding, node->right, s + "1");
	}
	int binaryStringToDecimal(const std::string &binaryString)
	{
		std::bitset<16> binaryNumber(binaryString); // Sử dụng std::bitset với kích thước tối đa là 64 bits

		// Chuyển đổi từ nhị phân sang thập phân

		return static_cast<int>(binaryNumber.to_ulong());
	}

	//* đầu vào là 1 cây và name đã được mã hóa Caesar -> đầu ra là result kết quả cần tìm.
	int encodingHuffman(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr)
			return 0;

		//* bước 1: lấy chuỗi kết quả của các kí tự đã mã hóa
		//* ví dụ cây 2('a', 'b') ta lưu encoding['a'] = '0' và encoding['b'] = '1'
		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);

		//* bước 2 lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái
		//! VD : 00000000000000000001 -> kq: 10000000000
		//^ chú ý: đừng có mà giải mã hết nameCaesar -> giải mã khi nào đủ 10 kí tự nhị phân là dừng
		// TODO
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
		//* bước 3 mã hóa binary sang thập phân -> này ez rồi
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
		for (int i = 0; i < freq.size(); i++)
		{
			if (i == freq.size() - 1)
				solution << "{"
						 << "'" << freq[i].first << "'"
						 << "," << freq[i].second << "}";
			else
				solution << "{"
						 << "'" << freq[i].first << "'"
						 << "," << freq[i].second << "},";
		}
		solution << "}" << endl;

		//* bước 2 xây dựng cây huff
		root = this->buildHuff(freq);

		if (root->left == nullptr && root->right == nullptr)
			return 0; //! trường hợp chỉ có 1 node
		this->print();

		//* bước 3 mã hóa.
		solution << "name   = " << name << endl;
		int result = this->encodingHuffman(root, name);
		solution << "result = " << result << endl;
		return -1;
	}

	void rec_print(const Node *tree)
	{
		if (tree == nullptr)
		{
			return;
		}
		if (tree->c)
			solution << "[" << tree->weight << "," << tree->c << "]";
		else
			solution << "[" << tree->weight << "]";

		if (tree->left != nullptr || tree->right != nullptr)
		{
			solution << "(";
			rec_print(tree->left);
			solution << ",";
			rec_print(tree->right);
			solution << ")";
		}
	}

	void print()
	{
		//* print theo chiều rộng anh có hướng dẫn rồi queue
		//* khi in chuyển từ cout << "char-freq/n" thành solution << "char-freq/n" cho anh dễ test
		solution << "root : ";
		rec_print(root);
		solution << '\n';
	}

private:
	class Node
	{
	public:
		int weight;
		int height;
		char c;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : height(1), weight(weight), c(c), left(left), right(right) {}
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
		//* mã hóa HuffTree_AVL kết quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		return;
	}

	//* xử lí nhà hàng gojo
	void KOKUSEN() {}
	void LIMITLESS(int num) {}

	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num) {}
	void CLEAVE(int num) {}

	//* xử lý HuffTree_AVL
	void HAND() { New_customers_arrive.print(); }
};
