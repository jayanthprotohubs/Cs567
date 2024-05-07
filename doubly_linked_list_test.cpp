#include <deepstate/DeepState.hpp>
#include "doubly_linked_list.cpp"
#include <algorithm>

using namespace deepstate;

// Function to fill the list with random elements and return the elements in a vector
// fill randomly in front or end
void fill_random(DoublyLinkedList &list, vector<int> &elements)
{
    int data;
    if (list.isEmpty())
    {
        data = DeepState_Int();
        list.insertFront(data);
        elements.insert(elements.begin(), data);

        // fill the list with random elements
        while (DeepState_Bool())
        {
            if (DeepState_Bool())
            {
                data = DeepState_Int();
                list.insertFront(data);
                elements.insert(elements.begin(), data);

                data = DeepState_Int();
                list.insertFront(data);
                elements.insert(elements.begin(), data);
            }
            else
            {
                data = DeepState_Int();
                list.insertEnd(data);
                elements.push_back(data);

                data = DeepState_Int();
                list.insertEnd(data);
                elements.push_back(data);
            }
        }
    }
}

TEST(DoublyLinkedList, all)
{
    // cout << "**********TEST**********" << endl;
    DoublyLinkedList list;
    int data;

    vector<int> elements;

    // Insert elements into the list Randomly
    fill_random(list, elements);

    auto result = list.displayForward();
    ASSERT_EQ(result, elements) << "Random Insertion failed";

    // check if the list is empty
    if (list.isEmpty())
    {
        ASSERT_EQ(result.size(), 0) << "The list is not empty";
    }
    else
    {
        ASSERT_EQ(result.size(), elements.size()) << "The list is not the same as the vector";
    }

    // Testing reverse print
    result = list.displayBackward();
    vector<int> reversed_elements(elements.rbegin(), elements.rend());
    ASSERT_EQ(result, reversed_elements) << "display backward failed";

    // Testing the delete front function
    // filling the list to test the delete front and delete end functions
    fill_random(list, elements);

    // Removing random elements from the front of the list and the vector and checking if the list is the same as the vector
    while (DeepState_Bool() && !list.isEmpty() && elements.size() > 0)
    {
        list.deleteFront();
        elements.erase(elements.begin());
    }
    ASSERT_EQ(list.displayForward(), elements) << "deleting front failed";

    // Testing the delete end function
    // filling the list to test the delete front and delete end functions

    fill_random(list, elements);

    // Removing random elements from the end of the list and the vector and checking if the list is the same as the vector
    while (DeepState_Bool() && !list.isEmpty() && elements.size() > 0)
    {
        list.deleteEnd();
        elements.pop_back();
    }

    result = list.displayForward();
    if (list.countNodes() == elements.size() && list.countNodes() != 0)
    {
        ASSERT_EQ(result, elements) << "deleting end failed";
    }

    // test delete node
    fill_random(list, elements);
    int index = (DeepState_UInt()) % list.countNodes();
    list.deleteNode(elements[index]);
    elements.erase(elements.begin() + index);
    ASSERT_EQ(list.displayForward(), elements) << "deleting node failed";

    // Testing Insert After
    fill_random(list, elements);
    index = (DeepState_UInt()) % list.countNodes();
    int new_element = DeepState_Int();
    // cout<<"index: "<<index<<endl;
    // cout<<"element to insert after: "<<elements[index]<<endl;
    // cout<<"new element: "<<new_element<<endl;
    list.insertAfter(elements[index], new_element);
    elements.insert(elements.begin() + index + 1, new_element);
    ASSERT_EQ(list.displayForward(), elements) << "insert after failed";

    // Testing Update
    fill_random(list, elements);
    index = (DeepState_UInt()) % list.countNodes();
    new_element = DeepState_Int();
    list.update(elements[index], new_element);
    elements[index] = new_element;
    ASSERT_EQ(list.displayForward(), elements) << "update failed";

    // Testing reverse
    fill_random(list, elements);
    list.reverse();
    vector<int> reversed_elements2(elements.rbegin(), elements.rend());
    ASSERT_EQ(list.displayForward(), reversed_elements2) << "reverse failed";

    // Testing Reverse print
    // Debug
    // fill_random(list, elements);
    // cout<<"elements size: "<<elements.size()<<endl;
    // cout<<"count: "<<list.countNodes()<<endl;
    // result = list.displayForward();
    // cout<<"result: "<<result.size()<<endl;
    // for (int i = 0; i < elements.size(); i++)
    // {
    //     cout<<"Element: "<<elements[i]<<endl;
    //     cout<<"List: "<<list.displayBackward()[i]<<endl;
    // }

    //Testing Sort
    fill_random(list, elements);
    std::sort(elements.begin(), elements.end());
    list.sort();
    ASSERT_EQ(list.displayForward(), elements) << "sort failed";

    //Testing Loop
    fill_random(list, elements);
    // list.create_loop();
    ASSERT_EQ(list.detectLoop(), false) << "loop failed";
}