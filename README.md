
# Movie Ticket Booking System

## Overview
The Movie Ticket Booking System is a console-based application that utilizes various data structures and Object-Oriented Programming (OOP) principles to manage theater ticket bookings. It supports both admin and user functionalities, allowing efficient management of movie tickets using **queue**, **unordered maps**, and **vectors**.

## Features

### Admin Features:
- Add tickets to the system for a specific theater.
- Remove tickets from the system for a specific theater.
- Display all tickets for a specific theater.
- Search for a specific ticket based on movie name and seat number.

### User Features:
- Buy a ticket for a specific theater.
- Display available tickets for a specific theater.
- Search for a specific ticket based on movie name and seat number.
- View purchased tickets for a specific user.

## Data Structures Used
- **Queue:** Stores tickets based on the **First In, First Out (FIFO)** principle.
- **Unordered Map:** Maps theater names to their respective ticket queues.
- **Vector:** Used for temporary storage during various operations.
- **2D Array:** Represents theater seating (5×5 matrix), associating each seat with a ticket.

## Classes & Attributes
### **Ticket Class**
The `Ticket` class holds the following attributes:
- **Seat Number:** Identifies the seat in the theater.
- **Username:** Specifies the user to whom the seat is assigned.
- **Availability:** Boolean indicating whether the seat is available.
- **Movie Name:** The movie assigned to the ticket.

## How It Works
1. **Admin Module:**
   - Admin adds tickets to the queue.
   - Assigns a movie to be displayed in a theater.
   - Manages seat availability.
2. **User Module:**
   - Users can book available seats.
   - Users can search for and view their booked tickets.

## Setup & Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/iuy-z/Movie-Ticket-Booking-System.git
   ```
2. Compile the source code (if using C++):
   ```sh
   g++ main.cpp -o movie_ticket_system
   ```
3. Run the application:
   ```sh
   ./movie_ticket_system
   ```

## Future Enhancements
- Implement a GUI for better user interaction.
- Add payment integration.
- Support for multiple theaters and dynamic seat arrangements.


