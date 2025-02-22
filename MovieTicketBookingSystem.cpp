// Admin password = password
/*
PROJECT TITLE: MOVIE TICKET BOOKING SYSTEM (ADMIN/USER)
THIS PROJECT IS PROGRAMMED BY
NAME:IRUM IMTIAZ
REG.NO: FA22-BCT-011

DESCRIBTION: i have used vector,queue,unordered map in order to make this system
             efficient also i have used merge algorithm which will set tickets according to
             seats numbers
*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

// Structure to represent a movie ticket
struct MovieTicket
{
    string movieName;
    int seatNumber;
    bool isAvailable;
    string username;

    // constructor to intitializie a ticket
    MovieTicket(const string &movie, int seat) : movieName(movie), seatNumber(seat), isAvailable(true){};
    MovieTicket(const string &movie, int seat, const string &user)
        : movieName(movie), seatNumber(seat), isAvailable(true), username(user) {}
};

// Class for Movie Ticket Booking System
class MovieTicketBookingSystem
{
private:
    //theaters name are mapped with tickets that are stored in queue 
    unordered_map<string, queue<MovieTicket>> theaters;
    static const int numRows = 5;
    static const int numCols = 5;
    string seats[numRows][numCols];

public:
    // Constructor to initialize seats with empty strings
    MovieTicketBookingSystem()
    {
        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                seats[i][j] = "";
            }
        }
    }

    // Add a new ticket into the system
    void AddTicket(const string theaterNames[], int theaterChoice)
    {

        if (theaterChoice >= 1 && theaterChoice <= 3)
        {
            string theaterName = theaterNames[theaterChoice - 1];

            // Check if the theater already has a movie set
            if (!theaters[theaterName].empty())
            {
                string existingMovie = theaters[theaterName].front().movieName;

                cout << "\nEnter Movie Name: ";
                string movieName;
                cin >> movieName;

                // Check if the admin is trying to insert tickets for a different movie
                if (existingMovie != movieName)
                {
                    cout << "\nError: Cannot insert tickets for a different movie in the same theater." << endl;
                    return;
                }
            }
            else
            {
                // If the theater is empty, prompt for the movie name
                cout << "\nEnter Movie Name: ";
                string movieName;
                cin >> movieName;

                // Set the same movie name for all seats in the theater
                for (int i = 0; i < numRows; ++i)
                {
                    for (int j = 0; j < numCols; ++j)
                    {
                        seats[i][j] = movieName;
                    }
                }
            }

            // Add tickets to the system  (tickets added in 2d array) as theature have rows and coloumn
            for (int i = 1; i <= numRows * numCols; ++i)
            {
                MovieTicket newTicket = {seats[(i - 1) / numCols][(i - 1) % numCols], i};
                theaters[theaterName].push(newTicket);
            }

            cout << "\nTickets added for all seats in " << theaterName << " theater for Movie: " << theaters[theaterName].front().movieName << " to the system." << endl;
        }
        else
        {
            cout << "\nInvalid theater number. Please choose between 1 and 3." << endl;
        }
    }

    // remove ticket
    void RemoveTicket(const string &theaterName)
    {
        if (theaters[theaterName].empty())
        {
            cout << "\nThere are no tickets in the theater." << endl;
        }
        else
        {
            MovieTicket canceledTicket = theaters[theaterName].front();
            theaters[theaterName].pop();

            int row = (canceledTicket.seatNumber - 1) / numCols;
            int col = (canceledTicket.seatNumber - 1) % numCols;
            seats[row][col] = ""; // Mark seat as available

            cout << "\nTicket Removed for seat " << canceledTicket.seatNumber << " for Movie: " << canceledTicket.movieName << " at " << theaterName << " theater." << endl;
        }
    }

    // Check if a ticket exists in the system
    bool TicketExists(const string &theaterName, const string &movieName, int seatNumber)
    {
        if (theaters.find(theaterName) != theaters.end())
        {
            queue<MovieTicket> theaterQueueCopy = theaters[theaterName]; // Copy the queue

            // Check each ticket in the theater for a match
            while (!theaterQueueCopy.empty())
            {
                const MovieTicket &currentTicket = theaterQueueCopy.front();
                if (currentTicket.movieName == movieName && currentTicket.seatNumber == seatNumber)
                {
                    cout << "Ticket found for movie: " << movieName << ", Seat: " << seatNumber << " at " << theaterName << " theater." << endl;
                    return true; // Ticket found
                }
                theaterQueueCopy.pop();
            }

            cout << "Ticket not found for movie: " << movieName << ", Seat: " << seatNumber << " at " << theaterName << " theater." << endl;
            return false; // Ticket not found
        }
        else
        {
            cout << "Invalid theater name: " << theaterName << endl;
            return false; // Invalid theater name
        }
    }

    // Display all tickets for a specific theater
    void displayTickets(const string &theaterName)
    {
        if (theaters[theaterName].empty())
        {
            cout << "\nNo tickets added by Admin in " << theaterName << " theater yet." << endl;
        }
        else
        {
            cout << "\nTotal Tickets at " << theaterName << " theater:" << endl;
            queue<MovieTicket> tempQueue = theaters[theaterName]; // Create a temporary queue for display
            while (!tempQueue.empty())
            {
                MovieTicket currentTicket = tempQueue.front();
                cout << "\nMovie: " << currentTicket.movieName << ", \nSeat: " << currentTicket.seatNumber << endl;
                tempQueue.pop();
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // user side functions

    static void Merge(vector<MovieTicket> &tickets, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Create temporary vectors
        vector<MovieTicket> leftSubarray(tickets.begin() + left, tickets.begin() + left + n1);
        vector<MovieTicket> rightSubarray(tickets.begin() + mid + 1, tickets.begin() + mid + 1 + n2);

        int i = 0, j = 0, k = left;

        // Merge the temporary vectors back into the original vector
        while (i < n1 && j < n2)
        {
            if (leftSubarray[i].seatNumber <= rightSubarray[j].seatNumber)
            {
                tickets[k++] = leftSubarray[i++];
            }
            else
            {
                tickets[k++] = rightSubarray[j++];
            }
        }

        // Copy the remaining elements of leftSubarray, if any
        while (i < n1)
        {
            tickets[k++] = leftSubarray[i++];
        }

        // Copy the remaining elements of rightSubarray, if any
        while (j < n2)
        {
            tickets[k++] = rightSubarray[j++];
        }
    }

    static void MergeSort(vector<MovieTicket> &tickets, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            // Recursively sort the two halves
            MergeSort(tickets, left, mid);
            MergeSort(tickets, mid + 1, right);

            // Merge the sorted halves
            Merge(tickets, left, mid, right);
        }
    }

    void BuyTicket(const string &theaterNumber, const string &userName)
    {
        int theaterChoice;
        try
        {
            theaterChoice = stoi(theaterNumber); // stoi functon convert string to int
        }
        catch (const std::invalid_argument &e)
        {
            cout << "\nInvalid theater number format: " << theaterNumber << endl;
            return;
        }

        if (theaterChoice >= 1 && theaterChoice <= 3)
        {
            string theaterName = "Theater " + to_string(theaterChoice);

            if (theaters.find(theaterName) != theaters.end())
            {
                queue<MovieTicket> &theaterQueue = theaters[theaterName];

                // Check if there are available tickets
                if (!theaterQueue.empty())
                {
                    // Get the first available ticket
                    MovieTicket firstAvailableTicket = theaterQueue.front();

                    // Mark the seat as unavailable
                    firstAvailableTicket.isAvailable = false;

                    cout << "\nTicket purchased for seat " << firstAvailableTicket.seatNumber << " in " << theaterName << " theater for user: " << userName << "." << endl;

                    // Remove the purchased ticket from the system
                    Removeticket(theaterName, firstAvailableTicket.seatNumber);
                }
                else
                {
                    cout << "\nNo available tickets in " << theaterName << " theater." << endl;
                }
            }
            else
            {
                cout << "\nInvalid theater name: " << theaterName << endl;
            }
        }
        else
        {
            cout << "\nInvalid theater number. Please choose between 1 and 3." << endl;
        }
    }

    void Removeticket(const string &theaterName, int seatNumber)
    {
        queue<MovieTicket> &theaterQueue = theaters[theaterName];

        // Create a temporary queue to hold the tickets you want to keep
        queue<MovieTicket> tempQueue;

        // Find the ticket with the specified seat number and remove it
        bool found = false;
        while (!theaterQueue.empty())
        {
            const MovieTicket &currentTicket = theaterQueue.front();

            if (currentTicket.seatNumber == seatNumber)
            {
                found = true;
                cout << "\nTicket removed for seat " << seatNumber << " in " << theaterName << " theater." << endl;
            }
            else
            {
                // Add tickets other than the one to be removed to the tempQueue
                tempQueue.push(currentTicket);
            }

            // Remove the front ticket from the original queue
            theaterQueue.pop();
        }

        // If the ticket wasn't found, display a message
        if (!found)
        {
            cout << "\nTicket not found for seat " << seatNumber << " in " << theaterName << " theater." << endl;
        }

        // Swap the temporary queue with the original queue
        swap(theaterQueue, tempQueue);
    }

    // Display available tickets after a purchase
    void DisplayAvailableTickets(const string &theaterName)
    {
        if (theaters.find(theaterName) != theaters.end())
        {
            queue<MovieTicket> tempQueue = theaters[theaterName];

            // Copy elements from the queue to a vector
            vector<MovieTicket> theaterVector;
            while (!tempQueue.empty())
            {
                theaterVector.push_back(tempQueue.front());
                tempQueue.pop();
            }

            // Sort the vector by seat number
            MergeSort(theaterVector, 0, theaterVector.size() - 1);

            // Display the available tickets after sorting
            cout << "Available tickets in " << theaterName << " theater (sorted by seat number):" << endl;
            for (const MovieTicket &ticket : theaterVector)
            {
                if (ticket.isAvailable)
                {
                    cout << "Seat: " << ticket.seatNumber << ", Movie: " << ticket.movieName << endl;
                }
            }
            return; ////////////////////
        }
        else
        {
            cout << "Invalid theater name: " << theaterName << endl;
        }
    }

    // give info about view user tickets details
    void ViewUserTickets(const string &userName)
    {
        bool found = false;

        for (const auto &theater : theaters)
        {
            const queue<MovieTicket> &tempQueue = theater.second;

            // Display the user's purchased tickets in the current theater
            cout << "User's purchased tickets in " << theater.first << " theater:" << endl;

            queue<MovieTicket> tempCopy = tempQueue; // Create a copy of the queue to avoid modifying the original

            while (!tempCopy.empty())
            {
                const MovieTicket &currentTicket = tempCopy.front();

                // Check if the ticket belongs to the user and is not available
                if (!currentTicket.isAvailable && currentTicket.username == userName)
                {
                    cout << "Seat: " << currentTicket.seatNumber << ", Movie: " << currentTicket.movieName << ", Theater: " << theater.first << endl;
                    found = true;
                }

                tempCopy.pop();
            }
        }

        if (!found)
        {
            cout << "No purchased tickets found for user: " << userName << endl;
        }
    }
};

int main()
{
    const string admin_password = "password";
    string pass;
    int ch;

    string theaterNames[3] = {"Theater 1", "Theater 2", "Theater 3"};
    MovieTicketBookingSystem bookingSystem;
    cout << "*************************************************************************************************************************************** " << endl;
    cout << "" << endl;
    cout << "                                               WELCOME TO MOVIE TICKET BOOKING SYSTEM                                            " << endl;
    cout << "                           THE PROGRAM IS GENERATED BY CS DEPARTMENT (BCT 3A) COMSATS UNIVERSITY ISLAMABAD                         " << endl;
    cout << "" << endl;
    cout << "*************************************************************************************************************************************** " << endl;
    cout << " " << endl;

    cout << "\n(1) If you want to enter as an Admin" << endl;
    cout << "\n(2) If you want to enter as a User" << endl;
    cout << "\n(3) Exit the Program.";
    cin >> ch;

    while (true)
    {
        if (ch == 1)
        {
            cout << "\nEnter admin password: ";
            cin >> pass;

            if (admin_password == pass)
            {

                while (true)
                {
                    cout << "\n====== Admin Menu ======" << endl;
                    cout << "1. Add Ticket in the System\n2. Remove Ticket\n3. Display Tickets in the System\n4. Search for Ticket\n5. Exit Admin Menu\n";
                    cout <<"---------------------------------"<<endl;
                    cout << "\nEnter your choice: ";

                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice)
                    {
                    case 1:
                    {
                        cout << "\nEnter Theater number (1-3): ";
                        int theaterChoice;
                        cin >> theaterChoice;

                        if (theaterChoice >= 1 && theaterChoice <= 3)
                        {
                            string theaterName = theaterNames[theaterChoice - 1];
                            bookingSystem.AddTicket(theaterNames, theaterChoice);
                        }
                        else
                        {
                            cout << "Invalid theater number. Please choose between 1 and 3." << endl;
                        }
                        break;
                    }
                    case 2:
                    {
                        cout << "\nEnter Theater number (1-3): ";
                        int theaterChoice;
                        cin >> theaterChoice;

                        if (theaterChoice >= 1 && theaterChoice <= 3)
                        {
                            string theaterName = theaterNames[theaterChoice - 1];
                            bookingSystem.RemoveTicket(theaterName);
                        }
                        else
                        {
                            cout << "Invalid theater number. Please choose between 1 and 3." << endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        cout << "\nEnter Theater number (1-3): ";
                        int theaterChoice;
                        cin >> theaterChoice;

                        if (theaterChoice >= 1 && theaterChoice <= 3)
                        {
                            string theaterName = theaterNames[theaterChoice - 1];
                            bookingSystem.displayTickets(theaterName);
                        }
                        else
                        {
                            cout << "Invalid theater number. Please choose between 1 and 3." << endl;
                        }
                        break;
                    }
                    case 4:
                    {
                        cout << "\nEnter Theater number (1-3): ";
                        int theaterChoice;
                        cin >> theaterChoice;

                        if (theaterChoice >= 1 && theaterChoice <= 3)
                        {
                            string theaterName = theaterNames[theaterChoice - 1];

                            cout << "Enter Movie Name: ";
                            string movieName;
                            cin >> movieName;

                            cout << "Enter Seat Number: ";
                            int seatNumber;
                            cin >> seatNumber;

                            // Search for the ticket
                            bookingSystem.TicketExists(theaterName, movieName, seatNumber);
                        }
                        else
                        {
                            cout << "Invalid theater number. Please choose between 1 and 3." << endl;
                        }
                        break;
                    }
                    case 5:
                        cout << "\n\t\tExiting Admin Menu! \n\t\t Thank you :)\n\n\n";
                        cout << "\n(1) If you want to enter as an Admin" << endl;
                        cout << "\n(2) If you want to enter as a User" << endl;
                        cout << "\n(3) Exit the Program."<<endl;
                        cout <<"---------------------------------"<<endl;

                        cin >> ch;

                        break;
                    default:
                        cout << "Invalid choice. Please enter a valid option.\n";
                    }

                    if (adminChoice == 5)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Incorrect password. Please try again.\n";
            }
        }
        else if (ch == 2)
        {
            while (true)
            {
                cout << "\n====== User Menu ======" << endl;
                cout << "(1) Buy Ticket\n(2) Display Available Tickets\n(3) Search for specific Ticket \n(4) Exit User Menu "<<endl;
                cout <<"---------------------------------"<<endl;
                cout << "\nEnter your choice: ";

                int userChoice;
                cin >> userChoice;

                switch (userChoice)
                {
                case 1:
                {
                    cout << "Enter Theater number (1-3): ";
                    int theaterChoice;
                    string username;
                    cin >> theaterChoice;
                    cout << "Enter your Name : ";
                    cin >> username;

                    bookingSystem.BuyTicket(to_string(theaterChoice), username);
                    break;
                }
                case 2:
                {
                    cout << "Enter Theater number (1-3): ";
                    int theaterChoice;
                    cin >> theaterChoice;

                    if (theaterChoice >= 1 && theaterChoice <= 3)
                    {
                        string theaterName = theaterNames[theaterChoice - 1];
                        bookingSystem.DisplayAvailableTickets(theaterName);
                    }
                    else
                    {
                        cout << "Invalid Theater Number" << endl;
                    }
                    break;
                }
                case 3:
                {
                    cout << "\nEnter Theater number (1-3): ";
                    int theaterChoice;
                    cin >> theaterChoice;

                    if (theaterChoice >= 1 && theaterChoice <= 3)
                    {
                        string theaterName = theaterNames[theaterChoice - 1];

                        cout << "Enter Movie Name: ";
                        string movieName;
                        cin >> movieName;

                        cout << "Enter Seat Number: ";
                        int seatNumber;
                        cin >> seatNumber;

                        // Search for the ticket
                        bookingSystem.TicketExists(theaterName, movieName, seatNumber);
                    }
                    else
                    {
                        cout << "Invalid theater number. Please choose between 1 and 3." << endl;
                    }
                    break;
                }
                case 4:
                {
                    cout << "\n\t\tExiting Admin Menu! \n\t\t Thank you :)\n\n\n";
                    cout << "\n(1) If you want to enter as an Admin" << endl;
                    cout << "\n(2) If you want to enter as a User" << endl;
                    cout << "\n(3) Exit the Program.";

                    cin >> ch;
                    break;
                }

                default:
                    cout << "Invalid choice. Please enter a valid option.\n";
                }

                if (userChoice == 3)
                {
                    break;
                }
            }
        }

        else if (ch == 3)
        {
            cout << "\n\t\tExiting the program. Thank you!\n";
            break;
        }
        else
        {
            cout << "Please Enter valid choice\n"
                 << endl;
        }
    }

    return 0;
}
