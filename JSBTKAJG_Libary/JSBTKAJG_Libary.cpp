
//Jovan Slijepcevic, Kathryn Austin, Brandon Turner, Jeff Gavin

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool checkInt(string num);

class Libary
{

private:

	string file = "BookList.txt";
	vector<string> books = {};
	fstream booklist;

	struct Client
	{

		string name;
		vector<string> borrowedBooks;

	};

	vector<Client> clients;

public:

	Libary()
	{

		booklist.open(file);

		if (booklist)
		{
			printf("Book List Opened!\n");

			string book;

			while (getline(booklist, book))
			{

				books.push_back(book);

			}

		}
		else
		{
			printf("Book list not found!\n");
		}

		booklist.close();
	}

	void addBook(string bookName)
	{

		books.push_back(bookName);
		printf("Book %s has been added!\n", bookName.c_str());

	}

	void removeBook(int bookNo)
	{

		printf("Removing %s!\n", books[bookNo - 1].c_str());
		books.erase(books.begin() + bookNo - 1);
		printf("Book successfully removed!\n");

	}

	void showBooks()
	{
		for (int i = 0; i < books.size(); i++)
		{

			printf("%d : %s\n", i + 1, books[i].c_str());

		}
	}


	void addClient(string name)
	{
		clients.push_back(Client());
		clients[clients.size() - 1].name = name;
	}

	void showAllClientsBooks()
	{

		if (clients.size() != 0)
		{
			printf("Clients : \n");
			for (int i = 0; i < clients.size(); i++)
			{
				printf("%s : \n ", clients[i].name.c_str());
				if (clients[i].borrowedBooks.size() != 0)
				{

					for (int j = 0; j < clients[i].borrowedBooks.size(); j++)
						if (j == clients[i].borrowedBooks.size() - 1)
							printf("%d : %s", j + 1, clients[i].borrowedBooks[j].c_str());
						else
							printf("%d : %s , ", j + 1, clients[i].borrowedBooks[j].c_str());
				}
				else
				{
					printf("Client has no books!");
				}

				printf("\n");
			}
		}
		else
			printf("There are no clients!\n");

	}

	void showClients()
	{
		if (clients.size() != 0)
		{
			printf("Clients : \n");
			for (int i = 0; i < clients.size(); i++)
			{
				printf("%d : %s \n", i + 1, clients[i].name.c_str());
			}
		}
		else
			printf("There are no clients!\n");
	}

	void showClientsBooks(int client)
	{
		printf("%s :\n ", clients[client - 1].name.c_str());
		if (clients[client - 1].borrowedBooks.size() != 0)
		{
			for (int i = 0; i < clients[client - 1].borrowedBooks.size(); i++)
				printf("%d : %s ", i + 1, clients[client - 1].borrowedBooks[i].c_str());
		}
		else
			printf("Client has no Books!");
		printf("\n");
	}

	void borrowBook(int bookNo, int client)
	{

		clients[client - 1].borrowedBooks.push_back(books[bookNo - 1]);
		books.erase(books.begin() + bookNo - 1);

	}

	void returnBook(int bookNo, int client)
	{

		books.push_back(clients[client - 1].borrowedBooks[bookNo - 1]);
		clients[client - 1].borrowedBooks.erase(clients[client - 1].borrowedBooks.begin() + bookNo - 1);

	}

	void saveBookList()
	{

		booklist.open(file, ios::out | ios::trunc);
		for (int i = 0; i < books.size(); i++)
		{

			booklist << books[i] << endl;

		}
		booklist.close();

	}

	void removeClient(int client)
	{

		clients.erase(clients.begin() + client - 1);

	}

	bool isClients()
	{
		if (clients.size() == 0)
			return false;
		else
			return true;

	}

};



int main()
{

	Libary libary;
	string Name;
	int book;
	int client;
	string selection;

	libary.showBooks();
	printf("\n\n\n");


	while (true) {

		while (true) {
			printf("What would you like to do : \n"
				"1 : Show Available Books\n"
				"2 : Show Clients\n"
				"3 : Add Book\n"
				"4 : Remove Book\n"
				"5 : Add Client\n"
				"6 : Remove Client\n"
				"7 : Borrow Book\n"
				"8 : Return Book\n"
				"9 : Exit\n"
				"Selection : ");

			cin >> selection;

			if (checkInt(selection))
				break;
			else
				printf("Please make valid selection!\n\n\n");

		}


		printf("\n");

		switch (stoi(selection))
		{
		case 1:

			libary.showBooks();
			printf("\n\n\n");
			break;

		case 2:

			if (libary.isClients())
			{
				libary.showAllClientsBooks();

			}
			else
			{
				printf("There are no clients!\n");
			}
			printf("\n\n\n");
			break;

		case 3:

			printf("Please input book name : ");
			cin.ignore();
			getline(cin, Name);
			printf("\n");
			libary.addBook(Name);
			printf("\n\n\n");
			break;

		case 4:

			libary.showBooks();
			printf("\nplease select book : ");
			cin >> book;
			libary.removeBook(book);
			printf("\n\n\n");
			break;

		case 5:

			printf("Please input name : ");
			cin.ignore();
			getline(cin, Name);
			printf("\n");
			libary.addClient(Name);
			libary.showClients();
			printf("\n\n\n");
			break;

		case 6:

			if (libary.isClients())
			{

				libary.showClients();
				printf("\n");
				printf("Please select client : ");
				cin >> client;
				libary.removeClient(client);
				printf("\n");
				libary.showClients();


			}
			else
			{

				printf("There are no clients!\n");

			}
			printf("\n\n\n");
			break;

		case 7:

			if (libary.isClients())
			{

				libary.showBooks();
				printf("\nPlease select book : ");
				cin >> book;
				printf("\n");
				libary.showClients();
				printf("\nPlease select client : ");
				cin >> client;
				printf("\n\n");
				libary.borrowBook(book, client);
				libary.showClientsBooks(client);

			}
			else
			{

				printf("There are no clients!\n");

			}
			printf("\n\n\n");
			break;

		case 8:

			if (libary.isClients())
			{

				libary.showClients();
				printf("Please select client : ");
				cin >> client;
				printf("\n");
				libary.showClientsBooks(client);
				printf("\nPlease select book : ");
				cin >> book;
				printf("\n");
				libary.returnBook(book, client);
				libary.showClientsBooks(client);

			}
			else
			{

				printf("There are no clients!\n");

			}
			printf("\n\n\n");
			break;

		case 9:

			libary.saveBookList();
			printf("Exiting \n");
			return 0;
			break;

		default:

			printf("Please make a valid selection!\n\n\n");
			break;
		}
	}


}

bool checkInt(string num)
{

	for (int i = 0; i < num.length(); i++)
	{

		if (isdigit(num[i]) == false)
		{

			printf("Please input a valid selection!\n\n");
			return false;

		}

	}

	return true;

}

