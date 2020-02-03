#include "OsuKey.hpp"


OsuKey::OsuKey()
	: _type(OsuKey::Tag::EMPTY), _val(nullptr)
	{}

OsuKey::OsuKey(size_t val)
	: _type(OsuKey::Tag::INDEX), _val(new size_t(val))
	{}

OsuKey::OsuKey(std::string val)
	: _type(OsuKey::Tag::STRING), _val(new std::string(std::move(val)))
	{}

OsuKey::~OsuKey()
{
	if (this->_type == OsuKey::Tag::INDEX)
		delete (size_t*)this->_val;
	else if (this->_type == OsuKey::Tag::STRING)
		delete (std::string*)this->_val;
}


OsuKey::OsuKey(const OsuKey &other)
	: _type(other._type), _val(nullptr)
{
	if (this->_type == OsuKey::Tag::INDEX)
		this->_val = new size_t(*(size_t*)other._val);
	else if (this->_type == OsuKey::Tag::STRING)
		this->_val = new std::string(*(std::string*)other._val);
}

OsuKey::OsuKey(OsuKey &&other)
	: OsuKey()
{
	swap(*this, other);
}

OsuKey	&OsuKey::operator=(OsuKey other)
{
	swap(*this, other);

	return *this;
}


bool		OsuKey::operator==(const OsuKey &other) const
{
	if (this->_type != other._type)
		return false;

	switch (this->_type)
	{
		default:
		case OsuKey::Tag::EMPTY:
			return true;
		case OsuKey::Tag::INDEX:
			return *(size_t*)this->_val == *(size_t*)other._val;
		case OsuKey::Tag::STRING:
			return *(std::string*)this->_val == *(std::string*)other._val;
	}
}

bool		OsuKey::operator!=(const OsuKey &other) const
{
	return !this->operator==(other);
}


bool		OsuKey::operator<(const OsuKey &other) const
{
	std::string	lhs;
	std::string	rhs;

	if (this->_type == OsuKey::Tag::INDEX && other._type == OsuKey::Tag::INDEX)
		return *(size_t*)this->_val < *(size_t*)other._val;

	switch (this->_type)
	{
		case OsuKey::Tag::EMPTY:
			break;
		case OsuKey::Tag::INDEX:
			lhs = std::to_string(this->getIndex()); break;
		case OsuKey::Tag::STRING:
			lhs = this->getStr(); break;
	}
	switch (other._type)
	{
		case OsuKey::Tag::EMPTY:
			break;
		case OsuKey::Tag::INDEX:
			rhs = std::to_string(other.getIndex()); break;
		case OsuKey::Tag::STRING:
			rhs = other.getStr(); break;
	}
	return lhs < rhs;
}

bool		OsuKey::operator<=(const OsuKey &other) const
{
	return this->operator<(other) || this->operator==(other);
}

bool		OsuKey::operator>(const OsuKey &other) const
{
	return !this->operator<=(other);
}

bool		OsuKey::operator>=(const OsuKey &other) const
{
	return !this->operator<(other);
}


OsuKey::Tag	OsuKey::getType() const
{
	return this->_type;
}

size_t		&OsuKey::getIndex()
{
	return *(size_t*)this->_val;
}

size_t		OsuKey::getIndex() const
{
	return *(size_t*)this->_val;
}

std::string	&OsuKey::getStr()
{
	return *(std::string*)this->_val;
}

const std::string	&OsuKey::getStr() const
{
	return *(std::string*)this->_val;
}


void	swap(OsuKey &lhs, OsuKey &rhs) noexcept
{
	std::swap(lhs._val, rhs._val);
	std::swap(lhs._type, rhs._type);
}

std::ostream	&operator<<(std::ostream &os, const OsuKey &rhs)
{
	switch (rhs.getType())
	{
		case OsuKey::Tag::EMPTY:
			os << std::string("no key"); break;
		case OsuKey::Tag::INDEX:
			os << std::to_string(rhs.getIndex()); break;
		case OsuKey::Tag::STRING:
			os << rhs.getStr(); break;
	}
	return os;
}
