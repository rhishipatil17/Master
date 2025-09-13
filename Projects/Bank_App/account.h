#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef unsigned int AccNo;
typedef char Name;
typedef char AccType;
typedef double Balance;
typedef double Amount;

class Account
{
	public:
		void createAccount();
		void showAccount() const;
		void modify();
		void deposit(const Amount &amount);
		void withdraw(const Amount &amount);
		void report() const;
		AccNo getAccountNunber() const;
		Balance getBalance() const;
		AccType getType() const;

	private:
		AccNo AccountNumber;
		Name name[30];
		AccType type;
		Balance balance;
};

#endif