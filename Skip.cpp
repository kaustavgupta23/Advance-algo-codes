#include <bits/stdc++.h>
using namespace std;
int maxLevel=5;
class Node
{
public:
    int data;
    vector<Node *> next;                                                // To maintain the levels of the skip list
    Node(int data, int Level) : data(data), next(Level + 1, nullptr) {} // declaring the data and the level of the node
};


class skipList
{
public:
    Node *head;
    int Level;

    skipList()
    {
        head = new Node(0, maxLevel);
        Level = 0;
    };





    void insert(int data)
    {
      
        int newLevel=0;

        while(newLevel<maxLevel && rand()%2==1)
        {
            newLevel++;
        }
        if(newLevel>Level)
        {
             head->next.resize(newLevel + 1, nullptr);

            Level = newLevel;
        }
     Node *current = head;
     vector<Node *> Update(Level + 1, nullptr); 
        for(int i=Level;i>=0;i--)
        {
            while(current->next[i]  && current->next[i]->data<data)
            {
                current=current->next[i];
            }
            Update[i]=current;

        }
        current=current->next[0];



         if (current == nullptr or current->data != data)//data is not present
        {
            Node *newNode = new Node(data, newLevel);

            for (int i = 0; i <= newLevel; i++)
            {
                newNode->next[i] = Update[i]->next[i];

                Update[i]->next[i] = newNode; // To insert the value at each level
            }

            cout << "Element " << data << " inserted successfully.\n";
        }
        else
        {
            cout << "Element " << data << " already exists.\n"; // Incase if value already exists
        }
    }






       void remove(int data)
    {

        
        Node *current = head; 

        vector<Node *> Update(Level + 1, nullptr); 

        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] and current->next[i]->data < data)
            {
                current = current->next[i];
            }

            Update[i] = current; 
        }

        current = current->next[0]; 

        if (current != nullptr and current->data == data) //val is present del val
        {
            for (int i = 0; i <= Level; i++)
            {
               
                if (Update[i]->next[i] != current)
                {
                    break;
                }
                else
                {
                    Update[i]->next[i] = current->next[i];
                }
            }

           

            while (Level > 0 and head->next[Level] == nullptr) 
            {
                Level--;
            }

            cout << "Element " << data << " deleted successfully." << endl;
        }
        else 
        {
            cout << "Element " << data << " not found." << endl;
        }

    } 


    bool search(int data)
    {
        Node *current = head; 

        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] and current->next[i]->data < data) 
            {
                current = current->next[i]; // moving forward
            }
        }

        current = current->next[0]; 

        if (current != nullptr && current->data == data) 
        {
            cout << "Element " << data << " found.\n";
            return true;
        }
        else // Incase value does not exist
        {
            cout << "Element " << data << " not found.\n";
            return false;
        }

    } 
    void display()
    {
        cout << "skip List:" << endl;

        for (int i = Level; i >= 0; i--) 
        {
            Node *current = head->next[i]; 

            cout << "Level " << i << ": ";

            while (current != nullptr) 
            {
                cout << current->data << " ";
                current = current->next[i]; 
            }
            cout << endl;
        }

    } 
};

int main(){
    std::srand(static_cast<unsigned>(std::time(0)));
    skipList sl;
    sl.insert(10);
    sl.insert(20);
    sl.insert(30);
    sl.insert(40);
    sl.insert(50);



    sl.display();



     sl.search(80);
    sl.search(50);

    sl.remove(40);
     sl.display();
    return 0;
}