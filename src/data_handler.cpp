//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.

#include "data_handler.h"

data_handler::data_handler()
{
    data_array = new std::vector<data *>;
    test_data = new std::vector<data *>;
    training_data = new std::vector<data *>;
    validation_data = new std::vector<data *>;
}
data_handler::~data_handler()
{
    // Free Dynamically Allocated stuff
}

int data_handler::get_class_counts()
{
    return num_classes;
}

void data_handler::read_feature_vector(std::string path)
{
    uint32_t header[4]; // Magic // Num Images // Row Size // Col Size
    unsigned char bytes[4];

    FILE *f = fopen(path.c_str(), "r");
    if(f)                               // f = fopen(path.c_str(), "r");
    {
        for(int i = 0; i < 4; i++)
        {
            if(fread(bytes, sizeof(bytes), 1, f)) //
            {
                header[i] = convert_to_little_endian(bytes);
            }
        }

        std::cout << "Done getting input file header." << std::endl;
        
        int image_size = header[2]*header[3];

        for(int i = 0; i < header[1]; i++)
        {
            data *d = new data();
            uint8_t element[1];

            for(int j = 0; j < image_size; j++)
            {
                if(fread(element, sizeof(element), 1, f))
                {
                    d->append_to_feature_vector(element[0]);
                } else
                {
                    std::cout << "Error Reading from File." << j << std::endl;
                    exit(1);
                }
            }
            data_array->push_back(d);
        }
      std::cout << "Successfully read and stored " << data_array->size() << " feature vectors." << std::endl;  
    } else
    {
        std::cout << "Could not find the file." << std::endl;
        exit(1);
    }
}
void data_handler::read_feature_labels(std::string path)
{
    uint32_t header[2]; // Magic // Images 
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");

    if(f)
    {
        for(int i = 0; i < 2; i++)
        {
            if(fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convert_to_little_endian(bytes);
            }
        }
        std::cout << "Done getting label file header." << std::endl;
        
        for(int i = 0; i < header[1]; i++)
        {
            uint8_t element[1];

            if(fread(element, sizeof(element), 1, f))
            {
                data_array->at(i)->set_label(element[0]);
                    
            } else
            {
                std::cout << "Error Reading from File." << std::endl;
                exit(1);
            }
        }
      std::cout << "Successfully read and stored " << data_array->size() << " feature labels." << std::endl;  
    } else
    {
        std::cout << "Could not find the file." << std::endl;
        exit(1);
    }
}

void data_handler::split_data()
{
    std::unordered_set<int> used_indexes;
    int train_size = data_array->size() * TRAIN_SET_PERCENT;
    int test_size = data_array->size() * TEST_SET_PERCENT;
    int validation_size = data_array->size() * VALIDATION_SET_PERCENT;

    // Training Data

    int count = 0;
    while(count < train_size)
    {
        int rand_index = rand() % data_array->size(); // 0 & data_array->size() - 1
        if(used_indexes.find(rand_index) == used_indexes.end())
        {
            training_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    // Test Data

    count = 0;
    while(count < test_size)
    {
        int rand_index = rand() % data_array->size(); // 0 & data_array->size() - 1
        if(used_indexes.find(rand_index) == used_indexes.end())
        {
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    // Validation Data

    count = 0;
    while(count < validation_size)
    {
        int rand_index = rand() % data_array->size(); // 0 & data_array->size() - 1
        if(used_indexes.find(rand_index) == used_indexes.end())
        {
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

    printf("Training Data Size: %lu.\n", training_data->size());
    printf("Test Data Size: %lu.\n", test_data->size());
    printf("Validation Data Size: %lu.\n", validation_data->size());
}
void data_handler::count_classes()
{
    int count{0};
    for(unsigned i = 0; i < data_array->size(); i++)
    {
        if(class_map.find(data_array->at(i)->get_label()) == class_map.end())
        {
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }
    num_classes = count;
    std::cout << "Successfully Extracted " << num_classes << " Unique Classes." << std::endl;
}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes)
{
    return (uint32_t) ((bytes[0] << 24) |
                       (bytes[1] << 16) |
                       (bytes[2] << 8) |
                       (bytes[3]));
}

std::vector<data *> * data_handler::get_training_data()
{
    return training_data;
}
std::vector<data *> * data_handler::get_test_data()
{
    return test_data;
}
std::vector<data *> * data_handler::get_validation_data()
{
    return validation_data;
}
