SERVICES PROVIDER APP:
Overview
This program is a Service Management System written in C++ that connects customers and workers. Customers can request services like plumbing or electrician work, and workers can manage the tasks assigned to them. The system uses object-oriented programming and file handling to store data like user details and tasks.
________________________________________
Main Features
1.	Classes for Users and Tasks
o	User (Base Class): Represents a general user with details like ID, name, password, and city.
	Worker: Extends User to include serviceType (e.g., Plumber) and fee.
	Customer: A simpler user class for customers.
o	Task: Represents tasks assigned to workers, including details like task description, status (Pending, Completed), and fee.
________________________________________
2.	Class for  ServiceManagementSystem
The ServiceManagementSystem class is the main controller of the program. It brings together workers, customers, and tasks and provides the necessary functionality to manage them. Below is a breakdown of its features:

Attributes
1.	workers (LinkedList): A linked list to store worker objects.
2.	customers (LinkedList): A linked list to store customer objects.
3.	tasks (LinkedList): A linked list to store task objects.
4.	uniqueId (int): A unique identifier for new users or tasks.

Functions
Account Management
1.	registerWorker(): Allows workers to sign up by providing details like name, city, service type, and fee.
2.	registerCustomer(): Allows customers to sign up with their name, password, and city.
3.	editAccount(User* user): Lets workers or customers update their password or city.
4.	deleteAccount(int userID): Deletes a user (worker or customer) from the system based on their ID.

Service and Task Management
1.	requestService():
o	Lets customers request a service.
o	Displays available workers in the customer’s city who offer the requested service.
o	Assigns tasks to selected workers and stores task details.
2.	viewTasksForWorker(int workerID):
o	Displays tasks assigned to a specific worker.
3.	changeTaskStatus(int workerID, int taskID):
o	Lets a worker update the status of a task (e.g., Pending, Completed).

File Operations
1.	saveWorkersToFile(): Saves worker details to workers.txt.
2.	saveCustomersToFile(): Saves customer details to customers.txt.
3.	saveTasksToFile(): Saves task details to tasks.txt.
4.	loadWorkersFromFile(): Loads worker details from the file into the program.
5.	loadCustomersFromFile(): Loads customer details from the file into the program.
6.	loadTasksFromFile(): Loads task details from the file into the program.

Menu Functions
1.	mainMenu(): Displays the main menu for users to choose between customer or worker roles and proceed to their respective options.
2.	customerLoginMenu(int customerID): Provides options for customers, such as requesting services and viewing tasks.
3.	workerLoginMenu(int workerID): Provides options for workers, such as viewing assigned tasks and updating task status.
________________________________________
3.	Dynamic Linked List
o	A custom-built linked list is used to manage workers, customers, and tasks. It allows adding, finding, and removing data dynamically.
4.	File Storage
o	Data (workers, customers, tasks) is saved in files to keep records even after the program is closed. The files are:
	workers.txt
	customers.txt
	tasks.txt
5.	Menu System
o	Interactive menus let users (customers or workers) log in, register, and perform actions like assigning or viewing tasks.
________________________________________
What Customers Can Do
•	Register: Create a new account by providing name, password, and city.
•	Login: Log in using their ID and password.
•	Request Services:
o	Choose a service like "Plumber" or "Electrician."
o	See available workers in their city and assign a task to a chosen worker.
•	Edit or Delete Account.
________________________________________
What Workers Can Do
•	Register: Sign up with details like name, password, city, service type, and fee.
•	Login: Log in using their ID and password.
•	Manage Tasks:
o	View tasks assigned to them.
o	Update task status (e.g., Completed or Denied).
o	Edit or delete their account.
________________________________________
How Data is Handled
•	Unique IDs: Each user and task gets a unique ID generated randomly and checked to avoid duplicates.
•	File Saving and Loading: Data is read from files when the program starts and saved back when it ends.
•	User-Friendly Display: Menus and information are displayed with colors and clear formatting for better readability.
________________________________________
Summary
The program creates a simple system for connecting customers and workers. Customers can assign tasks to workers, and workers can manage their assigned tasks. It works well but could improve by handling errors better, speeding up data searches, and securing user data.
