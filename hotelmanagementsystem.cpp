// hotelmanagementsystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstring>
#include <conio.h>

#define MAX_ROOMS 100

using namespace std;

class Guest {
public:
    char fullName[100];
    char city[100];
    char phoneNumber[12];
    char checkInDate[20];
    char checkOutDate[20];
    float advancePayment;
    int bookingID;
};

class Room {
public:
    char roomType;
    char bedType;
    char isAC;
    int roomNumber;
    int dailyRent;
    int status;

    Guest guest;

    Room add_room(int);
    void search_room(int);
    void display_room(Room);
    void delete_room(int);
};

Room rooms[MAX_ROOMS];
int roomCount = 0;

Room Room::add_room(int roomNumber) {
    Room room;
    room.roomNumber = roomNumber;
    cout << "\nType AC/Non-AC (A/N): ";
    cin >> room.isAC;
    cout << "\nType Bed (S/N): ";
    cin >> room.bedType;
    cout << "\nType Size (B/S): ";
    cin >> room.roomType;
    cout << "\nDaily Rent: ";
    cin >> room.dailyRent;
    room.status = 0;

    cout << "\nRoom Adding is Successful !!!";
    _getch();
    return room;
}

void Room::search_room(int roomNumber) {
    int i, found = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "Room Details\n";
        if (rooms[i].status == 1) {
            cout << "\nRoom is Reserved";
        }
        else {
            cout << "\nRoom is Available";
        }
        display_room(rooms[i]);
        _getch();
    }
    else {
        cout << "\nRoom Not Found";
        _getch();
    }
}

void Room::delete_room(int roomNumber) {
    int i, found = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        if (rooms[i].status == 1) {
            cout << "\nCannot delete a reserved room.";
        }
        else {
            // Delete the room by shifting elements in the array
            for (int j = i; j < roomCount - 1; j++) {
                rooms[j] = rooms[j + 1];
            }
            roomCount--;
            cout << "\nRoom " << roomNumber << " deleted successfully.";
        }
    }
    else {
        cout << "\nRoom not found";
    }
    _getch();
}

void Room::display_room(Room tempRoom) {
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N): " << tempRoom.isAC;
    cout << "\nType Bed (S/N): " << tempRoom.bedType;
    cout << "\nType Size (B/S): " << tempRoom.roomType;
    cout << "\nRent: " << tempRoom.dailyRent;
}

class HotelManagementSystem : protected Room {
public:
    void checkIn();
    void getAvailableRooms();
    void searchGuest(const char*);
    void checkOut(int);
    void guestSummaryReport();
};

void HotelManagementSystem::guestSummaryReport() {
    if (roomCount == 0) {
        cout << "\n No Guest is in the Hotel !!!";
    }
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].status == 1) {
            cout << "\n Customer Full Name: " << rooms[i].guest.fullName;
            cout << "\n Room Number: " << rooms[i].roomNumber;
            cout << "\n City: " << rooms[i].guest.city;
            cout << "\n Phone: " << rooms[i].guest.phoneNumber;
            cout << "\n_______________________________________";
        }
    }
    _getch();
}

void HotelManagementSystem::checkIn() {
    int i, found = 0, roomNumber;
    cout << "\nEnter a Room number : ";
    cin >> roomNumber;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        if (rooms[i].status == 1) {
            cout << "\nSORRY !!! Room is already Booked";
            _getch();
            return;
        }

        cout << "\nEnter booking id: ";
        cin >> rooms[i].guest.bookingID;

        cout << "\nEnter Customer Full Name: ";
        cin.ignore(); // Ignore newline character from previous input
        cin.getline(rooms[i].guest.fullName, sizeof(rooms[i].guest.fullName));

        cout << "\nEnter City: ";
        cin.getline(rooms[i].guest.city, sizeof(rooms[i].guest.city));

        cout << "\nEnter Phone: ";
        cin >> rooms[i].guest.phoneNumber;

        cout << "\nEnter Check-In Date: ";
        cin >> rooms[i].guest.checkInDate;

        cout << "\nEnter Check-Out Date: ";
        cin >> rooms[i].guest.checkOutDate;

        cout << "\nEnter Advance Payment: ";
        cin >> rooms[i].guest.advancePayment;

        rooms[i].status = 1;

        cout << "\n Customer Checked-in Successfully..";
        _getch();
    }
}

void HotelManagementSystem::getAvailableRooms() {
    int i, found = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].status == 0) {
            display_room(rooms[i]);
            cout << "\n\nPress enter for the next room";
            found = 1;
            _getch();
        }
    }
    if (found == 0) {
        cout << "\nSORRY!!! All rooms are reserved";
        _getch();
    }
}

void HotelManagementSystem::searchGuest(const char* fullName) {
    int i, found = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].status == 1 && _stricmp(rooms[i].guest.fullName, fullName) == 0) {
            cout << "\nCustomer Full Name: " << rooms[i].guest.fullName;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\nCity: " << rooms[i].guest.city;
            cout << "\nPhone: " << rooms[i].guest.phoneNumber;
            cout << "\n______________________________________";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nPerson not found.";
    }
    _getch();
}

void HotelManagementSystem::checkOut(int roomNumber) {
    int i, found = 0, days;
    float billAmount = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNumber) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "\nEnter Number of Days:\t";
        cin >> days;
        billAmount = static_cast<float>(days * rooms[i].dailyRent);

        cout << "\n\t______ CheckOut Details ______\n";
        cout << "\nCustomer Full Name : " << rooms[i].guest.fullName;
        cout << "\nRoom Number : " << rooms[i].roomNumber;
        cout << "\nCity : " << rooms[i].guest.city;
        cout << "\nPhone : " << rooms[i].guest.phoneNumber;
        cout << "\nTotal Due Amount : " << billAmount << " /";
        cout << "\nAdvance Paid: " << rooms[i].guest.advancePayment << " /";
        cout << "\n*** Total Payable: " << billAmount - rooms[i].guest.advancePayment << "/ only";

        rooms[i].status = 0;
    }
    _getch();
}

void manageRooms() {
    Room room;
    int opt, roomNumber, i, flag = 0;
    do {
        system("cls");
        cout << "\n**** Manage Rooms ****";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Delete Room";
        cout << "\n4. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
        case 1:
            cout << "\nEnter Room Number: ";
            cin >> roomNumber;
            i = 0;
            for (i = 0; i < roomCount; i++) {
                if (rooms[i].roomNumber == roomNumber) {
                    flag = 1;
                }
            }
            if (flag == 1) {
                cout << "\nRoom Number is Already Added.\nPlease Enter Another Number";
                flag = 0;
                _getch();
            }
            else {
                rooms[roomCount] = room.add_room(roomNumber);
                roomCount++;
            }
            break;
        case 2:
            cout << "\nEnter a Room Number: ";
            cin >> roomNumber;
            room.search_room(roomNumber);
            break;
        case 3:
            cout << "\nEnter Room Number to Delete: ";
            cin >> roomNumber;
            room.delete_room(roomNumber);
            break;
        case 4:
            // Nothing to do
            break;
        default:
            cout << "\nPlease Enter the Correct Option";
            break;
        }
    } while (opt != 4);
}

int main() {
    HotelManagementSystem hms;
    int opt, roomNumber;
    char fullName[100];

    system("cls");

    do {
        system("cls");
        cout << "~~~~~~~~~ Hotel Management System ~~~~~~~~~\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In a Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search a Guest";
        cout << "\n5. Check-Out a Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
        case 1:
            manageRooms();
            break;
        case 2:
            if (roomCount == 0) {
                cout << "\nPlease input room details to proceeed\nRoom data is not available at the moment.";
                _getch();
            }
            else
                hms.checkIn();
            break;
        case 3:
            if (roomCount == 0) {
                cout << "\nPlease input room details to proceeed\nRoom data is not available at the moment.";
                _getch();
            }
            else
                hms.getAvailableRooms();
            break;
        case 4:
            if (roomCount == 0) {
                cout << "\nPlease input room details to proceeed\nRoom data is not available at the moment.";
                _getch();
            }
            else {
                cout << "Enter Guest Full Name: ";
                cin.ignore();
                cin.getline(fullName, sizeof(fullName));
                hms.searchGuest(fullName);
            }
            break;
        case 5:
            if (roomCount == 0) {
                cout << "\nRooms are not available.\nPlease add the rooms first.";
                _getch();
            }
            else {
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                hms.checkOut(roomNumber);
            }
            break;
        case 6:
            hms.guestSummaryReport();
            break;
        case 7:
            cout << "\nTHANK YOU!";
            break;
        default:
            cout << "\nPlease Enter the correct option";
            break;
        }
    } while (opt != 7);

    _getch();
    return 0;
}

