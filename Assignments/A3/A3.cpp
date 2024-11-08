//Assignment 3 (used for A3_2.cpp)

#include <iostream>
#include <list>
using namespace std;

class Graph{
protected:
    struct Node{
        int vertex;
        Node* next;

        Node(int number): vertex(number), next(nullptr){} 
    };

    Node** adjacency_list;
    int size;

public: 
    Graph(): size(0), adjacency_list(nullptr) {}

    Graph(int num): size(num){
        adjacency_list= new Node*[num];
        size = num;
        for(int i=0; i<num; i++){
            adjacency_list[i] =  new Node(i+1);
        }
    }

    Graph(const Graph& other) : size(other.size){
        adjacency_list = new Node*[size];

        for (int i=0; i<size; i++){
            adjacency_list[i] = new Node(i+1);
                Node** current = &adjacency_list[i];
                Node* other_current = other.adjacency_list[i];

                while (other_current != nullptr){
                    *current= new Node(other_current->vertex);
                    current = &(*current)->next;
                    other_current = other_current->next;
                }
        }
    }

    ~Graph(){
        for(int i=0; i<size; i++){
            Node* current = adjacency_list[i];
            while (current != nullptr){
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] adjacency_list;
    }

    void add_edge_d(const int v1, const int v2){
        if (edge_exist(v1, v2)) return;

        Node* current = adjacency_list[v1-1];
        if(get_degree(v1) == 0){
            current->next = new Node(v2);
            return;
        }

        while (current->next!= nullptr){
            current = current->next;
        }
        current->next= new Node(v2);
    }

    virtual void add_edge(const int v1, const int v2){ //to implement the undirectd graph
        add_edge_d(v1, v2);
        add_edge_d(v2, v1);
    }
    
    bool remove_edge_d(const int v1, const int v2){
        if (edge_exist(v1, v2)){
            Node* prev = adjacency_list[v1-1];
            Node* current = adjacency_list[v1-1]->next;
            while (current != nullptr){
                if (current->vertex==v2){
                    prev->next = current->next;
                    delete current;
                    return true;
                }
                prev = current;
                current = current->next;
            }
        }

        return false;
    }

    bool remove_edge(const int v1, const int v2){ //to implement the undirected graph
        return remove_edge_d(v1, v2) &&  remove_edge_d(v2, v1);
    }
    
    bool edge_exist(const int v1, const int v2){
        Node* current = adjacency_list[v1-1]->next;

        while (current!= nullptr){
            if (current->vertex == v2){
                return true;
            }
            current = current->next;
        }

        return false;
    }

    int get_degree(const int v){
        Node* current = adjacency_list[v-1];
        int deg = 0;
        current = current->next;
        while (current!= nullptr){
            deg++;
            current = current->next;
        }

        return deg;
    }

    void operator++(){
        Node** new_list = new Node*[size+1];
        for (int i =0; i<size; i++){
            new_list[i] = adjacency_list[i];
        }
        new_list[size] = new Node(size+1);
        delete[] adjacency_list;
        adjacency_list = new_list;
        size++;
    }

    void operator--(){
        if (size == 0) return ;
        Node* current = adjacency_list[size-1]->next;

        while (current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        for (int i=0; i<size; i++){
            if (edge_exist(i+1, size)){
                remove_edge(i+1, size);
            }
        }

        delete adjacency_list[size-1];
        size--;

    }

    bool path_exist(const int v1, const int v2){
        list<int> stack;
        bool* visited = new bool[size];
        for (int i = 0; i < size; i++) {
            visited[i] = false;
        }

        stack.push_back(v1);

        while (!stack.empty()) {
            int cv = stack.back();
            stack.pop_back();
            if (cv == v2) {
                delete[] visited;
                return true;
            }
            if (!visited[cv-1]) {
                visited[cv-1] = true;
                Node* current = adjacency_list[cv-1];
                while (current != nullptr){
                    if (!visited[current->vertex-1]){
                        stack.push_back(current->vertex);
                    }
                    current = current->next;
                }
            }
        }

        delete[] visited;
        return false; 
    }


    void operator<<(Graph& g) {
        cout<< "----------------"<<endl;
        cout<< "V ={";
        for(int i=0; i<g.size; i++){
            cout<< g.adjacency_list[i]->vertex;
            if (i< g.size-1){
                cout<<", ";
            }
        }
        cout<< "}\n";
        cout<< "E = \n{";
        for (int i=0; i<g.size; i++){
            cout<<"\n "<<g.adjacency_list[i]->vertex<<" => ";
            Node* current = g.adjacency_list[i]->next;
            if (current == nullptr){
                cout<<"None";
            }
            while (current!=nullptr){
                cout<<current->vertex;
                if(current->next != nullptr){
                    cout<<", ";
                }
                current = current->next;
            }
        }
        cout<<" \n}\n";
        cout<< "----------------"<<endl;
    }
};
