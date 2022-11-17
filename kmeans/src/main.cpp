//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.s

#include "../include/kmeans.h"

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../dataset/train-images-idx3-ubyte");
    dh->read_feature_labels("../dataset/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();

    double performance{0.0};
    double best_performance{0.0};
    int best_k{1};

    for(int k = dh->get_class_counts(); k < dh->get_training_data()->size()*0.1; k++)
    {
        kmeans *km = new kmeans(k);
        km->set_training_data(dh->get_training_data());
        km->set_test_data(dh->get_test_data());
        km->set_validation_data(dh->get_validation_data());
        km->init_clusters();
        km->train();
        performance = km->validate();

        std::cout << "Current k = " << k << " Performance: " << performance << std::endl;

        if (performance > best_performance)
        {
            best_performance = performance;
            best_k = k;
        }
    }
    kmeans *km = new kmeans(best_k);
    km->set_training_data(dh->get_training_data());
    km->set_test_data(dh->get_test_data());
    km->set_validation_data(dh->get_validation_data());
    km->init_clusters();
    performance = km->test();
    std::cout << "Best k = " << best_k << " tested performance: " << performance << std::endl;
}