//
// StreamCopier.cpp
//
// $Id: //poco/1.4/Foundation/src/StreamCopier.cpp#2 $
//
// Library: Foundation
// Package: Streams
// Module:  StreamCopier
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/StreamCopier.h"
#include "Poco/Buffer.h"


namespace Poco {


std::streamsize StreamCopier::copyStream(std::istream& istr, std::ostream& ostr, std::size_t bufferSize)
{
	poco_assert (bufferSize > 0);

	Buffer<char> buffer(bufferSize);
	std::streamsize len = 0;
	istr.read(buffer.begin(), bufferSize);
	std::streamsize n = istr.gcount();
	while (n > 0)
	{
		len += n;
		ostr.write(buffer.begin(), n);
		if (istr && ostr)
		{
			istr.read(buffer.begin(), bufferSize);
			n = istr.gcount();
		}
		else n = 0;
	}
	return len;
}


#if defined(POCO_HAVE_INT64)
Poco::UInt64 StreamCopier::copyStream64(std::istream& istr, std::ostream& ostr, std::size_t bufferSize)
{
	poco_assert (bufferSize > 0);

	Buffer<char> buffer(bufferSize);
	Poco::UInt64 len = 0;
	istr.read(buffer.begin(), bufferSize);
	std::streamsize n = istr.gcount();
	while (n > 0)
	{
		len += n;
		ostr.write(buffer.begin(), n);
		if (istr && ostr)
		{
			istr.read(buffer.begin(), bufferSize);
			n = istr.gcount();
		}
		else n = 0;
	}
	return len;
}
#endif


std::streamsize StreamCopier::copyToString(std::istream& istr, std::string& str, std::size_t bufferSize)
{
	poco_assert (bufferSize > 0);

	Buffer<char> buffer(bufferSize);
	std::streamsize len = 0;
	istr.read(buffer.begin(), bufferSize);
	std::streamsize n = istr.gcount();
	while (n > 0)
	{
		len += n;
		str.append(buffer.begin(), static_cast<std::string::size_type>(n));
		if (istr)
		{
			istr.read(buffer.begin(), bufferSize);
			n = istr.gcount();
		}
		else n = 0;
	}
	return len;
}


#if defined(POCO_HAVE_INT64)
Poco::UInt64 StreamCopier::copyToString64(std::istream& istr, std::string& str, std::size_t bufferSize)
{
	poco_assert (bufferSize > 0);

	Buffer<char> buffer(bufferSize);
	Poco::UInt64 len = 0;
	istr.read(buffer.begin(), bufferSize);
	std::streamsize n = istr.gcount();
	while (n > 0)
	{
		len += n;
		str.append(buffer.begin(), static_cast<std::string::size_type>(n));
		if (istr)
		{
			istr.read(buffer.begin(), bufferSize);
			n = istr.gcount();
		}
		else n = 0;
	}
	return len;
}
#endif


std::streamsize StreamCopier::copyStreamUnbuffered(std::istream& istr, std::ostream& ostr)
{
    char c;
    std::streamsize len = 0;
    istr.get(c);
    while (istr && ostr)
    {
        ++len;
        ostr.put(c);
        istr.get(c);
    }
    return len;
}


#if defined(POCO_HAVE_INT64)
Poco::UInt64 StreamCopier::copyStreamUnbuffered64(std::istream& istr, std::ostream& ostr)
{
    char c;
    Poco::UInt64 len = 0;
    istr.get(c);
    while (istr && ostr)
    {
        ++len;
        ostr.put(c);
        istr.get(c);
    }
    return len;
}
#endif


} // namespace Poco
