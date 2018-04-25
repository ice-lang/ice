#include "IceObject.h"

namespace Ice
{
	IceFunctionObject::IceFunctionObject(const VariableList &arguments, std::shared_ptr<BlockExpr> block) : arguments(arguments), block(block)
	{
		type = TYPE::FUNCTION;
	}

	IceIntegerObject::IceIntegerObject(long value) : value(value)
	{
		type = TYPE::INT;
	}

	void IceIntegerObject::show()
	{
		std::cout << value << std::endl;
	}

	std::shared_ptr<IceObject> IceIntegerObject::binaryOperate(std::shared_ptr<IceObject> obj, Token::TOKEN op)
	{
		switch (obj->type)
		{
		case TYPE::INT:
			switch (op)
			{
			case Token::TOKEN::TADD:
				return std::make_shared<IceIntegerObject>(value + std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TSUB:
				return std::make_shared<IceIntegerObject>(value - std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TMUL:
				return std::make_shared<IceIntegerObject>(value * std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TDIV:
				return std::make_shared<IceIntegerObject>(value / std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TMOD:
				return std::make_shared<IceIntegerObject>(value % std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCEQ:
				return std::make_shared<IceIntegerObject>(value == std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCNE:
				return std::make_shared<IceIntegerObject>(value != std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCLT:
				return std::make_shared<IceIntegerObject>(value < std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCLE:
				return std::make_shared<IceIntegerObject>(value <= std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCGT:
				return std::make_shared<IceIntegerObject>(value > std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case Token::TOKEN::TCGE:
				return std::make_shared<IceIntegerObject>(value >= std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::DOUBLE:
			switch (op)
			{
			case Token::TOKEN::TADD:
				return std::make_shared<IceDoubleObject>(value + std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TSUB:
				return std::make_shared<IceDoubleObject>(value - std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TMUL:
				return std::make_shared<IceDoubleObject>(value * std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TDIV:
				return std::make_shared<IceDoubleObject>(value / std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TMOD:
				return std::make_shared<IceDoubleObject>(value % (long)std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCEQ:
				return std::make_shared<IceDoubleObject>(value == std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCNE:
				return std::make_shared<IceDoubleObject>(value != std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCLT:
				return std::make_shared<IceDoubleObject>(value < std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCLE:
				return std::make_shared<IceDoubleObject>(value <= std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCGT:
				return std::make_shared<IceDoubleObject>(value > std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case Token::TOKEN::TCGE:
				return std::make_shared<IceDoubleObject>(value >= std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			default:
				break;
			}
		default:
			break;
		}
		std::cout << "doesn't support this operator" << std::endl;
		exit(0);
		return nullptr;
	}

	bool IceIntegerObject::isTrue()
	{
		return value != 0;
	}

	IceDoubleObject::IceDoubleObject(double value)
	{
		type = TYPE::DOUBLE;
	}

	void IceDoubleObject::show()
	{
		std::cout << value << std::endl;
	}

	std::shared_ptr<IceObject> IceDoubleObject::binaryOperate(std::shared_ptr<IceObject> obj, Token::TOKEN op)
	{
		return nullptr;
	}

	bool IceDoubleObject::isTrue()
	{
		return value != 0.0;
	}

	IceStringObject::IceStringObject(std::string value) : value(value) 
	{
		type = TYPE::STRING;
	}

	void IceStringObject::show()
	{
		std::cout << value << std::endl;
	}

	std::shared_ptr<IceObject> IceStringObject::binaryOperate(std::shared_ptr<IceObject> obj, Token::TOKEN op)
	{
		return nullptr;
	}

	bool IceStringObject::isTrue()
	{
		return value != "";
	}
}

