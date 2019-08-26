#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function prototypes
vector<vector<int>> parseInputData();
vector<int> parseSubVectors(vector<int>);
vector<int> getMobMeetingCoordinates(vector<int>);
int getTotalDistanceTravelled(vector<int>, vector<int>);
void outputAnswer(vector<int>);

int main() {
  vector<vector<int>> parsedInputData = parseInputData();

  for(int counter = 0; counter < parsedInputData.size(); counter++) {
    outputAnswer(parseSubVectors(parsedInputData[counter]));
  }

  return 0;
}
/*

  This function takes input from
  a text file and adds it to a
  vector of vector<int>'s and
  returns that value

*/
vector<vector<int>> parseInputData() {
  vector<vector<int>> inputDataFromFileParsed;

  ifstream dataFile;

  dataFile.open("data.txt");
  if(dataFile.is_open()) {
    string tempHolder;

    while(getline(dataFile, tempHolder)) {
      stringstream myStringStream(tempHolder);

      int singleNumber;

      vector<int> rawdata;

      while(myStringStream >> singleNumber) {
        rawdata.push_back(singleNumber);
      }
      inputDataFromFileParsed.push_back(rawdata);
    }
  }
  return inputDataFromFileParsed;
}

/*
  This function takes in a vector
  of mob member positions and then
  distills a solution (or indicates
  'no solution') and returns it
*/
vector<int> parseSubVectors(vector<int> parsedInputData) {
  vector<int> getAnswerVector;

  getAnswerVector = getMobMeetingCoordinates(parsedInputData);
  getAnswerVector.push_back(getTotalDistanceTravelled(parsedInputData, getAnswerVector));

  return getAnswerVector;
}

/*
  This function returns a vector that
  contains 2 values, an X and Y coordinate
  indicating the best location for mob
  members to congregate at. Works by sorting
  the raw input data of points into EW and NS
  vectors, then removing the first and last
  values until only 1 or 2 values remain.
  Contest specifications say to always use the
  smaller of the 2 values (or just the 1 value
  if that's the result!) so just grab vector[0]
  because they've been sorted in this function.
  Also return the distance all mob members
  must travel to reach this point.
*/
vector<int> getMobMeetingCoordinates(vector<int> singleSolutionData) {
  vector<int> eastWestData;
  vector<int> northSouthData;
  vector<int> answerVector;

  for(int i = 1; i < singleSolutionData.size(); i+=2) {
    eastWestData.push_back(singleSolutionData[i]);
  }
  for(int i = 2; i < singleSolutionData.size(); i+=2) {
    northSouthData.push_back(singleSolutionData[i]);
  }

  sort(eastWestData.begin(), eastWestData.end());
  sort(northSouthData.begin(), northSouthData.end());

  if(eastWestData.size() > 1) {
    do {
      eastWestData.erase(eastWestData.begin());
      eastWestData.pop_back();

      northSouthData.erase(northSouthData.begin());
      northSouthData.pop_back();
    } while(eastWestData.size() >= 2);
  }

  answerVector.push_back(eastWestData[0]);
  answerVector.push_back(northSouthData[0]);

  return answerVector;
}

/*
  This function takes in the coordinate where
  mob members should meet and the raw input data
  of all mob members and then calculate the
  distance all mob members must travel
  to get to the answer coordinate.
*/
int getTotalDistanceTravelled(vector<int> singleCoordinatesSet, vector<int> answerVector) {
  int tempDistaceCounter = 0;

  for(int i = 1; i < singleCoordinatesSet.size(); i=i+2) {
    if(singleCoordinatesSet[i] > answerVector[0]) {
      tempDistaceCounter += singleCoordinatesSet[i] - answerVector[0];
    } else {
      tempDistaceCounter += answerVector[0] - singleCoordinatesSet[i];
    }
  }

  for(int i = 2; i < singleCoordinatesSet.size(); i=i+2) {
    if(singleCoordinatesSet[i] > answerVector[1]) {
      tempDistaceCounter += singleCoordinatesSet[i] - answerVector[1];
    } else {
      tempDistaceCounter += answerVector[1] - singleCoordinatesSet[i];
    }
  }
  return tempDistaceCounter;
}

/*
  This function takes in a vector with solution
  data (point + distance travelled) and outputs it
  in the format the contest specifies.
*/
void outputAnswer(vector<int> answerVector) {
    cout << "Solution: (" << answerVector[0] << "," << answerVector[1] << ") " << answerVector[2] << endl;
}
