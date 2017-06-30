# include "Header.h"
  
using namespace std;

int main()
{

	double  b;
	int dummy;
    bool Finished;
	bool FileError;


	int num_files;
    cout << "Total num files to process: ";
    cin >> num_files;
	
	//Data data[1400][580];
    vector<vector<Data*>> data;
	string  Initial ("detailedStat_B_") ; 
	string Format (".txt"); 
	string Number;
	string FileName;
	int digits;
	
	int UnwrittenData = 0; 

   
	ifstream ifs;

	for (int Ti = 0;  Ti < num_files; Ti++)
	{
		Finished = false;
        
		digits = ceil(log10(Ti + 1)); 
		if (digits==1 || digits == 0) {
			Number = "0000" + to_string(Ti);	
		}
		else if (digits == 2) {
			Number = "000" + to_string(Ti);
		}
		else if (digits == 3) {
			Number = "00" + to_string(Ti);
		}
		else if (digits == 4) {
			Number = "0" + to_string(Ti);
		}



		FileName = Initial + Number + Format;

		ifs.open(FileName.c_str());

		if (ifs.is_open())
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
		

		string input_string = "";
        char* input_c_string;
        char key[] = ":";
        char* data_field;

        vector<Data*> cells;
        Data* cell;

        /**** ANDREW'S CODE ****/
        // while loop to parse one file
        while (!Finished) {
            getline(ifs, input_string);
            input_c_string = new char[input_string.size()];
            strcpy(input_c_string,input_string.c_str()); 
            data_field = strtok(input_c_string,":",&input_c_string);
            
            string temp(data_field);
            if(temp == "CellRank") {
                int rank = atoi(input_c_string);
                if (rank > 0) {
                    //first push_back old cell onto vector
                    cells.push_back(cell);
                }
                //creates new current cell to store information
                cell = new Data;
                cell->CellRank = rank;
            }
            else if (temp == "GrowthProgress") {
                double prog = strtod(input_c_string, NULL);
                cell->GrowthProgress = prog;
            }
            else if (temp == "MembrGrowthProgress") {
                double prog = strtod(input_c_string, NULL);
                cell->MembrGrowthProgress = prog;
            }
            else if (temp == "IsBoundaryCell") {
                int num = atoi(input_c_string);
                cell->IsBoundaryCell = num;
            }
            else if (temp == "NumOfNeighbors") {
                int num = atoi(input_c_string);
                cell->NumOfNeighbors = num;
            }
            else if (temp == "CellArea") {
                double area = strtod(input_c_string, NULL);
                cell->CellArea = area;
            }
            else if (temp == "CellPerim") {
                double perim = strtod(input_c_string, NULL);
                cell->CellPerim = perim;
            }
            else if (temp == "NeighborCellsOrdered") {
                vector<int> neigh;

            }
            else if (temp == "NumberOfPointsInContactOrdered") {

            }
            else if (temp == "CurrentActiveIntnlNodes") {
                int nodes = atoi(input_c_string);
                cell->CurrentActiveIntnlNodes = nodes;
            }
            else if (temp == "CurrentActiveMembrNodes") {
                int nodes = atoi(input_c_string);
                cell->CurrentActiveMembrNodes = nodes;
            }
            else if (temp == "CellCenter") {
                
            }
            else if (temp == "") {
                //for reaching the end of a file
            }
            else {
                //come across some other string
                //throw an error
            }



        } //finished reading one file

    } //finished reading all the files

        /**** END ANDREW CODE ****/

		int kk = 0;
		while (Finished == false)   // start reading one file
		{
        /**** ALI'S CODE ******/
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

