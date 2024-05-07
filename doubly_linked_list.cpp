#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int data;
    Node *prev;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class DoublyLinkedList
{
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    // Function to insert a node at the front of the list
    void insertFront(int data)
    {
        Node *new_node = new Node(data);
        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    // Function to insert a node at the end of the list
    void insertEnd(int data)
    {
        Node *new_node = new Node(data);
        if (tail == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    // Function to delete a node from the front of the list
    void deleteFront()
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        tail = head == nullptr ? nullptr : tail;
        delete temp;
    }

    // Function to delete a node from the end of the list
    void deleteEnd()
    {
        if (tail == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *temp = tail;
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        head = tail == nullptr ? nullptr : head;
        delete temp;
    }

    // Function to insert a node after a given key
    bool insertAfter(int key, int data)
    {
        Node *temp = head;

        while (temp != NULL && temp->data != key)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            cout << "Key not found" << endl;
            return false;
        }
        if (temp->data == key)
        {
            Node *new_node = new Node(data);
            new_node->next = temp->next;
            new_node->prev = temp;
            if (tail == temp)
                tail = new_node;

            if (temp->next != NULL)
            {
                new_node->next->prev = new_node;
            }

            temp->next = new_node;

            return true;
        }
        return false;
    }

    // Function to delete a node with a given key
    bool deleteNode(int key)
    {
        Node *temp = head;
        while (temp != nullptr && temp->data != key)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            cout << "Key not found" << endl;
            return false;
        }

        if (temp == head)
        {
            head = temp->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
        }
        else
        {
            temp->prev->next = temp->next;
            if (temp->next != nullptr)
            {
                temp->next->prev = temp->prev;
            }
            else
            {
                tail = temp->prev;
            }
        }

        delete temp;
        return true;
    }

    // Function to update the data of a node with a given key
    void update(int key, int new_data)
    {
        Node *temp = head;
        while (temp != nullptr && temp->data != key)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            cout << "Key not found" << endl;
            return;
        }
        temp->data = new_data;
    }

    // Function to count the number of nodes in the list
    int countNodes()
    {
        int count = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Function to check if a loop exists in the linked list
    bool detectLoop()
    {
        if (head == nullptr || head->next == nullptr)
            return false;

        Node *slow = head;
        Node *fast = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true; // Loop detected
        }

        return false; // No loop detected
    }

    // Function to display the list in forward order and return a vector
    vector<int> displayForward()
    {
        vector<int> result;
        Node *temp = head;
        while (temp != nullptr)
        {
            result.push_back(temp->data);
            temp = temp->next;
        }
        // cout << "displayForward" << endl;
        return result;
    }

    // Function to display the list in backward order and return a vector
    vector<int> displayBackward()
    {
        vector<int> result;
        Node *temp = tail;
        while (temp != nullptr)
        {
            result.push_back(temp->data);
            temp = temp->prev;
        }
        return result;
    }

    // Function to reverse the list
    void reverse()
    {
        Node *current = head;
        Node *temp = nullptr;
        while (current != nullptr)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr)
        {
            head = temp->prev;
        }
    }

    // Function to sort the list
    void sort()
    {
        Node *current = head;
        Node *index = nullptr;
        int temp;
        while (current != nullptr)
        {
            index = current->next;
            while (index != nullptr)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    void create_loop()
    {
        Node *temp = head;
        if (head == nullptr)
        {
            return;
        }
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = head->next;
    }

    ~DoublyLinkedList()
    {
        Node *temp;

        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// int main()
// {
//     DoublyLinkedList dll;
//     dll.insertEnd(1);
//     dll.insertFront(2);
//     dll.insertEnd(3);
//     dll.insertFront(4);
//     dll.insertEnd(5);

//     cout << "Forward traversal:" << endl;
//     dll.displayForward();
//     cout << "Backward traversal:" << endl;
//     dll.displayBackward();

//     dll.deleteFront();
//     dll.deleteEnd();

//     cout << "Forward traversal after deleting front and end:" << endl;
//     dll.displayForward();

//     dll.insertAfter(2, 6);
//     cout << "Forward traversal after inserting 6 after 2:" << endl;
//     dll.displayForward();

//     dll.deleteNode(3);
//     cout << "Forward traversal after deleting node with data 3:" << endl;
//     dll.displayForward();

//     dll.update(2, 7);
//     cout << "Forward traversal after updating node with data 2 to 7:" << endl;
//     dll.displayForward();

//     cout << "Reversed list:" << endl;
//     dll.reverse();
//     dll.displayForward();

//     cout << "Sorted list:" << endl;
//     dll.sort();
//     dll.displayForward();

//     cout << "Number of nodes in the list: " << dll.countNodes() << endl;

//     return 0;
// }
