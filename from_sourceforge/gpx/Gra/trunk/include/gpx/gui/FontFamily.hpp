/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_FONTFAMILY_HPP_
#define GPX_Gra_FONTFAMILY_HPP_

#include <SFML/Graphics/Font.hpp>

#include <gpx/platform.hpp>

namespace gpx {
namespace gui {

class GPX_API FontFamily : public sf::Font
{
	typedef sf::Font Parent;

	public:
		typedef unsigned int res_t;

		struct FontData
		{
			explicit FontData(const char * data);

			const char * data;
		};

	public:
		FontFamily();

		FontFamily(const std::string & path, res_t res = 30, const sf::Unicode::Text & charset = DefaultCharset());

		FontFamily(const FontData & fontData, std::size_t bsize, res_t res = 30, const sf::Unicode::Text & charset = DefaultCharset());

		virtual ~FontFamily();

	public:
		static const sf::Unicode::Text & DefaultCharset();

	public:
		const sf::Unicode::Text & charset() const;

		res_t res() const;

	private:
		static const sf::Uint32 INITIAL_CHARSET[];
		static const char DEFAULT_FONT_DATA[];

	private:
		const sf::Unicode::Text & m_charset;
		res_t m_res;
};

}
}

#endif /* GPX_Gra_FONTFAMILY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
