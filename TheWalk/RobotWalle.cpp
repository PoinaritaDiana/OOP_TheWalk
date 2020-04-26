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