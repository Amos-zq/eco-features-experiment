/******************************************************************************
 * Filename      : GA.cpp
 * Header File(s): GA.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "GA.hpp"
#include "Creature.hpp"
#include "Subregion.hpp"
#include "Transform.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <random>
#include <iostream>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Subregions;
using namespace Transforms;
using namespace cv;
using namespace boost::filesystem;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::GA ( void ) { ; }
/*******************************************************************************
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::GA ( int population_size, int number_generations, 
         double fitness_penalty, int fitness_threshold )
{ 
    pop_size = population_size;
    num_gen  = number_generations;
    fit_pen  = fitness_penalty;
    fit_thresh  = fitness_threshold;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
GA::GA ( GA& obj ) { ; }
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::~GA ( void ) { ; }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
GA& GA::operator=( const GA& obj ) 
{
    if (this != &obj) // prevent self-assignment
    {
        ;
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
void GA::mutate ( Creature a )
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
Creature GA::crossover ( Creature a, Creature b )
{
    cout << "performing crossover" << endl;
    Creature child;
    
    cout << "Parent A: " << a.to_string() << endl;
    cout << "Parent B: " << b.to_string() << endl;
    
    TRANSORMS child_transforms;
    TRANSORMS a_transforms = a.get_transforms();
    TRANSORMS b_transforms = b.get_transforms();
    
    //hchild_transforms.reverse(1+b_transforms.size()-1);
    child_transforms.insert( child_transforms.end(), 
                             a_transforms.begin(), 
                             a_transforms.begin()+1 );
    child_transforms.insert( child_transforms.end(), 
                             b_transforms.begin()+1, 
                             b_transforms.end() );
    
    return child;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::load_images ( string pth_train, string pth_hold )
{
    cout << "loading images" << endl;
    
    Mat image;     
    directory_iterator end ;

    for( directory_iterator iter(pth_train) ; iter != end ; ++iter )
    {
         if ( !is_directory( *iter ) )
         {
            image = imread(iter->path().c_str(), CV_LOAD_IMAGE_COLOR);
            training_images.push_back(image);
         }
    }
    for( directory_iterator iter(pth_hold) ; iter != end ; ++iter )
    {
         if ( !is_directory( *iter ) )
         {
            image = imread(iter->path().c_str(), CV_LOAD_IMAGE_COLOR);
            holding_images.push_back(image);
         }
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::initialize ( void )
{
    
    cout << "initalizing" << endl;
    
    random_device rd;
    mt19937 rnd(rd());
    uniform_int_distribution<int> trans_dist(1,TRANSORM_NUM-1);
    uniform_int_distribution<int> trans1_dist(MINIMUM_TRANFORMS,MAXIMUM_TRANFORMS);
    uniform_int_distribution<int> param_dist(0,360);
    
    for ( int i = 0; i < pop_size; i++ )
    {
        Creature current_creature;       
        TRANSORMS transforms;
        int transform_count = trans1_dist(rnd);
        for ( int j = 0; j < transform_count; j++ )
        {
            Transform transform((TRANFORM_TYPE)trans_dist(rnd));  
            
            valarray<double> parameters(ParamterSize(transform.get_transform_type()));

            for ( int k = 0; k < parameters.size(); k++ )
            {
                parameters[k] = param_dist(rnd);
            }
            transform.set_parameters(parameters);
            
            transforms.push_back(transform);
        }
        uniform_int_distribution<int> x1_dist(0,MAXIMUM_WIDTH);
        int x1 = x1_dist(rnd);
        uniform_int_distribution<int> x2_dist(x1,MAXIMUM_WIDTH);
        int x2 = x2_dist(rnd);
        uniform_int_distribution<int> y1_dist(0,MAXIMUM_HEIGHT);        
        int y1 = y1_dist(rnd);
        uniform_int_distribution<int> y2_dist(y1,MAXIMUM_HEIGHT);        
        int y2 = y2_dist(rnd);
        Subregion subregion(x1,x2,y1,y2);
        current_creature.set_subregion(subregion);
        current_creature.set_transforms(transforms);
        current_creature.initialize();
        population.push_back(current_creature);
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::run ( void )
{
    random_device rd;
    mt19937 rnd(rd());
    
    cout << "running" << endl;
    for ( int generation = 0; generation < num_gen; generation++ )
    {
        for ( vector<int>::size_type creature_i = 0; 
              creature_i < population.size(); 
              creature_i++ )
        {
            cout << "initializing creature " << creature_i;
            population[creature_i].initialize();
            cout << " . training ";
            cout << population[creature_i].to_string() << endl;
            cout << "     creature " << creature_i << " at " ;
            for ( vector<int>::size_type training_images_i = 0; 
                 training_images_i < training_images.size(); 
                 training_images_i++ )
            {
                cout << training_images_i << ",";
                cout.flush();
                population[creature_i].perform_transforms(training_images[training_images_i]);
                population[creature_i].train_perceptron();
            }
            cout << endl;

//            for ( vector<int>::size_type holding_images_i = 0; 
//                 holding_images_i < holding_images.size(); 
//                 holding_images_i++ )
//            {
//                population[creature_i].perform_transforms(holding_images[holding_images]);
//                population[creature_i].output_perceptron(true);
//            }            
            population[creature_i].compute_fitness(fit_pen);
            
            cout << "     fitness = " << population[creature_i].get_fitness();
//            if ( population[creature_i].get_fitness() < fit_thresh )
//            {
//                cout << " deleted";
//                population.erase(population.begin()+creature_i);
//            }
            cout << endl;
        }
        
        for ( vector<int>::size_type creature_i = 0; 
              creature_i < pop_size - population.size(); 
              creature_i++ )
        {
            uniform_int_distribution<int> pop_dist(0,population.size());
            Creature a ( crossover(population[pop_dist(rnd)],population[pop_dist(rnd)]) );
            
            cout << "created: " << a.to_string() << endl;
            population.push_back(a);
            
            getchar();
        }
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
