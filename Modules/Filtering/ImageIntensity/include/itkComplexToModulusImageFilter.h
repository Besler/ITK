/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkComplexToModulusImageFilter_h
#define itkComplexToModulusImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkMath.h"

namespace itk
{
/** \class ComplexToModulusImageFilter
 * \brief Computes pixel-wise the Modulus of a complex image.
 *
 * \ingroup IntensityImageFilters  MultiThreaded
 * \ingroup ITKImageIntensity
 */
namespace Functor
{
template< typename TInput, typename TOutput >
class ComplexToModulus
{
public:
  ComplexToModulus() {}
  ~ComplexToModulus() {}
  bool operator!=(const ComplexToModulus &) const
  {
    return false;
  }

  bool operator==(const ComplexToModulus & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput & A) const
  {
    return (TOutput)( std::sqrt( A.real() * A.real()
                                + A.imag() * A.imag() ) );
  }
};
}

template< typename TInputImage, typename TOutputImage >
class ComplexToModulusImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage, TOutputImage,
                           Functor::ComplexToModulus<
                             typename TInputImage::PixelType,
                             typename TOutputImage::PixelType >   >
{
public:
  /** Standard class type aliases. */
  using Self = ComplexToModulusImageFilter;
  using Superclass = UnaryFunctorImageFilter<
    TInputImage, TOutputImage,
    Functor::ComplexToModulus< typename TInputImage::PixelType,
                               typename TOutputImage::PixelType > >;

  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(ComplexToModulusImageFilter,
               UnaryFunctorImageFilter);

  using InputPixelType = typename TInputImage::PixelType;
  using OutputPixelType = typename TOutputImage::PixelType;
  using InputPixelValueType = typename NumericTraits< InputPixelType >::ValueType;

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( InputMultiplyOperatorCheck,
                   ( Concept::MultiplyOperator< InputPixelValueType > ) );
  // End concept checking
#endif

protected:
  ComplexToModulusImageFilter() {}
  ~ComplexToModulusImageFilter() override {}

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(ComplexToModulusImageFilter);
};
} // end namespace itk

#endif
