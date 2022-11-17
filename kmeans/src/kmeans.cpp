//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.

#include "../include/kmeans.h"

kmeans::kmeans(int k)
{
    num_clusters = k;
    clusters = new std::vector<cluster_t *>;
    used_indexes = new std::unordered_set<int>;
}
void kmeans::init_clusters()
{
    for(int i = 0; i < num_clusters; i++)
    {
        int index = (rand() % training_data->size());
        while(used_indexes->find(index) != used_indexes->end())
        {
            index = (rand() % training_data->size());
        }
        clusters->push_back(new cluster_t(training_data->at(index)));
        used_indexes->insert(index);
    }
}
void kmeans::init_clusters_for_each_class()
{
    std::unordered_set<int> classes_used;
    for(int i = 0; i < training_data->size(); i++)
    {
        if(classes_used.find(training_data->at(i)->get_label()) == classes_used.end())
        {
            clusters->push_back(new cluster_t(training_data->at(i)));
            classes_used.insert(training_data->at(i)->get_label());
            used_indexes->insert(i);
        }
    }
}
void kmeans::train()
{
    while(used_indexes->size() < training_data->size())
    {
        int index = (rand() % training_data->size());
        while(used_indexes->find(index) != used_indexes->end())
        {
            index = (rand() % training_data->size());
        }
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster{0};
        for(int j = 0; j < clusters->size(); j++)
        {
            double current_dist = euclidian_distance(clusters->at(j)->centroid, training_data->at(index));
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        clusters->at(best_cluster)->add_to_cluster(training_data->at(index));
        used_indexes->insert(index);
    }

}

double kmeans::euclidian_distance(std::vector<double> *centroid , data * point)
{
    double dist{0.0};

    for(int i = 0; i < centroid->size(); i++)
    {
        dist = dist +  pow(centroid->at(i) - point->get_feature_vector()->at(i), 2);
    }
    return sqrt(dist);
}

double kmeans::validate()
{
    double num_correct{0.0};
    for(auto query_point : *validation_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster{0};

        for(int j = 0; j < clusters->size(); j++)
        {
            double current_dist = euclidian_distance(clusters->at(j)->centroid, query_point);
            // std::cout << "Current distance: " << current_dist << std::endl;
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        if(clusters->at(best_cluster)->most_frequent_class == query_point->get_label()) num_correct++;
    }
    // std::cout << "Num correct: " << num_correct << std::endl;
    return 100.0 * (num_correct / (double) validation_data->size());
}

double kmeans::test()
{
    double num_correct{0.0};
    for(auto query_point : *test_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster{0};
        for(int j = 0; j < clusters->size(); j++)
        {
            double current_dist = euclidian_distance(clusters->at(j)->centroid, query_point);
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        if(clusters->at(best_cluster)->most_frequent_class == query_point->get_label()) num_correct++;
    }
    return 100.0 * (num_correct / (double) test_data->size());
}