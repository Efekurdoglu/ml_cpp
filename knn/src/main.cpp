//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.

#include "../include/knn.h"
#include <cmath>
#include <limits>
#include <map>
#include <iostream>
#include "../../include/data_handler.h"

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("./../dataset/train-images-idx3-ubyte");
    dh->read_feature_labels("./../dataset/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();

    knn *knearest = new knn();
    knearest->set_training_data(dh->get_training_data());
    knearest->set_test_data(dh->get_test_data());
    knearest->set_validation_data(dh->get_validation_data());

    double performance{0.0};
    double best_performance{0.0};
    int best_k{1};

    for(int i = 1; i <= 4; i++)
    {
        if(i == 1)
        {
            knearest->set_k(i);
            performance = knearest->validate_performance();
            best_performance = performance;
        } else
        {
            knearest->set_k(i);
            performance = knearest->validate_performance();
            if(performance > best_performance)
            {
                best_performance = performance;
                best_k = i;
            }
        }
    }

    knearest->set_k(best_k);
    knearest->test_performance();
}