#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

void printDoctorShiftSlot(int doctor, int shift, int slot)
{
	cout << "Doctor: " << doctor+1<< " Shift: " << shift+1 << " Slot: " << slot+1 << endl;
}

void printShiftSlot(int shift, int slot)
{
	cout << "Shift: " << shift << " Slot: " << slot << endl;
}

void printSlotPrefs(vector<vector<unordered_set<int> > > &v)
{
	for(int i = 0; i < v.size(); i++) {
		cout << "Shift: " << i+1 << endl;
		for(int j = 0; j < v[i].size(); j++) {
			cout << " Slot: " << j+1 << " Doctors: " ;
			for(auto it = v[i][j].begin(); it!= v[i][j].end(); it++)
				cout << " " << *it+1;
			cout << endl;
		}
	}
}

void printDocPrefs(vector<vector<vector<int> > > &v)
{
	for(int i = 0; i < v.size(); i++) {
		for(int j = 0; j < v[i].size(); j++) {
			for(int k = 0; k < v[i][j].size(); k++)
				if(v[i][j][k])
					printDoctorShiftSlot(i, j, k);

		}
	}
}

void solveDoctorScheduling()
{
	int nDoctors, nSlots, nShifts;
	cin >> nDoctors >> nSlots >> nShifts;

	vector<int> doctorAvailSlots(nDoctors);
	for(int doctor = 0; doctor < nDoctors; ++doctor)
	{
		int slotAvailability;
		cin >> slotAvailability;
		doctorAvailSlots[doctor] = slotAvailability;
	}

	// initialize doctors prefs
	vector< vector< vector<int> > > doctorAvailPref(nDoctors, 
													vector<vector<int> >(
														nShifts,
														vector<int>(nSlots,0)));


	vector< vector< unordered_set<int> > > slotPreferences(nShifts,
														   vector<unordered_set<int> > (nSlots));
	bool slotNeedToBeAssigned = false;

	for(int doctor = 0; doctor < nDoctors; ++doctor)
	{
		for(int shift = 0; shift < nShifts; shift++)
		{
			int shiftPref;
			cin >> shiftPref;

			for(int slot = 0; slot < shiftPref; ++slot)
			{
				int slotPref;
				cin >> slotPref;

				doctorAvailPref[doctor][shift][slotPref-1] = 1;
				slotPreferences[shift][slotPref-1].insert(doctor);
				slotNeedToBeAssigned = true;

			}
		}
	}

//	printSlotPrefs(slotPreferences);
//	printDocPrefs(doctorAvailPref);
//	int temp;
//	cin >> temp;

	int nSlotAssigned = 0;
	vector<int> doctorRemoved(nDoctors, 0);
	while(slotNeedToBeAssigned)
	{

		bool removedNonConflicting = false;
		// remove all non conflicting 
		for(int shift = 0; shift < nShifts; shift++)
		{
			for(int slot = 0; slot < nSlots; slot++)
			{
				if(slotPreferences[shift][slot].size() == 1)
				{
					int doc = *slotPreferences[shift][slot].begin();
					if(doctorAvailSlots[doc] > 0 )
					{
						nSlotAssigned++;
						doctorAvailSlots[doc]--;
						slotPreferences[shift][slot].clear();
						removedNonConflicting = true;

//						printDoctorShiftSlot(doc, shift, slot);
						
						for(int doctor = 0; doctor < nDoctors; ++doctor)
							doctorAvailPref[doctor][shift][slot] = 0;
					}
				}
			}
		}

		// if there were no non conflicting, use up the doctors preferences
		if(!removedNonConflicting)
		{
			for(int doctor = 0; doctor < nDoctors; ++doctor)
			{
				if(doctorAvailSlots[doctor] > 0)
				{
					for(int shift = 0; shift < nShifts && doctorAvailSlots[doctor] > 0; shift++)
					{
						for(int slot = 0; slot < nSlots && doctorAvailSlots[doctor] > 0; slot++)
						{
							if(doctorAvailPref[doctor][shift][slot])
							{
								removedNonConflicting = true;
								nSlotAssigned++;
								slotPreferences[shift][slot].clear();
								doctorAvailSlots[doctor]--;
//								printDoctorShiftSlot(doctor, shift, slot);
								for(int doctor2 = 0; doctor2 < nDoctors; ++doctor2)
									doctorAvailPref[doctor2][shift][slot] = 0;
							}
						}
					}
					if(removedNonConflicting)
						break;
				}
			}
		}


		

		// remove doctors with no slots
		for(int doctor = 0; doctor < nDoctors; ++doctor)
		{
			if(doctorAvailSlots[doctor] == 0 && doctorRemoved[doctor] == 0)
			{
				for(int shift = 0; shift < nShifts; shift++)
				{
					for(int slot = 0; slot < nSlots; slot++)
					{
						slotPreferences[shift][slot].erase(doctor);
					}
				}
				doctorRemoved[doctor] = 1;
			}
		}
//	printSlotPrefs(slotPreferences);
//	printDocPrefs(doctorAvailPref);
		slotNeedToBeAssigned = false;		
		for(int shift = 0; shift < nShifts; shift++)
		{
			for(int slot = 0; slot < nSlots; slot++)
			{
				if(slotPreferences[shift][slot].size() > 0) {
					slotNeedToBeAssigned = true;

				}
			}
		}
//		int temp1;
//		cin >> temp1;
	}

	cout << nSlotAssigned << endl;
}

int main(int argc, char *argv[])
{
	solveDoctorScheduling();
	return 0;
}
