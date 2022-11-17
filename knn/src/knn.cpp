//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.

#include "../include/knn.h"
#include <cmath>
#include <limits>
#include <map>
#include <iostream>
#include "../../include/data_handler.h"
#include "../../include/data.h"
#include "../../include/coheir.h"

knn::knn(int val)
{
    k = val;
}
knn::knn()
{
    // Nothing
}
knn::~knn()
{
    // Nothing
}
// O(N) 
// k = 2
// NlogN

void knn::find_knearest(data *query_point)
{
    
    neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;

    int index{0};

    for(int i = 0; i < k; i++)
    {
        if(i == 0)
        {
            for(int j = 0; j < training_data->size(); j++)
            {
                double distance = calculate_distance(query_point, training_data->at(j));

                training_data->at(j)->set_distance(distance);

                if(distance < min)
                {
                    min = distance;
                    index = j;
                }
            }

        
        neighbors->push_back(training_data->at(index));
        previous_min = min;
        min = std::numeric_limits<double>::max();

    } else
    {
        for(int j = 0; j < training_data->size(); j++)
        {
            // double distance = calculate_distance(query_point, training_data->at(j));
            double distance = training_data->at(j)->get_distance();
            training_data->at(j)->set_distance(distance);

            if(distance > previous_min && distance < min)
            {
                min = distance;
                index = j;
            }
        }

        neighbors->push_back(training_data->at(index));
        previous_min = min;
        min = std::numeric_limits<double>::max();
        }
    }
}

void knn::set_k(int val)
{
    k = val;
}

int knn::predict()
{
    std::map<uint8_t, int> class_freq;
    for(int i = 0; i < neighbors->size(); i++)
    {
        if(class_freq.find(neighbors->at(i)->get_label()) == class_freq.end())
        {
            class_freq[neighbors->at(i)->get_label()] = 1;
        } else
        {
            class_freq[neighbors->at(i)->get_label()]++;
        }
    }

    int best{0};
    int max{0};

    for(auto kv : class_freq)
    {
        if(kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }

    delete neighbors;
    return best;
}


double knn::calculate_distance(data *query_point, data *input)
{
    
    double distance{0.0};
    
    if(query_point->get_feature_vector_size() != input->get_feature_vector_size())
    {
        std::cout << "Error Vector Size Mismatch!" << std::endl;
        exit(1);
    }
    
    for(unsigned i = 0; i < query_point->get_feature_vector_size(); i++)
    {   
        distance +=pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
        // std::cout << query_point->get_label() << std::endl;
    }
    distance = sqrt(distance);
    
    return distance;
}

double knn::validate_performance()
{
    double current_performance = 0.0;
    int count = 0;
    int data_index = 0;

    for(data *query_point : *validation_data)
    {   
        
        find_knearest(query_point);
        int prediction = predict();
        std::cout << prediction << "->" << query_point->get_label() << std::endl;
        if(prediction == query_point->get_label())
        {
            count++;
        }
        data_index++;
        std::cout << "Current Performance = " <<((double)count*100.0)/((double)data_index) << "%" << std::endl;
    }
    current_performance = ((double)count*100.0)/((double)validation_data->size());
    std::cout << "Validation Performance for K = " << k << ":" << current_performance << "%" << std::endl;

    return current_performance;
}
double knn::test_performance()
{
    double current_performance{0.0};
    int count{0};
    int data_index{0};

    for(data *query_point : *test_data)
    {
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label())
        {
            count++;
        }
    }
    current_performance = ((double)count*100.0/(double)test_data->size());
    std::cout << "Current Performance = " << current_performance << std::endl;
    return current_performance;
}


