/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmPropertyMap_h
#define cmPropertyMap_h

#include "cmProperty.h"

class cmPropertyMap : public std::map<std::string,cmProperty>
{
public:
  cmProperty *GetOrCreateProperty(const std::string& name);

  void SetProperty(const std::string& name, const char *value);

  void AppendProperty(const std::string& name, const char* value,
                      bool asString=false);

  const char *GetPropertyValue(const std::string& name) const;
};

#endif

