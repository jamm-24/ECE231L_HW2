#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Service {
	private:
		string problem_description;
		double cost;
	public:
		Service(string desc, double c) : problem_description(desc), cost(c) {}
		double getCost() const {
			return cost;
		}
		//overload the << operator
		friend ostream& operator<<(ostream& os, const Service& s){
			os << "Service: " << s.problem_description << " | Cost: $" << s.cost;
			return os;
		}
		//overload the + operator
		friend double operator+(const Service& s1, const Service& s2);
};
		double operator+(const Service& s1, const Service& s2){
			return s1.cost + s2.cost;
		}

class Vehicle {
	private:
		string make;
		string model;
		string color;
		int year;
	public:
		Vehicle(std::string ma, std::string mo, std::string co, int yr) : make(ma), model(mo), color(co), year(yr) {}

		//overload << operator
		friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};
		std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
			os << v.make << " " << v.model <<" " << v.color << " " << v.year;
			return os;
		}

class Customer_account {
	private:
		string customer_name;
		string customer_address;
		string customer_phoneNum;
		Vehicle customerVehicle;
		vector<Service> services;
		double totalAmount;
	public:
		Customer_account(const Vehicle& v, std::string name, std::string address, std::string phone) : customer_name(std::move(name)), customer_address(std::move(address)), customer_phoneNum(std::move(phone)), customerVehicle(v), totalAmount(0){}
		void addService(const Service& service){
			services.push_back(service);
			totalAmount += service.getCost();
		}
		Customer_account& operator+=(const Service& service){
			addService(service);
			return *this;
		}
		//overload the << operator
		friend ostream& operator<<(ostream& os, const Customer_account& accnt) {
			os << "==== Customer Account Information ====\n";
			os << "Customer Name: " << accnt.customer_name << "\n";
			os << "Customer Address: " << accnt.customer_address << "\n";
			os << "Customer Phone Number: " << accnt.customer_phoneNum << "\n";
			os << "Vehicle: " << accnt.customerVehicle << "\n";
			os << "Services:\n";
			for(const auto& service : accnt.services) {
				os << " - " << service << "\n";
			}
			os << "Total Amount: $" << accnt.totalAmount << "\n";
			os << "=======================================";
			return os;
		}
};
int main(){
	Vehicle myCar("Honda", "Pilot Black Edition", "Sonic Gray Pearl", 2025);
	Customer_account myAccount(myCar, "Jamm Lee", "123 Hollywood St., NM", "8321234567");

	Service windshieldWiperChange("Windshield wiper change:", 50.00);
	Service oilChange("Oil Change", 75.00);
	Service tireRotation("Tire Rotation", 60.00);

	myAccount.addService(windshieldWiperChange);
	myAccount.addService(oilChange);
	myAccount += tireRotation;

	cout << myAccount << endl;
	
	//report file
	ofstream reportFile("service_report.txt");
	if(reportFile.is_open()){
		reportFile << myAccount << "\n";
		reportFile.close();
		cout << "Service report completed to 'service_report.txt' file.\n";
	}
	return 0;
}




