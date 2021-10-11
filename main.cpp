#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Point
{
  int label;
  int distance;
};

const auto compare = [](const Point &lhs, const Point &rhs) {
  return lhs.distance < rhs.distance;
};

vector<vector<int>> trainingData;
vector<vector<int>> testData;

typedef unordered_multimap<int, vector<int>> umm;
umm separatedData;
vector<vector<int>> prototypes;

vector<vector<int>> read(const string &file)
{
  ifstream input(file);
  string line;
  vector<vector<int>> data;

  while (getline(input, line))
  {
    istringstream iss(line);
    string token;
    vector<int> arr;

    while (getline(iss, token, ','))
    {
      arr.push_back(stoi(token));
    }

    data.push_back(arr);
  }

  input.close();
  return data;
}

int euclideanDistance(const vector<int> &p, const vector<int> &q)
{
  int distance = 0;

  for (int i = 0; i < 64; ++i)
  {
    distance += (p[i] - q[i]) * (p[i] - q[i]);
  }

  return distance;
}

int knn(const vector<int> &unknownData, const int &k = 1)
{
  vector<Point> points;

  for (const auto &arr : trainingData)
  {
    points.push_back({arr[64], euclideanDistance(unknownData, arr)});
  }

  sort(points.begin(), points.end(), compare);

  int freq[10] = {0};
  for (int i = 0; i < k; ++i)
  {
    ++freq[points[i].label];
  }

  int max = 0;
  for (int i = 1; i < 10; ++i)
  {
    if (freq[i] > freq[max])
    {
      max = i;
    }
  }

  return max;
}

void testKNN()
{
  {
    int possibleOutcomes = 0;
    int favorableOutcomes = 0;
    for (const auto &arr : testData)
    {
      if (arr[64] == knn(arr, 5))
      {
        ++favorableOutcomes;
      }

      ++possibleOutcomes;
    }

    double probability =
        (static_cast<double>(favorableOutcomes) / possibleOutcomes) * 100;

    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << probability;

    cout << "Accuracy on the testing set with k-nn: " << oss.str() << endl;
  }
  {
    int possibleOutcomes = 0;
    int favorableOutcomes = 0;
    for (const auto &arr : trainingData)
    {
      if (arr[64] == knn(arr, 5))
      {
        ++favorableOutcomes;
      }

      ++possibleOutcomes;
    }

    double probability =
        (static_cast<double>(favorableOutcomes) / possibleOutcomes) * 100;

    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << probability;

    cout << "Accuracy on the training set with k-nn: " << oss.str() << endl;
  }
}

void separateData()
{
  for (const auto &arr : trainingData)
  {
    int label = arr[64];
    separatedData.insert(umm::value_type(label, arr));
  }
}

void constructPrototypes()
{
  for (int label = 0; label < 10; ++label)
  {
    //cout << "label : " << label << endl;
    auto its = separatedData.equal_range(label);
    vector<int> prototype(65, 0);
    prototype[64] = label;
    int counter = 0;

    for (auto it = its.first; it != its.second; ++it, ++counter)
    {
      for (int i = 0; i < 64; ++i)
      {
        prototype[i] += (it->second)[i];
      }
    }


    //cout << "counter : " <<counter << endl;

    for (int i = 0; i < 64; ++i)
    {
      prototype[i] /= counter;
    }

    prototypes.push_back(prototype);
  }

}

int centroid(const vector<int> &unknownData)
{
  vector<Point> points;
  for (const auto &arr : prototypes)
  {
    points.push_back({arr[64], euclideanDistance(unknownData, arr)});
  }

  sort(points.begin(), points.end(), compare);

  return points.front().label;
}

void testCentroid()
{
  {
    int possibleOutcomes = 0;
    int favorableOutcomes = 0;
    for (const auto &arr : testData)
    {
      if (arr[64] == centroid(arr))
      {
        ++favorableOutcomes;
      }

      ++possibleOutcomes;
    }

    double probability =
        (static_cast<double>(favorableOutcomes) / possibleOutcomes) * 100;

    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << probability;

    cout << "Accuracy on the testing set with centroid: " << oss.str() << endl;
  }
  {
    int possibleOutcomes = 0;
    int favorableOutcomes = 0;
    for (const auto &arr : trainingData)
    {
      if (arr[64] == centroid(arr))
      {
        ++favorableOutcomes;
      }

      ++possibleOutcomes;
    }

    double probability =
        (static_cast<double>(favorableOutcomes) / possibleOutcomes) * 100;

    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << probability;

    cout << "Accuracy on the training set with centroid: " << oss.str() << endl;
  }
}

int main(int argc, char const *argv[])
{
  trainingData = read("optdigits.tra");
  testData = read("optdigits.tes");

  separateData();
  constructPrototypes();

  //cout << prototypes.size() << endl;
  //out << prototypes[0].size() << endl;

  // for(int j = 0; j <= 9; j++){
  //   cout << "j = " << j << endl;
  //   for (int i = 0; i < prototypes[0].size(); ++i)
  //   {
  //     cout << prototypes[j][i] << " ";
  //   }
  //   cout << endl << endl;
  // }
  // cout << endl;

  // knn
  testKNN();

  // centroid
  //testCentroid();

  return 0;
}
