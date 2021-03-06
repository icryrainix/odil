/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/Reader.h"
#include "odil/registry.h"

std::vector<odil::DataSet> readBuffer(std::string const & buffer)
{
    std::istringstream istream(buffer);
    auto const header_and_data_set = odil::Reader::read_file(istream);
    
    std::vector<odil::DataSet> result;
    result.push_back(header_and_data_set.first);
    result.push_back(header_and_data_set.second);
    return result;
}

emscripten::val getTag(std::string const & name)
{
    auto const iterator = odil::registry::public_tags.find(name);
    
    emscripten::val result = emscripten::val::undefined();
    if(iterator != odil::registry::public_tags.end())
    {
        result = emscripten::val(iterator->second);
    }
    else
    {
        result = emscripten::val::null();
    }
    
    return result;
}


void wrap_DataSet();
void wrap_Tag();
void wrap_VR();

void wrap_webservices_HTTPRequest();
void wrap_webservices_HTTPResponse();
void wrap_webservices_Message();
void wrap_webservices_QIDORSRequest();
void wrap_webservices_QIDORSResponse();
void wrap_webservices_Selector();
void wrap_webservices_URL();
void wrap_webservices_Utils();
void wrap_webservices_WADORSRequest();
void wrap_webservices_WADORSResponse();

EMSCRIPTEN_BINDINGS(odil)
{
    using namespace emscripten;
    using namespace odil;
    
    register_vector<int32_t>("Integers"); // FIXME: Javascript has no 64-bits int
    register_vector<Value::Real>("Reals");
    register_vector<Value::String>("Strings"); 
    register_vector<DataSet>("DataSets");
    register_vector<Value::Binary::value_type::value_type>("BinaryItem");
    register_vector<Value::Binary::value_type>("Binary");
    register_vector<Tag>("VectorTag");
    
    register_map<std::string, std::string>("MapStringString");
    
    wrap_DataSet();
    wrap_Tag();
    wrap_VR();
    
    EM_ASM(
        Module['webservices'] = {};
    );
    
    wrap_webservices_Message();
    wrap_webservices_HTTPRequest();
    wrap_webservices_HTTPResponse();
    wrap_webservices_QIDORSRequest();
    wrap_webservices_QIDORSResponse();
    wrap_webservices_Selector();
    wrap_webservices_URL();
    wrap_webservices_Utils();
    wrap_webservices_WADORSRequest();
    wrap_webservices_WADORSResponse();
    
    emscripten::function("readBuffer", readBuffer);
    emscripten::function("getTag", getTag);
}
