# Shinkansen-Car-Rental

A robust Command-Line Interface (CLI) car rental management system implemented in modern C++. Shinkansen-Car-Rental is designed for both educational and practical application, demonstrating sophisticated use of Object-Oriented Programming (OOP) principles and the Standard Template Library (STL). The project uniquely handles data persistence using CSV files, allowing for custom implementation of searching and sorting algorithms rather than relying on external databases.

---

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Workflows & Automation](#workflows--automation)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

---

## Features

**Client Interface**
- **View Cars:** Display a detailed list of all available cars with specifications.
- **Book Cars:** Reserve a car by specifying the model and rental period. The system calculates and displays the total cost.
- **Generate Invoice:** Instantly produce an invoice with all booking details.
- **Cancel Booking:** Cancel an active reservation with confirmation.
- **User Registration:** New clients can register using their name and mobile number, with duplicate detection.

**Administrator Interface**
- **Car Inventory Management:** Add, delete, and update car records.
- **Advanced Search and Sort:** Filter cars by company, engine type, seating capacity, and price range. Sort results by price, seating, or company.
- **Client Database Access:** Review registered client details.
- **Security:** Admin access controlled via username and password authentication.

**Data Integrity and Reliability**
- All transactional and inventory data securely stored in CSV files: `car_rental_data.csv`, `ClientDetails.csv`, and `BookingDetails.csv`.
- The application ensures consistency and validates user inputs for all critical operations.

**Educational Focus**
- All searching and sorting algorithms are implemented from scratch, providing a deep dive into C++ STL and algorithm design.

---

## Installation

### Prerequisites

- **C++ Compiler:** GCC, Clang, or MSVC supporting C++11 or later.
- **Operating System:** Linux, macOS, or Windows.
- **Terminal/CLI Access**

### Setup

1. **Clone the Repository**
   ```bash
   git clone https://github.com/Rudrakshbhardwaj01/Shinkansen-Car-Rental.git
   cd Shinkansen-Car-Rental
   ```

2. **Compile the Application**
   ```bash
   g++ main.cpp -o shinkansen_car_rental
   ```

3. **Prepare Data Files**
   - The application will automatically create the necessary CSV files if they do not exist.
   - Optionally, you may pre-populate `car_rental_data.csv` for initial inventory.

---

## Usage

### Start the System

```bash
./shinkansen_car_rental
```

### Main Menu

- **Admin Access:** Enter `*` at the prompt. Use credentials:
  - Username: `admin`
  - Password: `RUDRAKSH`
- **Client Access:** Enter `#` at the prompt. Register or login as a client.
- **Exit:** Type `exit` to terminate the program.

#### Example Workflows

**Client Operations:**
1. Register with name and phone number.
2. View all cars.
3. Book a car.
4. Generate invoice or cancel booking.

**Admin Operations:**
1. Login with admin credentials.
2. Manage car inventory (add/update/delete).
3. Search and sort cars.
4. View client database.

---

## Code Structure

```
Shinkansen-Car-Rental/
│
├── main.cpp                # Entry point, contains all core logic and class definitions
├── car_rental_data.csv     # Persistent store for car inventory
├── ClientDetails.csv       # Persistent store for client information
├── BookingDetails.csv      # Persistent store for bookings and invoices
├── README.md               # Project documentation (this file)
```

**Key Components:**
- **Structs:** `Client`, `Booking`, `Car` – define core data models.
- **Classes:**
  - `ClientManager`: Handles client registration and validation.
  - `client`: All client-side operations and menu navigation.
  - `admin`: Administrative functions, car and client management.
  - `startSystem`: Application startup, authentication, and main loop.

---

## Workflows & Automation

- **Manual Operation:** The system does not currently include automated CI/CD pipelines or GitHub Actions.
- **Data Integrity:** All operations (add, update, delete) are transactional and ensure data consistency in CSV files.

---

## Contributing

We welcome contributions that improve functionality, performance, or documentation.

**How to Contribute:**
1. Fork the repository.
2. Create a feature branch.
3. Commit your changes with clear, descriptive messages.
4. Submit a pull request with a summary of changes.

**Guidelines:**
- Write professional, clear code and documentation.
- Ensure your changes do not break core functionalities.
- For significant changes, open an issue first for discussion.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for full terms.

---

## Author

Developed and maintained by **Rudraksh Bhardwaj**.

---

## Acknowledgments

Special thanks to contributors, users, and the open source community for feedback and improvements.
