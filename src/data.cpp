//  Created by Efe Kurdoglu, efekurdoglu@outlook.com on 6/11/2022.
//  Copyright © 2022 Efe Kurdoglu. All rights reserved.

#include "data.h"

data::data()
{
    feature_vector = new std::vector<uint8_t>;
}
data::~data()
{
    // Nothing written here
}

void data::set_feature_vector(std::vector<uint8_t> *vect)
{
    feature_vector = vect;
}
void data::append_to_feature_vector(uint8_t val)
{
    feature_vector->push_back(val);
}
void data::set_label(uint8_t val)
{
    label = val;
}
void data::set_enumerated_label(int val)
{
    enum_label = val;
}
void data::set_distance(double val)
{
    distance = val;
}

int data::get_feature_vector_size()
{
    return feature_vector->size();
}
uint16_t data::get_label()
{
    return label;
}
uint8_t data::get_enumerated_label()
{
    return enum_label;
}

std::vector<uint8_t> *data::get_feature_vector()
{
    return feature_vector;
}
double data::get_distance()
{
    return distance;
}