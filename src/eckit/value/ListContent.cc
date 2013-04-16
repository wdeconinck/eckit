/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "eckit/value/ListContent.h"
#include "eckit/parser/JSON.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

ClassSpec ListContent::classSpec_ = {&Content::classSpec(),"ListContent",};
Reanimator<ListContent>  ListContent::reanimator_;


ListContent::ListContent()
{
}

ListContent::ListContent(const vector<Value>& v)
{
    ::copy(v.begin(),v.end(),back_inserter(value_));
}

ListContent::ListContent(const Value& v)
{
    value_.push_back(v);
}

ListContent::ListContent(Stream& s):
	Content(s)
{
	long count;
	s >> count;
	for(int i = 0; i< count; i++)
        value_.push_back(Value(s));

}

void ListContent::encode(Stream& s) const
{
	Content::encode(s);
    long count = value_.size();
	s << count;
	for(int i = 0; i < count; ++i)
        s << value_[i];

}

ListContent::~ListContent()
{
}

void ListContent::value(vector<Value>& v) const
{
    v = value_;
}

int ListContent::compare(const Content& other)const
{
	return -other.compareList(*this);
}

int ListContent::compareList(const ListContent& other) const
{
    if(value_ == other.value_)
        return 0;
    if(value_ < other.value_)
        return -1;
    return 1;

}

void ListContent::json(JSON& s) const
{
    s.startList();

    for(size_t i = 0; i < value_.size(); i++)
	{
        s << value_[i];
	}

    s.endList();
}


void ListContent::print(ostream& s) const
{
    s << '(';

    for(size_t i = 0; i < value_.size(); i++)
    {
        if(i>0) s << ',';
        s << value_[i];
    }

    s << ')';
}


Content* ListContent::add(const Content& other) const
{
	return other.addList(*this);
}

Content* ListContent::addList(const ListContent& other) const
{
	vector<Value> tmp;
    ::copy(other.value_.begin(),other.value_.end(),back_inserter(tmp));
    ::copy(value_.begin(),value_.end(),back_inserter(tmp));
	return new ListContent(tmp);
}

Content* ListContent::sub(const Content& other) const
{
    return other.subList(*this);
}

Content* ListContent::mul(const Content& other) const
{
    return other.mulList(*this);
}

Content* ListContent::div(const Content& other) const
{
    return other.divList(*this);
}

Content* ListContent::mod(const Content& other) const
{
    return other.modList(*this);
}


void ListContent::value(long long& n) const 
{
    if(value_.size() == 1) n = value_[0];
	else Content::value(n);
}

void ListContent::value(bool& n) const
{
    if(value_.size() == 1) n = value_[0];
    else Content::value(n);
}

void ListContent::value(double& n) const
{
    if(value_.size() == 1) n = value_[0];
    else Content::value(n);
}

void ListContent::value(string& n) const 
{
    if(value_.size() == 1) n = string(value_[0]);
	else Content::value(n); 
}

void ListContent::value(Date& n) const 
{ 
    if(value_.size() == 1) n = value_[0];
	else Content::value(n); 
}

void ListContent::value(Time& n) const 
{ 
    if(value_.size() == 1) n = value_[0];
	else Content::value(n); 
}

void ListContent::value(DateTime& n) const 
{ 
    if(value_.size() == 1) n = value_[0];
	else Content::value(n); 
}

Value& ListContent::element(const Value& v)
{
    long long n = v;
    ASSERT( n >= 0 && (size_t) n < value_.size() );
    return value_.at(n);
}

//-----------------------------------------------------------------------------

} // namespace eckit
