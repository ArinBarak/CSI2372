// ------------------------------------------------------------------------------
// Assignment 1
// Written by: Arin Barak
// List the resources : cplusplus.com
// ----------------------------------------------------------------------------- 

#include <cstdio>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>

using namespace std;

//Question 1
int read_number(void)
{
	int n;
	printf("Enter a number : ");
	scanf_s("%d", &n);
	return n;
}

void enter_number(void) {
	int i, n;
	long total = 0;
	n = read_number();
	for (i = 1; i <= n; i++)
	{
		total += i;
		printf("i = %d, total = %ld \n", i, total);
	}
	printf("\n");
	printf("*** Final Total = %ld *** \n", total);
}

//Question 2
void q2_calculator() {
	int a, b;

	cout << "Please enter the first integer (a): ";
	cin >> a;
	cout << "Please enter the second integer (b); ";
	cin >> b;

	double u, v;
	u = pow((a + b), 2);
	v = pow((a - b), 2);

	cout << "The result for U is : " << u << "\nThe result for V is :" << v << endl;
}

//Question 3
void largest_in_sequence() {
	vector<int> seq;

	bool continue_seq = true;

	while (continue_seq) {
		int n;
		cout << "Enter an integer:";
		cin >> n;
		if (n < 0) {
			continue_seq = false;
			break;
		}

		seq.push_back(n);
	}

	int max = seq.front();
	for (vector<int>::iterator it = seq.begin(); it != seq.end(); ++it)
		if (max < *it) {
			max = *it;
		};

	cout << "The maximum number in this sequence is  " << max << endl;
}

//Question 4
void average_of_sequence() {
	vector<float> seq;

	bool continue_seq = true;

	while (continue_seq) {
		float n;
		cout << "Enter an integer:";
		cin >> n;
		if (n < 0) {
			continue_seq = false;
			break;
		}
		seq.push_back(n);
	}


	float total = 0;
	for (vector<float>::iterator it = seq.begin(); it != seq.end(); ++it)
		total += *it;

	cout << "The average is " << total / seq.size() << endl;
}

//Question 5
long converter(char* s) {
	long int res = 0;

	for (int i = 0; i < 80; ++i) {
		if (!isdigit(*(s + i))) {
			if (i != 0){
				break;
			}
		}
		else {
			res = res * 10 + (*(s + i) - '0');
		}
	}

	if (!isdigit(*s)) {
		res *= -1;
	}

	return res;
}

void converter_caller() {
	char str[80];

	cout << "Please enter a long number: ";
	cin >> str;

	char* r_str = str;
	long resu;
	resu = converter(r_str);

	cout << "The entire number is " << resu << endl;
}

int main()
{
	//Calling Question 1
	cout << "Question 1: " << endl;
	enter_number();

	//Calling Question 2
	cout << endl << "Question 2: " << endl;
	q2_calculator();

	//Calling Question 3
	cout << endl << "Question 3: " << endl;
	largest_in_sequence();

	//Calling Question 4
	cout << endl << "Question 4: " << endl;
	average_of_sequence();
	
	//Calling Question 5
	cout << endl << "Question 5: " << endl;
	converter_caller();

	return 0;
}
