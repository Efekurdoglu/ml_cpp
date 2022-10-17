#ifndef __COHEIR_H
#define __COHEIR_H

#include "data.h"
#include <vector>

class coheir
{

    protected:
        std::vector<data *> * training_data;
        std::vector<data *> * test_data;
        std::vector<data *> * validation_data;

    public:
        void set_training_data(std::vector<data *> *vect);
        void set_test_data(std::vector<data *> *vect);
        void set_validation_data(std::vector<data *> *vect);
};

#endif