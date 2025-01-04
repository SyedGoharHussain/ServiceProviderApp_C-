#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define nullptr NULL

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string ITALIC = "\033[3m";
const string UNDERLINE = "\033[4m";

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void printDoubleSeparator()
{
    cout << YELLOW << "===============================================" << RESET << std::endl;
}

class User
{
protected:
    int id;
    string name, password, city;

public:
    User() : id(0), name(""), password(""), city("") {}

    User(int id, const string &name, const string &password, const string &city)
        : id(id), name(name), password(password), city(city) {}

    virtual void display() const
    {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(15) << city;
    }

    void setPassword(const string &password)
    {
        this->password = password;
    }
    void setCity(const string &city)
    {
        this->city = city;
    }

    int getId() const
    {
        return id;
    }
    const string &getPassword() const
    {
        return password;
    }
    const string &getCity() const
    {
        return city;
    }
    const string &getName() const
    {
        return name;
    }

    virtual const string &getType() const = 0;
};

class Worker : public User
{
private:
    string serviceType;
    double fee;

public:
    Worker() : serviceType(""), fee(0) {}

    Worker(int id, const string &name, const string &password, const string &city, const string &serviceType)
        : User(id, name, password, city), serviceType(serviceType), fee(0) {}

    void setFee(double newFee)
    {
        fee = newFee;
    }

    double getFee() const
    {
        return fee;
    }

    void display() const override
    {
        User::display();
        cout << setw(20) << serviceType
             << setw(10) << fee << endl;
    }

    const string &getServiceType() const
    {
        return serviceType;
    }

    const string &getType() const override
    {
        static string type = "Worker";
        return type;
    }
};

class Customer : public User
{
public:
    Customer() {}

    Customer(int id, const string &name, const string &password, const string &city)
        : User(id, name, password, city) {}

    void display() const override
    {
        User::display();
        cout << endl;
    }

    const string &getType() const override
    {
        static string type = "Customer";
        return type;
    }
};

class Task
{
private:
    int taskId, workerId, customerId;
    string description, status;
    double fee;

public:
    Task()
        : taskId(0), workerId(0), customerId(0), description(""), status("Pending"), fee(0) {}

    Task(int taskId, int workerId, int customerId, const string &description, double fee)
        : taskId(taskId), workerId(workerId), customerId(customerId), description(description), status("Pending"), fee(fee) {}

    void display() const
    {
        cout << left << setw(10) << taskId
             << setw(10) << workerId
             << setw(10) << customerId
             << setw(25) << description
             << setw(15) << status
             << setw(10) << fee << endl;
    }

    int getTaskId() const
    {
        return taskId;
    }

    int getWorkerId() const
    {
        return workerId;
    }

    int getCustomerId() const
    {
        return customerId;
    }

    const string &getDescription() const

    {
        return description;
    }

    const string &getStatus() const
    {
        return status;
    }

    double getFee() const
    {
        return fee;
    }

    void setStatus(const string &newStatus)
    {
        status = newStatus;
    }
};

struct Node
{
public:
    void *data;
    Node *next;

public:
    Node(void *data, Node *next = nullptr)
        : data(data), next(next) {}
};

class LinkedList
{
public:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }

    Node *getHead() const { return head; }

    void add(void *data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    void traverse(void (*func)(void *))
    {
        Node *current = head;
        while (current)
        {
            func(current->data);
            current = current->next;
        }
    }

    void remove(int id)
    {
        Node *current = head;
        Node *prev = nullptr;

        while (current)
        {
            User *user = static_cast<User *>(current->data);
            if (user->getId() == id)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void *find(int id)
    {
        Node *current = head;

        while (current)
        {
            User *user = static_cast<User *>(current->data);
            if (user->getId() == id)
            {
                return current->data;
            }
            current = current->next;
        }

        return nullptr;
    }
};

class ServiceManagementSystem
{
private:
    LinkedList workers;
    LinkedList customers;
    LinkedList tasks;
    int uniqueId;

public:
    ServiceManagementSystem()
        : uniqueId(uniquenumber()) {}

    int uniquenumber() const
    {
        srand(time(0));
        int uniqueNum;
        bool found = true;

        while (found)
        {
            found = false;
            uniqueNum = rand() % 90000 + 10000;

            ifstream file("number.txt");
            int num;

            while (file >> num)
            {
                if (num == uniqueNum)
                {
                    found = true;
                    break;
                }
            }
            file.close();
        }

        ofstream outFile("number.txt", ios::app);
        outFile << uniqueNum << endl;
        outFile.close();

        return uniqueNum;
    }

    void editAccount(User *user);
    void deleteAccount(int userID);
    void registerWorker();
    void registerCustomer();
    void requestService();
    void viewTasksForWorker(int workerID);
    void changeTaskStatus(int workerID, int taskID);
    void workerLoginMenu(int workerID);
    void customerLoginMenu(int customerID);
    int generateUniqueId();
    void saveWorkersToFile();
    void saveCustomersToFile();
    void saveTasksToFile();
    void loadWorkersFromFile();
    void loadCustomersFromFile();
    void loadTasksFromFile();

    void mainMenu();
};

void ServiceManagementSystem::editAccount(User *user)
{
    char choice = ' ';
    do
    {
        cout << "\nEdit Account Menu:\n";
        cout << "1. Change Password\n";
        cout << "2. Change City\n";
        cout << "3. Exit\n";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            string newPassword;
            cout << "\nEnter new Password: ";
            cin >> newPassword;
            user->setPassword(newPassword);
            break;
        }
        case '2':
        {
            string newCity;
            cout << "\nEnter new City: ";
            cin >> newCity;
            user->setCity(newCity);
            break;
        }
        case '3':
            break;

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != '3');
}

void ServiceManagementSystem::deleteAccount(int userID)
{
    workers.remove(userID);
    customers.remove(userID);
    saveWorkersToFile();
    saveCustomersToFile();

    cout << "Account with ID " << userID << " has been deleted.\n";
}

void ServiceManagementSystem::registerWorker()
{
    string name, password, city, serviceType;
    double fee;

    cout << GREEN << "Enter name: ";
    cin >> name;
    cout << RESET;
    cout << GREEN << "Enter Password: ";
    cin >> password;
    cout << RESET;
    cout << GREEN << "Enter city: ";
    cin >> city;
    cout << RESET;
    cout << YELLOW << "Available Services:\n";
    cout << RESET;
    cout << YELLOW << "1. Plumber\n2. Electrician\n3. Mechanic\n4. Carpenter\n5. Cable Connector\n";
    cout << RESET;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        serviceType = "Plumber";
        break;
    case 2:
        serviceType = "Electrician";
        break;
    case 3:
        serviceType = "Mechanic";
        break;
    case 4:
        serviceType = "Carpenter";
        break;
    case 5:
        serviceType = "Cable Connector";
        break;

    default:
        cout << RED << "Invalid choice!\n"
             << RESET;
        return;
    }

    cout << GREEN << "Enter your hire fee: ";
    cin >> fee;
    cout << RESET;

    Worker *worker = new Worker(uniqueId, name, password, city, serviceType);
    worker->setFee(fee);
    workers.add(worker);

    saveWorkersToFile();

    cout << GREEN << "Worker registered! ID: " << uniqueId << RESET << endl;

    uniqueId++;
}

void ServiceManagementSystem::registerCustomer()
{
    string name, password, city;

    cout << BLUE << "Enter name: ";
    cin >> name;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter city: ";
    cin >> city;
    cout << RESET;

    Customer *customer = new Customer(uniqueId, name, password, city);
    customers.add(customer);
    system("cls");
    saveCustomersToFile();

    cout << YELLOW << "Customer registered! ID: " << uniqueId << RESET << endl;

    uniqueId++;
}

void ServiceManagementSystem::requestService()
{
    cout << BOLD << GREEN << "\n______________________________________\n"
         << RESET;
    cout << ITALIC << UNDERLINE << GREEN << "|************REQUESTING SERVICE**************|\n"
         << RESET;
    int customerID;

    cout << YELLOW << "Enter your Customer ID: ";
    cin >> customerID;
    cout << RESET;

    Customer *customer = static_cast<Customer *>(customers.find(customerID));

    if (!customer)
    {
        cout << RED << "Customer ID not found!\n"
             << RESET;
        return;
    }

    cout << YELLOW << "Available Services:\n";
    cout << RESET;
    cout
        << YELLOW << "1. Plumber\n2. Electrician\n3. Mechanic\n4. Carpenter\n5. Cable Connector\n";
    cout << RESET;

    int choice;
    cin >> choice;

    string serviceType;

    switch (choice)
    {
    case 1:
        serviceType = "Plumber";
        break;
    case 2:
        serviceType = "Electrician";
        break;
    case 3:
        serviceType = "Mechanic";
        break;
    case 4:
        serviceType = "Carpenter";
        break;
    case 5:
        serviceType = "Cable Connector";
        break;

    default:
        cout << RED << "Invalid choice!\n"
             << RESET;
        return;
    }

    string description;

    cout << YELLOW << "Enter a description of the task: ";
    cin.ignore();
    getline(cin, description);
    cout << RESET;

    cout << MAGENTA << "\nSearching for workers providing " << serviceType << " in your city (" << customer->getCity() << ")...\n";

    cout << "\nAvailable Workers:\n";
    cout << UNDERLINE << left << setw(10) << "Worker ID" << setw(20) << "Name" << setw(15) << "City" << setw(20)
         << "Service Type" << setw(10) << "Fee" << endl;

    Node *current = workers.getHead();

    int workerCount = 0;

    while (current)
    {
        Worker *worker = static_cast<Worker *>(current->data);

        if (worker->getCity() == customer->getCity() && worker->getServiceType() == serviceType)
        {
            worker->display();
            cout << "\n";
            workerCount++;
        }

        current = current->next;
    }

    if (workerCount == 0)
    {
        cout << RED << "\nNo workers available for the selected service in your city.\n"
             << RESET;
        return;
    }

    int selectedWorkerID;

    cout << "Enter the Worker ID to assign the task: ";
    cin >> selectedWorkerID;

    current = workers.getHead();

    while (current)
    {
        Worker *worker = static_cast<Worker *>(current->data);

        if (worker->getId() == selectedWorkerID)
        {
            double offeredFee;

            cout << "Enter your offered fee for this task: ";
            cin >> offeredFee;

            Task *task = new Task(generateUniqueId(), worker->getId(), customer->getId(), description, offeredFee);

            tasks.add(task);

            saveTasksToFile();

            cout << "Task assigned to worker " << worker->getName() << " (ID: " << worker->getId() << ") with task ID " << task->getTaskId() << endl;

            return;
        }
        current = current->next;
    }

    cout << "Worker ID not found.\n";
}

void ServiceManagementSystem::viewTasksForWorker(int workerID)
{
    cout << "\nYour Assigned Tasks:\n";
    cout << left << setw(10) << "Task ID" << setw(10) << "Customer ID" << setw(10) << "Worker ID" << setw(25) << "Description" << setw(15) << "Status" << setw(10) << "Fee" << endl;

    Node *current = tasks.getHead();

    while (current)
    {
        Task *task = static_cast<Task *>(current->data);

        if (task->getWorkerId() == workerID)
        {
            task->display();
        }
        current = current->next;
    }
}

void ServiceManagementSystem::changeTaskStatus(int workerID, int taskID)
{
    Node *current = tasks.getHead();

    while (current)
    {
        Task *task = static_cast<Task *>(current->data);

        if (task->getWorkerId() == workerID && task->getTaskId() == taskID)
        {
            cout << "Enter new status (Pending/Denied/Completed): ";
            string newStatus;
            cin >> newStatus;

            task->setStatus(newStatus);

            saveTasksToFile();

            cout << "Task status updated successfully!\n";

            return;
        }
        current = current->next;
    }

    cout << "Task not found!\n";
}

void ServiceManagementSystem::workerLoginMenu(int workerID)
{
    char choice = ' ';
    do
    {
        cout << "1. View Assigned Tasks\n2. Edit Account\n3. Delete Account\n4. Change Task Status\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            viewTasksForWorker(workerID);
            break;

        case '2':
        {
            User *worker = static_cast<User *>(workers.find(workerID));
            editAccount(worker);
            break;
        }

        case '3':
        {
            deleteAccount(workerID);
            break;
        }

        case '4':
        {
            int taskID;
            cout << "Enter Task ID: ";
            cin >> taskID;
            changeTaskStatus(workerID, taskID);
            break;
        }

        case '5':
            break;

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != '5');
}

void ServiceManagementSystem::customerLoginMenu(int customerID)
{
    char choice = ' ';
    do
    {
        cout << BOLD << GREEN << "\n_________________________________________\n"
             << RESET;
        cout << ITALIC << UNDERLINE << GREEN << "|************COSTUMER LOGIN MENU**************|\n"
             << RESET;

        cout << BLUE << "1. Request Service\n2. View Task Status\n3. Edit Account\n4. Delete Account\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            requestService();
            break;

        case '2':
        {
            int taskID;
            cout << "Enter Task ID: ";
            cin >> taskID;

            Node *current = tasks.getHead();

            while (current)
            {
                Task *task = static_cast<Task *>(current->data);

                if (task->getTaskId() == taskID)
                {
                    cout << "\nTask Status:\n";
                    task->display();
                    break;
                }
                current = current->next;
            }
            break;
        }

        case '3':
        {
            User *customer = static_cast<User *>(customers.find(customerID));
            editAccount(customer);
            break;
        }

        case '4':
        {
            deleteAccount(customerID);
            break;
        }

        case '5':
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != '5');
}

int ServiceManagementSystem::generateUniqueId()
{
    return uniqueId++;
}

void ServiceManagementSystem::saveWorkersToFile()
{
    ofstream out("workers.txt");

    Node *current = workers.getHead();

    while (current)
    {
        Worker *worker = static_cast<Worker *>(current->data);
        out << left << setw(10) << worker->getId() << setw(20) << worker->getPassword() << setw(15) << worker->getCity() << setw(20) << worker->getServiceType() << setw(10) << worker->getFee() << endl;
        current = current->next;
    }
    out.close();
}

void ServiceManagementSystem::saveCustomersToFile()
{
    ofstream out("customers.txt");

    Node *current = customers.getHead();

    while (current)
    {
        Customer *customer = static_cast<Customer *>(current->data);
        out << left << setw(10) << customer->getId() << setw(20) << customer->getPassword() << setw(15) << customer->getCity() << endl;
        current = current->next;
    }
    out.close();
}

void ServiceManagementSystem::saveTasksToFile()
{
    ofstream out("tasks.txt");
    if (!out)
    {
        cout << "Error opening tasks file for writing!" << endl;
        return;
    }

    Node *current = tasks.getHead();
    while (current)
    {
        Task *task = static_cast<Task *>(current->data);
        out << left << setw(10) << task->getTaskId()
            << setw(10) << task->getWorkerId()
            << setw(10) << task->getCustomerId()
            << setw(25) << task->getDescription()
            << setw(15) << task->getStatus()
            << setw(10) << task->getFee() << endl;
        current = current->next;
    }
    out.close();
}

void ServiceManagementSystem::loadWorkersFromFile()
{
    ifstream in("workers.txt");

    while (!in.eof())
    {
        int id;
        double fee;
        string password, city, serviceType;

        in >> id >> password >> city >> serviceType >> fee;

        if (in && !in.eof())
        {
            Worker *worker = new Worker(id, "", password, city, serviceType);
            worker->setFee(fee);
            workers.add(worker);
        }
    }

    in.close();
}

void ServiceManagementSystem::loadCustomersFromFile()
{
    ifstream in("customers.txt");

    while (!in.eof())
    {
        int id;
        string password, city;

        in >> id >> password >> city;

        if (in && !in.eof())
        {
            Customer *customer = new Customer(id, "", password, city);
            customers.add(customer);
        }
    }

    in.close();
}

void ServiceManagementSystem::loadTasksFromFile()
{
    ifstream in("tasks.txt");

    while (true)
    {
        int taskId, workerId, customerId;
        string description, status;
        double fee;

        in >> taskId >> workerId >> customerId >> ws;
        getline(in, description);
        in >> status >> fee;

        if (in.fail())
            break;

        Task *task = new Task(taskId, workerId, customerId, description, fee);
        task->setStatus(status);
        tasks.add(task);
    }
    in.close();
}


void ServiceManagementSystem::mainMenu()
{
    loadWorkersFromFile();
    loadCustomersFromFile();
    loadTasksFromFile();

    char userRole = ' ';
    cout << YELLOW
         << "        __        __  _____   _        ____    ___    __  __   _____ \n"
            "        \\ \\      / / | ____| | |      / ___|  / _ \\  |  \\/  | | ____|\n"
            "         \\ \\ /\\ / /  |  _|   | |     | |     | | | | | |\\/| | |  _|  \n"
            "          \\ V  V /   | |___  | |___  | |___  | |_| | | |  | | | |___ \n"
            "           \\_/\\_/    |_____| |_____|  \\____|  \\___/  |_|  |_| |_____|\n"
         << RESET;
    cout << YELLOW << "\n\n=================================================================\n\n"
         << RESET;
    cout << CYAN << "\n\t*************SERVICES PROVIDER SYSTEM*************\n"
         << RESET;
    do
    {
        cout << GREEN << "\nAre you a Customer or Worker? Enter 'c' for Customer / 'w' for Worker / 'e' to Exit: ";
        cin >> userRole;

        switch (userRole)
        {
        case 'c':
        {
            char cChoice = ' ';
            do
            {
                cout << BOLD << GREEN << "\n______________________________________\n"
                     << RESET;
                cout << ITALIC << UNDERLINE << GREEN << "|************COSTUMER MENU**************|\n"
                     << RESET;
                cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
                cin >> cChoice;
                cout << RESET;
                switch (cChoice)
                {
                case '1':
                    registerCustomer();

                    break;

                case '2':
                {
                    int customerID;
                    string password;

                    cout << "\nEnter Customer ID: ";
                    cin >> customerID;

                    cout << "Enter Password: ";
                    cin >> password;

                    User *customer = static_cast<User *>(customers.find(customerID));

                    if (customer && customer->getPassword() == password)
                    {
                        customerLoginMenu(customerID);
                    }
                    else
                    {
                        cout << RED << "\nInvalid Customer ID or Password!\n"
                             << RESET;
                    }
                    break;
                }

                case '3':
                    break;

                default:
                    cout << RED << "\nInvalid choice!\n " << RESET;
                }
            } while (cChoice != '3');
            break;
        }

        case 'w':
        {
            char wChoice = ' ';
            do
            {
                cout << BOLD << GREEN << "\n______________________________________\n"
                     << RESET;
                cout << ITALIC << UNDERLINE << GREEN << "|************WORKER MENU**************|\n"
                     << RESET;
                cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
                cin >> wChoice;
                switch (wChoice)
                {
                case '1':
                {
                    printDoubleSeparator();
                    registerWorker();
                    break;
                }
                case '2':
                {
                    cout << BOLD << GREEN << "\n______________________________________\n"
                         << RESET;
                    cout << ITALIC << UNDERLINE << GREEN << "|************LOGIN MENU**************|\n"
                         << RESET;
                    int workerID;
                    string password;

                    cout << MAGENTA << "\nEnter Worker ID: ";
                    cin >> workerID;

                    cout << "Enter Password: ";
                    cin >> password;

                    User *worker = static_cast<User *>(workers.find(workerID));

                    if (worker && worker->getPassword() == password)
                    {
                        workerLoginMenu(workerID);
                    }
                    else
                    {
                        cout << RED << "\nInvalid Worker ID or Password!\n"
                             << RESET;
                    }
                    break;
                }

                case '3':
                    break;

                default:
                    cout << RED << " \nInvalid choice!\n " << RESET;
                }
            } while (wChoice != '3');
            break;
        }

        case 'e':
            break;

        default:
            cout << RED << "\nInvalid choice!\n"
                 << RESET;
        }
    }

    while (userRole != 'e');

    saveWorkersToFile();
    saveCustomersToFile();
    saveTasksToFile();
};

int main()
{
    ServiceManagementSystem system;
    system.mainMenu();
    return 0;
}
