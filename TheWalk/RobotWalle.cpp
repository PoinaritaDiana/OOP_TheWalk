#include "RobotWalle.h"
#include <vector>
#include <map>
#include <cmath>

pair<int, int> RobotWalle::chooseNewPosition(const Harta& h) const {
	pair <int, int> p = make_pair(-1, -1);
	pair <int, int> loc = h.getLocatie();
	double dmin, d;
	dmin = -1;

	int i = this->getPosition().first;
	int j = this->getPosition().second;
	for(int l=i-1; l<=i+1;l++)
		for (int c = j - 1; c <= j + 1; c++) {
			if (l >= 0 && l < h.getRows() && c >= 0 && c < h.getColumns()) {
				if ((l != i || c != j) && h.getMatrix(l, c) != 'X') {
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
}
