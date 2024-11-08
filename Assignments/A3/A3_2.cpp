//Assignment 3
//main A3 source code

#include "A3.cpp"
#include <iostream>
#include <vector>

class Forest : public Graph{
public:
    //constructor of Forest Class
    Forest(int n) : Graph(n) {}  

    //Adds an edge to the forest
    void add_edge(const int v1, const int v2) override {
        //if (size<=2){
        //    Graph::add_edge(v1, v2);
        //}else{
            if (!forms_cycle(v1, v2)){
                Graph::add_edge(v1,v2);
            }else{
                std::cout<<"Can not add edge between "<< v1 <<" and "<< v2 << " , it forms a cycle!"<<endl;
            }
        //}
    }
private:
    //checks if the addition of an edge between the given vertices creates a cycle
    bool forms_cycle(const int v1, const int v2){
        return Graph::path_exist(v1, v2);
    }
};

class Tree : public Forest {
private:
    int root;
    int last;
public:
    //constructor of Tree Class
    Tree() : Forest(1), root(0), last(1) {}

    //adds a vertex to the tree and connects it with the last vertex added to the tree
    void operator++(){
        Graph::operator++();
        if (size>1){
            Graph::add_edge_d(last, size);
        }
        last = size;
    }

    //deletes the last vertex added to the tree, unless it's the root
    void operator--(){
        if (root != last){
            if (size == 0) return ;
            Node* current = adjacency_list[size-1]->next;

            while (current != nullptr){
                Node* temp = current;
                current = current->next;
                delete temp;
            }

            for (int i=1; i<size+1; i++){
                if (edge_exist(i, size)){
                    remove_edge(i, size);
                }
            }

            delete adjacency_list[size-1];
            size--;
            last--;
        }
    }

    //sets the root
    void set_root(const int a){
        if (a <= size){
            root = a;
        }else{
            std::cout<< "No such vertex exists."<<endl;
        }
    }

    //creates a vertex and connects it to the given vertex
    void add_vertex(const int v){
        Graph::operator++();
        Graph::add_edge_d(v, size);
        last = size;
    }

    friend std::ostream& operator<<(std::ostream& os,const Tree& t){
        os<< "----------------"<<std::endl;
        os<<t.root<<std::endl;
        vector<bool> visited(t.size, false);
        t.print_adjacents(t.root, os, 1, visited);
        return os;
    }

    //helper function for the "operator<<" overload
    void print_adjacents(const int v, std::ostream& os, int depth, vector<bool> vis) const{
        vis[v-1] = true;
        Node* current = adjacency_list[v-1]->next;
        while (current!=nullptr ){
            for (int i=0; i< depth; ++i) os << "   ";
            os<<"---"<<current->vertex<<std::endl;
            print_adjacents(current->vertex, os, depth+1, vis);
            current = current->next;
        }
    }
};

int main(){
    Forest forest = Forest(4);
    forest.add_edge(1, 2);
    forest.add_edge(2, 3);
    forest.add_edge(3, 4);
    forest.add_edge(1, 3);
    forest.add_edge(1, 4);
    forest.operator<<(forest);


    Tree tree;
    tree.set_root(1); 
    std::cout<<tree;
    
    ++tree; //creation of vertex 2
    ++tree; //creation of vertex 3
    std::cout << tree; 
    --tree; //deletion of vertex 3
    std::cout << tree;
    ++tree; //recreation of vertex 3
    tree.add_vertex(2); //creation of vertex 4 and connection of vertex 4 to the vertex 2
    std::cout << tree;

    tree.add_vertex(1); //creation of vertex 5 and connection of vertex 5 to the vertex 1
    ++tree; //creation of vertex 6
    ++tree; //creation of vertex 7
    tree.add_vertex(1); //creation of vertex 8, connection to the vertex 1
    std::cout <<tree;
    return 0;
}
