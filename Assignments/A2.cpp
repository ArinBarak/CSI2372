//Assignment 2

#include <iostream>
#include <list>
using namespace std;

class Graph{
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

    void add_edge(const int v1, const int v2){
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
    
    bool remove_edge(const int v1, const int v2){
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

        return false;
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
    
    int connectivity_type() {
    if (size == 0) return 0;
    
    list<int> dfs_result = DFS(1);
    if (dfs_result.size() != size) return 0; 
    
    Graph transposed(size);
    for (int v1 = 1; v1 <= size; v1++) {
        Node* current = adjacency_list[v1 - 1]->next;
        while (current != nullptr) {
            transposed.add_edge(current->vertex, v1);
            current = current->next;
        }
    }

    list<int> transposed_dfs_result = transposed.DFS(1);
    if (transposed_dfs_result.size() != size) return 0; 
    
    if (dfs_result.size() == size && transposed_dfs_result.size() == size) {
        return 3;
    }

    Graph undirected(size);
    for (int v1 = 1; v1 <= size; v1++) {
        Node* current = adjacency_list[v1 - 1]->next;
        while (current != nullptr) {
            undirected.add_edge(v1, current->vertex);
            undirected.add_edge(current->vertex, v1);
            current = current->next;
        }
    }

    list<int> undirected_dfs_result = undirected.DFS(1);
    if (undirected_dfs_result.size() != size) return 1;

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (i != j) {
                if (!path_exist(i, j) && !path_exist(j, i)) {
                    return 0;
                }
            }
        }
    }
    return 2;
}

    list<int> BFS(const int n1){
        list<int> result;
        list<int> queue;
        bool* visited = new bool[size];

        for (int i=0; i<size; i++){
            visited[i] = false;
        }

        visited[n1-1] = true;
        queue.push_back(n1);

        while (!queue.empty()){
            int v1 = queue.front();
            queue.pop_front();
            result.push_back(v1);

            Node* current = adjacency_list[v1-1];
            while (current != nullptr){
                if (visited[current->vertex-1] != true){
                    visited[current->vertex-1] = true;
                    queue.push_back(current->vertex);
                }
                current = current->next;
            }            
        }
        delete[] visited;
        return result;
    }
    
    list<int> DFS(const int n1){
        list<int> result;
        list<int> stack;
        bool* visited = new bool[size];

        for (int i=0; i<size; i++){
            visited[i] = false;
        }

        stack.push_back(n1);

        while (!stack.empty()){
            int cv= stack.back();
            stack.pop_back();

            if (!visited[cv-1]){
                visited[cv-1]=true;
                result.push_back(cv);

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
        return result;
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

void main(){
    Graph graph(6);

    graph.add_edge(1,2);
    graph.add_edge(2,1);
    graph.add_edge(2,3);
    graph.add_edge(2,4);
    graph.add_edge(3,3);//
    graph.add_edge(4,1);
    graph.add_edge(4,3);
    graph.add_edge(5,6);
    graph << graph ;

    graph.add_edge(6,2);
    graph << graph;
    
    graph.remove_edge(6,2);
    graph << graph;

    ++graph;
    graph << graph;

    graph.add_edge(1,7);
    graph.add_edge(3,7);
    graph.add_edge(7,5);
    graph << graph;

    --graph;
    graph << graph;

    cout<<"Edge between 1 and 3: "<< (graph.edge_exist(1,3) ? "true" : "false") <<endl;
    cout<<"Edge between 2 and 5: "<< (graph.edge_exist(2,5) ? "true" : "false")<<endl;
    cout<<"Edge between 4 and 3: "<< (graph.edge_exist(4,3) ? "true" : "false")<<endl;

    cout<<"Degree of 1:"<< graph.get_degree(1)<<endl;
    cout<<"Degree of 4:"<< graph.get_degree(4)<<endl;
    cout<<"Degree of 6:"<< graph.get_degree(6)<<endl;

    cout<< "Path between 1 and 6: "<< (graph.path_exist(1,6) ? "true" : "false")<<endl;
    cout<< "Path between 1 and 3: "<< (graph.path_exist(1,3) ? "true" : "false")<<endl;
    cout<< "Path between 6 and 4: "<< (graph.path_exist(6,4) ? "true" : "false")<<endl;

    list<int> res = graph.BFS(1);
    cout<< "BFS for the graph";
    for (int v : res) {
        cout << ' ' << v;
    }
    cout << endl;

    list<int> res2 = graph.DFS(1);
    cout<< "DFS for the graph";
    for (int v : res2) {
        cout << ' ' << v;
    }
    cout << endl;

}
