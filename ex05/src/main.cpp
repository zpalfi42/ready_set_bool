#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

enum class NodeType {
    OPERAND,
    AND,
    OR,
    NOT,
    IMPLIES,
    EQUIV
};

struct Node
{
    NodeType    type;
    char        value;
    Node        *left_child;
    Node        *right_child;

    Node(const char v, const NodeType t): type(t), value(v), left_child(nullptr), right_child(nullptr){}
};

std::string treeToString(Node* node) {
    if (!node) {
        return "";
    }

    switch (node->type) {
        case NodeType::OPERAND:
            return std::string(1, node->value); // Convert char to string

        case NodeType::NOT:
            return treeToString(node->left_child) + "!";

        case NodeType::AND:
            return treeToString(node->left_child) + treeToString(node->right_child) + "&";

        case NodeType::OR:
            return treeToString(node->left_child) + treeToString(node->right_child) + "|";

        // IMPLIES and EQUIV nodes should *not* exist in the NNF tree at this point
        // because convertToNNF transformed them away. If they appear here, it's an error.
        case NodeType::IMPLIES:
        case NodeType::EQUIV:
            std::cerr << "Error: IMPLIES or EQUIV node found in NNF tree during string conversion." << std::endl;
            return ""; // Or throw an exception
    }
    return ""; // Should not reach here
}

Node    *convertToNNF(Node *node);

Node    *NegateNNF(Node *node)
{
    if (!node)
        return nullptr;
    switch (node->type)
    {
    case NodeType::OPERAND: // A BECOMES !A
    {        
        Node    *newNodeOP = new Node('!', NodeType::NOT);
        newNodeOP->left_child = node;
        return newNodeOP;
    }
    case NodeType::NOT: // !!A BECOMES A
    {
        Node    *newNodeNOT = node->left_child;
        delete node;
        return convertToNNF(newNodeNOT->left_child);
    }
    case NodeType::AND: // !(A & B) BECOMES !A | !B
    {
        Node    *newNodeAND = new Node('|', NodeType::OR);
        newNodeAND->left_child = NegateNNF(node->left_child);
        newNodeAND->right_child = NegateNNF(node->right_child);
        delete node;
        return newNodeAND;
    }
    case NodeType::OR: // !(A | B) BECOMES  !A & !B
    {
        Node    *newNodeOR = new Node('&', NodeType::AND);
        newNodeOR->left_child = NegateNNF(node->left_child);
        newNodeOR->right_child = NegateNNF(node->right_child);
        delete node;
        return newNodeOR;
    }
    case NodeType::IMPLIES: // !(A > B) BECOMES A & !B
    {
        Node    *newNodeIMP = new Node('&', NodeType::AND);
        newNodeIMP->left_child = convertToNNF(node->left_child);
        newNodeIMP->right_child = NegateNNF(node->right_child);
        delete node;
        return newNodeIMP;
    }
    case NodeType::EQUIV: // !(A = B) BECOMES (!A | !B) & (A | B)
    {
        Node    *newNodeEQ = new Node('&', NodeType::AND);
        Node    *l = node->left_child;
        Node    *r = node->right_child;
        delete node;

        Node    *left = new Node('|', NodeType::OR);
        left->left_child = NegateNNF(l);
        left->right_child = NegateNNF(r);
        newNodeEQ->left_child = left;

        Node    *right = new Node('|', NodeType::OR);
        right->left_child = convertToNNF(l);
        right->right_child = convertToNNF(r);
        newNodeEQ->right_child = right;
        
        return newNodeEQ;
    }
    default:
        std::cerr << "Error with the formula 1" << std::endl;
        return nullptr;
    }
}

Node    *convertToNNF(Node *node)
{
    if (!node)
        return nullptr;
    switch (node->type)
    {
    case NodeType::OPERAND:
    {
        return node;
    }
    case NodeType::NOT:
    {
        Node*   child = node->left_child;
        delete  node;
        return  NegateNNF(child);
    }
    case NodeType::AND:
    {
        node->left_child = convertToNNF(node->left_child);
        node->right_child = convertToNNF(node->right_child);
        return node;
    }
    case NodeType::OR:
    {
        node->left_child = convertToNNF(node->left_child);
        node->right_child = convertToNNF(node->right_child);    
        return node;
    }
    case NodeType::IMPLIES: // A > B TURNS INTO !A | B
    {
        Node    *l1 = node->left_child;
        Node    *r1 = node->right_child;
        delete node;

        Node    *newNodeIMP = new Node('|', NodeType::OR);
        newNodeIMP->left_child = NegateNNF(l1);
        newNodeIMP->right_child = convertToNNF(r1);
        return  newNodeIMP;
    }
    case NodeType::EQUIV: // A = B TURNS INTO (A & B) | (!A & !B)
    {
        Node    *l = node->left_child;
        Node    *r = node->right_child;
        delete node;

        Node    *newNodeEQ = new Node('|', NodeType::OR);

        Node    *left = new Node('&', NodeType::AND);
        left->left_child = convertToNNF(l);
        left->right_child = convertToNNF(r);
        newNodeEQ->left_child = left;

        Node    *right = new Node('&', NodeType::AND);
        right->left_child = NegateNNF(l);
        right->right_child = NegateNNF(r);
        newNodeEQ->right_child = right;

        return  newNodeEQ;
    }
    default:
        std::cerr << "Error with the formula 2" << std::endl;
        return nullptr;
    }
}

std::string negation_normal_form(std::string formula)
{
    std::stack<Node*>  stack;
    for (char c: formula)
    {
        if (c >= 'A' && c <= 'Z')
        {
            Node    *newNode = new Node(c, NodeType::OPERAND);
            stack.push(newNode);
        }
        else if (c == '!' && stack.size() > 0)
        {
            Node    *childNode = stack.top(); stack.pop();
            Node    *newNode = new Node(c, NodeType::NOT);
            newNode->left_child = childNode;
            stack.push(newNode);
        }
        else if (stack.size() > 1)
        {
            Node    *right = stack.top(); stack.pop();
            Node    *left = stack.top(); stack.pop();
            NodeType    type;
            switch (c)
            {
                case '&':
                    type = NodeType::AND;
                    break;
                case '|':
                    type = NodeType::OR;
                    break;
                case '>':
                    type = NodeType::IMPLIES;
                    break;
                case '=':
                    type = NodeType::EQUIV;
                    break;
                default:
                    std::cerr << "Error with the formula 3" << std::endl;
                    return "";
            }
            Node    *newNode = new Node(c, type);
            newNode->left_child = left;
            newNode->right_child = right;
            stack.push(newNode);
        }
        else
        {
            std::cerr << "Error with the formula 4 ->" << stack.size() << "   ->   " << c << std::endl;
            return "";
        }
    }
    if (stack.size() != 1)
    {
        std::cerr << "Error with the formula 5" << std::endl;
        return "";
    }
    Node    *nnf_root = convertToNNF(stack.top());

    std::string res = treeToString(nnf_root);

    return res;
}

int main()
{
    std::cout << negation_normal_form("AB&!") << std::endl;
    std::cout << negation_normal_form("AB|!") << std::endl;
    std::cout << negation_normal_form("AB>") << std::endl;
    std::cout << negation_normal_form("AB=") << std::endl;
    std::cout << negation_normal_form("AB|C&!") << std::endl;
}