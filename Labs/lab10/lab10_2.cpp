//Lab 10
//Exercice 2

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Message{
private:
    unordered_map<int, string> gm;
public:
    void sendMessage(int gid, const string& m){
        gm.insert({gid, m});
        cout << "Message posted to group "<< gid << ": " << m <<endl;

    }

    vector<string> getMessages(int gid){
        vector<string> ms;
        auto range = gm.equal_range(gid);
        for (auto it = range.first; it!=range.second; ++it){
            ms.push_back(it->second);
        }

        return ms;
    }

    void clearGroup(int gid){
        gm.erase(gid);
        cout << "All messages cleared for group " << gid;
    }
};

int main(){
    Message m;

    m.sendMessage(1, "Hello Group 1!");
    m.sendMessage(1, "Second message Group 1!");
    m.sendMessage(2, "Hello Group 2!");

    vector<string> group1Messages = m.getMessages(1);
    cout << "\nMessages in Group 1:\n";
    for (const auto& message : group1Messages) {
        cout << "- " << message << endl;
    }

    vector<string> group2Messages = m.getMessages(2);
    cout << "\nMessages in Group 2:\n";
    for (const auto& message : group2Messages) {
        cout << "- " << message << endl;
    }

    m.clearGroup(1);
    m.clearGroup(2);

    return 0;
}
