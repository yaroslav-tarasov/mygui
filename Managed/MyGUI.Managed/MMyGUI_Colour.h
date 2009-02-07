/*!
	@file
	@author		Albert Semenov
	@date		01/2009
	@module
*/
#pragma once

#include <MyGUI.h>
#include "MMyGUI_Macros.h"
#include "MMyGUI_Marshaling.h"

namespace MMyGUI
{

	public value struct Colour
	{

		MMYGUI_DECLARE_EQUALS(Colour)

		int red, green, blue, alpha;

		Colour( int _red, int _green, int _blue, int _alpha ) : red( _red ), green( _green ), blue( _blue ), alpha( _alpha ) { }

		static bool operator == ( Colour lvalue, Colour rvalue )
        {
            return ( lvalue.red == rvalue.red && lvalue.green == rvalue.green && lvalue.blue == rvalue.blue && lvalue.alpha == rvalue.alpha );
        }

	};

	template <> struct Convert<const MyGUI::Colour&>
	{
		typedef Colour Type;
		inline static const Colour& To(const MyGUI::Colour& _value) { return reinterpret_cast<const Colour&>(_value); }
		inline static MyGUI::Colour& From(Colour& _value) { return reinterpret_cast<MyGUI::Colour&>(_value); }
	};

} // namespace MMyGUI
