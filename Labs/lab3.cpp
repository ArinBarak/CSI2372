//CSI2372 LAB 3
#include <iostream>
#include <string>

using namespace std;

//Question 1
string compare_strings(string* str1, string* str2){
    int i=0;
    
    while (true){
        if (*(str1+i) < *(str2+i)){
            return *str1;
            break;
        }
        else if (*(str2+i) < *(str1+i)){
            return *str2;
            break;
        }else{
            i++;
        }
    }
}


//Question 2
struct list{
    int number;
    char name[80];
    list *next;
};

list* create_children(int n){
    list* head = nullptr;
    list* last = nullptr;

    for (int i=0; i<=n; i++){
        list* new_child = new list;
        new_child-> number = i;
        new_child -> next = nullptr;

        if (!head){
            head = new_child;
            last = new_child;
        }else {
            last -> next = new_child;
            last = new_child;
        }
    }

    if (last){
        last -> next = head;
    }

    return head;
}

int find_child_pos(int n, int m, list* children){
    list* prev;
    list* current = children;

    while (n > 1){
        for (int i=0; i<m ; i++){
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        cout<< "Child at position " << current->number << " is eliminated." << endl;
        delete current;
        current = prev->next;

        n--;
    }

    return current->number;
}


//Question 3
class Rectangle{
    double length;
    double width;
public:
    Rectangle(){}
    Rectangle(double len, double wid): length(len) , width(wid) {};
    ~Rectangle(){};

    double calculate_area() const { return length*width; };
    
    double calculate_perimeter() const { return 2*(length+width); };

    void resize(double len, double wid){
        length = len;
        width = wid;
    };
    
    static bool compare(Rectangle& r1, Rectangle& r2){
        Rectangle rec1;
        Rectangle rec2;
        rec1.resize(r1.length, r1.width);
        rec2.resize(r2.length, r2.width);

        return rec1.calculate_area() > rec2.calculate_area();
    };
};


//Question 4
enum Suits{
    clubs,
    diamonds,
    hearts,
    spades
};

enum Ranks{
    Ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    Jack,
    Queen,
    King
};

class Card{
public:
    Suits suit;
    Ranks rank;

    Card(Suits s, Ranks r) : suit(s), rank(r) {};
    ~Card(){};
};

bool testPair(Card* c){
    bool found = false;

    int card_index = 0;
    for (int j=0; j<5; j++){
        for (int i=j+1; i<5; i++){
            if (c[i].suit == c[j].suit && c[i].rank == c[j].rank){
                found = true;
                break;
            }
        }
    }
    return found;
}


void main(){

    cout<< "Testing Exercice 1 \n";

    string s1 = "jane";
    string s2 = "emma";
    string res = compare_strings(&s1, &s2);
    cout<< res;


    cout<< "\n Testing Exercice 2 \n";

    int n = 6;
    int m = 3;
    list* children = create_children(n);
    int last_child_pos = find_child_pos(n,m,children);
    cout<< "Last child pos: "<< last_child_pos;


    cout<< "\n Testing Exercice 3 \n";

    Rectangle rect1(2.0, 5.0); 
    Rectangle rect2(5.0, 6.0); 
    cout << "Rectangle 1 Area: " << rect1.calculate_area() << endl;
    cout << "Rectangle 2 Area: " << rect2.calculate_area() << endl;
    bool result = Rectangle::compare(rect1, rect2);
    if (result) { cout<<"Rectangle 1 is bigger than Rectangle 2."; }
    else { cout<<"Rectangle 2 is bigger than Rectangle 1."; }


    cout<< "\n Testing Exercice 3 \n";

    Card cards[] = {
        Card(clubs, Ace),
        Card(diamonds, two),
        Card(hearts, three),
        Card(spades, three),  // Duplicate Ace of clubs
        Card(clubs, Jack)
    };
    if (testPair(cards)) { cout << "There is a pair." << std::endl;} 
    else { cout << "No pairs found." << std::endl; }

}
