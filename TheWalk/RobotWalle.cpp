#include "RobotWalle.h"
#include <vector>
#include <map>
#include <cmath>

pair<int, int> RobotWalle::chooseNewPosition(const Harta& h) const {
	/* 
		Robotul Wall-E nu poate vedea decat o pozitie in jurul sau (are vizibilitate 1)
		El incearca pe cat posibil sa evite capcanele, alegand mereu pozitia disponibila de pe harta care este cat mai aproape de destinatie
		Daca nu are de ales si este inconjurat de capcane, ori va arunca un bloc gigantic de deseuri pentru a distruge capcana (daca a adunat
		suficient gunoi), ori isi va sacrifica una din vieti pentru a ajunge la destinatie.
	*/
/*
	pair <int, int> p = make_pair(-1, -1);
	pair <int, int> loc = h.getLocatie();
	double dmin, d;
	dmin = -1;

	int i = this->getPosition().first;
	int j = this->getPosition().second;
	for(int l=i-1; l<=i+1;l++)
		for (int c = j - 1; c <= j + 1; c++) {
			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns()) {
				if ((l != i || c != j) && h.getMatrix(l, c) != 'X' && h.getMatrix(l, c) != '/') {
					d = sqrt((loc.first - l) * (loc.first - l) + (loc.second - c) * (loc.second - c));
					if (dmin == -1) {
						dmin = d;
						p = { l,c };
					}
					else
						if (d < dmin) {
							dmin = d;
							p = { l,c };
						}
				}
			}
		}
	return p;
	*/
}


void RobotWalle::itemEffect(char i) {
	if (i == 'T') {
		cout << "\nAi gasit un item pentru Terminator";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otheItems++;
	}
	if (i == 'Q') {
		cout << "\nAi gasit un item pentru Qrio";
		cout << "\nWall-E a transformat acest item intr-un cub.";
		this->otheItems++;
	}
	if (i == 'W') {
		cout << "\nYou're lucky! Ai gasit un item pentru Wall-E!";
		this->throwaAndDestroy++;
		if (this->throwaAndDestroy == 1)
			cout << "\nWall-E a primit primul sau bloc gigantic cu care poate distruge capcane!";
		else
			cout << "\nWall-E are acum " << this->throwaAndDestroy << "blocuri gigantice.";
	}
	//Daca a adunat suficiente cuburi(adica 3), le poate transforma intr-un bloc gigantic
	if (this->otheItems == 3){
		this->throwaAndDestroy++;
		this->otheItems = 0;
		cout << "\nUhuuu! Wall-E a strans 3 cuburi si a reusit sa le transforme intr-un bloc gigantic!";
		cout << "\nWall-E are acum " << this->throwaAndDestroy << "blocuri gigantice.";
	}
}