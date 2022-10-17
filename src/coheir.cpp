#include "../include/coheir.h"

void coheir::set_training_data(std::vector<data *> *vect)
{
    training_data = vect;
}
void coheir::set_test_data(std::vector<data *> *vect)
{
    test_data = vect;
}
void coheir::set_validation_data(std::vector<data *> *vect)
{
    validation_data = vect;
}