//============================================================================
// Name        : byteswap4b.cpp
// Author      : Makoto Sadahiro
// Version     :
// Copyright   : Texas Advanced Computing Center
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<cstdio>
#include<cstdlib>
#include<sys/types.h>
#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

void display_usage(){
	cout << "usage::endian_exchange rawfile_in rawfile_out " << "data_count"
	    << endl;
}

int main(int argc, char* argv[]){

	//standard procedure of taking CLI arguments
	if(argc < 4){
		display_usage();
		cout << "usage not correct- bailing out...." << endl;
		exit(1);
	}//incorrect usage of CLI

	FILE *file_in;
	if((file_in = fopen(argv[1], "r")) == NULL){
		cout << "sourceput file -" << argv[1] << "- does not exist" << endl
		    << "Bailing out...." << endl;
		exit(1);
	}//file opening assuarance

	FILE *file_out;
	if((file_out = fopen(argv[2], "w")) == NULL){
		cout << "destination file -" << argv[2] << "- error on opening" << endl
		    << "Bailing out...." << endl;
		exit(1);
	}//file opening assuarance

	int num_read, num_wrote;
	int data_count = atoi(argv[3]);
	int a_stripe_size = 2;
	short a_stripe[a_stripe_size];
	short temp_cell;

	for(int curr_loop = 0; curr_loop < data_count; curr_loop++){
		//read 2 bytes twice and swap, store
		num_read = fread(a_stripe, 2, 2, file_in);
		temp_cell = a_stripe[0];
		a_stripe[0] = a_stripe[1];
		a_stripe[1] = temp_cell;
		num_wrote = fwrite(a_stripe, 2, 2, file_out);
	}

	//closing up input file
	int file_in_close_result;
	file_in_close_result = fclose(file_in);
	if(file_in_close_result == -1){
		cout << "input file closing failed" << endl << "Bailing out...." << endl;
	}

	//closing up output file
	int file_out_close_result;
	file_out_close_result = fclose(file_out);
	if(file_out_close_result == -1){
		cout << "output file closing failed" << endl << "Bailing out...." << endl;
	}

	// this section is for testing result

	FILE *file_rin;
	if((file_rin = fopen(argv[2], "r")) == NULL){
		cout << "reopening output file -" << argv[1] << "- failed" << endl
		    << "Bailing out...." << endl;
		exit(1);
	}//file opening assuarance

	float a_cell[1];
	for(int curr_loop = 0; curr_loop < 100; curr_loop++){
		num_read = fread(a_cell, sizeof(float), 1, file_in);
		cout << "count: " << curr_loop << "   " << a_cell << endl;
	}

	//closing up rinput file
	int file_rin_close_result;
	file_rin_close_result = fclose(file_rin);
	if(file_rin_close_result == -1){
		cout << "reopened file closing failed" << endl << "Bailing out...." << endl;
	}

	// end of section for testing result

	cout << "done" << endl;
	return 0;
}
