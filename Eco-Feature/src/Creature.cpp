/******************************************************************************
 * Filename      : Creature.cpp
 * Header File(s): Creature.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Creature.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Creature::Creature ( void ) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature::Creature ( const Creature& obj )
{ 
    this->subregion = obj.subregion;
    this->transforms = obj.transforms;
    this->fitness = obj.fitness;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Creature::~Creature ( void )
{ 
    transforms.clear();
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature& Creature::operator=( const Creature& obj ) 
{
    if (this != &obj) // prevent self-assignment
    {
        this->subregion = obj.subregion;
        this->transforms = obj.transforms;
        this->fitness = obj.fitness;
    }
    return *this;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::set_fitness ( double _fitness )
{
    fitness = _fitness;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Creature::get_fitness ( void )
{
    return fitness;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::initialize ( void )
{
    ;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::set_subregion ( Subregions::Subregion& _subregion )
{
    subregion = _subregion;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Subregions::Subregion& Creature::get_subregion ( void )
{
    return subregion;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::set_transforms ( TRANSORMS _transorms )
{
    transforms = _transorms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
TRANSORMS & Creature::get_transforms ( void )
{
    return transforms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::perform_transforms ( Mat _image )
{    
    Mat image;
    cvtColor(_image, image, CV_BGR2GRAY);
        
    subregion.set_original(image);
    image = subregion.get_subregion();
        
    for ( vector<int>::size_type i = 0; i < transforms.size();  i++ )
    {
        cout << "performing " << transforms[i].get_transform_type() << endl;
        
        transforms[i].perform_transform(image);
        image = transforms[i].get_transform();    
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::train_perceptron ( void )
{
    perceptron.train(1);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
string Creature::to_string ( void )
{
    stringstream ss;
    
    valarray<int> subregion_values = subregion.get_subregion_values();
    
    int i;
    ss << "[";
    for ( i = 0; i < subregion_values.size()-1; i++ )
        ss << subregion_values[i] << ",";
    ss << subregion_values[i] << "] ";
    
    
    for ( vector<int>::size_type i = 0; i < transforms.size(); i++ )
    {
        valarray<double> tmp = transforms[i].get_paramaters();
        
        ss << "[" << transforms[i].get_transform_type() << " (";
        
        for ( vector<int>::size_type j = 0; j < tmp.size(); j++ )
        {
            ss << tmp[j] << ",";
        }        
        ss << ")] ";
    }
    
    return ss.str();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/