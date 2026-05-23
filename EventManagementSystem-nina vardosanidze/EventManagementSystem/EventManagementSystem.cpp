#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Participant {
private:
    int id;
    string name;
    string email;

public:
    Participant(int i, string n, string e) {
        id = i;
        name = n;
        email = e;
    }

    int getId() {
        return id;
    }

    void showParticipant() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
    }
};

class Ticket {
private:
    int ticketId;
    int participantId;
    double price;

public:
    Ticket(int t, int p, double pr) {
        ticketId = t;
        participantId = p;
        price = pr;
    }

    int getTicketId() {
        return ticketId;
    }

    void showTicket() {
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Participant ID: " << participantId << endl;
        cout << "Price: " << price << " GEL" << endl;
    }
};

class Event {
protected:
    int eventId;
    string title;
    string date;
    string location;

public:
    Event(int i, string t, string d, string l) {
        eventId = i;
        title = t;
        date = d;
        location = l;
    }

    int getEventId() {
        return eventId;
    }

    string getTitle() {
        return title;
    }

    string getLocation() {
        return location;
    }

    void setTitle(string t) {
        title = t;
    }

    void setDate(string d) {
        date = d;
    }

    void setLocation(string l) {
        location = l;
    }

    virtual void showEvent() {
        cout << "Event ID: " << eventId << endl;
        cout << "Title: " << title << endl;
        cout << "Date: " << date << endl;
        cout << "Location: " << location << endl;
    }
};

class Conference : public Event {
private:
    string speaker;

public:
    Conference(int i, string t, string d, string l, string s)
        : Event(i, t, d, l) {
        speaker = s;
    }

    void setSpeaker(string s) {
        speaker = s;
    }

    void showEvent() override {
        Event::showEvent();
        cout << "Speaker: " << speaker << endl;
    }
};

class EventSystem {
private:
    vector<Conference> events;
    vector<Participant> participants;
    vector<Ticket> tickets;

    void clearInput() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void addEvent() {
        int id;
        string title, date, location, speaker;

        cout << "Enter event ID: ";
        cin >> id;
        clearInput();

        for (int i = 0; i < events.size(); i++) {
            if (events[i].getEventId() == id) {
                cout << "Event already exists" << endl;
                return;
            }
        }

        cout << "Enter title: ";
        getline(cin, title);

        cout << "Enter date: ";
        getline(cin, date);

        cout << "Enter location: ";
        getline(cin, location);

        cout << "Enter speaker: ";
        getline(cin, speaker);

        events.push_back(Conference(id, title, date, location, speaker));
        cout << "Event added" << endl;
    }

    void showEvents() {
        if (events.empty()) {
            cout << "No events found" << endl;
            return;
        }

        for (int i = 0; i < events.size(); i++) {
            cout << endl;
            events[i].showEvent();
        }
    }

    void updateEvent() {
        int id;

        cout << "Enter event ID: ";
        cin >> id;
        clearInput();

        for (int i = 0; i < events.size(); i++) {
            if (events[i].getEventId() == id) {
                string title, date, location, speaker;

                cout << "New title: ";
                getline(cin, title);

                cout << "New date: ";
                getline(cin, date);

                cout << "New location: ";
                getline(cin, location);

                cout << "New speaker: ";
                getline(cin, speaker);

                events[i].setTitle(title);
                events[i].setDate(date);
                events[i].setLocation(location);
                events[i].setSpeaker(speaker);

                cout << "Updated successfully" << endl;
                return;
            }
        }

        cout << "Event not found" << endl;
    }

    void deleteEvent() {
        int id;

        cout << "Enter event ID: ";
        cin >> id;
        clearInput();

        for (int i = 0; i < events.size(); i++) {
            if (events[i].getEventId() == id) {
                events.erase(events.begin() + i);
                cout << "Deleted successfully" << endl;
                return;
            }
        }

        cout << "Event not found" << endl;
    }

    void searchEvent() {
        string title;

        cout << "Enter title: ";
        getline(cin, title);

        bool found = false;

        for (int i = 0; i < events.size(); i++) {
            if (events[i].getTitle() == title) {
                events[i].showEvent();
                found = true;
            }
        }

        if (!found) {
            cout << "Event not found" << endl;
        }
    }

    void filterLocation() {
        string location;

        cout << "Enter location: ";
        getline(cin, location);

        bool found = false;

        for (int i = 0; i < events.size(); i++) {
            if (events[i].getLocation() == location) {
                events[i].showEvent();
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No events in this location" << endl;
        }
    }

    void addParticipant() {
        int id;
        string name, email;

        cout << "Enter participant ID: ";
        cin >> id;
        clearInput();

        for (int i = 0; i < participants.size(); i++) {
            if (participants[i].getId() == id) {
                cout << "Participant already exists" << endl;
                return;
            }
        }

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter email: ";
        getline(cin, email);

        participants.push_back(Participant(id, name, email));
        cout << "Participant added" << endl;
    }

    void showParticipants() {
        if (participants.empty()) {
            cout << "No participants found" << endl;
            return;
        }

        for (int i = 0; i < participants.size(); i++) {
            cout << endl;
            participants[i].showParticipant();
        }
    }

    void buyTicket() {
        int ticketId;
        int participantId;
        double price;

        cout << "Enter ticket ID: ";
        cin >> ticketId;

        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].getTicketId() == ticketId) {
                cout << "Ticket already exists" << endl;
                clearInput();
                return;
            }
        }

        cout << "Enter participant ID: ";
        cin >> participantId;

        bool found = false;

        for (int i = 0; i < participants.size(); i++) {
            if (participants[i].getId() == participantId) {
                found = true;
            }
        }

        if (!found) {
            cout << "Participant not found" << endl;
            clearInput();
            return;
        }

        cout << "Enter price: ";
        cin >> price;
        clearInput();

        tickets.push_back(Ticket(ticketId, participantId, price));
        cout << "Ticket purchased" << endl;
    }

    void returnTicket() {
        int id;

        cout << "Enter ticket ID: ";
        cin >> id;
        clearInput();

        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].getTicketId() == id) {
                tickets.erase(tickets.begin() + i);
                cout << "Ticket returned" << endl;
                return;
            }
        }

        cout << "Ticket not found" << endl;
    }

    void showTickets() {
        if (tickets.empty()) {
            cout << "No tickets found" << endl;
            return;
        }

        for (int i = 0; i < tickets.size(); i++) {
            cout << endl;
            tickets[i].showTicket();
        }
    }
};

int main() {
    EventSystem system;
    int choice;

    do {
        cout << endl;
        cout << "===== EVENT MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Show Events" << endl;
        cout << "3. Update Event" << endl;
        cout << "4. Delete Event" << endl;
        cout << "5. Search Event" << endl;
        cout << "6. Filter by Location" << endl;
        cout << "7. Add Participant" << endl;
        cout << "8. Show Participants" << endl;
        cout << "9. Buy Ticket" << endl;
        cout << "10. Return Ticket" << endl;
        cout << "11. Show Tickets" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            system.addEvent();
            break;
        case 2:
            system.showEvents();
            break;
        case 3:
            system.updateEvent();
            break;
        case 4:
            system.deleteEvent();
            break;
        case 5:
            system.searchEvent();
            break;
        case 6:
            system.filterLocation();
            break;
        case 7:
            system.addParticipant();
            break;
        case 8:
            system.showParticipants();
            break;
        case 9:
            system.buyTicket();
            break;
        case 10:
            system.returnTicket();
            break;
        case 11:
            system.showTickets();
            break;
        case 0:
            cout << "Program ended" << endl;
            break;
        default:
            cout << "Wrong choice" << endl;
        }

    } while (choice != 0);

    return 0;
}