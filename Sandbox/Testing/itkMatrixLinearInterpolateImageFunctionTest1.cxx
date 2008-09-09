/*=========================================================================

  Program:   Lesion Sizing Toolkit
  Module:    itkMatrixLinearInterpolateImageFunctionTest1.cxx

  Copyright (c) Kitware Inc. 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "itkMatrixLinearInterpolateImageFunction.h"
#include "itkImage.h"
#include "itkMatrix.h"

int main( int argc, char * argv [] )
{

  const unsigned int Dimension = 2;
  const unsigned int NumberOfPhases = 2;

  typedef itk::Matrix< char,   NumberOfPhases, Dimension >   MatrixType1;
  typedef itk::Matrix< float,  NumberOfPhases, Dimension >   MatrixType2;
  typedef itk::Matrix< double, NumberOfPhases, Dimension >   MatrixType3;

  typedef itk::Image< MatrixType1, Dimension >   ImageType1;
  typedef itk::Image< MatrixType2, Dimension >   ImageType2;
  typedef itk::Image< MatrixType3, Dimension >   ImageType3;

  typedef itk::MatrixLinearInterpolateImageFunction< ImageType1 >  InterpolatorType1;
  typedef itk::MatrixLinearInterpolateImageFunction< ImageType2 >  InterpolatorType2;
  typedef itk::MatrixLinearInterpolateImageFunction< ImageType3 >  InterpolatorType3;

  InterpolatorType1::Pointer interpolator1 = InterpolatorType1::New();
  InterpolatorType2::Pointer interpolator2 = InterpolatorType2::New();
  InterpolatorType3::Pointer interpolator3 = InterpolatorType3::New();

  ImageType1::RegionType region;
  ImageType1::SizeType   size;
  ImageType1::IndexType  start;

  start.Fill( 0 );
  size.Fill( 10 );

  region.SetIndex( start );
  region.SetSize( size );

  ImageType1::Pointer image1 = ImageType1::New();
  image1->SetRegions( region );
  image1->Allocate();

  ImageType1::PixelType pixel1;

  pixel1(0,0) =  7;
  pixel1(0,1) =  9;
  pixel1(1,0) = 11;
  pixel1(1,1) = 13;

  image1->FillBuffer( pixel1 );

  interpolator1->SetInputImage( image1 );

  InterpolatorType1::ContinuousIndexType cindex;

  cindex[0] = 4.5;
  cindex[1] = 4.5;

  InterpolatorType1::OutputType value1 = interpolator1->EvaluateAtContinuousIndex( cindex );

  for( unsigned row=0; row < NumberOfPhases; row++ )
    {
    for( unsigned col=0; col < Dimension; col++ )
      {
      if( value1(row,col) != pixel1(row,col) )
        {
        std::cerr << "Error in EvaluateAtContinuousIndex()" << std::endl;
        return EXIT_FAILURE;
        }
      }
    } 

  InterpolatorType1::PointType point1;

  point1[0] = 4.5;
  point1[1] = 4.5;

  value1 = interpolator1->Evaluate( point1 );

  for( unsigned row=0; row < NumberOfPhases; row++ )
    {
    for( unsigned col=0; col < Dimension; col++ )
      {
      if( value1(row,col) != pixel1(row,col) )
        {
        std::cerr << "Error in EvaluateAtContinuousIndex()" << std::endl;
        return EXIT_FAILURE;
        }
      }
    } 

  InterpolatorType1::IndexType index;

  index[0] = 4;
  index[1] = 4;

  value1 = interpolator1->EvaluateAtIndex( index );

  for( unsigned row=0; row < NumberOfPhases; row++ )
    {
    for( unsigned col=0; col < Dimension; col++ )
      {
      if( value1(row,col) != pixel1(row,col) )
        {
        std::cerr << "Error in EvaluateAtContinuousIndex()" << std::endl;
        return EXIT_FAILURE;
        }
      }
    } 


  //
  // Test the code in a corner of the image
  //
  cindex[0] = -0.3;
  cindex[1] = -0.3;

  value1 = interpolator1->EvaluateAtContinuousIndex( cindex );

  interpolator1->Print( std::cout );

  std::cout << "Name of Class " << interpolator1->GetNameOfClass() << std::endl;
  std::cout << "Name of SuperClass " << interpolator1->Superclass::GetNameOfClass() << std::endl;


  return EXIT_SUCCESS;
}
