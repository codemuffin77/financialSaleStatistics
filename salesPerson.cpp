//This program is to use 2D array for monthly financial sales' slip statistics.
//It will input [salesPersonID.txt] for getting the salesPerson ID.
//If you want to use it for more salesperson, please adjust [NumberOfSalesPerson] value
//and input sale data file [salesPersonData.txt].
//Finally, it will output file [monthlysale.txt] for results.
//includes test1 file: [salesPersonID1.txt],[salesPersonData1.txt], and [monthlysale1.txt]
//test2 file:[salesPersonID2.txt],[salesPersonData2.txt], and [monthlysale2.txt]
//This program is free to use, you can redistribute it
//and modify it under the software license.
//Program Author: Zhen Qian (Martin), Rutgers University
//Email:qianzhen77@hotmail.com, or zhen.qian@rutgers.edu.com
//This program is distributed in the hope that it will be useful,
//but without any warranty for a particular purpose.
//This program is passed by Code::Blocks.
// Copyright (c) Oct 2015

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//it assumes that input a file that only contains [4 salesperson ID]
//if want to add more salesperson, please change value of NumberOfSalesPerson
const int NumberOfSalesPerson=4;  //assume input file only contains 4 salesperson ID

//struct is a public class to group the salesperson information
//string ID mean you can input numbers, char, or combo.
//assume [5 products] for monthly sale statistics and calculate total monthly sale amount by person-totalSale
struct salesPersonRec{
    string ID;
    double saleByProduct[5];
    double totalSale;
};

//------------prototype of functions---------------------
//get the salesperson ID from salesPerson.txt and initialize 2D array, list[row].saleByProduct[product]
void initialize(ifstream& infile, salesPersonRec list[],int listSize);
//get the sales data from salesPersonData.txt
void getData(ifstream& infile, salesPersonRec list[], int listSize);
//get the total sale amount for every product
void saleByProduct(salesPersonRec list[], int listSize, double totalByProduct[]);
//get the total sale amount for every salesperson
void totalSaleByPerson(salesPersonRec list[], int listSize);
//output print the tabular form
void printReport(ofstream& outfile, salesPersonRec list[],int listSize, double saleByProduct[]);

int main(){
//use inputFile and outFile to deal with the file name
//use infile and outfile to handle the file contents of
    ifstream infile;
	ofstream outfile;

	string inputFile;
	string outputFile;

//define total sale amount of every product in additional 1D array
	double totalSaleByProduct[5];

//create a object of struct
	salesPersonRec salesPersonList[NumberOfSalesPerson];

//input salesperson ID information and deal with it
	cout<<"Please Enter the sales person ID file name: ";
	cin>>inputFile;
	infile.open(inputFile.c_str());
	if(!infile){
		cout<<"Cannot open the sale person ID file."<<endl;
		return 1;
	}

//initialization of 2D array, list[row].saleByProduct[product]
	initialize(infile, salesPersonList, NumberOfSalesPerson);
	infile.close();
	infile.clear();

//input sales data and deal with it
	cout<<"Enter the sales data file name: ";
	cin>>inputFile;
	infile.open(inputFile.c_str());
	if(!infile){
		cout<<"Cannot open the sales data file."<<endl;
		return 1;
	}

//input the output file name for the result.
	cout<<"Enter the output monthly sale report file name: ";
	cin>>outputFile;
	outfile.open(outputFile.c_str());
	outfile<<fixed<<showpoint<<setprecision(2);

//functions
	getData(infile, salesPersonList, NumberOfSalesPerson);
	saleByProduct(salesPersonList, NumberOfSalesPerson, totalSaleByProduct);
	totalSaleByPerson(salesPersonList,NumberOfSalesPerson);
	printReport(outfile, salesPersonList, NumberOfSalesPerson, totalSaleByProduct);

	infile.close();
	outfile.close();
	return 0;
}

//--------------------functions-----------------------------
//listSize is equal to NumberOfSalesPerson
//2D array list[row].saleByProduct[product] initialization
//every salesperson total amount list[row].totalSale=0
void initialize(ifstream& indata, salesPersonRec list[], int listSize){
	int row;
	int product;
	for (row=0;row<listSize;row++){
		indata>>list[row].ID;
		for(product=0;product<5;product++)
			list[row].saleByProduct[product]=0.0;
        list[row].totalSale=0.0;
	}
}

//input sale data, assume input file format: salesperson ID, product number, the total value of that product sold
void getData(ifstream& infile, salesPersonRec list[], int listSize){
	int row;
	int product;
	string sID;
	double amount;

//deal with salesperson ID
	infile>>sID;
	while(infile){

//deal with product number and the total value of that product sold
		infile>>product>>amount;
		for(row=0;row<listSize;row++)
//the input file get sID (salesperson ID) to match list[row] using the sequential search.
//list[row].saleByProduct[product-1] will store the slip sale amount and add up
//if salePerson ID is not existed, it will report an error.
			if(sID==list[row].ID)
                if(row<listSize)
                    list[row].saleByProduct[product-1]+=amount;
			else
				cout<<"Invalid sales person's ID: "<<sID<<endl;
			infile>>sID;
		}
}

//calculate the total amount of every product
void saleByProduct(salesPersonRec list[], int listSize, double totalByProduct[]){
	int row;
	int product;
	for(product=0;product<5;product++)
		totalByProduct[product]=0.0;
	for(product=0;product<5;product++)
		for(row=0;row<listSize;row++)
			totalByProduct[product]+=list[row].saleByProduct[product];
}

//calculate the total amount by person
void totalSaleByPerson(salesPersonRec list[], int listSize){
	int row;
	int product;
	for(row=0;row<listSize;row++)
		for(product=0;product<5;product++)
			list[row].totalSale+=list[row].saleByProduct[product];
}

//output the tabular form
//P1 is the product 1.
void printReport(ofstream& outfile, salesPersonRec list[],int listSize, double saleByProduct[]){
	int row;
	int product;
	outfile<<"-----------Last Month Sales Report---------------"<<endl;
	outfile<<"ID               P1          P2          P3          P4          P5        Total"<<endl;
	for(row=0;row<listSize;row++){
//list[row].ID is salesperson ID
		outfile<<list[row].ID<<"	";
		for(product=0;product<5;product++)
			outfile<<setw(12)<<list[row].saleByProduct[product];
        outfile<<setw(12)<<list[row].totalSale<<endl;
	}
//the last row is total amount of every product
	outfile<<"Total   ";
	for(product=0;product<5;product++)
        outfile<<setw(12)<<saleByProduct[product];
    outfile<<endl;
}
