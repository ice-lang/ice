#include "Token.h"

namespace Ice
{
	Token::Token(std::string value) : value(value)
	{
		if (value == "if")
			token_id = TOKEN::TIF;
		else if (value == "else")
			token_id = TOKEN::TELSE;
		else if (value == "while")
			token_id = TOKEN::TWHILE;
		else if (value == "do")
			token_id = TOKEN::TDO;
		else if (value == "for")
			token_id = TOKEN::TFOR;
		else if (value == "to")
			token_id = TOKEN::TTO;
		else if (value == "return")
			token_id = TOKEN::TRETURN;
		else if (value == "and")
			token_id = TOKEN::TAND;
		else if (value == "or")
			token_id = TOKEN::TOR;
		else if (value == "not")
			token_id = TOKEN::TNOT;
		else
			token_id = TOKEN::TIDENTIFIER;
	}
}