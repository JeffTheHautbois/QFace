/*
 * CustomerModel.h
 *
 *  Created on: Nov 5, 2017
 *      Author: viraj
 */

#ifndef SRC_CPP_MODELS_CUSTOMERMODEL_H_
#define SRC_CPP_MODELS_CUSTOMERMODEL_H_

#include <string>

namespace CustomerModel {
  void initDb();
  void saveCustomer(std::string id);
}

#endif /* SRC_CPP_MODELS_CUSTOMERMODEL_H_ */
