#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StringPool {
private:
    string** stringPool;     // array of pointers, each one points to  heap string
    int currentSize;         // Strings in the pright now
    int maxSize;              // pool can only hold 5 max
    vector<string*> leaked;  // pointers removed but forgot (on purpose) to delete

public:
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string*[maxSize];
        for (int i = 0; i < maxSize; i++) {
            stringPool[i] = nullptr;
        }
    }

    // adds new string to the pool
    void addString(string s) {
        if (currentSize >= maxSize) {
            cout << "Pool is full, can't add \"" << s << "\"" << endl;
            return;
        }
        // allocates on heap
        stringPool[currentSize] = new string(s);
        currentSize++;
        cout << "Added: " << s << endl;
    }

    // removes string but doesn't delete it 
    void removeString(string s) {
        for (int i = 0; i < currentSize; i++) {
            if (*stringPool[i] == s) {
                // saves pointer somewhere so we can free it later
                leaked.push_back(stringPool[i]);

                // shift everything it back one spot
                for (int j = i; j < currentSize - 1; j++) {
                    stringPool[j] = stringPool[j + 1];
                }
                stringPool[currentSize - 1] = nullptr;
                currentSize--;

                cout << "Removed: " << s << " -> memory still allocated (leak!)" << endl;
                return;
            }
        }
        cout << s << " not found in pool" << endl;
    }

    // goes through everything we leaked and deletes it now
    void fixLeaks() {
        if (leaked.empty()) {
            cout << "Nothing to fix, no leaks right now." << endl;
            return;
        }
        cout << "Found " << leaked.size() << " leaked string(s), cleaning up" << endl;
        for (string* ptr : leaked) {
            delete ptr;
        }
        leaked.clear();
        cout << "Done, leaks fixed." << endl;
    }

    void displayPool() {
        cout << "\nPool Status: " << endl;
        cout << "Size: " << currentSize << "/" << maxSize << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << "  [" << i << "] " << *stringPool[i] << endl;
        }
        cout << "Leaked pointers not yet freed: " << leaked.size() << endl;
    }

    // Destructor frees whatever left so we don't leak when program ends
    ~StringPool() {
        for (int i = 0; i < currentSize; i++) {
            delete stringPool[i];
        }
        for (string* ptr : leaked) {
            delete ptr;
        }
        delete[] stringPool;
    }
};

int main() {
    StringPool pool;

    pool.addString("Apple");
    pool.addString("Banana");
    pool.addString("Cherry");
    pool.addString("Date");
    pool.addString("Elderberry");

    pool.displayPool();

    pool.removeString("Banana");
    pool.removeString("Date");

    pool.displayPool();

    pool.fixLeaks();

    pool.displayPool();

    return 0;
}