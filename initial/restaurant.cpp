#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

//* nhà hàng su cờ na
class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable; //! nơi lưu trữ các khu vực
	list<Node *> LRU;		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:
	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
	bool Compere(int index1, int index2)
	{
	}
	Node* whoFirst(Node* a, Node* b){
		list<Node*>::iterator it;
		for(it=LRU.begin();it!=LRU.end();it++){
			if(*it==a) return a;
			if(*it==b) return b;
		}	
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

		if(leftChild < areaTable.size()){
			if(areaTable[leftChild]->size() < areaTable[smallest]->size()){
				smallest = leftChild;
			}
			else if(areaTable[leftChild]->size() == areaTable[smallest]->size()){
				if(whoFirst(areaTable[leftChild],areaTable[smallest])==areaTable[leftChild]){
					smallest = leftChild;
				}
			}
		}
		if(rightChild < areaTable.size()){
			if(areaTable[rightChild]->size() < areaTable[smallest]->size()){
				smallest = rightChild;
			}
			else if(areaTable[rightChild]->size() == areaTable[smallest]->size()){
				if(whoFirst(areaTable[rightChild],areaTable[smallest])==areaTable[rightChild]){
					smallest = rightChild;
				}
			}
		}
		
		if(smallest != index){
			swap(areaTable[index],areaTable[smallest]);
			ReHeap_down(smallest);
		}
	}


	void ReHeap_up(int index)
	{
		// TODO: với giá trị xét là areaTable[index].size()
		// TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		// TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất
		// TODO: này xử lí tương tự reheap_down
		while (index > 0) {
            int parent = (index - 1) / 2;
            if (areaTable[index]->size() < areaTable[parent]->size() 
			|| (areaTable[index]->size()==areaTable[parent]->size() && whoFirst(areaTable[index],areaTable[parent])==areaTable[index])) {

                swap(areaTable[index], areaTable[parent]);
                index = parent;
            } 
            else break;
        }
	}

	// list<Node*>::iterator findNodeInList(Node* node){
	// 	list<Node*>::iterator it;
	// 	for(it=LRU.begin();it!=LRU.end();it++){
	// 		if(*it==node) return it;
	// 	}
	// 	return it;
	// }

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node *node)
	{
		// TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		list<Node*> ::iterator it = std::find(LRU.begin(),LRU.end(),node);
		// TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		if(it!=LRU.end()){
			LRU.erase(it);
		}
		LRU.push_front(node);
	
	}

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
	void removeNode(Node *node)
	{
		// TODO:
	}

public:
	RESTAURANT_Sukuna() {}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		// TODO bước 1
		for(int i=0;i<areaTable.size();i++){
			if(ID==areaTable[i]->ID) index=i;
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
		if (areaTable.size() <= 0)
			return;

		//* đuổi num khách hàng tại num khu vực
		int numberRemove = number;
		while (areaTable.size() != 0 && number != 0)
		{
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			solution << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			solution << "\n";

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if (areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number--;
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
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
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
			return dp[nleft + nRight][nleft] * DFS(node->left, dp) * DFS(node->right, dp);
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
			//*: trường hợp mà postoder cũng tạo ra một cây giống đó thì chỉ có 1 node -> nên không tính
			if (this->size() == 1)
				return;

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

class HuffTree_AVL
{
	class Node;

private:
	Node *root;

public:
	int encode(string name)
	{
		return stoi(name);
	}

	void print() {}

private:
	class Node
	{
	public:
		int weight;
		char c;
		int rankingPosition;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c, Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
		bool isLeaf() const { return left == nullptr && right == nullptr; }
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
		//* mã hóa HuffTree_AVL kế quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);

		//* phân chia nhà hàng
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
	void CLEAVE(int num) { heap.print_CLEAVE(num); }

	//* xử lý HuffTree_AVL
	void HAND() { New_customers_arrive.print(); }
};
