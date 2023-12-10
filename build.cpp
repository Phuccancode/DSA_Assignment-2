#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>
#include <sstream>
using namespace std;



class Node{
public:
    int weight;
    char c;
    int height;
    Node* left;
    Node* right;
    
    friend class HuffTree_AVL;
public:
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr): height(1), weight(weight), c(c), left(left), right(right) {}
};

std::string huffmanTreeToString(const Node* tree) ;




//********* CODE ********************************************************************

//TODO: điền code vào chú ý sau newNode = balanceTree(newNode, count); thêm dòng bên dưới in ra
	int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}
Node* rightRotate(Node* Node_A) {
    //* vẽ ra mới thấy nha các bạn ngồi nghĩ chắc tới mai
    //* ví dụ cây này đi A (B (D, E), C)  xem mấy này là node nha thật ra là cây con ví dụ cây con chỉ có 1 node cho dễ
    /*
    *            A                                          B
    *           / \                                        / \
    *          B   C        <--right router-->            D   A
    *         / \                                            / \
    *        D   E                                          E   C
    */
    Node* Node_B = Node_A->left; //! này là B
    Node* Node_E = Node_B->right; //! này là E

    Node_A->left = Node_E; //! CẬP NHẬT NODE E
    Node_B->right = Node_A; //! CẬP NHẬT NODE A


    return Node_B; //! NODE B đang là root
}

Node* leftRotate(Node* Node_A) {
    //* vẽ ra mới thấy nha các bạn ngồi nghĩ chắc tới mai
    //* ví dụ cây này đi A (B (D, E), C)  xem mấy này là node nha thật ra là cây con ví dụ cây con chỉ có 1 node cho dễ
    /*
    *            A                                          C
    *           / \                                        / \
    *          B   C        <-- left router-->            A   E
    *             / \                                    / \
    *            D   E                                  B   D
    */

    Node* Node_C = Node_A->right; //! này là C
    Node* Node_D = Node_C->left; //! này là D

    Node_A->right = Node_D; //! CẬP NHẬT NODE D
    Node_C->left = Node_A; //! CẬP NHẬT NODE A

    return Node_C; //! NODE C đang là root
}
enum class BalanceState {
    LEFT_HEAVY,
    BALANCED,
    RIGHT_HEAVY
};
BalanceState getBalanceState(Node* node) {
    //* rỗng thì hight cây con bên trái = hight cây con bên phải -> nên cân bằng
    if (node == nullptr) return BalanceState::BALANCED;

    //* lấy chiều cao cây con bên trái và bên phải
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    //* xem thử lệch bên nào rồi
    int balance = leftHeight - rightHeight;

    //* lệch bên trái rồi chiều cao bên trái cao hơn -> (lệch ở đây nghĩ là bên trái cao hơn thôi còn cao hơn nhiêu thì khôn cần biết)
    if (balance > 1) return BalanceState::LEFT_HEAVY;
    //* lệch bên phải rồi
    else if (balance < -1) return BalanceState::RIGHT_HEAVY;
    //* cân bằng Là 2 chiều cao không lệch nhau quá 1 đơn vị
    return BalanceState::BALANCED;
}

Node* balanceNode(Node* node, int& count)
{
    //TODO
    BalanceState rootState = getBalanceState(node);
    Node* leftNode = node->left;
    Node* rightNode = node->right;
    int balanceLeft = 0, balanceRight = 0;
    if (leftNode) balanceLeft = height(leftNode->left) - height(leftNode->right);
    if(rightNode) balanceRight = height(rightNode->left) - height(rightNode->right);

    //* LEFT OF LEFT -> nghĩa là cây con bên trái đang cao hơn cây con bên phải 2 đơn vị:  left - right = 2, với thêm bên trái của cây con bên trái
    if (rootState == BalanceState::LEFT_HEAVY && balanceLeft>=0) {
        //* mất cân bằng bên trái thì quay phải thôi
        //* ví dụ dễ hiểu nhất là A (B (C))  -> link list bên trái
        count += 1;
        return rightRotate(node);
    }
    //* RIGHT OF RIGHT -> nghĩa là cây con bên trái đang thấp hơn cây con bên phải 2 đơn vị:  left - right = -2, với thêm bên phải của cây con bên phải
    if (rootState == BalanceState::RIGHT_HEAVY && balanceRight <= 0) {
        //* mất cân bằng bên phải thì quay trái thôi
        //* ví dụ dễ hiểu nhất là A (null, B (null , C))  -> link list bên phải
        count += 1;
        return leftRotate(node);
    }
    //* LEFT OF RIGHT -> nghĩa là cây con bên trái đang cao hơn cây con bên phải 2 đơn vị:  left - right = 2, với thêm bên phải của cây con bên trái
    if (rootState == BalanceState::LEFT_HEAVY && balanceLeft<=-1) {
        //* xoay phải cây con bên trái trước
        //* ví dụ dễ hiểu nhất là A (B (null, C)) sau xoay A (C (B)) -> đã trở thành LEFT OF LEFT
        node->left = leftRotate(node->left);
        count += 2;
        //* cây đã thành LEFT OF LEFT -> giống trên
        return rightRotate(node);
    }

    //* RIGHT OF LEFT -> nghĩa là cây con bên trái đang thấp hơn cây con bên phải 2 đơn vị:  left - right = -2, với thêm bên trái của cây con bên phải
    if (rootState == BalanceState::RIGHT_HEAVY && balanceRight >= 1) {
        //* xoay trái cây con bên phải trước
        //* ví dụ dễ hiểu nhất là A (Null, B (C)) sau xoay A (Null,B (Null,C)) -> đã trở thành RIGHT OF RIGHT
        node->right = rightRotate(node->right);
        count += 2;
        //* cây đã thành RIGHT OF RIGHT -> giống trên
        return leftRotate(node);
    }

    //* không bị mất cân bằng thì thôi
    return node;

}

//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
Node* balanceTree(Node* node, int& count)
{
    //TODO
    if (count >= 3) return node;
    node = balanceNode(node, count);
    node -> left = balanceNode(node->left, count);
    node ->right = balanceNode(node->right, count);
    return node;
}

Node* buildHuff(vector<pair<char, int>> freq)
{
    //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
    //TODO: này không làm được đăng kí môn đi nha
    vector<Node*> build;
    for (int i = 0; i < (int)freq.size(); i++) {
        Node* x = new Node(freq[i].second, freq[i].first);
        build.push_back(x);
    }
    Node* res = nullptr;
    while (build.size() > 1)
    {
        //TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
        //TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node 
        //TODO: nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
        //^ chú ý : cập nhật height, weight
        int count = 0;
        Node* newNode = nullptr;
        Node* left = build.back(); build.pop_back();
        Node* right = build.back(); build.pop_back();
        newNode = new Node(left->weight + right->weight, '\0', left, right);
        
        //TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
        //^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn
        build.push_back(newNode);
        newNode = balanceTree(newNode, count);
        cout << "output_you = " << huffmanTreeToString(newNode) << "\n";
        if (build.back() != newNode) {
            build.pop_back(); build.push_back(newNode);
        }
        
        int newNodeIdx = build.size() - 1;
        while (newNodeIdx-1 >= 0 && build[newNodeIdx]->weight >= build[newNodeIdx - 1]->weight) {
            swap(build[newNodeIdx], build[newNodeIdx - 1]);
            newNodeIdx--;
        }

    }
    return build[0];
}
//* cout << "output_you = " << huffmanTreeToString(newNode) << "\n";
//* gửi phần vector<pair<char, int>> qua anh để anh chạy rồi bug cho dễ


//*********** code bên dưới không bận tâm ***************************
int main()
{
    //TODO nhập vector sai vào 
    vector<pair<char, int>> v = {{'i',14},{'y',4},{'x',4},{'m',4},{'d',4},{'t',3},{'p',3},{'n',3},{'k',3},{'g',2},{'a',2},{'v',1},{'r',1},{'j',1}};
    
    //TODO test
    Node* result = buildHuff(v);
    cout << "output_you = " << huffmanTreeToString(result) << "\n";
    return 1;
}

std::string huffmanTreeToString(const Node* tree) {
    std::stringstream ss;

    if (tree == nullptr) {
        return "";
    }

    if (tree->c) {
        ss << "[" << tree->weight << "," << tree->c << "]";
    } else {
        ss << "[" << tree->weight << "]";
    }

    if (tree->left != nullptr || tree->right != nullptr) {
        ss << "(";
        ss << huffmanTreeToString(tree->left);
        ss << ",";
        ss << huffmanTreeToString(tree->right);
        ss << ")";
    }

    return ss.str();
}
