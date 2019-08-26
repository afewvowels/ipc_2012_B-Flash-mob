#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> parseInputData();
void parseSubVectors(vector<vector<int>>);
vector<int> getMobMeetingCoordinates(vector<int>);
int getTotalDistanceTravelled(vector<int>, vector<int>);
void outputAnswer(vector<int>);

int main() {
  vector<vector<int>> parsedInputData = parseInputData();

  parseSubVectors(parsedInputData);

  return 0;
}

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

void parseSubVectors(vector<vector<int>> parsedInputData) {
  vector<int> getAnswerVector;

  for(int counter = 0; counter < parsedInputData.size(); counter++) {
    getAnswerVector = getMobMeetingCoordinates(parsedInputData[counter]);
    getAnswerVector.push_back(getTotalDistanceTravelled(parsedInputData[counter], getAnswerVector));
    outputAnswer(getAnswerVector);
    }
}

vector<int> getMobMeetingCoordinates(vector<int> singleSolutionData) {
  vector<int> eastWestData;
  vector<int> northSouthData;
  vector<int> answerVector;

  int tempDistaceCounter = 0;

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

void outputAnswer(vector<int> answerVector) {
    cout << "Solution: (" << answerVector[0] << "," << answerVector[1] << ") " << answerVector[2] << endl;
}
