# include "Header.h"  
using namespace std;



int main()
{

	double  b;
	int dummy;
	bool Finished;
	bool FileError;
	
	Data data[1400][580];
	string  Initial ("detailedStat_N01G02_") ; 
	string Format (".txt"); 
	string Number;
	string FileName;
	int digits;
	
	int UnwrittenData; 
		UnwrittenData = 0; 
		double  polygonclassNumber[4];
		



   

	ifstream inputc2;
	ofstream polygonClass;

	polygonClass.open("polygonClass.txt");
	if (polygonClass.is_open())
	{
	//	cout << "Writing this to a file." << endl; ;

	}
	polygonClass << " 4orless,5sided,6sided,7sided,8ormore,Time" << endl; ;


	for (int Ti = 0;  Ti < 5743; Ti++)
	{
		Finished = false;


		


		digits = ceil(log10(Ti + 1)); 
		if (digits==1 || digits == 0) {
			Number = "0000" + std::to_string(Ti);	
		}
		else if (digits == 2) {
			Number = "000" + std::to_string(Ti);
		}
		else if (digits == 3) {
			Number = "00" + std::to_string(Ti);
		}
		else if (digits == 4) {
			Number = "0" + std::to_string(Ti);
		}



		FileName = Initial + Number + Format;
		//cout << Number;

		//inputc2.open("detailedStat_N03G00_02654.txt");
	//	inputc2.open("detailedStat_N01G02_05700.txt");
		inputc2.open(FileName.c_str());

		char letter;


		if (inputc2.is_open())
		{
			cout << FileName << endl; 
			cout << " File is open" << endl; 
			FileError = false ;
		}
		else
		{
			cout << FileName << endl; 
			cout << " File is not available" << endl; 
			Finished = true; 
			FileError = true;
			UnwrittenData = UnwrittenData + 1; 
		}
		

		

		//for (int kk = 0; kk < 206; kk++) {

		for (int iii = 0; iii < 5; iii++) {
			polygonclassNumber[iii] = 0;
		}
		int kk = 0;
		while (Finished == false)   // start reading one file
		{

			kk = kk + 1;
		//	cout << kk;


			for (int i = 1; i < 11; i++) { // strat reading one cell
				//inputc2 >> Ali; 
				letter = 'A';
				if (i == 7) {
					while (letter != '{') {
						inputc2.get(letter);
			//			cout << letter;
					}
				}
				else if (i == 10) {
					while (letter != '(') {
						inputc2.get(letter);
				//		cout << letter;
					}


				}
				else {

					int 	jj = 0;
					while (letter != ':' && Finished == false) {
						inputc2.get(letter);
		//				cout << letter;
						jj = jj + 1;
						if (jj > 200) {
							Finished = true;
							inputc2.close();
						}
					}

					if (Finished) {
						break;
					}
				}

				if (i == 1) {
			//		cout << "\n";
					inputc2 >> data[kk][Ti- UnwrittenData].CellRank;
				//	cout << data[kk][Ti- UnwrittenData].CellRank;
				}

				if (i == 2) {
			//		cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].GrowthProgress;
			//		cout << data[kk][Ti - UnwrittenData].GrowthProgress;
				}

				if (i == 3) {
				//	cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].MembrGrowthProgress;
					//cout << data[kk][Ti - UnwrittenData].MembrGrowthProgress;
				}

				if (i == 4) {
					//cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].IsBoundrayCell;
					//cout << data[kk][Ti - UnwrittenData].IsBoundrayCell;
				}
				if (i == 5) {
			//		cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].NumOfNeighbors;
					//cout << data[kk][Ti - UnwrittenData].NumOfNeighbors;
				}

				if (i == 6) {
					//cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].CellArea;
					//cout << data[kk][Ti - UnwrittenData].CellArea;
				}
				/*
							if (i == 7) {
								cout << "\n";
								inputc2 >> data[kk][Ti].CellPerim;
								cout << data[kk][Ti].CellPerim;
							}
							*/

				if (i == 7) {
					//cout << "\n";
					for (int k = 0; k < data[kk][Ti - UnwrittenData].NumOfNeighbors; k++) {
						int tmp;
						inputc2 >> tmp;
						data[kk][Ti- UnwrittenData].NeighborCells.push_back(tmp);
						//cout << data[kk][Ti - UnwrittenData].NeighborCells[k] << " ";
					}

				}

				if (i == 8) {
					//cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].CurrentActiveIntnlNode;
					//cout << data[kk][Ti - UnwrittenData].CurrentActiveIntnlNode;
				}
				if (i == 9) {
					//cout << "\n";
					inputc2 >> data[kk][Ti - UnwrittenData].CurrentActiveMembrNodes;
					//cout << data[kk][Ti - UnwrittenData].CurrentActiveMembrNodes;
				}
				if (i == 10) {
					//cout << "\n";
					for (int j = 0; j < 3; j++) {
						inputc2 >> data[kk][Ti - UnwrittenData].CellCenter[j];
						inputc2.get(letter);
						//cout << data[kk][Ti - UnwrittenData].CellCenter[j] << " ";
					}
					inputc2.get(letter);
				}



         
			} //finish reading on cell


			if (Finished == false) {
				if (data[kk][Ti - UnwrittenData].NumOfNeighbors < 5 && data[kk][Ti - UnwrittenData].IsBoundrayCell == 0)
				{
					polygonclassNumber[0] = polygonclassNumber[0] + 1;
					
				}
				else if (data[kk][Ti - UnwrittenData].NumOfNeighbors < 6 && data[kk][Ti - UnwrittenData].IsBoundrayCell == 0) {
					polygonclassNumber[1] = polygonclassNumber[1] + 1;
				}

				else if (data[kk][Ti - UnwrittenData].NumOfNeighbors < 7 && data[kk][Ti - UnwrittenData].IsBoundrayCell == 0) {
					polygonclassNumber[2] = polygonclassNumber[2] + 1;
					//cout << data[7][1].IsBoundrayCell << "is boundary cell" << endl;
				}
				else if (data[kk][Ti - UnwrittenData].NumOfNeighbors < 8 && data[kk][Ti - UnwrittenData].IsBoundrayCell == 0) {

					polygonclassNumber[3] = polygonclassNumber[3] + 1;
				}

				else if (data[kk][Ti - UnwrittenData].NumOfNeighbors >= 8 && data[kk][Ti - UnwrittenData].IsBoundrayCell == 0) {
					polygonclassNumber[4] = polygonclassNumber[4] + 1;
				}

			}


			

		} // finish reading on file


		//cout << "Finsihed reading one file" << endl;
		int sum; 
		if (FileError == false) {
			double Time = Ti * 36;
			    sum = 0;
				sum = polygonclassNumber[0] + polygonclassNumber[1] + polygonclassNumber[2] + polygonclassNumber[3] + polygonclassNumber[4]; 
			

			polygonClass << polygonclassNumber[0]/sum << "," << polygonclassNumber[1] / sum << "," << polygonclassNumber[2] / sum << "," << polygonclassNumber[3] / sum << "," << polygonclassNumber[4] / sum << "," << Time/3600 << endl;

			//cout << polygonclassNumber[0] << "," << polygonclassNumber[1] << "," << polygonclassNumber[2] << "," << polygonclassNumber[3] << "," << polygonclassNumber[4] << "," << Time/3600 << endl;
		}

	} //finish reading all files

	//cout << "number of unwritten data are" << UnwrittenData << endl;
	
	
	polygonClass.close();

	cin >> b;


	return 0;
}

