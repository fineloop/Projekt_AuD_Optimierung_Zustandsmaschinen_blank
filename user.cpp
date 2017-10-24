// User.cpp : header file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "user.h"
#include "graphics\graphicfunctions.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

/**************************************************
Struktur fuer eine Zeile der Schaltwerkstabelle
**************************************************/
struct tabrow {									//tablerow
	char					curs;				//current state
	vector<char>			statetrans;			//state transition - Uebergangszustaende
	vector<vector<bool>>	bitout;				//boolsche Bitausgaenge - Adressierung: bitout[Input][Nr. Ausgangsvariable]
};
/*************************************************/
/**************************************************
allgemeine Klasse fuer eine Zustandsmaschine
**************************************************/
class automat {
	int cinput;				//count of inputs
	int inputp;				//binaere Eingagnsmoeglichkeiten
	int coutput;			//count of outputs
	int cstates;			//count of states
	vector<tabrow> rowvec;	//row vector - Vektor aller Reihen einer Tabelle
public:
	automat() {								//Konstruktor fuer undefinierten Automaten
		cinput  = 0;
		inputp	= 0;
		coutput = 0;
		cstates = 0;
	}
	automat(int ci, int co, int cs) {		//Konstruktor fuer anlegen eines Automaten mit entsprechender Speicherallokierung fuer alle Werte der Schaltwerktabelle und Dummyzustaenden/-werten
		cinput = ci;
		inputp = pow(2, cinput);
		coutput = co;
		cstates = cs;
		rowvec.resize(cstates);
		for (int ii = 0; ii < rowvec.size(); ii++) {
			rowvec[ii].curs			= 65 + ii;		//Dummyzustaende anlegen, ASCII 65 = 'A'
			rowvec[ii].statetrans.resize(inputp);
			for (int jj = 0; jj < rowvec[ii].statetrans.size(); jj++)
				rowvec[ii].statetrans[jj] = 'X';    //Dummyuebergangszustand 'X'
			rowvec[ii].bitout.resize(inputp);
			for (int jj = 0; jj < rowvec[ii].bitout.size(); jj++) {
				rowvec[ii].bitout[jj].resize(coutput);
				for (int kk = 0; kk < rowvec[ii].bitout[jj].size(); kk++)
					rowvec[ii].bitout[jj][kk] = 0;
			}
		}
	}
	void consoleprinttable() {
		// Zeile 1
		cout << " |";
		for (int ii = 0; ii < inputp * 2; ii++) {
			if (ii == inputp)
				cout << " | "<< ii%inputp;
			else
				cout << " " << ii%inputp;
			if (ii >= inputp)
				for (int jj = 1; jj < coutput; jj++)
					cout << " ";
		}
		cout << endl;
		// Zeile 2
		int ss = 2 + inputp * 2 * 2 + inputp * (coutput - 1) + 2;
		for (int ii = 0; ii < ss; ii++) {
			if (ii == 1 || ii == 2 + 2 * inputp + 1) cout << "|";
			else cout << "-";
		}
		cout << endl;
		// Zustandzeilen
		for (int state = 0; state < cstates; state++) {
			cout << rowvec[state].curs << "|";
			for (int ii = 0; ii < inputp; ii++) {
				cout << " " << rowvec[state].statetrans[ii];
			}
			cout << " |";
			for (int ii = 0; ii < inputp; ii++) {
				cout << " ";
				for (int jj = 0; jj < coutput; jj++)
					cout << rowvec[state].bitout[ii][jj];
			}
			cout << endl;
		}
	}
};
/*************************************************/

#include "math.h"
void user_main()
{
	automat A(3, 4, 4);			// Dummyautomat anlegen mit 3 Eingaengen, 4 Ausgaengen und 4 moeglichen Zustaenden
	A.consoleprinttable();
	cout << endl << endl << endl;
	automat B(2, 2, 10);
	B.consoleprinttable();
}