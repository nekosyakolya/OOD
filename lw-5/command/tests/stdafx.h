// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include <boost/algorithm/string.hpp>
#include <boost/dll/import.hpp>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/optional/optional_io.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define BOOST_FILESYSTEM_VERSION 3

#define BOOST_TEST_INCLUDED
#pragma warning(disable : 4702)
#include <boost/test/unit_test.hpp>
