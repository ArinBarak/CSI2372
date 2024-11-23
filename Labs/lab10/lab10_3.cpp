//Lab 10
//Exercice 3

#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Feedback{
    string comment;
    unordered_multiset<string> tag;

    //Feedback(const string& cmn, const string& tg) : comment(cmn), tag(tg) {}
};

class FeedBackAnalyser{
private:
    unordered_multiset<string> tagNum;
    vector<Feedback> feedbacks;

public:
    void addFeedback(const string& ms, const unordered_multiset<string>& tags){
        Feedback newfeedback{ms, tags};
        feedbacks.push_back(newfeedback);

        for (const auto& tag : tags){
            tagNum.insert(tag);
        }
    }

    void getFeedBackfromTag(const string& tag){
        bool found = false;
        cout <<  "\nFeedback for tag "<< tag<< " :\n";
        for (const auto& feedback : feedbacks){
            if (feedback.tag.find(tag) != feedback.tag.end()) {
                cout << "- " << feedback.comment << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No feedback found for tag: " << tag << "\n";
        }
    }

    void getTagStatistics() {
        if (tagNum.empty()) {
            cout << "No tags available for statistics.\n";
            return;
        }

        auto mostCommonTag = *max_element(tagNum.begin(), tagNum.end(),
            [this](const string& a, const string& b) {
                return tagNum.count(a) < tagNum.count(b);
            });

        auto leastCommonTag = *min_element(tagNum.begin(), tagNum.end(),
            [this](const string& a, const string& b) {
                return tagNum.count(a) < tagNum.count(b);
            });
        
        cout << "\nTag Statistics:\n";
        cout << "Most common tag: '" << mostCommonTag << "' (Count: " << tagNum.count(mostCommonTag) << ")\n";
        cout << "Least common tag: '" << leastCommonTag << "' (Count: " << tagNum.count(leastCommonTag) << ")\n";
    }
};

unordered_multiset<string> parseTags(const string& tagsInput) {
    unordered_multiset<string> tags;
    stringstream ss(tagsInput);
    string tag;
    while (getline(ss, tag, ',')) {
        tag.erase(0, tag.find_first_not_of(' '));
        tag.erase(tag.find_last_not_of(' ') + 1); 
        if (!tag.empty()) {
            tags.insert(tag);
        }
    }
    return tags;
}

int main(){
    FeedBackAnalyser analyse;
    bool exit = false;
    int option = 0;
    string comment;
    string taginput;
    unordered_multiset<string> tags;

    while (!exit){
        cout<< "\n1. Add Feedback\n2. View Feedback by Tag\n3. Display Tag Statistics\n 4. Exit" << endl;
        cout<< "Enter your choice: ";
        cin >> option;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option){
            case 1:{
                cout << "Enter feedback text: ";
                getline(cin, comment);

                cout << "Enter tags (comma-separated): ";
                getline(cin, taginput);

                tags = parseTags(taginput);

                analyse.addFeedback(comment, tags);
                break;
            }case 2:{
                cout <<"Enter tag to search feedback: ";
                cin >> taginput;
                analyse.getFeedBackfromTag(taginput);
                break;
            }case 3:{
                analyse.getTagStatistics();
                break;
            }case 4:{
                exit = true;
                break;
            }
        }
    }
    return 0;
}
