//============================================================================
// Name        : Bank_project.cpp
// Author      : A.Shawqy
// Version     :
// Copyright   : This File is Developed by: A.Shawqy in 2022
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>

using namespace std;

/* class to handle exceptions */
class InsufficientFunds{};

/* class to account */
class Account
{
private:
	long account_number;
	string first_name;
	string last_name;
	float balance;
	float minimum_amount_allowed; /* under this withdraw can't be done */
	static long next_account_number; /* to be incremented for the next account number */
public:

	/* Constructors */
	Account(){}
	Account(string firsr_name,string last_name,float balance,float minimum_amount_allowed);

	/* to get account number */
	long getAccNo(){return this->account_number;}

	/* to get first and last name */
	string getFirstName(){return this->first_name;}
	string getLastName(){return this->last_name;}

	/* to get the current balance */
	float getBalance(){return this->balance;}


	/* to get the minimum amount allowed balance */
	float getMinimunAllowedBalance(){return this->minimum_amount_allowed;}

	/* to get the minimum amount allowed balance */
	void setMinimunAllowedBalance(float amount){ this->minimum_amount_allowed = amount;  }

	/* to deposit money in current balance */
	void Deposit(float amount);

	/* to withdraw money from the current balance */
	void Withdraw(float amount);

	/* set and get for the account number for next user */
	static void setLastAccountNumber(long account_number) {next_account_number = account_number;}
	static long getLastAccountNumber() {return next_account_number;}

	/* to write all data of an account in a file for keeping data safe */
	friend ofstream & operator<<(ofstream &ofs,Account &acc);

	/* to read all data of an account from a file to work with */
	friend ifstream & operator>>(ifstream &ifs,Account &acc);

	/* to display the account details on the screen like cout function */
	friend ostream & operator<<(ostream &os,Account &acc);
};
long Account::next_account_number=0;

/* class to Bank */

class Bank
{
private:
	/* data structure to store all data of accounts */
	map<long,Account> accounts;

public:
	/* Constructor */
	Bank();

	/* to create a new account */
	Account OpenAccount(string firsr_name,string last_name,float balance);

	/* get all account info. */
	Account BalanceEnquiry(long accountNumber);

	/* deposit amount in an account */
	Account Deposit(long accountNumber,float amount);

	/* withdraw amount from an account */
	Account Withdraw(long accountNumber,float amount);

	/* close an account aka remove it */
	void CloseAccount(long accountNumber);

	/* display all account info. */
	void ShowAllAccounts();

	/* destractor */
	~Bank();

};


int main()
{
	Bank b;
	Account acc;

	/* to do some action */
	int choice;

	/* first and last name */
	string fname,lname;

	/* account number */
	long accountNumber;

	/* current balance */
	float balance;

	/* minimum amount */
	float minimun_amount;

	/* to deposit or withdraw */
	float amount;
	cout<<"***Welcome To Banking System***"<<endl;

	do
	{
		cout<<"\n\tSelect one option below ";
		cout<<"\n\t1 Open an Account";
		cout<<"\n\t2 Balance Enquiry";
		cout<<"\n\t3 Deposit";
		cout<<"\n\t4 Withdrawal";
		cout<<"\n\t5 Close an Account";
		cout<<"\n\t6 Show All Accounts";
		cout<<"\n\t7 Quit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
		/* Open an Account */
		case 1:
			cout<<"Enter First Name: ";
			cin>>fname;
			cout<<"Enter Last Name: ";
			cin>>lname;
			cout<<"Enter initial Balance: ";
			cin>>balance;
			acc=b.OpenAccount(fname,lname,balance);
			cout<<endl<<"Congratulations Your Account Has Been Created"<<endl;
			cout<<acc;
			break;

		/* Balance Enquiry */
		case 2:
			cout<<"Enter Account Number:";
			cin>>accountNumber;
			acc=b.BalanceEnquiry(accountNumber);
			cout<<endl<<"Your Account Details "<<endl;
			cout<<acc;
			break;

		/* Deposit */
		case 3:
			cout<<"Enter Account Number:";
			cin>>accountNumber;
			cout<<"Enter Balance:";
			cin>>amount;
			acc=b.Deposit(accountNumber, amount);
			cout<<endl<<"Amount Has Been Deposited"<<endl;
			cout<<acc;
			break;

		/*  Withdrawal */
		case 4:
			cout<<"Enter Account Number:";
			cin>>accountNumber;
			cout<<"Enter Balance:";
			cin>>amount;
			acc=b.Withdraw(accountNumber, amount);
			cout<<endl<<"Amount Withdrawn"<<endl;
			cout<<acc;
			break;

		/* Close an Account */
		case 5:
			cout<<"Enter Account Number:";
			cin>>accountNumber;
			b.CloseAccount(accountNumber);
			cout<<endl<<"Account Has Been Closed"<<endl;
			cout<<acc;
			break;

		/* Show All Accounts */
		case 6:
			b.ShowAllAccounts();
			break;

		/* Quit */
		case 7: break;

		default:
			cout<<"\nEnter Correct Choice";
			exit(0);
		}
	}while(choice!=7);


	return 0;
}

/*
 * Constructor for Account object
 * parameters: firsr_name
 * 			   last_name
 * 			   balance : initial balance for this account.
 * return:     None
 * */

Account::Account(string firsr_name,string last_name,float balance,float minimum_amount_allowed = 500)
{
	/* increment the static variable to get the account number */
	next_account_number++;

	/* assign the value to the account number data member */
	this->account_number = next_account_number;

	this->first_name = firsr_name;
	this->last_name = last_name;
	this->balance = balance;
	this->minimum_amount_allowed = minimum_amount_allowed;
}


/*
 * Deposit some money in an account
 * parameters: amount : to be deposited in an account.
 * return:     None
 * */

void Account:: Deposit(float amount)
{
	this->balance += amount;
}

/*
 * Withdraw some money from an account
 * parameters: amount : to be Withdrawed from an account.
 * return:     None
 * */

void Account:: Withdraw(float amount)
{
	if(this->balance < this->minimum_amount_allowed)
		throw InsufficientFunds();
	else
		this->balance -= amount;
}


/*
 * save data of an account into a file
 * parameters: ofs: reference to output stream.
 *			   acc: reference to the account we want to save.
 * return:     output stream ofs.
 * */

ofstream & operator<<(ofstream &ofs,Account &acc)
{
	/* writing data onto a file */
	ofs << acc.account_number << endl;
	ofs << acc.first_name << endl;
	ofs << acc.last_name << endl;
	ofs << acc.balance << endl;
	ofs << acc.minimum_amount_allowed << endl;

	/* return output file stream */
	return ofs;
}

/*
 * read data of an account from a file
 * parameters: ifs: reference to input stream.
 *			   acc: reference to the account we want to save.
 * return:     input file stream ifs.
 * */

ifstream & operator>>(ifstream &ifs,Account &acc)
{
	/* read data from a file */
	ifs >> acc.account_number ;
	ifs >> acc.first_name ;
	ifs >> acc.last_name ;
	ifs >> acc.balance ;
	ifs >> acc.minimum_amount_allowed;

	/* return input file stream */
	return ifs;
}


ostream & operator<<(ostream &os,Account &acc)
{

	/* display data */
	os << "Account Number is: " << acc.getAccNo() << endl;
	os << "First Name is: " << acc.getFirstName() << endl;
	os << "Last Name is: " << acc.getLastName() << endl;
	os << "Your Current Balance is: " << acc.getBalance() << endl;
	os << "Your Minimum allowed Amount is: " << acc.getMinimunAllowedBalance() << endl;

	/* return output stream */
	return os;
}




/*
 * Constructor for Bank object
 * parameters: None
 * return:     None
 * */

Bank::Bank()
{

	Account account;
	ifstream infile;

	/* open the file to read accounts data */
	infile.open("Bank.data");

	if(!infile)
	{
		//cout<<"Error in Opening! File Not Found!!"<<endl;
		return;
	}

	/* read data accounts */
	while(!infile.eof())
	{
		infile>>account;
		accounts.insert(pair<long,Account>(account.getAccNo(),account));
	}

	/* for next account */
	Account::setLastAccountNumber(account.getAccNo());

	/* close the file connection */
	infile.close();

}


/*
 * destructor for Bank object
 * parameters: None
 * return:     None
 * */

Bank::~Bank()
{
	ofstream outfile;

	/* open the file to write accounts data */
	outfile.open("Bank.data", ios::trunc);

	/* iterator */
	map<long,Account>::iterator itr;

	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		/* write the account object onto a file.
		 * second here refer to account object.
		 * as map element is a pair its first is id 'here account number'
		 * its second is the actual account object.
		 * */
		outfile << itr->second;
	}

	/* close the file connection */
	outfile.close();
}


/*
 * OpenAccount for new user
 * parameters: firsr_name
 * 			   last_name
 * 			   balance : initial balance for this account.
 * return:     account
 * */

Account Bank::OpenAccount(string firsr_name,string last_name,float balance)
{
	ofstream outfile;
	/* create account object */
	Account account(firsr_name,last_name,balance);

	/* add the new account to Bank data */
	accounts.insert(pair<long,Account>(account.getAccNo(),account));

	/* save the Bank data after adding the new account */
	outfile.open("Bank.data", ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		/* write the account object onto a file.
		 * second here refer to account object.
		 * as map element is a pair its first is id 'here account number'
		 * its second is the actual account object.
		 * */
		outfile<<itr->second;
	}

	/* close the file connection */
	outfile.close();

	/* return the new account */
	return account;
}

/*
 * CloseAccount for a user
 * parameters: accountNumber
 * return:     None
 * */

void Bank::CloseAccount(long accountNumber)
{
	/* find the account using its number */
	map<long,Account>::iterator itr=accounts.find(accountNumber);

	/* info of closed account */
	cout<<"Account Deleted "<<itr->second;

	/* deleting the account */
	accounts.erase(accountNumber);
}

/*
 * BalanceEnquiry for a user
 * parameters: accountNumber
 * return:     account
 * */

Account Bank::BalanceEnquiry(long accountNumber)
{
	/* find the account using its number */
	map<long,Account>::iterator itr=accounts.find(accountNumber);

	/*
	 * second here refer to account object.
	 * as map element is a pair its first is id 'here account number'
	 * its second is the actual account object.
	 * */
	return itr->second;
}


/*
 * Deposit for a user
 * parameters: accountNumber
 * 			   amount
 * return:     account
 * */

Account Bank::Deposit(long accountNumber,float amount)
{
	/* find the account using its number */
	map<long,Account>::iterator itr=accounts.find(accountNumber);

	/* apply the deposit */
	itr->second.Deposit(amount);

	/* return the account after deposit is done */
	return itr->second;
}


/*
 * Withdraw for a user
 * parameters: accountNumber
 * 			   amount
 * return:     account
 * */

Account Bank::Withdraw(long accountNumber,float amount)
{
	/* find the account using its number */
	map<long,Account>::iterator itr=accounts.find(accountNumber);

	/* apply the Withdraw */
	itr->second.Withdraw(amount);

	/* return the account after deposit is done */
	return itr->second;
}


/*
 * ShowAllAccounts
 * parameters: None
 * return:     None
 * */
void Bank::ShowAllAccounts()
{
	/* iterator to loop on accounts */
	map<long,Account>::iterator itr;

	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		/*
		 * second here refer to account object.
		 * as map element is a pair its first is id 'here account number'
		 * its second is the actual account object.
		 * */
		cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
	}
}
