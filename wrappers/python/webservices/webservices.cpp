/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_webservices_BulkData();
void wrap_webservices_HTTPResponse();
void wrap_webservices_HTTPRequest();
void wrap_webservices_Message();
void wrap_webservices_QIDORSResponse();
void wrap_webservices_QIDORSRequest();
void wrap_webservices_Selector();
void wrap_webservices_STOWRSResponse();
void wrap_webservices_STOWRSRequest();
void wrap_webservices_URL();
void wrap_webservices_Utils();
void wrap_webservices_WADORSResponse();
void wrap_webservices_WADORSRequest();


namespace
{
    class webservices_namespace {};
}

void wrap_webservices()
{
    using namespace boost::python;

    scope webservices = class_<webservices_namespace>("webservices");

    wrap_webservices_Message();
    wrap_webservices_URL();

    wrap_webservices_BulkData();

    wrap_webservices_HTTPResponse();
    wrap_webservices_HTTPRequest();

    wrap_webservices_Selector();
    wrap_webservices_Utils();

    wrap_webservices_WADORSResponse();
    wrap_webservices_WADORSRequest();

    wrap_webservices_QIDORSResponse();
    wrap_webservices_QIDORSRequest();

    wrap_webservices_STOWRSResponse();
    wrap_webservices_STOWRSRequest();
}
