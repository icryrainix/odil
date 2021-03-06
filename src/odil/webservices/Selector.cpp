/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <cassert>
#include "odil/webservices/Selector.h"

namespace odil
{

namespace webservices
{

Selector
::Selector(std::map<std::string, std::string> const & selector, std::vector<int> const & frames):
    _study_present(false), _series_present(false), _instance_present(false),_frames(frames)
{
    for (auto const pair_: selector)
    {
        if (pair_.first == "studies")
        {
            _study_present = true;
            _study = pair_.second;
        }
        else if (pair_.first == "series")
        {
            _series_present = true;
            _series = pair_.second;
        }
        else if (pair_.first == "instances")
        {
            _instance_present = true;
            _instance = pair_.second;
        }
        else
        {
            throw Exception("Unknown option " + pair_.first);
        }
    }
}

bool
Selector
::operator==(Selector const & other) const
{
    return (
        this->_study == other._study
        && this->_study_present == other._study_present
        && this->_series == other._series
        && this->_series_present == other._series_present
        && this->_instance == other._instance
        && this->_instance_present == other._instance_present
        && this->_frames == other._frames
    );
}

bool
Selector
::operator!=(Selector const & other) const
{
    return !(*this == other);
}

bool
Selector
::is_study_present() const
{
    return _study_present;
}

bool
Selector
::is_series_present() const
{
    return _series_present;
}

bool
Selector
::is_instance_present() const
{
    return _instance_present;
}

std::string const &
Selector
::get_study() const
{
    return _study;
}

std::string const &
Selector
::get_series() const
{
    return _series;
}

std::string const &
Selector
::get_instance() const
{
    return _instance;
}

std::vector<int> const &
Selector
::get_frames() const
{
    return this->_frames;
}

Selector &
Selector
::set_study(std::string const & study)
{
    this->_study = study;
    this->_study_present = true;

    return *this;
}

Selector &
Selector
::set_series(std::string const & series)
{
    this->_series = series;
    this->_series_present = true;
    return *this;
}

Selector &
Selector
::set_instance(std::string const & instance)
{
    this->_instance = instance;
    this->_instance_present = true;
    return *this;
}

Selector &
Selector
::set_frames(std::vector<int> const &frames)
{
    this->_frames = frames;
    return *this;
}

std::string
Selector
::get_path(bool include_frames) const
{
    std::string path;
    if(this->_study_present)
    {
        path = "/studies";
        if (!this->_study.empty())
        {
            path += "/" + this->_study;
        }
    }
    if(this->_series_present)
    {
        path += "/series";
        if (!this->_series.empty())
        {
            path += "/" + this->_series;
        }
    }
    if(this->_instance_present)
    {
        path += "/instances";
        if (!this->_instance.empty())
        {
            path += "/" + this->_instance;
        }
    }
    if(include_frames && !this->_frames.empty())
    {
        path += "/frames/";
        auto const last = --this->_frames.end();
        auto it = this->_frames.begin();
        while(it != last)
        {
            path += std::to_string(*it) + ",";
            ++it;
        }
        path += std::to_string(*last);
    }
    return path;
}

}

}
