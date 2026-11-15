
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

bool restoreBackup(const string& backup,
                   const string& destination) {
    FILE* source = fopen(backup.c_str(), "rb");

    if (source == NULL) {
        cout << "Error: Backup file not found.\n";
        return false;
    }

    cout << "Overwrite destination if it exists? (y/n): ";
    char choice;
    cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        fclose(source);
        cout << "Restore cancelled.\n";
        return false;
    }

    FILE* target = fopen(destination.c_str(), "wb");

    if (target == NULL) {
        fclose(source);
        cout << "Error: Cannot open destination file.\n";
        return false;
    }

    int ch;
    while ((ch = fgetc(source)) != EOF) {
        if (fputc(ch, target) == EOF) {
            fclose(source);
            fclose(target);
            cout << "Error while copying file.\n";
            return false;
        }
    }

    fclose(source);
    fclose(target);

    cout << "Restore completed successfully.\n";
    return true;
}

int main() {
    string backupPath, destinationPath;

    cout << "Enter backup file path: ";
    cin >> backupPath;

    cout << "Enter destination file path: ";
    cin >> destinationPath;

    restoreBackup(backupPath, destinationPath);

    return 0;
}
