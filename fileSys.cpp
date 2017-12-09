#include <iostream>
#include <string>
#include <math.h>
using namespace std;

bool keepOnOrNah() {
    while (true) {
        string another;
        cout << endl << "Another one? (enter 'y' or 'n'):  ";
        cin >> another;
        if (another.compare("y") == 0) // another
            return true;
        else if (another.compare("n") == 0) // no more
            break;
    }
    return false;
}

void convert (bool kb = true) {
    int bytes;
    cout << "Bytes:  ";
    cin >> bytes;
	if (kb)
	    cout << (bytes/1024.0) << " KB\n";
	else
    	cout << (bytes/1048576.0) << " MB\n";
}

int main() {
    cout << "\n\nYa dirty cheat." << endl
            << "Remember, 1k bytes is 1024. 1M is 1048576." << endl;

    bool keepGoing = true;
    while (keepGoing) {
reset:

         int block_size, inode_size, indirection; 
    
        cout << "Block size (in bytes):  ";
        cin >> block_size;

        cout << "Bytes per i-node:  ";
        cin >> inode_size;

        cout << "Single Indirect blocks: 1, Double Indirect blocks: 2, etc..." << endl
        << "How many levels of indirection are there: ";
        cin >> indirection;

label:
        int choice;
        cout << "\n\n<==---------------------+|+---------------------==>\n\n";
        cout << "What do you want to calculate? (enter #)\n"
                << "1: 'How big is the i-table?'\n"
                << "2: 'How much data can we store?'\n"
                << "3: 'How big is the smallest file?'\n"
                << "4: 'How big is a file with 1 byte?'\n"
                << "5: 'How big is the largest file we can have?'\n"
                << "6: 'What is the largest number of files?'\n"
                << "7: B -> KB\n"
                << "8: B -> MB\n"
                << "9: Change file system config\n"
                << "\nChoice:  ";
        cin >> choice;
        switch (choice) {
            case 1: // i-table size
            {
                int inode_bitmap_size;
                cout << "I-Node bitmap size in blocks:  ";
                cin >> inode_bitmap_size;
                int answer = inode_bitmap_size * block_size; // i-node bitmap size in bytes
                answer *= 8; // # of i-nodes
                cout << "i-table contains " << answer << " i-nodes, and takes up ";
                answer *= inode_size; // i-table size
                cout << answer << " bytes (or ";
                answer /= block_size; // blocks per i-table
                cout << answer << " (2^" << log2(answer) << ") blocks)" << endl;
                break;
            }
            case 2: // how much data
            {
                int data_bitmap_size;
                cout << "Data bitmap size in blocks:  ";
                cin >> data_bitmap_size;
                int answer = data_bitmap_size * block_size * 8;
                cout << "Can store " << answer << " (2^" << log2(answer) << ") blocks, or ";
                answer *= block_size;
                cout << answer << " (2^" << log2(answer) << ") bytes." << endl;
                break;
            }
            case 3: // size smallest
            {
                cout << "Smallest file (0B data) has " << (inode_size * 8 + 1)
                        << " bits of overhead.\n";
                break;
            }
            case 4: // TODO size file w/ 1 byte
            {

            }
            case 5: // TODO size largest
            {

                uint64_t largest_size = 0;
                // Add the direct block
                largest_size += block_size;
                int number_of_pointers = pow((block_size / 4), indirection);
                largest_size += block_size*number_of_pointers;
                cout << "Largest file size is: " << largest_size << " B" << endl;
                break;



            }
            case 6: // TODO largest num files
                cout << endl << "You chose '" << choice << "'." << endl;
                goto label2;
            case 7: // B->KB
            {
            	convert();
                break;
            }
            case 8: // B->MB
            {
            	convert(false);
                break;
            }
            case 9:
            {
                goto reset;
            }
            default:
                cout << endl << "Please choose one of the options." << endl;
                goto label;
        }
label2:
        keepGoing = keepOnOrNah();
    }
    return 0;
}
