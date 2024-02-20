/*1.Music playlist creation*/
#include <iostream>
#include <string>
using namespace std;

// Class to represent a song Node
class Song {
public:
    string title;
    string singer;
    Song* prev;
    Song* next;
    Song(string t, string s) : title(t), singer(s), prev(NULL), next(NULL) {} };
// Class to represent a playlist
class Playlist {
public:
    Song* head;
    Song* current; // Pointer to the currently selected song
    // Constructor to initialize an empty playlist
    Playlist() : head(NULL), current(NULL) {}
    // add a song to the end of the playlist
    void addSong(string title, string singer) {
        Song* newSong = new Song(title, singer);
        if (head == NULL) {
            head = newSong;
        } else {
            Song* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newSong;
            newSong->prev = temp;
        }
        cout << "Song \"" << title << "\" added to the end of the playlist." << endl;
    }
    // remove a song by its title
    void removeSongByTitle(string title) {
        if (head == NULL) {
            cout << "Playlist is empty. Cannot remove song." << endl;
            return;
        }
        Song* temp = head;
        while (temp) {
            if (temp->title == title) {
                if (temp == head) {
                    head = head->next;
                    if (head)
                        head->prev = nullptr;
                } else {
                    temp->prev->next = temp->next;
                    if (temp->next)
                        temp->next->prev = temp->prev;
                }
                if (current == temp) 
                    current = NULL;  
                delete temp;
                cout << "Song \"" << title << "\" removed successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song \"" << title << "\" not found in the playlist." << endl;
    }
    // remove the last song from the playlist
    void removeLastSong() {
        if (head == NULL) {
            cout << "Playlist is empty. Cannot remove song." << endl;
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = nullptr;
            cout << "Last song removed successfully." << endl;
            return;
        }
        Song* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        cout << "Last song removed successfully." << endl;
    }
    // remove the first song from the playlist
    void removeFirstSong() {
        if (head == NULL) {
            cout << "Playlist is empty. Cannot remove song." << endl;
            return;
        }
        Song* temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        delete temp;
        cout << "First song removed successfully." << endl;
    }
    // display all songs in the playlist
    void displaySongs() {
        if (head == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "Playlist Songs:" << endl;
        cout << "----------------------------------------" << endl;
        Song* temp = head;
        while (temp) {
            cout << "Title: " << temp->title << endl;
            cout << "Singer: " << temp->singer << endl;
            cout << "----------------------------------------" << endl;
            temp = temp->next;
        }
    }
    // select a song by it's title
    void selectSongByTitle(string title) {
        Song* temp = head;
        while (temp) {
            if (temp->title == title) {
                current = temp;
                cout<<"searching....\n";
                cout<<"now playing "<<current->title<<"\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song \"" << title << "\" not found in the playlist." << endl;
    }
    // move to the next song
    void nextSong() {
        if (current && current->next){
            current = current->next;
            cout<<"moving to next song \n";
            cout<<"now playing "<<current->title<<" \n";
        }
        else{
            cout << "No next song available." << endl;
        }
    }
    // move to the previous song
    void previousSong() {
        if (current && current->prev){
            current = current->prev;
            cout<<"moving to previous song \n";
            cout<<"now playing "<<current->title<<" \n";
        }
        else{
            cout << "No previous song available.";
        }
    }
    // delete the currently selected song
    void deleteCurrentSong() {
        if (current) {
            string title = current->title;
            removeSongByTitle(title);
            current = NULL; 
        } else {
            cout << "No song selected." << endl;
        }
    }
};
int main() {
    Playlist myPlaylist;
    int choice;
    string title, singer;
    do {
        cout << "\n1. Add Song\n2. Remove Song by Title\n3. Remove Last Song\n4. Remove First Song\n5. Select Song\n6. Next Song\n7. Previous Song\n8. Delete Current Song\n9. Display Playlist\n10. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, title);
                cout << "Enter singer: ";
                getline(cin, singer);
                myPlaylist.addSong(title, singer);
                break;
            case 2:
                cout << "Enter the title of the song to remove: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, title);
                myPlaylist.removeSongByTitle(title);
                break;
            case 3:
                myPlaylist.removeLastSong();
                break;
            case 4:
                myPlaylist.removeFirstSong();
                break;
            case 5:
                cout << "Enter the title of the song to select: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, title);
                myPlaylist.selectSongByTitle(title);
                break;
            case 6:
                myPlaylist.nextSong();
                break;
            case 7:
                myPlaylist.previousSong();
                break;
            case 8:
                myPlaylist.deleteCurrentSong();
                break;
            case 9:
                myPlaylist.displaySongs();
                break;
            case 10:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 10);
    return 0;
}
