/**
 * File: FSift128.cpp
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: functions for Surf64 descriptors
 * License: see the LICENSE.txt file
 *
 */
 
#include <vector>
#include <string>
#include <sstream>

#include "FClass.h"
#include "FSift128.h"

using namespace std;

namespace DBoW2 {

// --------------------------------------------------------------------------

void FSift128::meanValue(const std::vector<FSift128::pDescriptor> &descriptors,
  FSift128::TDescriptor &mean)
{
//  mean.resize(0);
//  mean.resize(FSift128::L, 0);

  vector<FSift128::pDescriptor>::const_iterator it;
  for (it = descriptors.begin(); it != descriptors.end(); ++it)
    mean += **it;
  mean /= descriptors.size();
}

// --------------------------------------------------------------------------
  
double FSift128::distance(const FSift128::TDescriptor &a, const FSift128::TDescriptor &b)
{
  double sqd = 0.;

  sqd = cv::norm(a, b, cv::NORM_L2);

  return sqd;
}

// --------------------------------------------------------------------------

std::string FSift128::toString(const FSift128::TDescriptor &a)
{
  stringstream ss;
  const float *p = a.ptr<float>();

  for(int i = 0; i < FSift128::L; ++i)
  {
    ss << (float)*p << " ";
  }
  return ss.str();
}

// --------------------------------------------------------------------------
  
void FSift128::fromString(FSift128::TDescriptor &a, const std::string &s)
{
  a.create(1, FSift128::L, CV_32F);
  float *p = a.ptr<float>();

  stringstream ss(s);
  for(int i = 0; i < FSift128::L; ++i, ++p)
  {
    float n;
    ss >> n;

    if(!ss.fail())
      *p = (float)n;
  }

}

// --------------------------------------------------------------------------

void FSift128::toMat32F(const std::vector<TDescriptor> &descriptors,
    cv::Mat &mat)
{
  if(descriptors.empty())
  {
    mat.release();
    return;
  }
  
  const int N = descriptors.size();
  const int L = FSift128::L;
  
  mat.create(N, L, CV_32F);
  
  for(int i = 0; i < N; ++i)
  {
    const TDescriptor& desc = descriptors[i];
    mat.push_back(desc);
  } 
}

// --------------------------------------------------------------------------

} // namespace DBoW2

