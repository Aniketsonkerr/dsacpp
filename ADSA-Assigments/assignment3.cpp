// // #include <iostream>
// // using namespace std;

// // int dat[1000];

// // int main() {
// //     for (int i = 0; i < 1000; i++) {
// //         dat[i] = -1;
// //     }

// //     int n, key, choice;

// //     cout << "Enter number of elements to insert: ";
// //     cin >> n;

// //     cout << "Enter " << n << " positive keys:\n";
// //     for (int i = 0; i < n; i++) {
// //         cin >> key;
// //         dat[key] = key;
// //     }

// //     while (true) {
// //         cout << "\n1. Search\n2. Delete\n3. Display\n4. Exit\nEnter choice: ";
// //         cin >> choice;

// //         if (choice == 1) {
// //             cout << "Enter key to search: ";
// //             cin >> key;
// //             if (dat[key] != -1) {
// //                 cout << "Key found at index " << key << endl;
// //             } else {
// //                 cout << "Key not found\n";
// //             }
// //         } else if (choice == 2) {
// //             cout << "Enter key to delete: ";
// //             cin >> key;
// //             if (dat[key] != -1) {
// //                 dat[key] = -1;
// //                 cout << "Key deleted\n";
// //             } else {
// //                 cout << "Key not present\n";
// //             }
// //         } else if (choice == 3) {
// //             cout << "Direct Access Table:\n";
// //             for (int i = 0; i < 1000; i++) {
// //                 if (dat[i] != -1) {
// //                     cout << "Index " << i << " : " << dat[i] << endl;
// //                 }
// //             }
// //         } else {
// //             break;
// //         }
// //     }

// //     return 0;
// // }

// #include <iostream>
// using namespace std;

// int main() {
//     int table_size, n, key, choice;
//     int collisions = 0;

//     cout << "Enter hash table size: ";
//     cin >> table_size;

//     int hash_table[100];
//     for (int i = 0; i < table_size; i++) {
//         hash_table[i] = -1;
//     }

//     cout << "Enter number of elements to insert: ";
//     cin >> n;

//     cout << "Enter " << n << " keys:\n";
//     for (int i = 0; i < n; i++) {
//         cin >> key;
//         int index = key % table_size;
//         cout << "Key " << key << " -> Initial Hash: " << index << endl;

//         while (hash_table[index] != -1) {
//             collisions++;
//             index = (index + 1) % table_size;
//         }
//         hash_table[index] = key;
//     }

//     while (true) {
//         cout << "\n1. Search\n2. Delete\n3. Display\n4. Total Collisions\n5. Exit\nEnter choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             cout << "Enter key to search: ";
//             cin >> key;
//             int index = key % table_size;
//             int start = index;
//             int comparisons = 0;
//             bool found = false;

//             while (hash_table[index] != -1) {
//                 comparisons++;
//                 if (hash_table[index] == key) {
//                     cout << "Found at index " << index << " in " << comparisons << " comparisons\n";
//                     found = true;
//                     break;
//                 }
//                 index = (index + 1) % table_size;
//                 if (index == start) break;
//             }

//             if (!found) {
//                 cout << "Key not found\n";
//             }
//         } else if (choice == 2) {
//             cout << "Enter key to delete: ";
//             cin >> key;
//             int index = key % table_size;
//             int start = index;
//             bool deleted = false;

//             while (hash_table[index] != -1) {
//                 if (hash_table[index] == key) {
//                     hash_table[index] = -2;
//                     cout << "Key deleted\n";
//                     deleted = true;
//                     break;
//                 }
//                 index = (index + 1) % table_size;
//                 if (index == start) break;
//             }

//             if (!deleted) cout << "Key not found\n";
//         } else if (choice == 3) {
//             cout << "Hash Table:\n";
//             for (int i = 0; i < table_size; i++) {
//                 cout << "Index " << i << " : " << hash_table[i] << endl;
//             }
//         } else if (choice == 4) {
//             cout << "Total collisions during insertion: " << collisions << endl;
//         } else {
//             break;
//         }
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;

// struct Symbol {
//     string name;
//     string type;
//     string value;
//     bool is_occupied = false;
// };

// int getHash(string key, int size) {
//     int sum = 0;
//     for (int i = 0; i < key.length(); i++) {
//         sum += key[i];
//     }
//     return sum % size;
// }

// int main() {
//     int table_size = 10;
//     Symbol table[10];
//     int choice;

//     while (true) {
//         cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             string name, type, value;
//             cout << "Enter Identifier Name: ";
//             cin >> name;
//             cout << "Enter Data Type: ";
//             cin >> type;
//             cout << "Enter Value: ";
//             cin >> value;

//             int index = getHash(name, table_size);
//             while (table[index].is_occupied) {
//                 index = (index + 1) % table_size;
//             }

//             table[index].name = name;
//             table[index].type = type;
//             table[index].value = value;
//             table[index].is_occupied = true;
//             cout << "Inserted at index " << index << endl;
//         } else if (choice == 2) {
//             string name;
//             cout << "Enter Identifier Name to search: ";
//             cin >> name;

//             int index = getHash(name, table_size);
//             int start = index;
//             bool found = false;

//             while (table[index].is_occupied) {
//                 if (table[index].name == name) {
//                     cout << "Found!\n";
//                     cout << "Name: " << table[index].name << endl;
//                     cout << "Type: " << table[index].type << endl;
//                     cout << "Value: " << table[index].value << endl;
//                     found = true;
//                     break;
//                 }
//                 index = (index + 1) % table_size;
//                 if (index == start) break;
//             }

//             if (!found) cout << "Identifier not found\n";
//         } else if (choice == 3) {
//             string name;
//             cout << "Enter Name to delete: ";
//             cin >> name;

//             int index = getHash(name, table_size);
//             int start = index;
//             bool deleted = false;

//             while (table[index].is_occupied) {
//                 if (table[index].name == name) {
//                     table[index].is_occupied = false;
//                     table[index].name = "";
//                     cout << "Deleted successfully\n";
//                     deleted = true;
//                     break;
//                 }
//                 index = (index + 1) % table_size;
//                 if (index == start) break;
//             }

//             if (!deleted) cout << "Not found\n";
//         } else if (choice == 4) {
//             cout << "Symbol Table Contents:\n";
//             for (int i = 0; i < table_size; i++) {
//                 if (table[i].is_occupied) {
//                     cout << "Index " << i << " -> " << table[i].name << " | " << table[i].type << " | " << table[i].value << endl;
//                 } else {
//                     cout << "Index " << i << " -> Empty\n";
//                 }
//             }
//         } else {
//             break;
//         }
//     }

//     return 0;
// }
#include <iostream>
using namespace std;

int dat[1000];

int main() {
    for (int i = 0; i < 1000; i++) {
        dat[i] = -1;
    }

    int n, key, choice;

    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter " << n << " positive keys:\n";
    for (int i = 0; i < n; i++) {
        cin >> key;
        dat[key] = key;
    }

    while (true) {
        cout << "\n1. Search\n2. Delete\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter key to search: ";
            cin >> key;
            if (dat[key] != -1) {
                cout << "Key found at index " << key << endl;
            } else {
                cout << "Key not found\n";
            }
        } else if (choice == 2) {
            cout << "Enter key to delete: ";
            cin >> key;
            if (dat[key] != -1) {
                dat[key] = -1;
                cout << "Key deleted\n";
            } else {
                cout << "Key not present\n";
            }
        } else if (choice == 3) {
            cout << "Direct Access Table:\n";
            for (int i = 0; i < 1000; i++) {
                if (dat[i] != -1) {
                    cout << "Index " << i << " : " << dat[i] << endl;
                }
            }
        } else {
            break;
        }
    }

    return 0;
}