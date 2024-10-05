#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
using namespace std;
struct Client
{
    string name;
    string phoneNumber;
};
struct Booking
{
    string clientName;
    string carModel;
    string rentalDuration;
    string bookingDate;
    double totalPrice;
};
struct Car
{
    string company;
    string model;
    string type;
    int seatingCapacity;
    string engineType;
    double rentalPrice;
};

class client;
class startSystem;
class ClientManager
{
    friend class client;

public:
    static void registerClient()
    {
        Client newClient;
        cout << "Enter your name: ";
        cin >> newClient.name;
        cout << "Enter your phone number: ";
        cin >> newClient.phoneNumber;

        if (clientExists(newClient))
        {
            cout << "Account already exists!" << endl;
        }
        else
        {
            appendClientToCSV(newClient);
            cout << "Registration successful!" << endl;
        }
    }

private:
    static bool clientExists(const Client &client)
    {
        ifstream file("ClientDetails.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, phone;
            getline(ss, name, ',');
            getline(ss, phone, ',');
            if (name == client.name && phone == client.phoneNumber)
            {
                return true;
            }
        }
        return false;
    }

    static void appendClientToCSV(const Client &client)
    {
        ofstream file("ClientDetails.csv", ios::app);
        file << client.name << "," << client.phoneNumber << endl;
        file.close();
    }
};

class client
{
    friend class startSystem;
    friend class admin;

public:
    static void cancelBooking()
    {
        string clientName, phoneNumber, carModel;
        cout << "Enter your name to cancel the booking: ";
        cin >> clientName;
        cout << "Enter your phone number: ";
        cin >> phoneNumber;
        cout << "Enter the model of the car you want to cancel: ";
        cin >> carModel;

        ifstream file("BookingDetails.csv");
        if (!file.is_open())
        {
            cout << "Error: Unable to open the booking file!" << endl;
            return;
        }

        vector<Booking> bookings;
        string line;
        bool bookingFound = false;

        // Read all bookings and store them in a vector, except the one to cancel
        while (getline(file, line))
        {
            stringstream ss(line);
            Booking booking;
            string totalPrice;

            getline(ss, booking.clientName, ',');
            getline(ss, booking.carModel, ',');
            getline(ss, booking.rentalDuration, ',');
            getline(ss, booking.bookingDate, ',');
            getline(ss, totalPrice, ',');
            booking.totalPrice = stod(totalPrice);

            string clientPhone = getClientPhone(booking.clientName);

            if (booking.clientName == clientName && clientPhone == phoneNumber && booking.carModel == carModel)
            {
                bookingFound = true;
                continue;
            }
            bookings.push_back(booking);
        }
        file.close();

        if (!bookingFound)
        {
            cout << "Booking not found for " << clientName << " with phone number " << phoneNumber << " and car model " << carModel << "!" << endl;
            return;
        }

        ofstream outFile("BookingDetails.csv");
        if (!outFile.is_open())
        {
            cout << "Error: Unable to open the booking file for writing!" << endl;
            return;
        }

        for (const auto &b : bookings)
        {
            outFile << b.clientName << "," << b.carModel << "," << b.rentalDuration << "," << b.bookingDate << "," << b.totalPrice << endl;
        }
        outFile.close();

        cout << "Booking for " << carModel << " by " << clientName << " (Phone: " << phoneNumber << ") has been successfully canceled!" << endl;
    }

    static string getClientPhone(const string &clientName)
    {
        ifstream file("ClientDetails.csv");
        string line, name, phone;

        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, phone, ',');

            if (name == clientName)
            {
                return phone;
            }
        }
        return "";
    }

    static void readCars()
    {
        ifstream in("car_rental_data.csv");
        if (!in.is_open())
        {
            cout << "Unable to open the file!" << endl;
            return;
        }

        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            string CarCompany, CarModel, CarType, Seating, EngineType, RentalPrice;

            getline(ss, CarCompany, ',');
            getline(ss, CarModel, ',');
            getline(ss, CarType, ',');
            getline(ss, Seating, ',');
            getline(ss, EngineType, ',');
            getline(ss, RentalPrice, ',');

            cout << "Company: " << CarCompany << " | " << "Model: " << CarModel << " | " << "Type: " << CarType << " | " << "Seating: " << Seating << " | " << "Engine Type: " << EngineType << " | " << endl;
            cout << "Price per hour: " << "$ " << RentalPrice << endl;
        }
        in.close();
    }
    static void bookCar()
    {
        string carModel;
        string rentalDuration;
        cout << "Enter the model of the car you want to book: ";
        cin >> carModel;
        cout << "Enter the rental duration (in hours): ";
        cin >> rentalDuration;
        string line;
        ifstream in("car_rental_data.csv");

        if (!in.is_open())
        {
            cerr << "Error: Unable to open the file!" << endl;
        }

        double pricePerHour;
        while (getline(in, line))
        {
            stringstream ss(line);
            string CarCompany, CarModel, CarType, Seating, EngineType, RentalPrice;

            getline(ss, CarCompany, ',');
            getline(ss, CarModel, ',');
            getline(ss, CarType, ',');
            getline(ss, Seating, ',');
            getline(ss, EngineType, ',');
            getline(ss, RentalPrice, ',');
            if (!RentalPrice.empty())
            {
                try
                {
                    pricePerHour = stod(RentalPrice);
                }
                catch (const invalid_argument &e)
                {
                    cout << "Invalid price format for car: " << CarModel << endl;
                }
                catch (const out_of_range &e)
                {
                    cout << "Price out of range for car: " << CarModel << endl;
                }
            }
            else
            {
                cout << "Rental price is empty for car: " << CarModel << endl;
            }
        }

        in.close();

        double totalPrice = pricePerHour * stoi(rentalDuration);
        string Date;
        cout << "Enter the date for which you want to book a car (Format: DD-MM-YYYY): ";
        cin >> Date;

        string clientName;
        cout << "Enter your name to confirm the booking: ";
        cin >> clientName;
        Booking newBooking = {clientName, carModel, rentalDuration, Date, totalPrice};
        appendBookingToCSV(newBooking);

        cout << "Booking confirmed for " << carModel << " for " << rentalDuration << " hours." << endl
             << "Total price: $" << totalPrice << endl;
    }

private:
    static void appendBookingToCSV(const Booking &booking)
    {
        ofstream file("BookingDetails.csv", ios::app);
        file << booking.clientName << "," << booking.carModel << "," << booking.rentalDuration << "," << booking.bookingDate << "," << booking.totalPrice << endl;
        file.close();
    }
    static void invoice()
    {
        cout << "-- Booking Invoice --" << endl;
        string line;
        ifstream in("BookingDetails.csv");
        while (getline(in, line))
        {
            stringstream sS(line);
            string name, Model, rentalHours, date, Rental;
            getline(sS, name, ',');
            getline(sS, Model, ',');
            getline(sS, rentalHours, ',');
            getline(sS, date, ',');
            getline(sS, Rental, ',');

            cout << "Name: " << name << endl
                 << "Car Booked: " << Model << endl
                 << "Rented for " << rentalHours << " hours." << endl
                 << "Total bill amount: " << Rental;
        }
        in.close();
    }

    static void clientMenu()
    {
        int choice;
        cout << "----- Client Services -----" << endl;
        cout << "" << endl;
        cout << "Enter 1 to view all the available cars. " << endl;
        cout << "Enter 2 to book a car. " << endl;
        cout << "Enter 3 to generate an invoice. " << endl;
        cout << "Enter 4 to cancel a booking. " << endl;
        cout << "Enter 00 to exit the program.  " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "----- Available Cars -----" << endl;
            readCars();
            break;
        case 2:
            cout << "----- Booking Portal -----" << endl;
            bookCar();
            break;
        case 3:
            cout << "----- Invoice ----- " << endl;
            invoice();
            break;
        case 4:
            cout << "----- Cancellation Portal -----" << endl;
            cancelBooking();
        case 00:
            cout << "----- Exiting the system! ----- " << endl;
            exit(0);
            break;
        }
    }
};

class admin
{
    friend class startSystem;

public:
    static void addCar()
    {
        string carCompany, carModel, carType, seatingCapacity, engineType;
        double rentalPrice;

        cout << "Enter the car company: ";
        cin >> carCompany;
        cout << "Enter the car model: ";
        cin >> carModel;
        cout << "Enter the car type (e.g., SUV, Sedan, etc.): ";
        cin >> carType;
        cout << "Enter seating capacity: ";
        cin >> seatingCapacity;
        cout << "Enter engine type (e.g., Petrol, Diesel, Electric): ";
        cin >> engineType;
        cout << "Enter rental price per hour: ";
        cin >> rentalPrice;

        ofstream outFile("car_rental_data.csv", ios::app);
        if (outFile.is_open())
        {
            outFile << carCompany << "," << carModel << "," << carType << "," << seatingCapacity << "," << engineType << "," << rentalPrice << endl;
            outFile.close();
            cout << "Car added successfully!" << endl;
        }
        else
        {
            cout << "Error: Unable to open the car rental data file!" << endl;
        }
    }
    static void deleteCar()
    {
        string carModel;
        cout << "Enter the model of the car you want to delete: ";
        cin >> carModel;

        ifstream inFile("car_rental_data.csv");
        if (!inFile.is_open())
        {
            cout << "Error: Unable to open the car rental data file!" << endl;
            return;
        }

        vector<string> carData;
        string line;
        bool carFound = false;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string CarCompany, CarModel, CarType, Seating, EngineType, RentalPrice;

            getline(ss, CarCompany, ',');
            getline(ss, CarModel, ',');
            getline(ss, CarType, ',');
            getline(ss, Seating, ',');
            getline(ss, EngineType, ',');
            getline(ss, RentalPrice, ',');

            if (CarModel == carModel)
            {
                carFound = true;
                continue;
            }

            carData.push_back(line);
        }
        inFile.close();

        if (!carFound)
        {
            cout << "Car with model " << carModel << " not found!" << endl;
            return;
        }

        ofstream outFile("car_rental_data.csv");
        if (!outFile.is_open())
        {
            cout << "Error: Unable to open the car rental data file for writing!" << endl;
            return;
        }

        for (const string &data : carData)
        {
            outFile << data << endl;
        }
        outFile.close();

        cout << "Car with model " << carModel << " has been successfully deleted!" << endl;
    }

    static void readClients()
    {
        ifstream in("ClientDetails.csv");
        if (!in.is_open())
        {
            cout << "Unable to open the file!" << endl;
            return;
        }

        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            string name, phone;

            getline(ss, name, ',');
            getline(ss, phone, ',');

            cout << "Name: " << name << " | " << "Phone Number: " << phone << endl;
        }
        in.close();
    }
    static void updateCarDetails()
    {
        string carModel;
        cout << "Enter the model of the car you want to update: ";
        cin >> carModel;

        ifstream inFile("car_rental_data.csv");
        if (!inFile.is_open())
        {
            cout << "Error: Unable to open the car rental data file!" << endl;
            return;
        }

        vector<string> carData;
        string line;
        bool carFound = false;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string CarCompany, CarModel, CarType, Seating, EngineType, RentalPrice;

            getline(ss, CarCompany, ',');
            getline(ss, CarModel, ',');
            getline(ss, CarType, ',');
            getline(ss, Seating, ',');
            getline(ss, EngineType, ',');
            getline(ss, RentalPrice, ',');

            if (CarModel == carModel)
            {
                carFound = true;

                cout << "Current Details for " << carModel << ":" << endl;
                cout << "Car Company: " << CarCompany << endl;
                cout << "Car Type: " << CarType << endl;
                cout << "Seating Capacity: " << Seating << endl;
                cout << "Engine Type: " << EngineType << endl;
                cout << "Rental Price per hour: " << RentalPrice << endl;

                cout << "Enter updated Car Company: ";
                cin >> CarCompany;
                cout << "Enter updated Car Type: ";
                cin >> CarType;
                cout << "Enter updated Seating Capacity: ";
                cin >> Seating;
                cout << "Enter updated Engine Type: ";
                cin >> EngineType;
                cout << "Enter updated Rental Price per hour: ";
                cin >> RentalPrice;

                string updatedLine = CarCompany + "," + CarModel + "," + CarType + "," + Seating + "," + EngineType + "," + RentalPrice;
                carData.push_back(updatedLine);
            }
            else
            {
                carData.push_back(line);
            }
        }
        inFile.close();

        if (!carFound)
        {
            cout << "Car with model " << carModel << " not found!" << endl;
            return;
        }

        ofstream outFile("car_rental_data.csv");
        if (!outFile.is_open())
        {
            cout << "Error: Unable to open the car rental data file for writing!" << endl;
            return;
        }

        for (const string &data : carData)
        {
            outFile << data << endl;
        }
        outFile.close();

        cout << "Car details for model " << carModel << " have been successfully updated!" << endl;
    }

    static vector<Car> loadCarsFromCSV(const string &filename)
    {
        vector<Car> cars;
        ifstream in(filename);

        if (!in.is_open())
        {
            cerr << "Error: Unable to open file." << endl;
            return cars;
        }

        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            Car car;
            string seating;

            getline(ss, car.company, ',');
            getline(ss, car.model, ',');
            getline(ss, car.type, ',');
            getline(ss, seating, ',');
            car.seatingCapacity = stoi(seating);
            getline(ss, car.engineType, ',');
            string price;
            getline(ss, price, ',');
            car.rentalPrice = stod(price);

            cars.push_back(car);
        }
        in.close();

        return cars;
    }

    static vector<Car> searchCars(const vector<Car> &cars, const string &engineType, const string &company,
                                  int seatingCapacity, double minPrice, double maxPrice)
    {
        vector<Car> result;
        for (const auto &car : cars)
        {
            if ((engineType.empty() || car.engineType == engineType) &&
                (company.empty() || car.company == company) &&
                (seatingCapacity == -1 || car.seatingCapacity == seatingCapacity) &&
                (car.rentalPrice >= minPrice && car.rentalPrice <= maxPrice))
            {
                result.push_back(car);
            }
        }
        return result;
    }

    static void sortCars(vector<Car> &cars, const string &sortBy)
    {
        if (sortBy == "price")
        {
            sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                 { return a.rentalPrice < b.rentalPrice; });
        }
        else if (sortBy == "seating")
        {
            sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                 { return a.seatingCapacity < b.seatingCapacity; });
        }
        else if (sortBy == "company")
        {
            sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                 { return a.company < b.company; });
        }
    }

    static void displayCars(const vector<Car> &cars)
    {
        for (const auto &car : cars)
        {
            cout << "Company: " << car.company << " | Model: " << car.model
                 << " | Type: " << car.type << " | Seating: " << car.seatingCapacity
                 << " | Engine: " << car.engineType << " | Price: $" << car.rentalPrice << endl;
        }
    }

    static void searchCars()
    {
        vector<Car> cars = loadCarsFromCSV("car_rental_data.csv");
        string engineType, company, sortBy;
        int seatingCapacity;
        double minPrice, maxPrice;

        cout << "Enter Engine Type (or leave blank): ";
        cin.ignore();
        getline(cin, engineType);
        cout << "Enter Car Company (or leave blank): ";
        getline(cin, company);
        cout << "Enter Seating Capacity (or -1 for any): ";
        cin >> seatingCapacity;
        cout << "Enter Minimum Price: ";
        cin >> minPrice;
        cout << "Enter Maximum Price: ";
        cin >> maxPrice;
        cout << "Sort by (price/seating/company): ";
        cin.ignore();
        getline(cin, sortBy);

        vector<Car> filteredCars = searchCars(cars, engineType, company, seatingCapacity, minPrice, maxPrice);
        sortCars(filteredCars, sortBy);

        if (filteredCars.empty())
        {
            cout << "No cars found matching your criteria." << endl;
        }
        else
        {
            displayCars(filteredCars);
        }
    }

    static void adminMenu()
    {
        int choice;
        cout << "----- Admin Features -----" << endl;
        cout << "" << endl;
        cout << "Enter 1 to view all the available cars. " << endl;
        cout << "Enter 2 to add a new car. " << endl;
        cout << "Enter 3 to delete an existing car. " << endl;
        cout << "Enter 4 to update car details. " << endl;
        cout << "Enter 5 search for a particular car. " << endl;
        cout << "Enter 6 to view the client database." << endl;
        cout << "Enter 00 to exit the program.  " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "----- Available Cars -----" << endl;
            client::readCars();
            break;
        case 2:
            cout << "----- Car Addition Portal -----" << endl;
            addCar();
            break;
        case 3:
            cout << "----- Car Deletion Portal -----" << endl;
            deleteCar();
            break;
        case 4:
            cout << "----- Car Detail Updation Portal ----- " << endl;
            updateCarDetails();
            break;
        case 5:
            cout << "-- Car Search --" << endl;
            searchCars();
            break;
        case 6:
            cout << "-- Client Database --" << endl;
            readClients();
            break;
        case 00:
            cout << "----- Exiting the system! ----- " << endl;
            exit(0);
            break;
        }
    }
};

class startSystem
{
public:
    friend class client;
    string userType;
    void authentication()
    {
        cout << "Press * to enter as an admin." << endl;
        cout << "Press # to enter as a client." << endl;
        cout << "Type exit to exit the program." << endl;
        cout << "Enter your choice:";
        cin >> userType;
        transform(userType.begin(), userType.end(), userType.begin(), ::tolower);
        if (userType == "*")
        {
            cout << "-- LOGIN --" << endl;
            string userName;
            cout << "Enter username:" << endl;
            cin >> userName;
            transform(userName.begin(), userName.end(), userName.begin(), ::tolower);
            string password;
            cout << "Enter password:" << endl;
            cin >> password;
            if (userName == "admin" && password == "RUDRAKSH")
            {
                cout << " " << endl;
                cout << "Verifying credentials...." << endl;
                cout << "Credentials matched!" << endl;
                cout << " " << endl;
                cout << "Welcome to the server (admin) side." << endl;
                admin::adminMenu();
            }
            else
            {
                cout << "-- Invalid Credentials --" << endl;
                cout << "-- Try Again --" << endl;
                authentication();
            }
        }
        else if (userType == "#")
        {
            cout << "---- Shinkansen Car Rentals ----" << endl;
            ClientManager::registerClient();
            client::clientMenu();
        }
        else if (userType == "exit")
        {
            cout << "-- Exiting the system --" << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid choice! Try again!" << endl;
            cout << "" << endl;
            startSystem();
        }
    }
    startSystem()
    {
        cout << "Welcome to the Shinkansen Car Rental Services" << endl;
        authentication();
        string yn;
        while (yn != "no")
        {
            cout << "Do you want to continue using the program? " << "(Enter yes or no): " << endl;
            ;
            cin >> yn;
            transform(yn.begin(), yn.end(), yn.begin(), ::tolower);
            if (yn == "yes")
            {
                if (userType == "#")
                {
                    client::clientMenu();
                }
                else if (userType == "*")
                {
                    admin::adminMenu();
                }
                else
                {
                    cout << "Invalid Choice!" << endl;
                }
            }
            else if (yn == "no")
            {
                cout << "Exiting the program!" << endl;
                exit(0);
            }
            else
            {
                cout << "Invalid option!" << " " << "Exiting the program!" << endl;
                exit(0);
            }
        }
    }
};
int main()
{
    cout << "-------------------- SHINKANSEN CAR RENTAL --------------------" << endl;
    startSystem carRental;
    return 0;
}
