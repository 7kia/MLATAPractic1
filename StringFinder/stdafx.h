#ifndef STDAFX_H
#define STDAFX_H

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <string>

#if defined(_MSC_VER)
#pragma warning (disable: 4512)
#endif // _MSC_VER

#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_INCLUDED

#if defined(_MSC_VER)
#pragma warning (disable: 4702)
#pragma warning (disable: 4535)
#endif // _MSC_VER
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>

#endif // STDAFX_H
