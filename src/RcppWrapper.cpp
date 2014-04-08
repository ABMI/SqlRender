/**
 * @file RcppWrapper.cpp
 *
 * This file is part of SQLRender
 *
 * Copyright 2014 Observational Health Data Sciences and Informatics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author Observational Health Data Sciences and Informatics
 * @author Martijn Schuemie
 * @author Marc Suchard
 */

#ifndef __RcppWrapper_cpp__
#define __RcppWrapper_cpp__

#include <Rcpp.h>
#include "SqlRender.h"

// [[Rcpp::export]]
Rcpp::List renderSqlInternal(std::string sql, Rcpp::List parameters) {

  using namespace ohdsi::sqlRender;

	try {
		//Convert list to map:
		SqlRender::ParameterMap parameterToValue;
		Rcpp::List names = parameters.attr("names");
		for (int i = 0; i < parameters.size(); i++) {
			parameterToValue[names[i]] = Rcpp::as<std::string>(parameters[i]);
		}

		SqlRender::String renderedSql = SqlRender::renderSql(sql, parameterToValue);
		return Rcpp::List::create(Rcpp::Named("parameterizedSql") = sql, Rcpp::Named("sql") = renderedSql, Rcpp::Named("parameters") = parameterToValue);

	} catch (std::exception &e) {
		forward_exception_to_r(e);
	} catch (...) {
		::Rf_error("c++ exception (unknown reason)");
	}
  return Rcpp::List::create();
}

#endif // __SQLRender_cpp__